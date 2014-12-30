#ifndef GUARD_config_h
#define GUARD_config_h

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include "equity.h"
#include "order.h"
#include "source.h"
#include "client.h"
#include <sstream>

template<typename T>
struct CompEquity{
	bool operator()(const T& a, const T& b) const{
		return a->name < b->name;
	}
};

struct Config{
	bool isS;
	bool isV;
	bool isM;
	bool isT;
	bool isH;
	std::vector<std::string> ttt;
	std::unordered_set<std::string> insiders;
	long long current;
	std::string lastOrder = "";
	long long s_commission = 0;
	long long s_transfer = 0;
	long long s_numOfCompletedTrades = 0;
	long long s_numOfSharesTraded = 0;
	std::stringstream ss;


	Config();
	void setup(const int, char *const*);
	void print_M(std::set<Equity*, CompEquity<Equity*>>&);
	Order* genOrder(std::unordered_map<std::string, Equity*>&,
	   Source*&);
	void update_S(Order*&);
	void print_V(Order*&, Equity*&);
	void update_T(Order*&, 
	   std::unordered_map<std::string, Client_stat*>&, Equity*&);
	Equity* genEquity(std::unordered_map<std::string, Equity*>&, 
	   Order*&);
	void genEquity_ttt(std::unordered_map<std::string, Equity*>&);
};
#endif
