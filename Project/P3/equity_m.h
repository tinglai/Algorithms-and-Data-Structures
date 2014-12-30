#ifndef GUARD_equity_m_h
#define GUARD_equity_m_h

#include <queue>
#include <set>
#include "equity.h"
#include <iostream>
#include "order.h"

class Equity_m: public Equity{
public:
	typedef std::multiset<long long>::iterator
	   mIterator;
	Equity_m(){
		//timestamp1 = -2;
		//timestamp2 = -2;
	}
	Equity_m(Order* nextOrder){
		//timestamp1 = -2;
		//timestamp2 = -2;
		if(nextOrder){
			name = nextOrder->equity;
		}
	}

	virtual Order* trade();
	virtual long long getMedian();
	virtual ~Equity_m(){}
	virtual void findOpt(long long&, long long&){}
	virtual void findTTT(Order*&){}

public:
	void calMedian(long long&);//relocate median after insertion
};

#endif
