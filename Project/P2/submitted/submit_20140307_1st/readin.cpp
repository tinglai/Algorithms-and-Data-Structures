#include <vector>
#include <list>
#include <fstream>
#include "zombie.h"
#include "readin.h"
#include <iostream>

using namespace std;

void ZombieWave::readin(ifstream& file){
	int round = 0;
	string temp;
	int zombieRound = 0;//record when new zombies coming
	int zombieNum = 0;//record how many new zombies generate randomly
	sum = 0;
	while(file){	
		round++;

		getline(file, temp);
		temp.assign(temp.begin() + 7, temp.end());
		zombieRound = atoi(temp.c_str());

		while(zombieRound != round){
			round++;
		}

		getline(file, temp);
		temp.assign(temp.begin() + 13, temp.end());
		zombieNum = atoi(temp.c_str());
	
		sum = sum + zombieNum;
		while (1){
			getline(file, temp);
			if(temp == "---" || !file) break;
			sum++;
		}//while

	}//while for outer loop
}//readin
