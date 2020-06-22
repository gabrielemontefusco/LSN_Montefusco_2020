#include "population.h"


using namespace std;

//Individual methods

Individual :: Individual(int N){
  city.assign(N,0);
  size=N;
  lenght=0;
}

Individual :: ~Individual(){}

void Individual :: fillCity(vector<int> ct){
  for(int i=0;i<size;i++){
    city[i]=ct[i];
  }
}

void Individual :: EvalLenght(vector<double> x,vector<double> y){
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
  lenght=dist;
}

void Individual :: print(){

  for(int i=0;i<size;i++)
      cout<<city[i]<<endl;

}

void Individual :: copy(Individual old){
  for(int i=0; i<size; i++){
    city[i]=old.GetCity(i);
  }
  lenght=old.GetLenght();
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

void Individual :: Check(int num){

  if(city[0]!=1){
    cout<<"The individual "<<num<<" does not have right first city"<<endl<<"print wrong individual "<<endl;
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
      cout<<"The individual "<<num<<" does not pass through every city "<<endl<<"print wrong individual "<<endl;
      print();
      cout<<"exit from program"<<endl<<endl;
      exit(EXIT_FAILURE);
    }
  }
  vector <int> ().swap(appo);

}

//Population methods

Population :: Population(int N,int M,int L,double exp,double pr_mut,double pr_cross,int rank){

  N_city=N;
  N_pop=M;
  N_iteration=L;
  Rank=rank;
  P_exp=exp;
  Prob_mut=pr_mut;
  Prob_cross=pr_cross;
  x.assign(N_city,0);
  y.assign(N_city,0);
  ind.assign(N_pop,Individual(N_city));
  ind_new.assign(N_pop,Individual(N_city));
  rnd=new Random();
  SetGen (rnd);

}

Population :: ~Population(){}

void Population :: circle(double r){
  vector<int> city_start;
  P_r=r;
  P_l=0;

  //setting cities's positions on a circle
  for(int i=0; i<N_city; i++){
    double theta=rnd->RanAngle();
    x[i]=r*cos(theta);
    y[i]=r*sin(theta);
    city_start.push_back(i+1);
  }

  //generating initial population
  ind[0].fillCity(city_start);
  for(int i=1;i<N_pop;i++){
    int swap1=rnd->Rannyu(1,N_city),swap2;
    do{
      swap2=rnd->Rannyu(1,N_city);
    }while(swap2==swap1);
    ind[i].copy(ind[i-1]);
    ind[i].swap(swap1,swap2);
    ind[i].Check(i);
    ind[i].EvalLenght(x,y);
  }

  sort(ind.begin(),ind.end());


}

void Population :: square(double l){
  vector<int> city_start;
  P_r=0;
  P_l=l;

  //setting city position inside a square
  for(int i=0; i<N_city; i++){
    x[i]=rnd->Rannyu(-l/2.,l/2.);
    y[i]=rnd->Rannyu(-l/2.,l/2.);
    city_start.push_back(i+1);
  }


  //generating initial population
  ind[0].fillCity(city_start);
  for(int i=1;i<N_pop;i++){
    int swap1=rnd->Rannyu(1,N_city),swap2;
    do{
      swap2=rnd->Rannyu(1,N_city);
    }while(swap2==swap1);
    ind[i].copy(ind[i-1]);
    ind[i].swap(swap1,swap2);
    ind[i].Check(i);
    ind[i].EvalLenght(x,y);
  }

  sort(ind.begin(),ind.end());

  Random *newgen=new Random();
  SetGen(newgen,Rank);
  rnd=newgen;


}

void Population :: FillCityB(int *ct,int i){
  vector<int> appo;
  for(int j=0;j<N_city;j++)
    appo.push_back(ct[j]);

  ind[i].fillCity(appo);
  ind[i].EvalLenght(x,y);
  sort(ind.begin(),ind.end());
}

void Population :: mutation(int j){
  if(rnd->Rannyu()<Prob_mut){
    double sel=rnd->Rannyu();

    if(sel>=0 && sel<0.25){
      int swap1=rnd->Rannyu(1,N_city),swap2;
      do{
        swap2=rnd->Rannyu(1,N_city);
      }while(swap2==swap1);
      ind[j].swap(swap1,swap2);
      ind[j].Check(j);
      ind[j].EvalLenght(x,y);
    }

    if(sel>=0.25 && sel<0.5){
      int shift_size=rnd->Rannyu(1,N_city-2);
      ind[j].rigidshift(shift_size);
      ind[j].Check(j);
      ind[j].EvalLenght(x,y);
    }

    if(sel>=0.5 && sel<0.75){
      int start=rnd->Rannyu(1,N_city/2),end;
      do{
        end=rnd->Rannyu(start,(N_city+start)/2.);
      }while(end==start);
      ind[j].permutation(start,end);
      ind[j].Check(j);
      ind[j].EvalLenght(x,y);
    }

    if(sel>=0.75 && sel<1){
      int start=rnd->Rannyu(1,N_city),end;
      do{
        end=rnd->Rannyu(1,(N_city-start));
      }while(end==start);
      ind[j].inversion(start,end);

      ind[j].Check(j);
      ind[j].EvalLenght(x,y);
    }
  }
}

void Population :: crossover(int genitore1,int genitore2,int index){

  int cut=rnd->Rannyu(1,N_city);
  int appo;
  Individual son1(N_city), son2(N_city);

  for (int i=0; i<cut; i++){
    son1.SetCity(i,ind[genitore1].GetCity(i));
    son2.SetCity(i,ind[genitore2].GetCity(i));
  }

  int i=cut;
  for(int j=0; j<N_city; j++){
    appo=0;
    for(int k=0; k<i; k++){
      if(ind[genitore2].GetCity(j)==son1.GetCity(k))
        appo++;
    }
    if(appo==0){
      son1.SetCity(i,ind[genitore2].GetCity(j));
      i++;
    }
  }

  i=cut;
  for(int j=0; j<N_city; j++){
    appo=0;
    for(int k=0; k<i; k++){
      if(ind[genitore1].GetCity(j)==son2.GetCity(k))
        appo++;
    }
    if(appo==0){
      son2.SetCity(i,ind[genitore1].GetCity(j));
      i++;
    }
  }

  son1.Check(101); //101 because individual of the "real" generation are 100, if i read error from 101 i will know that is from a son of crossover
  son2.Check(101);
  son1.EvalLenght(x,y);
  son2.EvalLenght(x,y);
  ind_new[index].copy(son1);
  ind_new[N_pop-index-1].copy(son2);


}

void Population :: evolution(){

    for(int j=0;j<N_pop/2;j++){

      //setting index and variable
      int j1=select(),j2;
      Individual i1(N_city),i2(N_city);
      do{
        j2=select();
      }while(j1==j2);
      i1.copy(ind[j1]);
      i2.copy(ind[j2]);

      //mutation
      mutation(j1);
      mutation(j2);
      ind[j1].EvalLenght(x,y);
      ind[j2].EvalLenght(x,y);

      //crossover
      if(rnd->Rannyu()<Prob_cross){
        crossover(j1,j2,j);
      }else{
        ind_new[j].copy(ind[j1]);
        ind_new[N_pop-1-j].copy(ind[j2]);
      }
      ind[j1].copy(i1);
      ind[j2].copy(i2);
    }

    //update generation and order
    for(int k=0;k<N_pop;k++)
      ind[k].copy(ind_new[k]);
    sort(ind.begin(),ind.end());

    //making iteration averages
    averages();

    //save best path at iteration i
    best_path.push_back(ind[0].GetLenght());


}

void Population :: averages(){
  double sum=0,sum2=0;
  for(int i=0;i<N_pop/2;i++){
    sum+=ind[i].GetLenght();
    sum2+=ind[i].GetLenght()*ind[i].GetLenght();
  }
  //err.push_back(error(sum,sum2,N_pop/2));
  ave.push_back(sum/(N_pop/2.));
}

double Population :: error(double av,double av2,int n){
  return sqrt(abs((av2-av*av))/(double)n);
}

void Population :: printresult(int node){

  if(node==0){
    char *filename,*filename1;
    filename=(char *)"IterationAve0.dat";
    print(filename,ave);
    filename1=(char *)"BestPathC0.dat";
    print(filename1,best_path);
  }

  if(node==1){
    char *filename,*filename1;
    filename=(char *)"IterationAve1.dat";
    print(filename,ave);
    filename1=(char *)"BestPathC1.dat";
    print(filename1,best_path);
  }

  if(node==2){
    char *filename,*filename1;
    filename=(char *)"IterationAve2.dat";
    print(filename,ave);
    filename1=(char *)"BestPathC2.dat";
    print(filename1,best_path);
  }

  if(node==3){
    char *filename,*filename1;
    filename=(char *)"IterationAve3.dat";
    print(filename,ave);
    filename1=(char *)"BestPathC3.dat";
    print(filename1,best_path);
  }


}

void Population :: printpath(int node){

  if(node==0){
    char* filename;
    filename=(char *)"pathS0.dat";
    ofstream fout(filename);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<N_city; i++)
    fout <<ind[0].GetCity(i)<<"\t"<<x[ind[0].GetCity(i)-1]<<"\t"<<y[ind[0].GetCity(i)-1]<<endl;
  }

  if(node==1){
    char* filename;
    filename=(char *)"pathS1.dat";
    ofstream fout(filename);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<N_city; i++)
    fout <<ind[0].GetCity(i)<<"\t"<<x[ind[0].GetCity(i)-1]<<"\t"<<y[ind[0].GetCity(i)-1]<<endl;
  }

  if(node==2){
    char* filename;
    filename=(char *)"pathS2.dat";
    ofstream fout(filename);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<N_city; i++)
    fout <<ind[0].GetCity(i)<<"\t"<<x[ind[0].GetCity(i)-1]<<"\t"<<y[ind[0].GetCity(i)-1]<<endl;
  }

  if(node==3){
    char* filename;
    filename=(char *)"pathS3.dat";
    ofstream fout(filename);
  if(!fout) {
    cout<<"cannot open output_file"<<endl;
    exit(0);
     }
  for (int i=0; i<N_city; i++)
    fout <<ind[0].GetCity(i)<<"\t"<<x[ind[0].GetCity(i)-1]<<"\t"<<y[ind[0].GetCity(i)-1]<<endl;
  }


}

int Population :: select(){
  int i;
  double r=rnd->Rannyu();
  i=(int)(N_pop*pow(r,P_exp));
  return i;
}
