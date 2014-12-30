#ifndef GUARD_equity_ttt_h
#define GUARD_equity_ttt_h

#include <queue>
#include <set>
#include <unordered_map>
#include "equity.h"
#include <iostream>
#include "order.h"
#include <string>
#include <utility>
#include <vector>



class Equity_ttt: public Equity{
public:
	//typedef std::pair<priceType, long long> tradeStat;//ID, time
	typedef std::vector<Order*> bookType;
	typedef std::multiset<long long>::iterator
	   mIterator;

	Equity_ttt(std::string n){
		//timestamp1 = -1;
		//timestamp2 = -1;
		name = n;
		//asks = 
		//   new std::set<Order*, Comp_ttt<Order*>>(Comp_ttt<Order*>(1));// 
		//bids = 
		//   new std::set<Order*, Comp_ttt<Order*>>(Comp_ttt<Order*>(0));//
	}
	virtual Order* trade();
	virtual long long getMedian(){return 0;}
	virtual ~Equity_ttt(){}
	virtual void getTTT(long long&, long long&);
	virtual void findTTT(Order*&);
	
private:
	long long bestBuyTime = -1;
	long long bestBuyPrice = 0;
	long long lowestBuyTime = -1;
	long long lowestBuyPrice = 0;

	long long bestSellTime = -1;
	long long bestSellPrice = 0;

	//std::set<Order*, Comp_ttt<Order*>>* asks;
	//std::set<Order*, Comp_ttt<Order*>>* bids;
	//long long timestamp1, timestamp2;
	//std::vector<Order*> asks;
	//std::vector<Order*> bids;
	//std::vector<Order*> chesh;
	//long long mymax(std::vector<Order*>&, long long&);
};

#endif
