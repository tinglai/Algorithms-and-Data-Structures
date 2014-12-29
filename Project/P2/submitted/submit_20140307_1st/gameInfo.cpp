#include "gameInfo.h"
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "config.h"

using namespace std;

GameInfo::GameInfo(){
	counter = 0;
}

int GameInfo::getQuiverCap() const {return quiverCap;}

int GameInfo::getRandomSeed() const {return randomSeed;}

int GameInfo::getMaxDistance() const {return maxDistance;}

int GameInfo::getMaxSpeed() const {return maxSpeed;}

int GameInfo::getMaxHealth() const {return maxHealth;}

int GameInfo::getPlayerHealth() const {return playerHealth;}

void GameInfo::setGameInfo(ifstream& file){
	string temp;
	getline(file, temp);
	temp.assign(temp.begin() + 17, temp.end());
	quiverCap = atoi(temp.c_str());

	getline(file, temp);
	temp.assign(temp.begin() + 13, temp.end());
	randomSeed = atoi(temp.c_str());

	getline(file, temp);
 	temp.assign(temp.begin() + 19, temp.end());
	maxDistance = atoi(temp.c_str());

	getline(file, temp);
	temp.assign(temp.begin() + 16, temp.end());
	maxSpeed = atoi(temp.c_str());

	getline(file, temp);
	temp.assign(temp.begin() + 17, temp.end());
	maxHealth = atoi(temp.c_str());

	getline(file, temp);
	temp.assign(temp.begin() + 15, temp.end());
	playerHealth = atoi(temp.c_str());
}//setGameInfo

int GameInfo::getCounter(){return counter++;}

int GameInfo::getDeathtouch() const {return deathtouch;}

void GameInfo::setDeathtouch(const Config& config){
	if(config.getArrow() == "LIGHT")
		deathtouch = 1;
	else
		deathtouch = 0;
}

void GameInfo::playerBiten(int zombieHealth){
	playerHealth = (1 - deathtouch) * (playerHealth - zombieHealth);
}
