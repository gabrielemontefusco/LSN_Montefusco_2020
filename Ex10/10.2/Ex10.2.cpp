#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "random.h"
#include "population.h"
#include "mpi.h"

using namespace std;

//RANDOMSEED	130 3557 189 1219

int main(int argc,char* argv[]) {
  int rank,size;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  //initialize the simulation
  vector<double> x_c,y_c,x_s,y_s; //_c means circle's coordinates while _s square coordinates
  int N_city,N_pop,N_iteration,N_ex;
  double l,exp,Prob_mut,Prob_cross;
  ifstream ReadInput;
  Random *r=new Random();
  SetGen(r);
  //MPI variable
  MPI_Status stat0, stat1, stat2, stat3;
  MPI_Request req;
  int itag1=1, itag2=2, itag3=3, itag4=4;

  /*cout <<endl << "Travelling Salesman problem        " << endl << endl;
  cout << "Monte Carlo simulation             " << endl;
  cout << "The program uses genetic optimization algorithm with parallel computation on 4 nodes " << endl << endl;*/

  //Read input informations
  ReadInput.open("input.dat");

  ReadInput >> N_city;

  ReadInput >> N_pop;

  ReadInput >> N_ex;

  ReadInput >> l;

  ReadInput >> exp;

  ReadInput >> Prob_mut;

  ReadInput >> Prob_cross;

  ReadInput >> N_iteration;

  ReadInput.close();

  //array for the exchange
  int *Path=new int[N_city];
  int *PathRec=new int[N_city];

  Population pop(N_city,N_pop,N_iteration,exp,Prob_mut,Prob_cross,rank);
  pop.square(l);

  //preparing selection algorithm for exchange
  Individual sel(4);
  vector<int> appo;
  for(int i=0;i<4;i++)
    appo.push_back(i);
  sel.fillCity(appo);

  //making of simulation and printing result
  for(int i=0;i<N_iteration;i++){
    pop.evolution();
    if((i+1)%N_ex==0){
      int swap1=r->Rannyu(0,4),swap2;
      do{
        swap2=r->Rannyu(0,4);
      }while(swap2==swap1);
      sel.swap(swap1,swap2);
      //cout<<"dentro exchange, iterazione "<<i<<" rank "<<rank<<endl;
      if(rank==sel.GetCity(0)){
        for(int j=0;j<N_city;j++){
          Path[j]=pop.GetCity(j,0);
        }
        MPI_Isend(&Path[0],N_city,MPI_INTEGER,sel.GetCity(1),itag1, MPI_COMM_WORLD,&req);
        MPI_Recv(&PathRec[0],N_city,MPI_INTEGER,sel.GetCity(1),itag2,MPI_COMM_WORLD,&stat0);
        pop.FillCityB(PathRec,0);
      };
      if(rank==sel.GetCity(1)){
        for(int j=0;j<N_city;j++){
          Path[j]=pop.GetCity(j,0);
        }
        MPI_Isend(&Path[0],N_city,MPI_INTEGER,sel.GetCity(0),itag2, MPI_COMM_WORLD,&req);
        MPI_Recv(&PathRec[0],N_city,MPI_INTEGER,sel.GetCity(0),itag1,MPI_COMM_WORLD,&stat1);
        pop.FillCityB(PathRec,0);
      }
      if(rank==sel.GetCity(2)){
        for(int j=0;j<N_city;j++)
          Path[j]=pop.GetCity(j,0);
        MPI_Isend(&Path[0],N_city,MPI_INTEGER,sel.GetCity(3),itag3, MPI_COMM_WORLD,&req);
        MPI_Recv(&PathRec[0],N_city,MPI_INTEGER,sel.GetCity(3),itag4,MPI_COMM_WORLD,&stat2);
        pop.FillCityB(PathRec,0);
      }
      if(rank==sel.GetCity(3)){
        for(int j=0;j<N_city;j++)
          Path[j]=pop.GetCity(j,0);
        MPI_Isend(&Path[0],N_city,MPI_INTEGER,sel.GetCity(2),itag4, MPI_COMM_WORLD,&req);
        MPI_Recv(&PathRec[0],N_city,MPI_INTEGER,sel.GetCity(2),itag3,MPI_COMM_WORLD,&stat3);
        pop.FillCityB(PathRec,0);
      }
    }

  }

  //print result on file
  pop.printresult(rank);

  //print best path
  pop.printpath(rank);

  MPI_Finalize();

  return 0;
}
