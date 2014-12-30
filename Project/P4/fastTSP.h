#ifndef GUARD_fastTSP_h
#define GUARD_fastTSP_h

#include "config.h"
#include "mst.h"
#include <iostream>
#include <vector>

void fastTSP(Config&);

class CompIndex{
public:
	std::vector<double>* dis;
	CompIndex(std::vector<double>& D): dis(&D) {}
	bool operator()(const unsigned int& a, const unsigned int& b){
		return isLess((*dis)[a], (*dis)[b]);
	}
}; 

class FastTSP{
public:
	void build();
	void readin(/*std::istream&*/);

	unsigned int M;
	int lx, ly, rx, ry;
	std::vector<int> x;
	std::vector<int> y;
private:
	double distance(unsigned int, unsigned int);
	void opt();
	void flip(unsigned int, unsigned int);
	void flip_3opt(unsigned int, unsigned int, bool);

	std::vector<bool> K;
	std::vector<double> D;
	std::vector<unsigned int> prev;
	std::vector<unsigned int> next;
	unsigned int num = 5; //extream numbers
	clock_t start;
	//std::vector<unsigned int> route;
	//std::vector<unsigned int> position;//records the positions of those vertices in the route vector
					   //like the dual space of route, or inverse
	std::vector<unsigned int> nearestNeighbors;
};


#endif
