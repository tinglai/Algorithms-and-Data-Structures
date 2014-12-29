#include <iostream>
#include <list>
#include "verbose.h"
#include "zombie.h"
#include <vector>

using namespace std;

void verbose(list<Zombie*>& actZombies,
	     list<Zombie*>& inactZombies,
	     unsigned int v, int roundCount){
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

	//most active v zombies and least active v zombies
	//by count sort
	int vvv;
	if (v > inactZombies.size() + actZombies.size())
		vvv = inactZombies.size() + actZombies.size();
	else
		vvv = v;

	vector<list<Zombie*>> stat(roundCount);
	temp = inactZombies.begin();
	int round = 0;
	while(temp != inactZombies.end()){
		round = (*temp)->getActRound();
		listInsert(stat[round-1], *temp);
		temp++;
		inactZombies.pop_front();
	}
	temp = actZombies.begin();
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
}//verbose

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
