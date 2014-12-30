#include "source_TL.h"
#include <string>
#include "order.h"
#include <iostream>

using namespace std;

void Source_TL::setup(istream& in){
	readin = &in;
}

bool Source_TL::empty(){
	return readin->fail();
}

Order* Source_TL::nextOrder(){
	Order* next = new Order;
	string buyOrSell;
	char temp;
	char temp1;
	string temp2;
	*readin >> next->time >> next->client >> buyOrSell 
		  >> next->equity>> temp >> next->price
		  >> temp1 >> next->quant;
	if(empty()){
		delete next;
		next = nullptr;
		return next;
	}
	if(temp != '$'){
		exit(1);
	}
	if(temp1 != '#'){
		exit(1);
	} 
	if(next->time < 0){
		exit(1);
	}
	if(next->price <= 0){
		exit(1);
	}
	if(next->equity.size() > 5 || next->equity.size() < 1){
		exit(1);
	} 
	if(next->client.find_first_not_of
           ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")
               != string::npos){
		exit(1);
	}
	if(buyOrSell == "BUY")
		next->isBuy = 1;
	else if(buyOrSell == "SELL")
		next->isBuy = 0;
	else{
		exit(1);
	}
	next->ID = IDcount;
	IDcount++;
	return next;
}
