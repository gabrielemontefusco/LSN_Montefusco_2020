#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "random.h"


//generic variable useful not only for the main
std::vector<double> x_c,y_c,x_s,y_s; //_c means circle's coordinates while _s square coordinates
int N_city,N_pop;
double r,l;
Random *rnd=new Random();
