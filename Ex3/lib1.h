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


//Class EuropeOption, the structure of the class is described inside the jupyter

class EuropeOption {
private:
  int N_step;
  double s0,t,T,K,r,sigma,s_T; //s_T rappresent the asset price
  Random *rnd;

public:
  EuropeOption();
  EuropeOption(double,double,double,double,double,double,int, Random *);
  ~EuropeOption();
  void MakeDiscretePrice();
  void MakePrice();
  double GetsT();
  double GetDiscCPrice();
  double GetCPrice();
  double GetDiscPPrice();
  double GetPPrice();
};
