#include "problem4.h"

using namespace std;

const Router* potentiallyBrokenRouter(const std::vector<const Router*>&
					   routersReportingErrors){
	vector<Router*> stk;
	unsigned max_depth = 0;
	unsigned count = 0;
	
	//find root
	Router* root = nullptr;
	for(unsigned int i = 0; i < routersReportingErrors.size(); i++){
		if (!(routersReportingErrors[i]->source)){
			if(!routersReportingErrors[i]->destination1 &&
			   !routersReportingErrors[i]->destination2)
				return routersReportingErrors[i];
			else if(routersReportingErrors[i]->destination1)
		 		root = routersReportingErrors[i]->
                                           destination1->source;
			else
				root = routersReportingErrors[i]->
                                           destination2->source;
		}//if
	}//for
	
	Router* candidate = root;

	//find leaf
	stk.push_back(root);
	Router* temp;
	while(!stk.empty()){
		temp = stk.back();
		stk.pop_back();

		if(!temp->destination1 && !temp->destination2){
			count = 0;
			while(temp->source){
				temp = temp->source;
				count++;
			}
			if (count > max_depth){
				candidate = temp;
				max_depth = count;
			}
		}
		else{
			if(temp->destination1)
				stk.push_back(temp->destination1);
			if(temp->destination2)
				stk.push_back(temp->destination2);
		}
	}//while
	if(candidate->source){
		candidate = candidate->source;
	}
	const Router* ans = candidate;
	return ans;
}
