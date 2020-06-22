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
  double lenght;
  vector<int> city;

protected:

public:
  // constructors
  Individual(int N);
  // destructor
  ~Individual();
  // methods
  void fillCity(vector<int> ct);
  void EvalLenght(vector<double> x,vector<double> y);
  double GetLenght() {return lenght;};
  void print();
  int GetCity(int i) {return city[i];};
  void SetCity(int i,int ct) {city[i]=ct;};
  void swap(int i,int j);
  void rigidshift(int n);
  void permutation(int start,int end);  //start and end refers to the index of the vector not to the city
  void inversion(int start,int end);  //as said before, furthermore this two methods require attention to starting and ending point
  void Check(int num);
  void copy(Individual);
  bool operator<(Individual a) {return GetLenght()<a.GetLenght();};
};

#endif // __Individual__


#ifndef __Population__
#define __Population__

class Population {

private:
  int N_city,N_pop,N_iteration,Rank;
  double Prob_mut,Prob_cross;
  double P_r,P_l,P_exp;
  vector<double> x,y;
  vector<double> ave,err,best_path;
  vector<Individual> ind, ind_new;
  Random *rnd;

protected:

public:
  // constructors
  Population(int N,int M,int L,double exp,double pr_mut,double pr_cross, int rank);
  // destructor
  ~Population();
  // methods
  void circle(double r);
  void square(double l);
  int GetCity(int city,int i) { return ind[i].GetCity(city); };
  void FillCityB(int *ct,int i);
  int select();
  void mutation(int j);
  void crossover(int genitore1,int genitore2,int index);
  void evolution();
  void averages();
  double error(double av,double av2,int n);
  void printresult(int node);
  void printpath(int node);
};

#endif // __Population__
