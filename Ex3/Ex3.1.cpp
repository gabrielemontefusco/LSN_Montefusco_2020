#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "lib1.h"
#include "random.h"


using namespace std;


int main()  {
  //setting useful variable
    Random *rnd=new Random();
    SetGen (rnd);
    int N=100; //number of blocks and of step for discrete sampling
    int M=pow(10,5); //number of evaluation
    double t=0,T=1,s0=100,k=100,r=0.1,sigma=0.25;
    vector<double> DiscCall(M,0),Call(M,0),DiscPut(M,0),Put(M,0);
    Simulation Exchange(M,N); //blocking method class
    EuropeOption EO(t,T,s0,k,r,sigma,N,rnd);

    for(int i=0;i<M;i++){ //cycle over M evaluation for every option
      DiscCall[i]=EO.GetDiscCPrice();
      Call[i]=EO.GetCPrice();
      DiscPut[i]=EO.GetDiscPPrice();
      Put[i]=EO.GetPPrice();
    }

    //running blocking method and printing result for every option
    Exchange.FillAve(DiscCall);
    Exchange.Simulate();
    char *filename=(char*) "DiscCall.dat";
    Exchange.Print(filename);

    Exchange.FillAve(Call);
    Exchange.Simulate();
    char *filename1=(char*) "Call.dat";
    Exchange.Print(filename1);

    Exchange.FillAve(DiscPut);
    Exchange.Simulate();
    char *filename2=(char*) "DiscPut.dat";
    Exchange.Print(filename2);

    Exchange.FillAve(Put);
    Exchange.Simulate();
    char *filename3=(char*) "Put.dat";
    Exchange.Print(filename3);
}
