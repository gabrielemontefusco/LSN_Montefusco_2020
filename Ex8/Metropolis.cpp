#include <iostream>
#include <algorithm>
#include <cmath>
#include "Metropolis.h"

trialstate :: trialstate(double mu, double sigma) {
	Mu=mu;
	Sigma=sigma;
}

trialstate :: ~trialstate(){
}




Metropolis :: Metropolis(double d,double pos, basedistribution* f, Random *r){

	delta=d;
	m_R=r;
	m_D=f;
	acc=0;
	x_old=pos;
	x_new=0;
	val_old=m_D->eval(x_old);

}

void Metropolis :: setx0(double pos){
	x_old=pos;
	val_old=m_D->eval(x_old);
}

void Metropolis :: UnifStep(){
	double val_new,a;
	double prob;


	x_new=m_R->Rannyu(-delta,delta);
	x_new+=x_old;
	val_new=m_D->eval(x_new);

	a=min(1.,val_new/val_old);
	prob=m_R->Rannyu();
	if(prob<a){
		x_old=x_new;
		val_old=val_new;
		acc++;
	}
	if(acc<10){
		//cout<<acc<<"\t"<<x_old<<"\t"<<a<<endl;
	}

}

void Metropolis :: EquilibrateU(int n){
	for(int i=0;i<n;i++)
		UnifStep();
}
