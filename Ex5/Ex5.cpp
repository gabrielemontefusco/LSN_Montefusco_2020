#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "Metropolis.h"


using namespace std;

//2018 2415 3433 2674
int main() {
  //setting useful variable
    Random *rnd=new Random();
    SetGen (rnd);
    int N=100,M=pow(10,6),eq_u=250,eq_g=300;
    Simulation Stat(M,N);
    double delta1s_u=1.25,delta1s_g=0.65,delta2p_u=3.25,delta2p_g=1.85;
    vector<double> r_u(M,0),r_g(M,0);
    vector<double> pos_1s(3,2.),pos_2p(3,4.);
    groundstate *gs=new groundstate();
    firstexcited *p=new firstexcited();
    Metropolis mtrU(delta1s_u,pos_1s,gs,rnd);
    Metropolis mtrG(delta1s_g,pos_1s,gs,rnd);

    //making simulation for 1s with uniform and gauss
    mtrU.EquilibrateU(eq_u);
    mtrG.EquilibrateG(eq_g);
    for(int i=0;i<M;i++){
      mtrU.UnifStep();
      mtrG.GaussStep();
      double ru_app=0,rg_app=0;
      for(int j=0;j<3;j++){
        ru_app+=mtrU.getCord(j)*mtrU.getCord(j);
        rg_app+=mtrG.getCord(j)*mtrG.getCord(j);
      }
      r_u[i]=sqrt(ru_app);
      r_g[i]=sqrt(rg_app);
    }


    Stat.FillAve(r_u);
    Stat.Simulate();
    char *filename=(char*) "GroundStateU.dat";
    Stat.Print(filename);


    Stat.FillAve(r_g);
    Stat.Simulate();
    char *filename1=(char*) "GroundStateG.dat";
    Stat.Print(filename1);


    cout<<endl<<"accettanza unif 1s "<< (double) mtrU.getAcc()/M<<endl;
    cout<<"accetanza gauss 1s "<< (double) mtrG.getAcc()/M<<endl<<endl;

    //making simulation for 2p with uniform and gauss
    mtrU.setDist(p);
    mtrU.setx0(pos_2p);
    mtrU.setDelta(delta2p_u);
    mtrU.resetAcc();
    mtrG.setDist(p);
    mtrG.setx0(pos_2p);
    mtrG.setDelta(delta2p_g);
    mtrG.resetAcc();

    eq_u=300;
    eq_g=350;
    mtrU.EquilibrateU(eq_u);
    mtrG.EquilibrateG(eq_g);
    for(int i=0;i<M;i++){
      mtrU.UnifStep();
      mtrG.GaussStep();
      double ru_app=0,rg_app=0;
      for(int j=0;j<3;j++){
        ru_app+=mtrU.getCord(j)*mtrU.getCord(j);
        rg_app+=mtrG.getCord(j)*mtrG.getCord(j);
      }
      r_u[i]=sqrt(ru_app);
      r_g[i]=sqrt(rg_app);
    }


    Stat.FillAve(r_u);
    Stat.Simulate();
    char *filename2=(char*) "FirstExcitedU.dat";
    Stat.Print(filename2);


    Stat.FillAve(r_g);
    Stat.Simulate();
    char *filename3=(char*) "FirstExcitedG.dat";
    Stat.Print(filename3);


    cout<<"accettanza unif 2p "<< (double) mtrU.getAcc()/M<<endl;
    cout<<"accetanza gauss 2p "<< (double) mtrG.getAcc()/M<<endl<<endl;
    return 0;
}
