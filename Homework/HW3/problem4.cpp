#include "problem4.h"

using namespace std;

bool ifDone(vector<Router*>& sources){
	for(unsigned i = 1; i < sources.size(); i++){
		if(sources[i] != sources[0])
			return 0;
	}
	return 1;
}

const Router* potentiallyBrokenRouter(const std::vector<const Router*>&
					   routersReportingErrors){
	if(routersReportingErrors.empty())
		return nullptr;

	//find ans
	Router* temp;
	int count = 0;
	vector<int> depth;
	vector<Router*> sources;

	if (!(routersReportingErrors[0]->source)){
		if(!routersReportingErrors[0]->destination1 &&
	   	    !routersReportingErrors[0]->destination2)
			return routersReportingErrors[0];
		else if(routersReportingErrors[0]->destination1)
	 		temp = routersReportingErrors[0]->
                                     destination1->source;
		else
			temp = routersReportingErrors[0]->
                                     destination2->source;
	}//if
	else{
		if(routersReportingErrors[0]->source->destination1 == 
		      routersReportingErrors[0])
			temp = routersReportingErrors[0]->source->destination1;
		else
			temp = routersReportingErrors[0]->source->destination2;
	}//else
	sources.push_back(temp);
	while(temp->source){
		temp = temp->source;
		count++;
	}//while
	int min_depth = count;
	depth.push_back(count);

	for(unsigned int i = 1; i < routersReportingErrors.size(); i++){
		if (!(routersReportingErrors[i]->source)){
			if(!routersReportingErrors[i]->destination1 &&
		   	    !routersReportingErrors[i]->destination2)
				return routersReportingErrors[i];
			else if(routersReportingErrors[i]->destination1)
	 			temp = routersReportingErrors[i]->
                                      destination1->source;
			else
				temp = routersReportingErrors[i]->
                                      destination2->source;
		}//if
		else{
			if(routersReportingErrors[i]->source->destination1 == 
			      routersReportingErrors[i])
				temp = routersReportingErrors[i]->source->destination1;
			else
				temp = routersReportingErrors[i]->source->destination2;
		}//else
		count = 0;
		sources.push_back(temp);
		while(temp->source){
			temp = temp->source;
			count++;
		}//while
		if(count < min_depth){
			min_depth = count;
		}
		depth.push_back(count);
	}//for
	
	for(unsigned int i = 0; i < depth.size(); i++){
		depth[i] -= min_depth;
	}
	for(unsigned int i = 0; i < sources.size(); i++){
		for(int j = 0; j < depth[i]; j++){
			sources[i] = sources[i]->source;
		}
	}
	while(!ifDone(sources)){
		for(unsigned int i = 0; i < sources.size(); i++){
			sources[i] = sources[i]->source;
		}
	}
	const Router* ans = sources[0];
	return ans;
}//func
