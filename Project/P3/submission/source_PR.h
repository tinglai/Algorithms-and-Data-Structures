#ifndef GUARD_source_PR_h
#define GUARD_source_PR_h

#include "source.h"
#include "order.h"
#include <iostream>
#include <random>

class Source_PR: public Source{
private:
	int random_seed;
	long long orderNum;
	char last_c;
	char last_e;
	double arr_rate;
	long long genTime = 0;
	std::mt19937* gen;
	std::uniform_int_distribution<char>* clients;
	std::uniform_int_distribution<char>* equities;
	std::exponential_distribution<>* arrivals;
	std::bernoulli_distribution buy_or_sell;
	std::uniform_int_distribution<>* price;
	std::uniform_int_distribution<>* quantity;
public:
	Order* nextOrder();
	void setup(std::istream&);
	bool empty();
	Source_PR();
	~Source_PR();
};

#endif
