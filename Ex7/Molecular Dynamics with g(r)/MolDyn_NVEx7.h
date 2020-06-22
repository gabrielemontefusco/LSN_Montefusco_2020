/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <vector>
#include <cstdlib>


//parameters, observables
const int m_props=4;
int n_props;
int iv,ik,it,ie;
double stima_pot, stima_kin, stima_etot, stima_temp;

// averages
double acc,att;

//configuration
const int m_part=108;
double x[m_part],y[m_part],z[m_part],xold[m_part],yold[m_part],zold[m_part];
double vx[m_part],vy[m_part],vz[m_part];

// thermodynamical state
int npart;
double energy,temp,temp_eq,vol,rho,box,rcut,epsilon,eps_kb, bin_size;

// simulation
int nstep, n_block, n_blockstep, block=1, iprint, seed ,nbins=100;
double delta,sumpot=0,sumkin=0,sumtemp=0,sumtot=0;
std::vector<double> ave_ekin,av2_ekin;
std::vector<double> ave_epot,av2_epot;
std::vector<double> ave_etot,av2_etot;
std::vector<double> ave_temp,av2_temp;
double blk_av[100],glob_av[100],glob_av2[100];
bool prv_sim;

//functions
void Input(void);
void Move(void);
void ConfFinal(void);
void OldFinal(void);
void ConfXYZ(int);
void Measure(void);
void DataBlocking(int);
double Force(int, int);
double Pbc(double);
double DevSt (double, double, int);
double Error(double , double , int);
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
