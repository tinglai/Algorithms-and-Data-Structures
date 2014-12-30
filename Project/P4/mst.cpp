#include "mst.h"
#include <vector>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

bool isLess(double& dis1, double& dis2){
	if(dis1 == -1)
		return false;
	else if(dis2 == -1)
		return true;
	else
		return dis1 < dis2;
}

void MST::readin(/*istream& in*/){
	cin >> lx >> ly >> rx >> ry >> M;
	if(lx >= rx || ly >= ry){
		cerr << "error in boundary coordinates\n";
		exit(1);
	}
	x.resize(M);
	y.resize(M);
	int t = 0;
	while(true){
		cin >> x[t] >> y[t];
		if(cin.fail() == true) break;
		t++;
	}//while
}

void MST::build(){
	K.resize(M, false);
	D.resize(M, -1);
	P.resize(M);
	K[0] = true;
	D[0] = 0.0;
	unsigned int latestIdx = 0;//latest index enters the MST
	unsigned int leastIdx = 0;
	for(unsigned int j = 1; j < D.size(); j++){
		double leastDis = -1;
		for(unsigned int i = 1; i < D.size(); i++){
			if(K[i] == false){
				double tempDis = distance(latestIdx, i);
				if(isLess(tempDis, D[i])){
					D[i] = tempDis;
					P[i] = latestIdx;
				}
				if(isLess(D[i], leastDis)){
					leastDis = D[i];
					leastIdx = i;
				}
			}//outer if
		}//for
		if(leastDis == -1){
			cerr << "Cannot construct MST";
			exit(1);
		}
		K[leastIdx] = true;
		latestIdx = leastIdx;
	}//for
	stringstream ss;
	double totalDis = 0;
	for(unsigned int i = 1; i < D.size(); i++){
		if(i < P[i]){
			ss << '\n' << i << ' ' << P[i];
		}
		else{
			ss << '\n' << P[i] << ' ' << i;
		}
		totalDis += D[i];
	}
	cout << totalDis << ss.str() << endl;
}//void

int MST::classify(unsigned int index){
	if(x[index] < lx 
	      || y[index] < ly
	      || x[index] > rx
	      || y[index] > ry)
		return -1;//outside the boundary
	else if(x[index] > lx 
	      && y[index] > ly
	      && x[index] < rx
	      && y[index] < ry)
		return 1;//inside the boundary
	else
		return 0;//at the boundary
}

double MST::distance(unsigned int index1, unsigned int index2){
	if(classify(index1) * classify(index2) == -1){
		return -1;
	}
	else{
		return sqrt(
			  (double(x[index1]) 
			  - double(x[index2]))
			  * (double(x[index1]) 
			  - double(x[index2]))
			  +
			  (double(y[index1]) 
			  - double(y[index2]))
			  * (double(y[index1]) 
			  - double(y[index2]))
			);
	}
	return -1;
}
