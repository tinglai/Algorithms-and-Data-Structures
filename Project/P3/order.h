#ifndef GUARD_order_h
#define GUARD_order_h

#include <string>
//#include <iostream>

struct Order{
	long long time;
	std::string client;
	bool isBuy;
	std::string equity;
	long long price;
	long long quant;
	long long ID;
	

	Order(long long& t, std::string& c, bool b, std::string& e,
	      long long& p, long long& q, long long& id):
	      time(t), client(c), isBuy(b), equity(e), price(p),
	      quant(q), ID(id){}
	Order(){}
	Order(Order* in, long long& strike){
		time = in->time;
		client = in->client;
		isBuy = in->isBuy;
		equity = in->equity;
		price = strike;
		quant = in->quant;
		ID = in->ID;
	}
/*	Order(Order* in){
		time = in->time;
		client = in->client;
		isBuy = in->isBuy;
		equity = in->equity;
		price = in->price;
		quant = in->quant;
		ID = in->ID;
	}
*/
};

#endif

