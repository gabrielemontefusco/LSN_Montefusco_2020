#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "lib1.h"
#include "random.h"


using namespace std;


int main() {
  //setting useful variable
    Random *rnd=new Random();
    SetGen (rnd);
    int N=100;
    int n_rw=pow(10,4);
    double a=1;
    vector<double> r(n_rw,0),x(n_rw,0),y(n_rw,0),z(n_rw,0);
    vector<double> r2_meand(N,0),r2_errd(N,0),r2_meanc(N,0),r2_errc(N,0);
    Simulation RW(n_rw,N);
    RandomWalk Walk(a,rnd);

    for(int i=0;i<N;i++){
      for(int t=0;t<n_rw;t++){
        Walk.MakeDiscreteStep(x[t],y[t],z[t]);
        x[t]=Walk.GetX();
        y[t]=Walk.GetY();
        z[t]=Walk.GetZ();
        r[t]=x[t]*x[t]+y[t]*y[t]+z[t]*z[t];
      };
      RW.FillAve(r);
      RW.Simulate();
      r2_meand[i]=sqrt(RW.GetMean());
      r2_errd[i]=RW.GetErr()/(2*sqrt(r2_meand[i]));
    };

    char *filename=(char*) "RWsc.dat";
    print(filename,r2_meand,r2_errd);

    x.assign(n_rw,0),z.assign(n_rw,0),y.assign(n_rw,0);


    for(int i=0;i<N;i++){
      for(int t=0;t<n_rw;t++){
        Walk.MakeContinuosStep(x[t],y[t],z[t]);
        x[t]=Walk.GetX();
        y[t]=Walk.GetY();
        z[t]=Walk.GetZ();
        r[t]=x[t]*x[t]+y[t]*y[t]+z[t]*z[t];
      };
      RW.FillAve(r);
      RW.Simulate();
      r2_meanc[i]=sqrt(RW.GetMean());
      r2_errc[i]=RW.GetErr()/(2*sqrt(r2_meanc[i]));
    };

    char *filename1=(char*) "RWc.dat";
    print(filename1,r2_meanc,r2_errc);


    return 0;
}
