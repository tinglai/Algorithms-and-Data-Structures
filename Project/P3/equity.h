#ifndef GUARD_equity_h
#define GUARD_equity_h

#include <algorithm>
#include <iostream>
#include <string>
#include "order.h"
#include <set>
#include <queue>
#include <vector>
#include <functional>

template <typename T>
struct Comp{
	bool i;

	Comp():i(0){}
	Comp(const bool& i):i(i){}
	bool operator()(const T& a, const T& b) const{
		if(i== true){
			if(a->price < b->price)
				return 1;
			else if(a->price == b->price)
				return a->ID > b->ID;
			else
				return 0;
		}
		else{
			if(a->price > b->price)
				return 1;
			else if(a->price == b->price)
				return a->ID > b->ID;
			else
				return 0;
		}
	}
};

template <typename T>
struct CompOrder{
	bool operator() (const T& a, const T& b) const{
		if(a->price < b->price){
			return 1;
		}
		/*else if (a->price == b->price){
			if(a->ID < b->ID)
				return 1;
			else
				return 0;
		}*/
		else
			return 0;
	}
};


template <typename T>
struct Comp_ttt{//specially for 
	bool i;

	Comp_ttt():i(0){}
	Comp_ttt(const bool& i):i(i){}
	bool operator()(const T& a, const T& b) const{
		if(i== true){
			if(a->price < b->price)
				return 1;
			else if(a->price == b->price)
				return a->ID < b->ID;
			else
				return 0;
		}
		else{
			if(a->price > b->price)
				return 1;
			else if(a->price == b->price)
				return a->ID < b->ID;
			else
				return 0;
		}
	}
};


class Equity{
public:
	//typedef std::priority_queue<Order*, std::vector<Order*>, Comp<Order*>>
	typedef std::vector<Order*> bookType;
	typedef long long priceType;
	typedef std::multiset<long long>::iterator
	   mIterator;
//data	
	std::string name;
	//Order* counterparty = nullptr;
	std::string counterparty;
	bookType buyOrders;
	bookType sellOrders;
	//long long median = 0;
	std::priority_queue<long long, std::vector<long long>,
			       std::less_equal<long long>> smallHalf;
	std::priority_queue<long long, std::vector<long long>, 
			       std::greater_equal<long long>> bigHalf;
	//std::multiset<long long> sold_prices;
	//std::multiset<long long>::iterator loc_m = sold_prices.begin();
	//long long timestamp1, timestamp2;
	
//functions

	//trade() returns the order that traded in one single match;
	virtual Order* trade();
	virtual long long getMedian(){return 0;}
	void insert(Order*&);//insert new order
	virtual void getTTT(long long&, long long&){}
	virtual void findTTT(Order*&){}
	Equity(){
		//timestamp1 = -2;
		//timestamp2 = -2;
	}
	Equity(Order* nextOrder){
		//timestamp1 = -2;
		//timestamp2 = -2;
		if(nextOrder){
			name = nextOrder->equity;
		}
	}
	virtual void clean();
	virtual ~Equity(){}
};
#endif
