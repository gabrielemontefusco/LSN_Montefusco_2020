#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "Metropolis.h"


using namespace std;


int main() {
  //setting useful variable
    Random *rnd=new Random();
    SetGen (rnd);
    int N=100,M=pow(10,6),eq_u=250;
    double x=2,mu=0.1,sigma=0.2,delta=0.25;
    double e_min=0,err_min,mu_min,sigma_min,delta_min,acc_min;
    trialstate *ts=new trialstate(mu,sigma);
    Metropolis mtr(delta,x,ts,rnd);
    Simulation Stat(M,N);
    vector<double> energy(M,0);
    ofstream fout("energy.0",ios::app);

    for(int j=0;j<30;j++){ //cycle on mu, need to reset sigma and delta after cycle on sigma
      sigma=0.2;
      ts->setSigma(sigma);
      delta=0.25;
      mtr.setDelta(delta);
      for(int k=0;k<30;k++){ //cycle on sigma, need to reset starting point and riequilibrate
        mtr.setx0(2);
        mtr.EquilibrateU(eq_u);
        mtr.resetAcc();
        for(int i=0;i<M;i++){ //filling energy
          mtr.UnifStep();
          x=mtr.getX();
          energy[i]=e_tot(x,mu,sigma);
        }
        Stat.FillAve(energy); //make averages on energy
        Stat.Simulate();    //block averages
        fout<<mu<<"\t"<<sigma<<"\t"<<Stat.GetMean()<<"\t"<<Stat.GetErr()<<endl;
        if(Stat.GetMean()<e_min){ //search for the minimum
          e_min=Stat.GetMean();
          err_min=Stat.GetErr();
          mu_min=mu;
          sigma_min=sigma;
          delta_min=delta;
          acc_min=(double) mtr.getAcc()/M;
        }
        sigma+=0.1;
        delta+=0.3;    //need to increase delta for the 50 rules on acceptance
        mtr.setDelta(delta);
        ts->setSigma(sigma);
        Stat.ResetSim();
        //cout<<"accettanza "<<j+1<<" "<<k<<"\t"<< (double) mtr.getAcc()/M<<endl;
      }
      mu+=0.1;
      ts->setMu(mu);
    }
    fout.close();

    cout<<e_min<<" +/- "<<err_min<<" with mu="<<mu_min<<" and sigma="<<sigma_min<<endl<<"delta was "<<delta_min<<" with an acceptance of "<<acc_min<<endl;


    return 0;
}
