#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
#include "integral.h"

using namespace std;


int main() {
//setting useful variable
  Random *rnd=new Random();
  SetGen (rnd);
  int M=pow(10,5);
  int N=100;
  int n_throw=M/N;
  double inf=0.,sup=1.;
  vector<double> Int(N,0),Intis(N,0);
  funzione *f=new funzione();
  funzioneIS *is=new funzioneIS();
  integral my_int(inf,sup,f,rnd);

  for(int i=0;i<N;i++)
    Int[i]=my_int.media(n_throw);

  Simulation integ(M,N);
  integ.SetVectorAve(Int);
  integ.Simulate();
  char *filename=(char*) "int.dat";
  integ.Print(filename);

  my_int.setF(is);
  for(int i=0;i<N;i++)
    Intis[i]=my_int.mediaIS(n_throw);

  integ.SetVectorAve(Intis);
  integ.Simulate();
  char *filename1=(char*) "intis.dat";
  integ.Print(filename1);

  return 0;

}
