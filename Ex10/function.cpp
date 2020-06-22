#include "function.h"


using namespace std;

//Individual methods

Individual :: Individual(int N,vector<double> x1,vector<double> y1){
  city.assign(N,0);
  size=N;
  for(int i=0;i<N;i++){
    x.push_back(x1[i]);
    y.push_back(y1[i]);
  }
}

Individual :: ~Individual(){}

void Individual :: fillCity(vector<int> ct){
  for(int i=0;i<size;i++){
    city[i]=ct[i];
  }
  EvalLength();
}

void Individual :: EvalLength(){
  double dist=0;
  for(int i=0;i<size-1;i++){
    double appo=0;
    appo+=pow(x[city[i+1]-1]-x[city[i]-1],2);
    appo+=pow(y[city[i+1]-1]-y[city[i]-1],2);
    dist+=sqrt(appo);
  }
  double appo=0;
  appo+=pow(x[city[0]-1]-x[city[size-1]-1],2);
  appo+=pow(y[city[0]-1]-y[city[size-1]-1],2);
  dist+=sqrt(appo);
  length=dist;
}

void Individual :: print(){

  for(int i=0;i<size;i++)
      cout<<city[i]<<endl;

}

void Individual :: copy(Individual *old){
  for(int i=0; i<size; i++){
    city[i]=old->GetCity(i);
  }
  length=old->GetLength();
}

void Individual :: swap(int i,int j){

  int i_appo=i,j_appo=j,appo;
//checking and correct if i==0 or j==0 (the first city cannot be swapped)
  if(i==0){
      i_appo=i+1;
  }

  if(j==0){
      j_appo=j+1;
  }

//swapping
  appo=city[i_appo];
  city[i_appo]=city[j_appo];
  city[j_appo]=appo;

}

void Individual :: rigidshift(int n){
  int range=size-n;
  vector<int> appo;

  for(int i=0;i<size;i++)
    appo.push_back(city[i]);


  for(int j=1;j<range;j++)
    city[j+n]=appo[j];


  for(int k=0;k<n;k++)
    city[k+1]=appo[range+k];

}

void Individual :: permutation(int start,int end){

  if(end-start<0){
    int appo=start;
    start=end;
    end=appo;
  }

  int range=end-start;
  vector<int> appo;

  for(int i=start;i<end;i++)
    appo.push_back(city[i]);


  for(int j=start;j<end;j++){
    city[j]=city[j+range];
    city[j+range]=appo[j-start];
  }

}

void Individual :: inversion(int start,int end){

  if(end-start<0){
    int appo=start;
    start=end;
    end=appo;
  }

  int range=end-start;

  for(int i=0;i<range/2;i++)
      swap(start+i,end-i);

}

void Individual :: mutation(Random *rnd){

    double sel=rnd->Rannyu();

    if(sel>=0 && sel<0.25){
      int swap1=rnd->Rannyu(1,size),swap2;
      do{
        swap2=rnd->Rannyu(1,size);
      }while(swap2==swap1);
      swap(swap1,swap2);
      Check();
      EvalLength();
    }

    if(sel>=0.25 && sel<0.5){
      int shift_size=rnd->Rannyu(1,size-2);
      rigidshift(shift_size);
      Check();
      EvalLength();
    }

    if(sel>=0.5 && sel<0.75){
      int start=rnd->Rannyu(1,size/2),end;
      do{
        end=rnd->Rannyu(start,(size+start)/2.);
      }while(end==start);
      permutation(start,end);
      Check();
      EvalLength();
    }

    if(sel>=0.75 && sel<1){
      int start=rnd->Rannyu(1,size),end;
      do{
        end=rnd->Rannyu(1,(size-start));
      }while(end==start);
      inversion(start,end);
      Check();
      EvalLength();
    }

}

void Individual :: Check(){

  if(city[0]!=1){
    cout<<"The individual does not have right first city"<<endl<<"print wrong individual "<<endl;
    print();
    cout<<"exit from program"<<endl;
    exit(EXIT_FAILURE);
  }

  vector<int> appo(size,0);
  int j;
  for (int i=0; i<size; i++){
    j=city[i];
    appo[j-1]+=1;
  }
  for (int i=0; i<size; i++){
    if (appo[i]!=1){
      cout<<"The individual does not pass through every city "<<endl<<"print wrong individual "<<endl;
      print();
      cout<<"exit from program"<<endl<<endl;
      exit(EXIT_FAILURE);
    }
  }
  vector <int> ().swap(appo);

}


//Metropolis methods

Metropolis :: Metropolis(int N,double b,vector<double> x1,vector<double> y1, Random *r){

  ind_old=new Individual(N,x1,y1);
  vector<int> city_start;
  for(int i=0;i<N;i++)
    city_start.push_back(i+1);
  ind_old->fillCity(city_start);
  ind_new=new Individual(N,x1,y1);
  ind_new->fillCity(city_start);
  beta=b;
	m_R=r;
	acc=0;
	old_length=ind_old->GetLength();
	new_length=0;

}

void Metropolis :: Step(){
	double a;
	double prob;

  ind_new->copy(ind_old);
	ind_new->mutation(m_R);
	ind_new->EvalLength();
  new_length=ind_new->GetLength();
  
  if(new_length<old_length){
    old_length=new_length;
    ind_old->copy(ind_new);
    acc++;
  }else{
  	a=min(1.,exp(-beta*(new_length-old_length)));
  	prob=m_R->Rannyu();
  	if(prob<a){
  		old_length=new_length;
      ind_old->copy(ind_new);
  		acc++;
	   }
   }

}
