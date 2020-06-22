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
    int N=100,M=pow(10,8),eq_u=350;
    double x=2,mu=0.8,sigma=0.615,delta=2.5;
    trialstate *ts=new trialstate(mu,sigma);
    Simulation Stat(M,N);
    Metropolis mtr(delta,x,ts,rnd);
    vector<double> energy(M,0);

  //setting histogram variable
    int nbins=200;
    double x_min=-3,x_max=3, bin_size=(x_max-x_min)/(double)nbins;
    vector<double> pop(nbins,0);

    mtr.EquilibrateU(eq_u);
    mtr.resetAcc();
    for(int i=0;i<M;i++){ //filling energy
    mtr.UnifStep();
    x=mtr.getX();
    for(int j=0;j<nbins;j++){
      if(x>x_min+j*bin_size && x<=x_min+(j+1)*bin_size)
        pop[j]+=1./(double)(M*bin_size);
    }
    energy[i]=e_tot(x,mu,sigma);
    }

    cout<<mtr.getAcc()/(double) M<<endl;

    Stat.FillAve(energy); //make averages on energy
    Stat.Simulate();    //block averages
    char *filename=(char*) "OptVarState.dat";
    Stat.Print(filename);

    char *filename1=(char*) "Pop.dat";
    print(filename1, pop);


    return 0;
}
