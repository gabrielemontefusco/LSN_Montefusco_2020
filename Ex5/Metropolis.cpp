#include <iostream>
#include <algorithm>
#include <cmath>
#include "Metropolis.h"

groundstate :: groundstate() {
}

groundstate :: ~groundstate(){
}


firstexcited :: firstexcited() {
};

firstexcited :: ~firstexcited(){
};


Metropolis :: Metropolis(double d,vector<double> pos, basedistribution* f, Random *r){

	delta=d;
	m_R=r;
	m_D=f;
	dim=pos.size();
	acc=0;
	for(int i=0;i<dim;i++)
			x_old.push_back(pos[i]);
	x_new.assign(dim,0);
	val_old=m_D->eval(x_old);

}

void Metropolis :: setx0(vector<double> pos){

	int dim=pos.size();
	for(int i=0;i<dim;i++)
			x_old.push_back(pos[i]);
	val_old=m_D->eval(x_old);
}

void Metropolis :: UnifStep(){
	double x,y,z;
	double val_new,a;
	double prob;


	x=m_R->Rannyu(-delta,delta);
	y=m_R->Rannyu(-delta,delta);
	z=m_R->Rannyu(-delta,delta);
	x_new[0]=x;
	x_new[1]=y;
	x_new[2]=z;

	for(int i=0;i<dim;i++)
		x_new[i]+=x_old[i];
	val_new=m_D->eval(x_new);

	a=min(1.,val_new/val_old);
	prob=m_R->Rannyu();
	if(prob<a){
		for(int i=0;i<dim;i++)
			x_old[i]=x_new[i];
		val_old=val_new;
		acc++;
	}

}


void Metropolis :: GaussStep(){
	double val_new,a;
	double prob;


		x_new[0]=m_R->Gauss(0,delta);
		x_new[1]=m_R->Gauss(0,delta);
		x_new[2]=m_R->Gauss(0,delta);


	for(int i=0;i<dim;i++)
		x_new[i]+=x_old[i];
	val_new=m_D->eval(x_new);

	a=min(1.,val_new/val_old);
	prob=m_R->Rannyu();
	if(prob<a){
		for(int i=0;i<dim;i++)
			x_old[i]=x_new[i];
		val_old=val_new;
		acc++;
	}

}


void Metropolis :: EquilibrateU(int n){
	for(int i=0;i<n;i++){
		double appo=0;
		UnifStep();
		for(int j=0;j<dim;j++){
			appo+=x_old[j]*x_old[j];
		}
		//cout<<i<<"\t"<<sqrt(appo)<<endl;
	}
}


void Metropolis :: EquilibrateG(int n){
	for(int i=0;i<n;i++)
		GaussStep();
}
