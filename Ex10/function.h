#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "random.h"
#include "lib1.h"

using namespace std;

#ifndef __Individual__
#define __Individual__


class Individual {

private:
  int size;
  double length;
  vector<int> city;
  vector<double> x;
  vector<double> y;

protected:

public:
  // constructors
  Individual(int N,vector<double> x1,vector<double> y1);
  // destructor
  ~Individual();
  // methods
  void fillCity(vector<int> ct);
  void EvalLength();
  double GetLength() {return length;};
  void print();
  int GetCity(int i) {return city[i];};
  double GetX(int i) {return x[city[i]-1];};
  double GetY(int i) {return y[city[i]-1];};
  void SetCity(int i,int ct) {city[i]=ct;};
  void swap(int i,int j);
  void rigidshift(int n);
  void permutation(int start,int end);  //start and end refers to the index of the vector not to the city
  void inversion(int start,int end);  //as said before, furthermore this two methods require attention to starting and ending point
  void mutation(Random *rnd);
  void Check();
  void copy(Individual *old);
  bool operator<(Individual a) {return GetLength()<a.GetLength();};
};

#endif // __Individual__


#ifndef __Metropolis__
#define __Metropolis__

class Metropolis {
public:
	Metropolis (int N,double b,vector<double> x1,vector<double> y1,Random *r);
  void setBeta(double b) { beta=b; };
	void resetAcc() {acc=0;}
	void Step();
	double getLength() { return old_length; }
	int getAcc(){ return acc; }
  double getX(int i){ return ind_old->GetX(i);};
  double getY(int i){ return ind_old->GetY(i);};


private:
	double old_length, new_length;
	double beta;
	int acc;
  Individual *ind_old,*ind_new;
	Random *m_R;
};

#endif
