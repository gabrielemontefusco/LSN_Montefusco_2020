#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "random.h"


using namespace std;

//funzioni generiche

void SetGen (Random *);

void print (char *, vector<int> );

void print (char *, vector<double> );

void print (char *,vector<double>, vector<double>);


//Classe Simulation

class Simulation {
private:
  vector <double> data ,ave , av2, sum_prog, su2_prog, err_prog;
  int N,M,L;
  double mean, error;
  double DevSt (const vector <double>, const vector <double>, int);

public:
  Simulation();
  Simulation(vector <double>, int, int);
  Simulation(int, int);
  ~Simulation();
  void SetSimulation(int,int);
  void SetVectorData(vector<double>);
  void SetVectorAve(vector<double>);
  void FillAve(vector<double>);
  void FillAve();
  void Simulate();
  void CleanData();
  void Print(char *);
  double GetMean();
  double GetErr();
};


//Class RandomWalk

class RandomWalk {
private:
  double x,y,z,a;
  Random *rnd;
  //double last_r2, last_r2err;

public:
  RandomWalk();
  RandomWalk(double, Random *);
  RandomWalk(Random *);
  ~RandomWalk();
  void MakeDiscreteStep(double,double,double);
  void MakeContinuosStep(double,double,double);
  double GetX();
  double GetY();
  double GetZ();
};
