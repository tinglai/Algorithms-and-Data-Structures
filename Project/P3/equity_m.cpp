#include "equity.h"
#include "equity_m.h"
#include <iostream>
#include <set>

using namespace std;

Order* Equity_m::trade(){
	if(buyOrders.empty() || sellOrders.empty())
		return nullptr;

	Order* buyTop = buyOrders.front();
	Order* sellTop = sellOrders.front();
	if(buyTop->price < sellTop->price) 
		return nullptr;
	if (buyTop->quant > sellTop->quant){
		buyTop->quant -= sellTop->quant;
		counterparty = buyTop->client;
		//counterparty = buyTop;
		if(buyTop->ID < sellTop->ID){
			sellTop->price = buyTop->price;
		}
		pop_heap(sellOrders.begin(), sellOrders.end(), Comp<Order*>(0));
		sellOrders.pop_back();
		//sold_prices.insert(sellTop->price);
		calMedian(sellTop->price);
		return sellTop;
	}
	else if(buyTop->quant < sellTop->quant){
		sellTop->quant -= buyTop->quant;
		counterparty = sellTop->client;
		//counterparty = sellTop;
		if(buyTop->ID > sellTop->ID){
			buyTop->price = sellTop->price;
		}
		pop_heap(buyOrders.begin(), buyOrders.end(), Comp<Order*>(1));
		buyOrders.pop_back();
		//sold_prices.insert(buyTop->price);
		calMedian(buyTop->price);
		return buyTop;
	}
	else{
		buyTop->quant -= sellTop->quant;
		counterparty = buyTop->client;
		//sellTop->counterparty = buyTop->client;
		if(buyTop->ID < sellTop->ID){
			sellTop->price = buyTop->price;
		}
		pop_heap(sellOrders.begin(), sellOrders.end(), Comp<Order*>(0));
		sellOrders.pop_back();
		pop_heap(buyOrders.begin(), buyOrders.end(), Comp<Order*>(1));
		buyOrders.pop_back();
		delete buyTop;
		//sold_prices.insert(sellTop->price);
		calMedian(sellTop->price);
		return sellTop;
	}
}//trade
/*
void Equity_m::calMedian(long long& sold){
	if(sold_prices.size() == 1){
		loc_m = sold_prices.begin();
	}
	else if(sold_prices.size() % 2 == 0){
		if (sold < *loc_m)
			loc_m--; 
	}
	else if(sold_prices.size() % 2 == 1){
		if (sold >= *loc_m)
			loc_m++;
	}
}

long long Equity_m::getMedian(){
	if (sold_prices.size() == 0){
		return 0;
	}
	else if (sold_prices.size() % 2 == 1){
		return *loc_m;
	}
	else{
		mIterator temp = loc_m;
		temp++;
		return (*loc_m+ *temp) / 2;
	}
}
*/
void Equity_m::calMedian(long long& sold){
	if(smallHalf.size() == 0){
		smallHalf.push(sold);
	}
	else{
		if(smallHalf.size() > bigHalf.size()){
			if(smallHalf.top() < sold){
				bigHalf.push(sold);
			}
			else{
				smallHalf.push(sold);
				bigHalf.push(smallHalf.top());
				smallHalf.pop();
			}
		}
		else{
			if(smallHalf.top() < sold){
				bigHalf.push(sold);
				smallHalf.push(bigHalf.top());
				bigHalf.pop();
			}
			else{
				smallHalf.push(sold);
			}
		}
	}
}

long long Equity_m::getMedian(){
	if (smallHalf.empty()){
		return 0;
	}
	if (smallHalf.size() == bigHalf.size()){
		return (smallHalf.top() + bigHalf.top()) / 2;
	}
	else{
		return smallHalf.top();
	}
}
