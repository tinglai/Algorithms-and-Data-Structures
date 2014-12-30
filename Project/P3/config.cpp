#include "config.h"
#include "equity.h"
#include "equity_m.h"
#include "equity_ttt.h"
#include "equity_ttt_m.h"
#include <unordered_map>
#include <iostream>
#include <getopt.h>
#include <set>
#include "source.h"
#include "client.h"

using namespace std;

Config::Config(): isS(0), isV(0), isM(0), isT(0), isH(0), current(0) {}

void Config::setup(const int argc, char *const* argv){
	const struct option longopts[] = {
		{"summary", no_argument, 0, 's'},
		{"verbose", no_argument, 0, 'v'},
		{"median", no_argument, 0, 'm'},
		{"help", no_argument, 0, 'h'},
		{"transfers", no_argument, 0, 't'},
		{"insider", required_argument, 0, 'i'},
		{"ttt", required_argument, 0, 'g'}
	};
	int option_index = 0;
	int c = getopt_long(argc, argv, "svmhti:g:", longopts, &option_index);
	while (c != -1)
	{
		switch(c){
			case 'h':
				cout << "help!!!!!!!!!!!!!!!!!!!!!! \n";
				exit(0);
				break;
			case 's':
				if (isS == 0){
					isS = 1;
				}
				else{
					cerr << "More than one S options!\n";
					exit(1);
				}
				break;
			case 'v':
				if (isV == 0){
					isV = 1;
				}
				else{
					cerr << "More than one V options!\n";
					exit(1);
				}
				break;
			case 'm':
				if (isM == 0){
					isM = 1;
				}
				else{
					cerr << "More than one M options!\n";
					exit(1);
				}
				break;
			case 't':
				if (isT == 0){
					isT = 1;
				}
				else{
					cerr << "More than one T options!\n";
					exit(1);
				}
				break;
			case 'i':
				insiders.insert(string(optarg));
				break;
			case 'g':
				ttt.push_back(string(optarg));
				break;
			case '?':
				break;
			default:
				abort();
		}//switch
		c = getopt_long(argc, argv, "svmhti:g:",longopts, &option_index);
	}
}//Config::setup

void Config::print_M(set<Equity*, CompEquity<Equity*>>& m_equities){
	set<Equity*, CompEquity<Equity*>>::iterator i 
					      = m_equities.begin();
	while(i != m_equities.end()){
		ss << "Median match price of " << (*i)->name 
		  << " at time "
		  << current << " is $"
		  << (*i)->getMedian() << '\n';
		i++;
	}//while
}

Order* Config::genOrder(unordered_map<string, Equity*>& equities, 
   Source*& source){
	Order* next = nullptr;
	if(insiders.empty() || /*equities.size() == ttt.size()*/ lastOrder == ""){
		next = source->nextOrder();
	}
	else {
		Equity* temp = equities[lastOrder];
		if(temp->smallHalf.empty() == false  
                             && insiders.count(lastOrder)){
			if(!temp->sellOrders.empty()
			   && (9 * temp->getMedian() > 
				   10 * (temp->sellOrders).front()->price)){
				Order* ask = (temp->sellOrders).front();
				string in = "INSIDER_" + temp->name;
				next = new Order(current, in,
						      true, temp->name, ask->price, 
						      ask->quant,source->IDcount);
				source->IDcount++;
			}
			else if(!temp->buyOrders.empty() 
			        && 10 * ((temp->buyOrders).front()->price)>
				      11 * temp->getMedian()){
				Order* bid = (temp->buyOrders).front();
				string in = "INSIDER_" + temp->name;
				next= new Order(current, in,
						      false, temp->name, bid->price, 
						      bid->quant,source->IDcount);
				source->IDcount++;
			}
			else{
				next = source->nextOrder();
			}
		}//if(temp->median
		else{
			next = source->nextOrder();
		}
	}
	if(next != nullptr){
		lastOrder = next->equity;
	}
	return next;
}

void Config::update_S(Order*& done){
	if(isS){
		s_commission += 
		   ((done->price * done->quant) /100) * 2;
		s_transfer += (done->price * done->quant);
		s_numOfCompletedTrades++;
		s_numOfSharesTraded += done->quant;
	}
}

void Config::print_V(Order*& done, Equity*& newEquity){
	if(isV){
		if(done->isBuy){
			ss << done->client
		  	   << " purchased "	
		  	   << done->quant
		 	   << " shares of "
		  	   << done->equity << " from "
		  	   << newEquity->counterparty<< " for $"
		 	   << done->price << "/share\n";
		}
		else{
			ss << newEquity->counterparty
		  	   << " purchased "	
		  	   << done->quant
		 	   << " shares of "
		  	   << done->equity << " from "
		  	   << done->client << " for $"
		 	   << done->price << "/share\n";
		}
	}
}

void Config::update_T(Order*& done, unordered_map<string, Client_stat*>& tStat,
			 Equity*& newEquity){
	if(isT){
		if(done->isBuy){
			tStat[done->client]->bought += done->quant;
			tStat[done->client]->transfer -= 
			   (done->quant * done->price);
			tStat[newEquity->counterparty]->sold += done->quant;
			tStat[newEquity->counterparty]->transfer += 
			   (done->quant * done->price);
		}
		else{
			tStat[done->client]->sold += done->quant;
			tStat[done->client]->transfer += 
			   (done->quant * done->price);
			tStat[newEquity->counterparty]->bought += done->quant;
			tStat[newEquity->counterparty]->transfer -= 
			   (done->quant * done->price);
		}
	}//if(isT)
}

Equity* Config::genEquity(unordered_map<string, Equity*>& equities, 
   Order*& nextOrder){
	Equity* newEquity = nullptr;
	if(isM 
 	     || (!(insiders.empty()) && insiders.count(nextOrder->equity))){
		newEquity = new Equity_m(nextOrder);
		newEquity->insert(nextOrder);
		equities.emplace(newEquity->name, newEquity);
	}
	else{
		newEquity = new Equity(nextOrder);
		newEquity->insert(nextOrder);
		equities.emplace(newEquity->name, newEquity);
	}
	return newEquity;
}

void Config::genEquity_ttt(unordered_map<string, Equity*>& equities){
	if(ttt.empty()){
		return;
	}
	else{
		if(isM == true){
			for(unsigned long long i = 0; i < ttt.size(); i++){
				Equity* newEquity = new Equity_ttt_m(ttt[i]);
				equities.emplace(newEquity->name, newEquity);
			}
		}
		else if(insiders.empty() == true){
			for(unsigned long long i = 0; i < ttt.size(); i++){
				Equity* newEquity = new Equity_ttt(ttt[i]);
				equities.emplace(newEquity->name, newEquity);
			}
		}
		else{
			for(unsigned long long i = 0; i < ttt.size(); i++){
				if(insiders.count(ttt[i])){
					Equity* newEquity = new Equity_ttt_m(ttt[i]);
					equities.emplace(newEquity->name, newEquity);
				}
				else{
					Equity* newEquity = new Equity_ttt(ttt[i]);
					equities.emplace(newEquity->name, newEquity);
				}
			}	
		}
	}
}//genEquity

