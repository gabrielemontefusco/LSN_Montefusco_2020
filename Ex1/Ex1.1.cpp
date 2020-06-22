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
   vector <int> x;

//Getting ready the abscissas
   for (int i=0; i<N; i++)
      x.push_back(i*M/N);
   char *filename1=(char*) "x.dat";
   print(filename1, x);


//Execute exercise1.1 part 1
   vector <double> r(M,0);
   for (int i=0; i<M; i++)
      r[i]=rnd->Rannyu();
   Simulation unif(r,M,N); //class simulation implement blocking method
   unif.FillAve();    //making averages
   unif.Simulate();   //blocking method
   char *filename2=(char*) "ex1.1.dat";
   unif.Print(filename2);


//Execute exercise1.1 part 2
   vector<double> r2(M,0);
   for (int i=0; i<M; i++)
     r2[i]=pow(r[i]-0.5,2);
   unif.FillAve(r2);
   unif.Simulate();
   char *filename3=(char*) "ex1.2.dat";
   unif.Print(filename3);

//Execute exercise1.1 part 3
  N=10000;
  M=100;
  vector<double> r3(N,0);
  vector<double> chi2(M,0);
  char *filename4=(char*) "ex1.3.dat";
  for(int l=0;l<M;l++){
    int k=0;
    vector<int> count(M,0);
    for(int i=0;i<N;i++){
      r3[i]=rnd->Rannyu();
    };
    sort(r3.begin(),r3.end());
    for(int j=0;j<M;j++){
      while(r3[k]>=(double)j/M && r3[k]<(double)(j+1)/M && k<N){
        k++;
        count[j]+=1;
      };
      chi2[l]+=pow(count[j]-N/M,2)/(double)(N/M);
    };
  };
  print(filename4,chi2);


   return 0;
 }
