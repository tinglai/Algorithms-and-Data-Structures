#include "equity.h"
#include "equity_ttt.h"
#include "order.h"
#include <iostream>
#include <climits>
#include <map>
#include <set>

using namespace std;

Order* Equity_ttt::trade(){
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

void Equity_ttt::findTTT(Order*& nextOrder){
	if(nextOrder->isBuy == false){
		if(bestBuyTime == -1){
			bestBuyPrice = nextOrder->price;
			bestBuyTime = nextOrder->time;
			lowestBuyPrice = nextOrder->price;
			lowestBuyTime = nextOrder->time;
		}
		else{
			if(nextOrder->price < lowestBuyPrice){
				lowestBuyPrice = nextOrder->price;
				lowestBuyTime = nextOrder->time;
				if(bestSellTime == -1){
					bestBuyPrice = nextOrder->price;
					bestBuyTime = nextOrder->time;
				}
			}
		}
	}
	else{
		if(bestBuyTime == -1){
			return;
		}
		else{
			if(bestSellTime == -1){
				bestSellPrice = nextOrder->price;
				bestSellTime = nextOrder->time;
			}
			else{
				if((nextOrder->price - lowestBuyPrice) > 
		           	     (bestSellPrice - bestBuyPrice)){
					bestSellPrice = nextOrder->price;
					bestBuyPrice = lowestBuyPrice;
					bestSellTime = nextOrder->time;
					bestBuyTime = lowestBuyTime;
				}
			}
		}
	}
}//func

void Equity_ttt::getTTT(long long& timestamp1,
			      long long& timestamp2){
	if(bestSellTime == -1){
		timestamp1 = -1;
		timestamp2 = -1;
	}
	else{
		timestamp1 = bestBuyTime;
		timestamp2 = bestSellTime;
	}
}

