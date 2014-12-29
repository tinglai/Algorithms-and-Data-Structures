#include <iostream>
#include <list>
#include "verbose.h"
#include "zombie.h"
#include <vector>
#include <algorithm>

using namespace std;

void verbose(list<Zombie*>& actZombies,
	     list<Zombie*>& inactZombies,
	     unsigned int v){
	unsigned vv;
	if (v > inactZombies.size())
		vv = inactZombies.size();
	else
		vv = v;
	
	//first vv zombies killed
	cout << "Zombies still active: "
	     << actZombies.size() << '\n'
	     << "First zombies killed:\n";
	list<Zombie*>::iterator temp = inactZombies.begin();
	unsigned int i = 0;
	while (i < vv){
		cout << (*temp)->getName() << ' ' << ++i << '\n';
		temp++;
	}

	//last vv zombies killed
	cout << "Last zombies killed:\n";
	temp = inactZombies.end();
	i = 0;
	while (i < vv){
		temp--;
		cout << (*temp)->getName() << ' ' << (vv-i) << '\n';
		i++;
	}

/*
	//most active v zombies and least active v zombies
	//by count sort
	int vvv;
	if (v > inactZombies.size() + actZombies.size())
		vvv = inactZombies.size() + actZombies.size();
	else
		vvv = v;

	vector<list<Zombie*>> stat(roundCount);
//cout << "debug info 0: stat.size = "<< stat.size() << endl;
//cout << "debug info 1: inactZombie.size= "<< inactZombies.size() << endl;
	temp = inactZombies.begin();
//cout << "debug info 2: temp = "<< (*temp)->getName() << endl;
	int round = 0;
	while(temp != inactZombies.end()){
//cout << "debug info 3: temp = "<< (*temp)->getName() << endl;
		round = (*temp)->getActRound();
		listInsert(stat[round-1], *temp);
		temp++;
		inactZombies.pop_front();
	}
//cout << "debug info 1: stat.size = "<< stat.size() << endl;
	temp = actZombies.begin();
//cout<<"I'm processeing!!!"<<endl;
	while(temp != actZombies.end()){
		round = (*temp)->getActRound();
		listInsert(stat[round-1], *temp);
		temp++;
		actZombies.pop_front();
	}
	//most active
	vv = vvv;
	i = 0;
	unsigned int j = roundCount - 1;
	cout << "Most active zombies:\n";
	while(vv != 0){
		if(stat[j].empty()){
			j--;
			continue;
		}
		if(vv >= stat[j].size()){
			temp = stat[j].begin();
			while(temp != stat[j].end()){
				cout << (*temp)->getName() << ' ' 
                             << (*temp)->getActRound() << '\n';
				temp++;
			}
			vv = vv - stat[j].size();
			j--;
		}
		else{
			temp = stat[j].begin();
			for(unsigned int lala = 0; lala < vv; lala++){
				cout << (*temp)->getName() << ' ' 
                            << (*temp)->getActRound() << '\n';
				temp++;
			}
			break;
		}
	}//while
	
	//least active
	i = 0;
	j = 0;
	cout << "Least active zombies:\n";
	vv = vvv;
	while(vv != 0){
		if(stat[j].empty()){
			j++;
			continue;
		}
		if(vv >= stat[j].size()){
			temp = stat[j].begin();
			while(temp != stat[j].end()){
				cout << (*temp)->getName() << ' ' 
                              << (*temp)->getActRound() << '\n';
				temp++;
			}
			vv = vv - stat[j].size();
			j++;
		}
		else{
			temp = stat[j].begin();
			for(unsigned int lala = 0; lala < vv; lala++){
				cout << (*temp)->getName() << ' ' 
                              << (*temp)->getActRound() << '\n';
				temp++;
			}
			break;
		}
	}//while

	for(unsigned int i = 0; i < stat.size(); i++){
		temp = stat[i].begin();
		while(temp != stat[i].end()){
			delete *temp;
			temp++;
		}
	}
*/

actZombies.splice(actZombies.end(), inactZombies);

int vvv;
if (v > actZombies.size())
	vvv = actZombies.size();
else
	vvv = v;
//vector<Zombie*> MostAct;
vector<Zombie*> leastAct;
int size = actZombies.size();
//if(vvv<v){
	for(int i = 0; i < size;i++){
		leastAct.push_back(actZombies.back());
		actZombies.pop_back();
	}
	sort(leastAct.begin(), leastAct.end(), compare_larger<Zombie*>);
	cout<<"Most active zombies:\n";
	for (int i = 0; i < vvv; i++ ){
		cout<<leastAct[i]->getName()<<' '<< leastAct[i]->getActRound()<<'\n';
	}
	sort(leastAct.begin(), leastAct.end(), compare_less<Zombie*>);
	cout<<"Least active zombies:\n";
	for (int i = 0; i < vvv; i++ ){
		cout<<leastAct[i]->getName()<<' '<< leastAct[i]->getActRound()<<'\n';
	}

	for(int i = 0; i < size; i ++){
		delete leastAct[i];
	}
//}

/*else{
	for(int i = 0; i < vvv;i++){
		leastAct.push_back(actZombies.back());
		actZombies.pop();
	}
	list<Zombie*>::iterator l= actZombies.begin();
	while (l != actZombies.end()){
		if compare()
	}
}*/



}//verbose


template <typename T>
bool compare_less(T a, T b){
	if(a->getActRound() < b->getActRound()){
		return 1;
	}
	else{
		if(a->getActRound() == b->getActRound()){
			return (a)->getName() < (b)->getName();
		}
		else return 0;
	}
}

template <typename T>
bool compare_larger(T a, T b){
	if(a->getActRound() > b->getActRound()){
		return 1;
	}
	else{
		if(a->getActRound() == b->getActRound()){
			return (a)->getName() < (b)->getName();
		}
		else return 0;
	}
}

void listInsert(list<Zombie*>& ll, Zombie* in){
	if(ll.empty()){
		ll.push_back(in);
	}
	else{
		list<Zombie*>::iterator temp = ll.end();
		while(temp != ll.begin()){
			temp--;
			if((*temp)->getName() < in->getName()){
				ll.insert(++temp, in);
				return;
			}
		}
		ll.push_front( in);
	}
	
}
