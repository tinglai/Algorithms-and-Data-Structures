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
			numRam.push_back(0);
			numSpec.push_back(0);
		}

		getline(file, temp);
		temp.assign(temp.begin() + 13, temp.end());
		zombieNum = atoi(temp.c_str());
	
		numRam.push_back(zombieNum);
		sum = sum + zombieNum;
		numSpec.push_back(0);
		while (1){
			getline(file, temp);
			if(temp == "---" || !file) break;
			Zombie* newZombie = new Zombie(temp);
			specZombies.push_back(newZombie);
			numSpec.back() = numSpec.back() + 1;
			sum++;
		}//while

	}//while for outer loop

}//readin
