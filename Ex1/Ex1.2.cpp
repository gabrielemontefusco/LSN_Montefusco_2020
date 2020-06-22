#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "lib1.h"

using namespace std;


int main() {

  int M=10000;
  int N=4*M;
  int k=0;
  double lambda=1,gamma=1,mu=0.;
  vector<double> Unifmean(N,0);
  vector<double> Expmean(N,0);
  vector<double> Lorentzianmean(N,0);
  Random *rnd=new Random();
  SetGen(rnd);

  //Execute standard dice


  for(int l=0;l<3;l++){
    if(l==1){
      for(int j=0; j<M ; j++){
        double mean=0;
        for(int i=0; i<2 ; i++)
            mean+=rnd->Rannyu();
        Unifmean[j+l*M]=mean/2;
      };
      k++;
    };
    for(int j=0; j<M; j++){
      double mean=0;
      for(int i=0; i<pow(10,l) ; i++)
          mean+=rnd->Rannyu();
      Unifmean[j+M*k]=mean/pow(10,l);
    };
    k++;
  };

  char *filename3=(char*) "stand.dat";
  print(filename3,Unifmean);



  //Execute exponential dice

  k=0;
  for(int l=0;l<3;l++){
    if(l==1){
      for(int j=0; j<M ; j++){
        double mean=0;
        for(int i=0; i<2 ; i++)
            mean+=rnd->Exp(lambda);
        Expmean[j+l*M]=mean/2;
      };
      k++;
    };
    for(int j=0; j<M; j++){
      double mean=0;
      for(int i=0; i<pow(10,l) ; i++)
          mean+=rnd->Exp(lambda);
      Expmean[j+M*k]=mean/pow(10,l);
    };
    k++;
  };

  char *filename=(char*) "exp.dat";
  print(filename, Expmean);


  //Execute lorentzian dice

  k=0;
  for(int l=0;l<3;l++){
    if(l==1){
      for(int j=0; j<M ; j++){
        double mean=0;
        for(int i=0; i<2 ; i++)
            mean+=rnd->Lorentzian(mu,gamma);
        Lorentzianmean[j+l*M]=mean/2;
      };
      k++;
    };
    for(int j=0; j<M; j++){
      double mean=0;
      for(int i=0; i<pow(10,l) ; i++)
          mean+=rnd->Lorentzian(mu,gamma);
      Lorentzianmean[j+M*k]=mean/pow(10,l);
    };
    k++;
  };

  char *filename1=(char*) "lorentzian.dat";
  print(filename1, Lorentzianmean);



}
