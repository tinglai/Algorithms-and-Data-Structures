#include "fastTSP.h"
#include "config.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "mst.h"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

void FastTSP::readin(/*istream& in*/){
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

void FastTSP::build(){
	start = clock();
	if(num >= M) num = M;
	prev.resize(M);
	next.resize(M);
	unsigned int leastIdx = 0; //index of verticle with the lowest distance from latestIdx
	unsigned int latestIdx = 0;
	nearestNeighbors.resize(num * M);
	D.resize(M, -1);//distance of current j to current i
	K.resize(M, false);
	K[0] = true;
	for(unsigned int i = 0; i < M; i++){
		double leastDis = -1;
		unsigned int count = 0;
		for(unsigned int j = 0; j < M; j++){
			if(j == latestIdx) continue;
			D[j] = distance(latestIdx, j);
			CompIndex comp(D);
			if (count < num){
				nearestNeighbors[num * latestIdx + count] = j;
				push_heap(nearestNeighbors.begin() + num * latestIdx,
					     nearestNeighbors.begin() + num * latestIdx + count, comp);
				count++;
			}
			else if(isLess(D[j], D[nearestNeighbors[num * latestIdx]])){
				pop_heap(nearestNeighbors.begin() + num * latestIdx, 
					     nearestNeighbors.begin() + num * latestIdx + num, comp);
				nearestNeighbors[num * latestIdx + num - 1] = j;
				push_heap(nearestNeighbors.begin() + num * latestIdx, 
					     nearestNeighbors.begin() + num * latestIdx + num, comp);
			}
			if(K[j] == false && isLess(D[j], leastDis)){
				leastDis = D[j]; 
				leastIdx = j;
			}
		}//inner for loop
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
		latestIdx = next[latestIdx];
	}//for
/*
else{
	K.resize(M, false);
	K[0] = true;
	for(unsigned int i = 0; i < M; i++){
		double leastDis = -1;
		for(unsigned int j = 0; j < M; j++){
			if(j == latestIdx) continue;
			if(K[j] == true) continue;
			double d = distance(latestIdx, j);
			if(isLess(d, leastDis)){
				leastDis = d; 
				leastIdx = j;
			}
		}
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
	latestIdx = next[latestIdx];
double duration = (clock() - start) / double(CLOCKS_PER_SEC);
	}//for
}//else
*/	
	opt();
	unsigned int currIdx = 0;
	stringstream ss;
	double totalDistance = 0;
	for(unsigned int i = 0; i < M; i++){
		totalDistance += distance(currIdx, next[currIdx]);
		ss << currIdx;
		if(i != M-1)
			ss << ' ';
		currIdx = next[currIdx];
	}
	cout << totalDistance << '\n' << ss.str() << '\n';
}
/*
void FastTSP::opt(){
	clock_t start = clock();
	double duration;
	unsigned int bestToSwap1 = 0;
	unsigned int bestToSwap2 = 0;
	//unsigned int currIdx = 0;
	//unsigned int currIdx = 0;
	unsigned int latest;
	double mostReducedDis = 0;
	unsigned int count = 0;
while(true){
	latest = 0;
	mostReducedDis = 0;
	K.assign(M, 0);
	for(unsigned int i = 0; i < M; i++){
		K[latest] = true;//meaing those pairs with A = latest have been checked
		unsigned candidate = next[next[latest]];
		for(unsigned int j = 0; j < M; j++){
			if(K[candidate] == true) continue;
			else if(candidate == latest || candidate == next[latest] || candidate == prev[latest])
				continue;
			else{
				double ad = distance(latest, next[latest]);
					//thinking a rectangle abcd, starting from downleft, couter-clock
					//here route[i] denotes the points of a
					//nearestNeighbors[num*j+1] denotes the points of c
				double ac = distance(latest, candidate);
				double bd = distance(next[candidate], next[latest]);
				double bc = distance(next[candidate], candidate);
				if(ad < ac) continue;
				if(ad + bc - ac - bd > mostReducedDis){
					mostReducedDis = ad + bc - ac - bd;
					bestToSwap1 = latest;
					bestToSwap2 = candidate;
				}
			}
			candidate = next[candidate];
		}//inner for loop
		latest = next[latest];
	}//outer for loop
	count++;
	if(mostReducedDis > 0.0000001){
		flip(bestToSwap1, bestToSwap2);
		if(5000 * count > M){
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			if(duration > 11) break;
		}
	}
	else break;
}//whlie
}
*/

void FastTSP::opt(){
	double duration = 0;
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
			unsigned candidate = nearestNeighbors[num * latest + j];
			if(candidate == next[latest] || candidate == prev[latest])
				continue;
			else{
				double ad = distance(latest, next[latest]);
					//thinking a rectangle abcd, starting from downleft, couter-clock
					//here route[i] denotes the points of a
					//nearestNeighbors[num*j+1] denotes the points of c
				double ac = distance(latest, candidate);
				double bd = distance(next[candidate], next[latest]);
				double bc = distance(next[candidate], candidate);
				//if(ad < ac) continue;
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
		//if(M * count >= 5000){
		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		if(duration > 12) break;
			//count = 0;
		//}
	}
	else break;
}//whlie
	duration = (start - clock()) / (double)CLOCKS_PER_SEC;
	if(duration > 12) return;
	//if time permits, go on to do 3-opt
	else{
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
				unsigned int D = nearestNeighbors[num * i + j];
				unsigned int C = prev[D];
				unsigned int B = next[i];
				if(B == C || B == D || B == E || B == F
				     || C == E || C == F || D == E || D == F)
					continue;
				else{
					//***version 1***
					double AB = distance(i, B);
					double CD = distance(C, D);
					double EF = distance(E, F);
					double AD = distance(i, D);
					double BE = distance(B, E);
					double CF = distance(C, F);
					if(AB + CD + EF - AD - BE - CF > mostReducedDis){
						mostReducedDis = AB + CD + EF - AD - BE - CF;
						bestToSwap1 = i;
						bestToSwap2 = D;
						isVersion1 = true;
					}
					//***version 2***
					double BF = distance(B, F);
					double CE = distance(C, E);
					if(AB + CD + EF - AD - BF - CE > mostReducedDis){
						mostReducedDis = AB + CD + EF - AD - BF - CE;
						bestToSwap1 = i;
						bestToSwap2 = D;
						isVersion1 = false;
					}
				}
			}//inner for loop
		}//outer for loop
		if(mostReducedDis > 0.000001){
			flip_3opt(bestToSwap1, bestToSwap2, isVersion1);
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			if(duration > 12) break;
		}
		else break;
	}//while
	}//else
}//func

void FastTSP::flip(unsigned int currIdx, unsigned int bestToSwap){
	unsigned int t = next[next[currIdx]];
	while(t != bestToSwap){
		swap(next[t], prev[t]);
		t = prev[t];
	}
	unsigned int D = next[currIdx];
	unsigned int B = next[bestToSwap];
	prev[D] = next[D];
	next[D] = B;
	prev[B] = D;
	next[currIdx] = bestToSwap;
	next[bestToSwap] = prev[bestToSwap];
	prev[bestToSwap] = currIdx;
}

void FastTSP::flip_3opt(unsigned int A, unsigned int D, bool isVersion1){
	unsigned int F = prev[A];
	unsigned int E = prev[F];
	unsigned int C = prev[D];
	unsigned int B = next[A];
	unsigned int t = next[B];

	if(isVersion1 == true){
		next[A] = D;
		prev[D] = A;
		next[E] = B;
		prev[B] = E;
		next[C] = F;
		prev[F] = C;
	}
	else{
		while(t != C){
			swap(next[t], prev[t]);
			t = prev[t];
		}
		prev[B] = next[B];
		next[C] = prev[C];
		next[A] = D;
		prev[D] = A;
		next[E] = C;
		prev[C] = E;
		next[B] = F;
		prev[F] = B;
	}
}

double FastTSP::distance(unsigned int index1, unsigned int index2){
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
