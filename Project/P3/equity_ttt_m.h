#ifndef GUARD_equity_ttt_m_h
#define GUARD_equity_ttt_m_h

#include <queue>
#include <set>
#include <unordered_map>
#include "equity.h"
#include "equity_m.h"
#include "equity_ttt.h"
#include <iostream>
#include "order.h"
#include <string>
#include <utility>

class Equity_ttt_m: public Equity{
public:
	//typedef std::pair<priceType, long long> tradeStat;//ID, time
	typedef std::vector<Order*> bookType;
	typedef std::multiset<long long>::iterator
	   mIterator;

	Equity_ttt_m(std::string n){
		//timestamp1 = -1;
		//timestamp2 = -1;
		name = n;
		//asks = 
		//   new std::set<Order*, Comp_ttt<Order*>>(Comp_ttt<Order*>(1));// 
		//asks = 
		//   new std::vector<Order*>;// 
		//bids = 
		//   new std::set<Order*, Comp_ttt<Order*>>(Comp_ttt<Order*>(0));//
		//bids = 
		//   new std::vector<Order*>;// 
	}
	virtual Order* trade();
	virtual long long getMedian();
	virtual ~Equity_ttt_m(){}
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
	//std::vector<Order*>* asks;
	//std::vector<Order*>* bids;
	//std::vector<Order*> chesh;
	//mIterator loc_m;

	void calMedian(long long&);//relocate median after insertion
	//long long mymax(std::vector<Order*>&, long long&);
};

#endif
