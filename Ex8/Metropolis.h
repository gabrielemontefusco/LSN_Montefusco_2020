#include <cstdlib>
#include <cmath>
#include <vector>
#include "random.h"
#include "lib1.h"


using namespace std;

class basedistribution {
public:
virtual	double eval(double x) const=0;
};


class trialstate: public basedistribution {
public:
	trialstate(double mu,double sigma);
	void setMu(double mu){ Mu=mu; };
	void setSigma(double sigma){ Sigma=sigma; };
	~trialstate();
	virtual double eval (double x) const {return (pow(exp(-pow((x-Mu),2)/(2*Sigma*Sigma))+exp(-pow((x+Mu),2)/(2*Sigma*Sigma)),2));};

private:
	double Mu,Sigma;

};




class Metropolis {
public:
	Metropolis (double d,double pos, basedistribution* f, Random *r);
	void setx0(double pos);
	void setDelta(double d) {delta=d;};
	void setDist(basedistribution *f) {m_D=f;};
	void resetAcc(){acc=0;}
	void UnifStep();
	void EquilibrateU(int n);
	double getX(){ return x_old; }
	int getAcc(){ return acc; }


private:
	double x_old, x_new;
	double delta,val_old;
	int acc;
	basedistribution *m_D;
	Random *m_R;
};
