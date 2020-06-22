#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "lib1.h"

using namespace std;


int main() {

  //setting useful variable
     Random *rnd=new Random();
     SetGen (rnd);
     int M=100000;
     int N=100;
     int n_throw=M/N;
     double lenght=3.,d=6.,teta,x,x0;
     vector<double> pi(N,0);

     for(int i=0;i<N;i++){
       int nhit=0;
       for(int j=0;j<n_throw;j++){
        teta=rnd->RanAngle();
        x=lenght*abs(cos(teta))/2;
        x0=rnd->Rannyu(0.,d);
        if(x0<=x || x0>=d-x)
          nhit++;
        };
        pi[i] = (n_throw*2.*lenght)/(nhit*d);
      };


    Simulation buffon(M,N);
    buffon.SetVectorAve(pi);
    buffon.Simulate();
    char *filename=(char*) "pi.dat";
    buffon.Print(filename);

  return 0;

}
