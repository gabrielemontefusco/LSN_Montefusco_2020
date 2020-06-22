#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "integral.h"

funzione:: funzione() {
};

funzione:: ~funzione(){
};


funzioneIS:: funzioneIS() {
};

funzioneIS:: ~funzioneIS(){
};


integral:: integral(double a,double b, funzionebase* f){

	m_a=min(a,b);
	m_b=max(a,b);
	m_R=NULL;
	if(a>b) m_sign= -1;
	else m_sign = 1;
	m_f=f;

}

integral:: integral(double a,double b, funzionebase* f, Random* r){

	m_a=min(a,b);
	m_b=max(a,b);
	m_R=r;
	if(a>b) m_sign= -1;
	else m_sign = 1;
	m_f=f;

}

double integral:: simpson(unsigned int nstep){
	if(nstep%2!=0)
		nstep=nstep+1;

	m_h= (m_b-m_a)/(double)nstep;
	m_sum=0.;
	m_sum= m_f->eval(m_a)+m_f->eval(m_b);
	for (unsigned int i=2; i<nstep; i+=2)
	m_sum+=2*m_f->eval(m_a+i*m_h);

	for (unsigned int i=1; i<nstep; i+=2)
	m_sum+=4*m_f->eval(m_a+i*m_h);

	m_integral=m_sum*m_h/3.;
	return m_integral;
}

double integral:: simpson(double prec){
	double err;
	unsigned int nstep=2;
	double I0= simpson (nstep);
	do{
	nstep=2*nstep;
	m_integral=simpson(nstep);
	err=16./15.*fabs(m_integral-I0);
	I0=m_integral;
	}
	while (err>prec);
	return m_integral;
}

double integral:: media (unsigned int nstep){
	double sum=0;
	double x,y;
	for (unsigned int i=0; i<nstep; i++){
	x=m_R->Rannyu(m_a, m_b);
	y=m_f->eval(x);
	sum+= y;
	}
	m_integral=(m_b-m_a)*sum/nstep;
	return m_integral;
}

double integral:: mediaIS (unsigned int nstep){
	double sum=0;
	double x,y;
	for (unsigned int i=0; i<nstep; i++){
	x=m_R->ImpSamp();
	y=m_f->eval(x);
	sum+= y;
	}
	m_integral=(m_b-m_a)*sum/nstep;
	return m_integral;
}

double integral:: hitmiss (unsigned int nstep, double max){
	double x, y, g;
	int nhit=0;
	for (unsigned int i=0; i<nstep; i++){
	x=m_R->Rannyu(m_a, m_b);
	y=m_R->Rannyu(0,max);
	g=m_f->eval(x);
	if (y<g){
		nhit++;
		}
	}
	m_integral=(m_b-m_a)*max*nhit/nstep;
	return m_integral;
}
