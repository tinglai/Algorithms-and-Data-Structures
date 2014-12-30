#ifndef GUARD_mst_h
#define GUARD_mst_h

#include <vector>

bool isLess(double&, double&);//if the first int less than the second

class MST{
public:
	void build();
	void readin(/*std::istream&*/);

	unsigned int M;
	int lx, ly, rx, ry;
	std::vector<int> x;
	std::vector<int> y;
private:
	int classify(unsigned int);
	double distance(unsigned int, unsigned int);
	std::vector<bool> K;
	std::vector<double> D;
	std::vector<unsigned int> P;
};

#endif
