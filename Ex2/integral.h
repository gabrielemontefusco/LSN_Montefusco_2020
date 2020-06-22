#include <cstdlib>
#include <cmath>
#include <vector>
#include "random.h"
#include "lib1.h"


using namespace std;

class funzionebase {
public:
virtual	double eval(double x) const=0;
};

class funzione: public funzionebase {
public:
	funzione();
	//funzione (double a, double b);
	~funzione();
	//void SetB(double b) {m_b=b;};
	virtual double eval (double x) const {return (M_PI/2*cos(M_PI*x/2));};

private:
	double m_a,m_b;

};


class funzioneIS: public funzionebase {
public:
	funzioneIS();
	//funzione (double a, double b);
	~funzioneIS();
	//void SetB(double b) {m_b=b;};
	virtual double eval (double x) const {return (M_PI/2*cos(M_PI*x/2)/(2*(1-x)));};

private:
	double m_a,m_b;

};

/*class derivata: public funzionebase {
public:
	derivata();
	derivata (double a, double b);
	~derivata();
	void SetB(double b) {m_b=b;};
	virtual double eval (double x) const {return (-m_b+m_a*x*x);};

private:
	double m_a,m_b;

};*/



class integral {
public:
	integral (double a, double b, funzionebase* f);
	integral (double a, double b, funzionebase* f, Random *r);
	void setA(double a){m_a=a;};
	void setB(double b){m_b=b;};
	void setF(funzionebase *f){m_f=f;};
	double simpson(unsigned int nstep);
	double simpson(double prec);
	double media (unsigned int nstep);
	double mediaIS (unsigned int nstep);
	double hitmiss (unsigned int nstep, double max);
	double getH(){return m_h;};

private:
	double m_a, m_b;
	double m_sum;
	double m_h;
	int m_sign;
	double m_integral;
	funzionebase *m_f;
	double m_prec;
	Random *m_R;
};
