#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "random.h"
#include "population.h"


using namespace std;

//RANDOMSEED	130 3557 189 1219

int main() {
  //initialize the simulation
  vector<double> x_c,y_c,x_s,y_s; //_c means circle's coordinates while _s square coordinates
  int N_city,N_pop,N_iteration;
  double r,l,exp,Prob_mut,Prob_cross;
  ifstream ReadInput;

  cout <<endl << "Travelling Salesman problem        " << endl << endl;
  cout << "Monte Carlo simulation             " << endl;
  cout << "The program uses genetic optimization algorithm " << endl << endl;

  //Read input informations
  ReadInput.open("input.dat");

  ReadInput >> N_city;
  cout << "Number of city = " << N_city << endl;

  ReadInput >> N_pop;
  cout << "Number of total population = " << N_pop << endl;

  ReadInput >> r;
  cout << "Radius of the circle = " << r << endl;

  ReadInput >> l;
  cout << "Side of the square = " << l << endl ;

  ReadInput >> exp;
  cout << "Exponential for select = " << exp << endl ;

  ReadInput >> Prob_mut;
  cout << "Probability for a mutation = " << Prob_mut << endl ;

  ReadInput >> Prob_cross;
  cout << "Probability for crossover = " << Prob_cross << endl ;

  ReadInput >> N_iteration;
  cout << "Number of iteration = " << N_iteration << endl ;

  ReadInput.close();


  Population pop_c(N_city,N_pop,N_iteration,exp,Prob_mut,Prob_cross);
  pop_c.circle(r);
  Population pop_s(N_city,N_pop,N_iteration,exp,Prob_mut,Prob_cross);
  pop_s.square(l);

  //making of simulation and printing result
  pop_c.evolution();
  pop_s.evolution();


  return 0;
}
