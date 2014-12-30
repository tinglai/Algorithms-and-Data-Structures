#include "source_PR.h"
#include <random>
#include "order.h"
#include <iostream>
#include <string>

using namespace std;

Source_PR::Source_PR(){
	gen = nullptr;
	clients = nullptr;
	equities = nullptr;
	arrivals = nullptr;
	price = nullptr;
	quantity = nullptr;
}

void Source_PR::setup(istream& in){
	string temp;
	in >> temp >> random_seed;
	in >> temp >> orderNum;
	in >> temp >> last_c;
	in >> temp >> last_e;
	in >> temp >> arr_rate;

	gen = new mt19937(random_seed);
	clients = new uniform_int_distribution<char>('a', last_c);
	equities = new uniform_int_distribution<char>('A', last_e);
	arrivals = new exponential_distribution<>(arr_rate);
	price = new uniform_int_distribution<>(2, 11);
	quantity = new uniform_int_distribution<>(1, 30);
}

Order* Source_PR::nextOrder(){
	if(empty())
		return nullptr;

	Order* next = new Order;
	next->time = genTime;
	genTime += (long long)((*arrivals)(*gen) + 0.5);
	next->client = "C_";
	next->client += (*clients)(*gen);
	next->isBuy = buy_or_sell(*gen);
	next->equity = "E_";
	next->equity += (*equities)(*gen);
	next->price = 5 * (*price)(*gen);
	next->quant = (*quantity)(*gen);
	next->ID = IDcount;
	IDcount++;
	orderNum--;

	return next;
}

bool Source_PR::empty(){
	return(orderNum == 0);
}

Source_PR::~Source_PR(){
	delete gen;
	delete clients;
	delete equities;
	delete arrivals;
	delete price;
	delete quantity;
}

