#include <cstdlib>
#include <cmath>
#include <vector>
#include "random.h"
#include "lib1.h"


using namespace std;

class basedistribution {
public:
virtual	double eval(vector<double> x) const=0;
};


class groundstate: public basedistribution {
public:
	groundstate();
	~groundstate();
	virtual double eval (vector<double> x) const {return (exp(-2*sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]))/M_PI);};

private:


};


class firstexcited: public basedistribution {
public:
	firstexcited();
	~firstexcited();
	virtual double eval (vector<double> x) const {return (x[2]*x[2]*exp(-sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]))/(32*M_PI));};

private:

};


class Metropolis {
public:
	Metropolis (double d,vector<double> pos, basedistribution* f, Random *r);
	void setx0(vector<double> pos);
	void setDelta(double d){delta=d;};
	void setDist(basedistribution *f){m_D=f;};
	void resetAcc(){acc=0;}
	void UnifStep();
	void GaussStep();
	void EquilibrateU(int n);
	void EquilibrateG(int n);
	double getCord(int i){ return x_old[i]; }
	int getAcc(){ return acc; }


private:
	vector<double> x_old, x_new;
	double delta,val_old;
	int dim,acc;
	basedistribution *m_D;
	Random *m_R;
};
