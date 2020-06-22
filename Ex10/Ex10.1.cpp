#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "random.h"
#include "function.h"


using namespace std;


int main() {
  //initialize the simulation
  vector<double> x_c,y_c,x_s,y_s; //_c means circle's coordinates while _s square coordinates
  int N_city,N_iteration,N_bstep;
  double r,l,beta,delta_b;
  ifstream ReadInput;
  Random *rnd;
  fstream fout_c,fout_s;

  //setting random gen
  rnd=new Random();
  SetGen (rnd);


  cout <<endl << "Travelling Salesman problem        " << endl << endl;
  cout << "Monte Carlo simulation             " << endl;
  cout << "The program uses simulated annealing " << endl << endl;

  //Read input informations
  ReadInput.open("input.dat");

  ReadInput >> N_city;
  cout << "Number of city = " << N_city << endl;

  ReadInput >> r;
  cout << "Radius of the circle = " << r << endl;

  ReadInput >> l;
  cout << "Side of the square = " << l << endl ;

  ReadInput >> beta;
  cout << "Starting beta = " << beta << endl ;

  ReadInput >> delta_b;
  cout << "Steps size for raise up beta = " << delta_b << endl ;

  ReadInput >> N_bstep;
  cout << "Number of steps size for raise up beta = " << N_bstep << endl ;

  ReadInput >> N_iteration;
  cout << "Number of iteration for circle = " << N_iteration << endl << endl;

  ReadInput.close();

  if(l==0){ //making circle simulation
    //setting cities's positions on a circle
    for(int i=0; i<N_city; i++){
      double theta=rnd->RanAngle();
      x_c.push_back(r*cos(theta));
      y_c.push_back(r*sin(theta));
    }

    //setting Metropolis
    Metropolis mtr_c(N_city,beta,x_c,y_c,rnd);

    //open file out for length
    fout_c.open("length_c.0",ios::app);

    //making annealing and saving best lenght
    for(int i=0;i<N_bstep;i++){
      if(i>0)
        beta=beta*delta_b;
      mtr_c.setBeta(beta);
      for(int j=0;j<N_iteration;j++){
        mtr_c.Step();
      }
      fout_c<<mtr_c.getLength()<<endl;
    }

    //close file out for length and open it for best path
    fout_c.close();
    fout_c.open("bestpath_c.0",ios::app);

    //printing best path
    for(int i=0;i<N_city;i++)
      fout_c<<mtr_c.getX(i)<<"\t"<<mtr_c.getY(i)<<endl;


    //closing file out
    fout_c.close();
  }

  if(r==0){ //making square simulation
    //setting city position inside a square
    for(int i=0; i<N_city; i++){
      x_s.push_back(rnd->Rannyu(-l/2.,l/2.));
      y_s.push_back(rnd->Rannyu(-l/2.,l/2.));
    }

    //setting Metropolis
    Metropolis mtr_s(N_city,beta,x_s,y_s,rnd);

    //open file out for length
    fout_s.open("length_s.0",ios::app);

    //making annealing and saving best lenght
    for(int i=0;i<N_bstep;i++){
      if(i>0)
        beta=beta*delta_b;
      mtr_s.setBeta(beta);
      for(int j=0;j<N_iteration;j++){
        mtr_s.Step();
      }
      fout_s<<mtr_s.getLength()<<endl;
    }

    //close file out for length and open it for best path
    fout_s.close();
    fout_s.open("bestpath_s.0",ios::app);

    //printing best path
    for(int i=0;i<N_city;i++)
      fout_s<<mtr_s.getX(i)<<"\t"<<mtr_s.getY(i)<<endl;


    //closing file out
    fout_c.close();
  }

  return 0;
}
