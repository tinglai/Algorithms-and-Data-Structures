#include "equity.h"
#include "order.h"
#include <iostream>

using namespace std;

Order* Equity::trade(){
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
		return buyTop;
	}
	else{
		buyTop->quant -= sellTop->quant;
		counterparty = buyTop->client;
		//counterparty = buyTop;
		if(buyTop->ID < sellTop->ID){
			sellTop->price = buyTop->price;
		}
		pop_heap(sellOrders.begin(), sellOrders.end(), Comp<Order*>(0));
		sellOrders.pop_back();
		pop_heap(buyOrders.begin(), buyOrders.end(), Comp<Order*>(1));
		buyOrders.pop_back();
		delete buyTop;
		buyTop = nullptr;
		return sellTop;
	}
}//trade


void Equity::insert(Order*& next){
	if(next->isBuy == 1){
		buyOrders.push_back(next);
		push_heap(buyOrders.begin(), buyOrders.end(), Comp<Order*>(1));
	}
	else{
		sellOrders.push_back(next);
		push_heap(sellOrders.begin(), sellOrders.end(), Comp<Order*>(0));
	}
}

void Equity::clean(){
	bookType::iterator temp = buyOrders.begin();
	while(temp != buyOrders.end()){
		delete *temp;
		*temp = nullptr;
		temp++;
	}
	temp = sellOrders.begin();
	while(temp != sellOrders.end()){
		delete *temp;
		*temp = nullptr;
		temp++;
	}
}
