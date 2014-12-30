#include <iostream>
#include <algorithm>
#include <set>
#include <utility>
#include <unordered_map>
#include "source.h"
#include "source_PR.h"
#include "source_TL.h"
#include <string>
#include "config.h"
#include "equity.h"
#include "equity_m.h"
#include "equity_ttt.h"
#include "equity_ttt_m.h"
#include "client.h"
#include <sstream>

using namespace std;

int main(const int argc, char *const* argv){
	//set arguments
	Config config;
	config.setup(argc, argv);
	//readin mode TL or PR
	string mode;
	getline(cin, mode);
	
	
	//setup source of orders
	Source_PR PRsource;
	Source_TL TLsource;
	Source* source;
	if(mode == "TL")
		source = &TLsource;
	else
		source = &PRsource;
	source->setup(cin);
	

	unordered_map<string, Equity*> equities; 
	set<Equity*, CompEquity<Equity*>> m_equities;//equities that already traded catalog
	vector<string> t_clients;//client catalog
	unordered_map<string, Client_stat*> tStat;
	
	config.genEquity_ttt(equities);
	if(config.isT == true && config.insiders.empty() == false){
		for (unordered_set<string>::iterator i = config.insiders.begin();
		         i != config.insiders.end(); i++){
			string in = "INSIDER_" + *i; 
			Client_stat* newClient = new Client_stat;
			tStat.emplace(in, newClient);
			t_clients.push_back(in);
		}
	}


	Order* nextOrder = nullptr;
	while((nextOrder = config.genOrder(equities, source))){

		if(nextOrder->time < config.current)
			exit(1);

		if(config.isT){
			//if(t_clients.count(nextOrder->client) == 0){
			if(tStat.count(nextOrder->client) == 0){
				t_clients.push_back(nextOrder->client);
				Client_stat* newClient = new Client_stat;
				tStat.emplace(nextOrder->client, newClient);
			}
		}
	
		if(config.current != nextOrder->time){
			if(config.isM){
				config.print_M(m_equities);
			}//if
			config.current = nextOrder->time;
		}//outer if
	
		if(equities.count(nextOrder->equity)){
			Equity* newEquity = equities[nextOrder->equity];
			newEquity->findTTT(nextOrder);
			newEquity->insert(nextOrder);
			Order* done;

			while((done = newEquity->trade())){
				config.update_S(done);
				config.print_V(done, newEquity);
				
				if(config.isM && (newEquity->smallHalf).size() 
						     + (newEquity->bigHalf).size() == 1){
					m_equities.insert(newEquity);
				}
				//if(config.insiders.empty() == false
				//      && config.insiders.count(newEquity->name)){
				//}
				config.update_T(done, tStat, newEquity);
				      //|| newEquity->isTTT()/*newEquity->timestamp1 == -1*/){
				delete done;
				done = nullptr;
			}//(done)
		}//if
		else{
			Equity* newEquity = config.genEquity(equities, nextOrder);
			newEquity->findTTT(nextOrder);
		}
	}//while

	//output
	if(config.isM)
		config.print_M(m_equities);
	config.ss << "---End of Day---\n"; 
	if(config.isS){
		config.ss << "Commission Earnings: $" << config.s_commission << '\n';
		config.ss << "Total Amount of Money Transferred: $" << config.s_transfer << '\n';
		config.ss << "Number of Completed Trades: " << config.s_numOfCompletedTrades << '\n';
		config.ss << "Number of Shares Traded: " << config.s_numOfSharesTraded << '\n';
	}
	if(config.isT){
		sort(t_clients.begin(), t_clients.end());
		for(unsigned long long i = 0; i < t_clients.size(); i++){
			config.ss << t_clients[i] << " bought " << tStat[t_clients[i]]->bought 
			   << " and sold "
			   << tStat[t_clients[i]]->sold << " for a net transfer of $"
			   << tStat[t_clients[i]]->transfer << '\n';
			delete tStat[t_clients[i]];
			tStat[t_clients[i]] = nullptr;
		}
	}
	if(config.ttt.size() > 0){
		for(unsigned long long i = 0; i < config.ttt.size(); i++){
			long long timestamp1;
			long long timestamp2;
			equities[config.ttt[i]]->getTTT(timestamp1, timestamp2);
			config.ss << "Time travelers would buy " << config.ttt[i]
			     << " at time: " << timestamp1
			     << " and sell it at time: " << timestamp2
			     << '\n';
		}
	}
	cout << config.ss.str();
	unordered_map<string, Equity*>::iterator eq = equities.begin();
	while(eq != equities.end()){
		eq->second->clean();
		delete (*eq).second;
		(*eq).second = nullptr;
		eq++;
	}
	return 0;
}
