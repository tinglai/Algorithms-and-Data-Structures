#include "optTSP.h"
#include "fastTSP.h"
#include "mst.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

void OptTSP::readin(/*clock_t& s*/){
	cin >> lx >> ly >> rx >> ry >> M;
	if(lx >= rx || ly >= ry){
		cerr << "error in boundary coordinates\n";
		exit(1);
	}
	x.resize(M);
	y.resize(M);
	int t = 0;
	int xin, yin;
	while(true){
		cin >> xin >> yin;
		if(cin.fail() == true) break;
		x[t] = xin;
		y[t] = yin;
		t++;
	}//while
}

void OptTSP::findRoute(unsigned int latestIdx, double& lowerBound, double& currDistance){
	if(route.size() == M){
		//if(currDistance + distance(route.back(), 0) < totalDistance){
		if(currDistance + D[route.back() * M] < totalDistance){
			//totalDistance = currDistance + distance(route.back(), 0);
			totalDistance = currDistance + D[route.back() * M];
			optRoute.assign(route.begin(), route.end());
			upperBound = totalDistance;
		}
	}
	for(unsigned int j = 0; j < M - 1; j++){
		unsigned int candidate = neighbors[latestIdx * (M - 1) + j];
		if(K[candidate] == false) continue;
		double tempLowerBound;
		//tempLowerBound = lowerBound - distance(latestIdx, neighbors[latestIdx * (M - 1)])
		tempLowerBound = lowerBound - D[latestIdx * M + neighbors[latestIdx * (M - 1)]]
				    - D[candidate * M + neighbors[candidate * (M - 1) + 1]] 
				    + 2 * D[latestIdx * M + candidate];
		if(tempLowerBound >= 2 * upperBound){
			continue;
		}
		//if(currDistance + distance(candidate, 0) >= upperBound)
		if(currDistance + D[candidate * M] >= upperBound)
			continue;
		//double tempCurrDistance = currDistance + distance(candidate, route.back());
		route.push_back(candidate);
		K[candidate] = false;//now K[i] being false means i is in the route;
		//findRoute(candidate, tempLowerBound, tempCurrDistance);
		//currDistance += distance(candidate, *(route.end() - 2));
		currDistance += D[candidate * M + *(route.end() - 2)];
		findRoute(candidate, tempLowerBound, currDistance);
		//currDistance -= distance(candidate, *(route.end() - 2));
		currDistance -= D[candidate * M + *(route.end() - 2)];
		route.pop_back();
		K[candidate] = true;
	}
}

void OptTSP::build(){
	findBound();//find initial upper bound
	totalDistance = upperBound;
	currDistance = 0;
	route.push_back(0);

	K[0] = false;
	findRoute(0, lowerBound, currDistance);
	stringstream ss;
	ss << setprecision(2);
	ss << fixed;
	ss << totalDistance << '\n';
	ss << optRoute[0];
	for(unsigned int i = 1; i < M; i++){
		ss << ' ' << optRoute[i];
	}
	ss << '\n';
	cout << ss.str();
}

void OptTSP::findBound(){
	if(M > 20)
		num = 20;
	else
		num = M - 1;
	start = clock();
	prev.resize(M);
	next.resize(M);
	unsigned int leastIdx = 0; //index of verticle with the lowest distance from latestIdx
	unsigned int latestIdx = 0;
	neighbors.resize(M * M - M);
	D.resize(M * M, 0);
	//vector<double> D(M, -1);//distance of current j to current i
	K.resize(M, false);
	K[0] = true;
	unsigned int count;

	for(unsigned int i = 0; i < M; i++){
		count = 0;
		double leastDis = -1;
		for(unsigned int j = 0; j < M; j++){
			if(j == latestIdx) continue;
			D[latestIdx * (M) + j] = distance(latestIdx, j);
			if(K[j] == false){
				//if(isLess(D[latestIdx * (M - 1) + count], leastDis)){
				if(isLess(D[j], leastDis)){
					leastDis = D[latestIdx * (M) + j]; 
					leastIdx = j;
				}
			}
			neighbors[latestIdx * (M - 1) + count] = j;
			count++;
		}
		vector <double> tempD(D.begin() + latestIdx * M, D.end() + latestIdx * M + M);
		CompIndex comp(tempD);
		sort(neighbors.begin() + latestIdx * (M - 1), 
			neighbors.begin() + latestIdx * (M - 1) + M - 1,
			comp);

		if(leastDis != -1){
			K[leastIdx] = true;
			next[latestIdx] = leastIdx;
			prev[leastIdx] = latestIdx;
		}
		else{
			K[latestIdx] = true;
			next[latestIdx] = 0;
			prev[0] = latestIdx;
		}
		latestIdx = leastIdx;
	}
	opt();
	unsigned int currIdx = 0;
	optRoute.resize(M);
	for(unsigned int i = 0; i < M; i++){
		//lowerBound += distance(neighbors[currIdx * (M - 1)], currIdx)
		lowerBound += D[neighbors[currIdx * (M - 1)] * M + currIdx]
				 + D[neighbors[currIdx * (M - 1) + 1] * M + currIdx];
		//upperBound += distance(currIdx, next[currIdx]);
		upperBound += D[currIdx * M + next[currIdx]];
		optRoute[i] = currIdx;
		currIdx = next[currIdx];
	}
	swap(neighbors[1], neighbors[0]);
}//func

void OptTSP::opt(){
	//clock_t start = clock();
	//double duration = 0;
	unsigned int bestToSwap1 = 0;
	unsigned int bestToSwap2 = 0;
	//unsigned int currIdx = 0;
	//unsigned int currIdx = 0;
	unsigned int latest;
	double mostReducedDis = 0;
	//unsigned int count = 0;
//if(M > 10000) return;
while(true){
	latest = 0;
	mostReducedDis = 0;
	for(unsigned int i = 0; i < M; i++){
		for(unsigned int j = 0; j < num; j++){
			unsigned candidate = neighbors[(M - 1) * latest + j];
			if(candidate == next[latest] || candidate == prev[latest])
				continue;
			else{
				//double ad = distance(latest, next[latest]);
				double ad = D[latest * M + next[latest]];
					//thinking a rectangle abcd, starting from downleft, couter-clock
					//here route[i] denotes the points of a
					//nearestNeighbors[num*j+1] denotes the points of c
				//double ac = distance(latest, candidate);
				double ac = D[latest * M + candidate];
				//double bd = distance(next[candidate], next[latest]);
				double bd = D[next[candidate] * M + next[latest]];
				//double bc = distance(next[candidate], candidate);
				double bc = D[next[candidate] * M + candidate];
				if(ad < ac) break;
				if(ad + bc - ac - bd > mostReducedDis){
					mostReducedDis = ad + bc - ac - bd;
					bestToSwap1 = latest;
					bestToSwap2 = candidate;
				}
			}
		}//inner for loop
		latest = next[latest];
	}//outer for loop
	if(mostReducedDis > 0.0000001){
		flip(bestToSwap1, bestToSwap2);
		//count++;
		//if(M * count >= 50000){
		//	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		//	count = 0;
		//}
		//if(duration > 5.6) break;
	}
	else break;
}//whlie

	//duration = (start - clock()) / (double)CLOCKS_PER_SEC;
	//if(duration > 10) return;
	//if time permits, go on to do 3-opt
	//else{
	while(true){
		double mostReducedDis = 0;
		double bestToSwap1 = 0;
		double bestToSwap2 = 0;
		bool isVersion1 = true;
		for(unsigned int i = 0; i < M; i++){
			for(unsigned int j = 0; j < num; j++){
				//thinking a six sides convex thing (Liu Bian Xing), couter-clock
				//i.e ABCDEF, where A is the starting point, i
				unsigned int F = prev[i];
				//unsigned int F = t;
				unsigned int E = prev[F];
				unsigned int DD = neighbors[(M - 1) * i + j];
				unsigned int C = prev[DD];
				unsigned int B = next[i];
				if(B == C || B == DD || B == E || B == F
				     || C == E || C == F || DD == E || DD == F)
					continue;
				else{
					//***version 1***
					//double AB = distance(i, B);
					double AB = D[i * M + B];
					//double CD = distance(C, DD);
					double CD = D[C * M + DD];
					//double EF = distance(E, F);
					double EF = D[E * M + F];
					//double AD = distance(i, DD);
					double AD = D[i * M + DD];
					//double BE = distance(B, E);
					double BE = D[B * M + E];
					//double CF = distance(C, F);
					double CF = D[C * M + F];
					if(AB + CD + EF - AD - BE - CF > mostReducedDis){
						mostReducedDis = AB + CD + EF - AD - BE - CF;
						bestToSwap1 = i;
						bestToSwap2 = DD;
						isVersion1 = true;
					}
					//***version 2***
					//double BF = distance(B, F);
					double BF = D[B * M + F];
					//double CE = distance(C, E);
					double CE = D[C * M + E];
					if(AB + CD + EF - AD - BF - CE > mostReducedDis){
						mostReducedDis = AB + CD + EF - AD - BF - CE;
						bestToSwap1 = i;
						bestToSwap2 = DD;
						isVersion1 = false;
					}
				}
			}//inner for loop
		}//outer for loop
		if(mostReducedDis > 0.000001){
			flip_3opt(bestToSwap1, bestToSwap2, isVersion1);
			//duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			//if(duration > 11) break;
		}
		else break;
	}//while
	//}//else

}//func

void OptTSP::flip(unsigned int currIdx, unsigned int bestToSwap){
	unsigned int t = next[next[currIdx]];
	while(t != bestToSwap){
		swap(next[t], prev[t]);
		t = prev[t];
	}
	unsigned int DD = next[currIdx];
	unsigned int B = next[bestToSwap];
	prev[DD] = next[DD];
	next[DD] = B;
	prev[B] = DD;
	next[currIdx] = bestToSwap;
	next[bestToSwap] = prev[bestToSwap];
	prev[bestToSwap] = currIdx;
}

void OptTSP::flip_3opt(unsigned int A, unsigned int DD, bool isVersion1){
	unsigned int F = prev[A];
	unsigned int E = prev[F];
	unsigned int C = prev[DD];
	unsigned int B = next[A];
	unsigned int t = next[B];

	if(isVersion1 == true){
		next[A] = DD;
		prev[DD] = A;
		next[E] = B;
		prev[B] = E;
		next[C] = F;
		prev[F] = C;
	}
	else{
		int count = 0;
		while(t != C){
			swap(next[t], prev[t]);
			t = prev[t];
			count++;
		}
		prev[B] = next[B];
		next[C] = prev[C];
		next[A] = DD;
		prev[DD] = A;
		next[E] = C;
		prev[C] = E;
		next[B] = F;
		prev[F] = B;
	}
}

double OptTSP::distance(unsigned int index1, unsigned int index2){
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
