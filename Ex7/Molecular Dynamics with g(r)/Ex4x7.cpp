/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>     // srand, rand: to generate random number
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include <iomanip>
#include "MolDyn_NVEx7.h"

using namespace std;

int main(){
  Input();             //Inizialization
  int nconf = 1;
  for(int istep=1; istep <= nstep; ++istep){
     Move();           //Move particles with Verlet algorithm
     if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
     if(istep%10 == 0){
        Measure();     //Properties measurement
//        ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"!
        nconf += 1;
     }
     if(istep%(10*n_blockstep) == 0){
       DataBlocking(block);
       block++;
     }
  }
  OldFinal();
  ConfFinal();         //Write final configuration to restart
  ofstream WriteInput;
  WriteInput.open("bool.dat");
  WriteInput << 1 <<endl<<endl<<"    "<<  "ReadBool >> prv_sim"<<endl;
  WriteInput.close();

  return 0;
}


void Input(void){ //Prepare all stuff for the simulation
  ifstream ReadInput,ReadBool,ReadConf,ReadOld;
  ofstream WriteConf0,WriteOld0;
  double ep, ek, pr, et, vir;

  cout << "Classic Lennard-Jones fluid        " << endl;
  cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
  cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
  cout << "The program uses Lennard-Jones units " << endl;

  seed = 1;    //Set seed for random numbers
  srand(seed); //Initialize random number generator

  ReadBool.open("bool.dat");
  ReadBool >> prv_sim;
  ReadBool.close();


  ReadInput.open("input.dat"); //Read input

  ReadInput >> temp;

  ReadInput >> npart;
  cout << "Number of particles = " << npart << endl;

  ReadInput >> rho;
  cout << "Density of particles = " << rho << endl;
  vol = (double)npart/rho;
  cout << "Volume of the simulation box = " << vol << endl;
  box = pow(vol,1.0/3.0);
  cout << "Edge of the simulation box = " << box << endl ;

  ReadInput >> rcut;
  ReadInput >> delta;
  ReadInput >> nstep;
  ReadInput >> n_block;
  ReadInput >> iprint;
  n_blockstep=nstep/(n_block*10);


  cout << "The program integrates Newton equations with the Verlet method " << endl;
  cout << "Time step = " << delta << endl;
  cout << "Number of steps = " << nstep << endl << endl;
  ReadInput.close();

//Prepare array for measurements
  iv = 0; //Potential energy
  ik = 1; //Kinetic energy
  ie = 2; //Total energy
  it = 3; //Temperature
  n_props = 4; //Number of observables


  bin_size = (box/2.0)/(double)nbins;

  for (int i=0; i<nbins; i++){
    blk_av[i]=0;
    glob_av[i]=0;
    glob_av2[i]=0;
  }


if(prv_sim==false){
  //Read initial configuration
    cout << "Read initial configuration from file config.0 " << endl << endl;
    ReadConf.open("config.0");
    for (int i=0; i<npart; ++i){
      ReadConf >> x[i] >> y[i] >> z[i];
      x[i] = x[i] * box;
      y[i] = y[i] * box;
      z[i] = z[i] * box;
    }
    ReadConf.close();

  //Prepare initial velocities
    cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
    double sumv[3] = {0.0, 0.0, 0.0};
    for (int i=0; i<npart; ++i){
      vx[i] = rand()/double(RAND_MAX) - 0.5;
      vy[i] = rand()/double(RAND_MAX) - 0.5;
      vz[i] = rand()/double(RAND_MAX) - 0.5;

      sumv[0] += vx[i];
      sumv[1] += vy[i];
      sumv[2] += vz[i];
    }
    for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
    double sumv2 = 0.0, fs;
    for (int i=0; i<npart; ++i){
      vx[i] = vx[i] - sumv[0];
      vy[i] = vy[i] - sumv[1];
      vz[i] = vz[i] - sumv[2];

        sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
    }
    sumv2 /= (double)npart;

    fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor
    for (int i=0; i<npart; ++i){
      vx[i] *= fs;
      vy[i] *= fs;
      vz[i] *= fs;

        xold[i] = Pbc(x[i] - vx[i] * delta);
        yold[i] = Pbc(y[i] - vy[i] * delta);
        zold[i] = Pbc(z[i] - vz[i] * delta);
    }
  }else{
    cout << "Read initial configuration from file config.0 " << endl << endl;
    ReadConf.open("config.final");
    WriteConf0.open("config.0");
    for (int i=0; i<npart; ++i){
      ReadConf >> x[i] >> y[i] >> z[i];
      WriteConf0 << x[i] << "\t" << y[i] << "\t" << z[i] << endl;
      x[i] = x[i] * box;
      y[i] = y[i] * box;
      z[i] = z[i] * box;
    }
    ReadConf.close();
    WriteConf0.close();

    cout << "Read n-1 step configuration from old.0 " << endl << endl;
    ReadOld.open("old.final");
    WriteOld0.open("old.0");

    for (int i=0; i<npart; ++i){
      ReadOld >> xold[i] >> yold[i] >> zold[i];
      WriteOld0 << xold[i] << "\t" << yold[i] << "\t" << zold[i] << endl;
      xold[i] = xold[i] * box;
      yold[i] = yold[i] * box;
      zold[i] = zold[i] * box;
    }
    ReadOld.close();
    WriteOld0.close();

    Move();

  for(int i=0; i<npart; ++i){
      vx[i] = Pbc(x[i] - xold[i])/delta;
      vy[i] = Pbc(y[i] - yold[i])/delta;
      vz[i] = Pbc(z[i] - zold[i])/delta;
    }


    double sumv2 = 0.0, fs;
    for (int i=0; i<npart; ++i)
        sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
    sumv2 /= (double)npart;
    temp_eq=sumv2/3;
    fs=sqrt(temp/temp_eq);  // fs = velocity scale factor
    for (int i=0; i<npart; ++i){
      vx[i] *= fs;
      vy[i] *= fs;
      vz[i] *= fs;

        xold[i] = Pbc(x[i] - vx[i] * delta);
        yold[i] = Pbc(y[i] - vy[i] * delta);
        zold[i] = Pbc(z[i] - vz[i] * delta);
    }


  }
    return;
}


void Move(void){ //Move particles with Verlet algorithm
  double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

  for(int i=0; i<npart; ++i){ //Force acting on particle i
    fx[i] = Force(i,0);
    fy[i] = Force(i,1);
    fz[i] = Force(i,2);
  }

  for(int i=0; i<npart; ++i){ //Verlet integration scheme

    xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
    ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
    znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

    vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
    vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
    vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

    xold[i] = x[i];
    yold[i] = y[i];
    zold[i] = z[i];

    x[i] = xnew;
    y[i] = ynew;
    z[i] = znew;
  }
  return;
}

double Force(int ip, int idir){ //Compute forces as -Grad_ip V(r)
  double f=0.0;
  double dvec[3], dr;

  for (int i=0; i<npart; ++i){
    if(i != ip){
      dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
      dvec[1] = Pbc( y[ip] - y[i] );
      dvec[2] = Pbc( z[ip] - z[i] );

      dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
      dr = sqrt(dr);

      if(dr < rcut){
        f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
      }
    }
  }

  return f;
}

void Measure(){ //Properties measurement
  int bin;
  double v, t, vij;
  double dx, dy, dz, dr;
  ofstream Epot, Ekin, Etot, Temp;

  /*Epot.open("output_epot.dat",ios::app);
  Ekin.open("output_ekin.dat",ios::app);
  Temp.open("output_temp.dat",ios::app);
  Etot.open("output_etot.dat",ios::app);
  Etot.precision(10);*/

  v = 0.0; //reset observables
  t = 0.0;

//cycle over pairs of particles
  for (int i=0; i<npart-1; ++i){
    for (int j=i+1; j<npart; ++j){

     dx = Pbc( xold[i] - xold[j] );
     dy = Pbc( yold[i] - yold[j] );
     dz = Pbc( zold[i] - zold[j] );

     dr = dx*dx + dy*dy + dz*dz;
     dr = sqrt(dr);

     if(dr < rcut){
       vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);

//Potential energy
       v += vij;
     }

//update of the histogram of g(r)
     for (int i=0; i<nbins; i++){
       if(dr>i*bin_size && dr<=(i+1)*bin_size)
         blk_av[i]+=2;
     }
    }
  }

//Kinetic energy
  for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);

    /*stima_pot = v/(double)npart; //Potential energy per particle
    stima_kin = t/(double)npart; //Kinetic energy per particle
    stima_temp = (2.0 / 3.0) * t/(double)npart; //Temperature
    stima_etot = (t+v)/(double)npart; //Total energy per particle

    sumpot+=stima_pot;
    sumkin+=stima_kin;
    sumtemp+=stima_temp;
    sumtot+=stima_etot;

    Epot << stima_pot  << endl;
    Ekin << stima_kin  << endl;
    Temp << stima_temp << endl;
    Etot << stima_etot << endl;

    Epot.close();
    Ekin.close();
    Temp.close();
    Etot.close();*/

    return;
}


void ConfFinal(void){ //Write final configuration
  ofstream WriteConf;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config.final");

  for (int i=0; i<npart; ++i){
    WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
  }
  WriteConf.close();
  return;
}


void OldFinal(void){ //Write final configuration
  ofstream WriteOld;

  cout << "Print n-1 configuration to file old.final " << endl << endl;
  WriteOld.open("old.final");

  for (int i=0; i<npart; ++i){
    WriteOld << xold[i]/box << "   " <<  yold[i]/box << "   " << zold[i]/box << endl;
  }
  WriteOld.close();
  return;
}

void ConfXYZ(int nconf){ //Write configuration in .xyz format
  ofstream WriteXYZ;

  WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
  WriteXYZ << npart << endl;
  WriteXYZ << "This is only a comment!" << endl;
  for (int i=0; i<npart; ++i){
    WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
  }
  WriteXYZ.close();
}

double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
    return r - box * rint(r/box);
}

void DataBlocking(int block){
  double mean,err,sum_prog=0,su2_prog=0,err_prog;
  double r, gdir, err_gdir, vol_g;
  ofstream  Gave;


  //g(r)
      for (int i=0; i<nbins; i++){
        r=i*bin_size;
        vol_g=4*M_PI/3*(pow(r+bin_size,3)-pow(r,3));
        gdir=blk_av[i]/(n_blockstep*rho*npart*vol_g);
        glob_av[i]+=gdir;
        glob_av2[i]+=gdir*gdir;
        blk_av[i]=0;
      }

      if(block==n_block){
      const int wd=12;
      Gave.open("NVE.gave.0");
      for(int i=0; i<nbins; i++){
        err_gdir=Error(glob_av[i],glob_av2[i],n_block);
        Gave << setw(wd) << glob_av[i]/(double)n_block << setw(wd) << err_gdir << endl;
      }
      Gave.close();
    }
  /*Epot.open("ave_epot.dat",ios::app);
  Ekin.open("ave_ekin.dat",ios::app);
  Temp.open("ave_temp.dat",ios::app);
  Etot.open("ave_etot.dat",ios::app);
  Etot.precision(10);*/

//storage averages in the vector
  /*ave_epot.push_back(sumpot/n_blockstep);
  av2_epot.push_back(pow(ave_epot[block-1],2));
  ave_ekin.push_back(sumkin/n_blockstep);
  av2_ekin.push_back(pow(ave_ekin[block-1],2));
  ave_temp.push_back(sumtemp/n_blockstep);
  av2_temp.push_back(pow(ave_temp[block-1],2));
  ave_etot.push_back(sumtot/n_blockstep);
  av2_etot.push_back(pow(ave_etot[block-1],2));*/

//Evaluate and print ekin with error
/*    for (int j=0; j<block; j++){
      sum_prog+=ave_ekin[j];
      su2_prog+=av2_ekin[j];
    }
  sum_prog/=(block);
  su2_prog/=(block);
  err_prog=DevSt(sum_prog,su2_prog,block);
  Ekin << sum_prog << "\t" << err_prog << endl;


//Evaluate and print epot with error
  sum_prog=0;
  su2_prog=0;
    for (int j=0; j<block; j++){
      sum_prog+=ave_epot[j];
      su2_prog+=av2_epot[j];
    }
  sum_prog/=(block);
  su2_prog/=(block);
  err_prog=DevSt(sum_prog,su2_prog,block);
  Epot << sum_prog << "\t" << err_prog << endl;

//Evaluate and print etot with error
  sum_prog=0;
  su2_prog=0;
    for (int j=0; j<block; j++){
      sum_prog+=ave_etot[j];
      su2_prog+=av2_etot[j];
    }
  sum_prog/=(block);
  su2_prog/=(block);
  err_prog=DevSt(sum_prog,su2_prog,block);
  Etot << sum_prog << "\t" << err_prog << endl;

//Evaluate and print temp with error
  sum_prog=0;
  su2_prog=0;
    for (int j=0; j<block; j++){
      sum_prog+=ave_temp[j];
      su2_prog+=av2_temp[j];
    }
  sum_prog/=(block);
  su2_prog/=(block);
  err_prog=DevSt(sum_prog,su2_prog,block);
  Temp << sum_prog << "\t" << err_prog << endl;

  sumpot=0;
  sumkin=0;
  sumtemp=0;
  sumtot=0;*/


}

double DevSt (double av, double av2, int n){
  if(n==1) return 0;
    else
      return sqrt(abs(av2/n-pow(av,2)/n));
}

double Error(double sum, double sum2, int iblk){
    if( iblk == 1 ) return 0.0;
    else return sqrt(abs((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)iblk));
}
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
