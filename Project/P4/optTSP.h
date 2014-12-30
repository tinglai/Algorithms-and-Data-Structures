#ifndef GUARD_optTSP_h
#define GUARD_optTSP_h

#include <vector>
#include <ctime>


class OptTSP{
public:
	void build();
	void readin(/*clock_t&*/);

	unsigned int M;
	int lx, ly, rx, ry;
	std::vector<int> x;
	std::vector<int> y;

private:
	double distance(unsigned int, unsigned int);
	void findBound();
	void findRoute(unsigned int, double&, double&);
	void opt();
	void flip(unsigned int, unsigned int);
	void flip_3opt(unsigned int, unsigned int, bool);

	std::vector<bool> K;
	std::vector<double> D;//distance of current j to current i
	std::vector<unsigned int> prev;
	std::vector<unsigned int> next;
	std::vector<unsigned int> route;
	std::vector<unsigned int> optRoute;
	std::vector<unsigned int> neighbors;
	unsigned int num; //extream numbers
	double upperBound = 0;
	double lowerBound = 0;//is initially the sum of lowestDis divided by 2
	int numC = 1;
	double totalDistance;
	double currDistance;
	clock_t start;
};

#endif
