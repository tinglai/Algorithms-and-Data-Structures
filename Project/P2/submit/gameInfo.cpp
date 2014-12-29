#include "gameInfo.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "config.h"
#include <sstream>

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

	//stringstream ss1;
	//getline(file, temp);
	//ss1.str(temp);
	string name;
	//temp.assign(temp.begin() + 17, temp.end());
	file >> name >> quiverCap;
//cout<<"debug info 0: "<< name<<' '<<quiverCap << endl;
	file >> name >> randomSeed;
	file >> name >> maxDistance;
	file >> name >> maxSpeed;
	file >> name >> maxHealth;
	file >> name >> playerHealth;
}
/*	stringstream ss2;
	getline(file, temp);
	ss2.str(temp);
//	temp = ss.str();
//cout<<"******temp = "<<temp<<"*****"<<endl;
	string seed;
//debugcheck.assign(temp.begin(), temp.begin() + 13);
//if(debugcheck == "Random_Seed: "){
//	temp.assign(temp.begin() + 13, temp.end());
	//randomSeed = atoi(temp.c_str());
	ss2 >> seed >> randomSeed;

//else{
//cout<<debugcheck;
//}
//cout<<"debug info 1: "<< seed <<' '<< randomSeed << endl;

	stringstream ss3;
	getline(file, temp);
	string distance;
	ss3.str(temp);
//debugcheck.assign(temp.begin(), temp.begin() + 19);
//if(debugcheck == "Max_Rand_Distance: "){
// 	temp.assign(temp.begin() + 19, temp.end());
	//maxDistance = atoi(temp.c_str());
	ss3 >> distance >> maxDistance;
//}
//else{
//cout<<debugcheck;
//}
//cout<<"debug info 2: "<<distance<<maxDistance<< endl;

	stringstream ss4;
	temp.clear();
	getline(file, temp);
//debugcheck.assign(temp.begin(), temp.begin() + 16);
//if(debugcheck == "Max_Rand_Speed: "){
	string speed;
	ss4.str(temp);
//	temp.assign(temp.begin() + 16, temp.end());
//	maxSpeed = atoi(temp.c_str());
	ss4 >> speed >> maxSpeed;
//}
//else{
//cout<<debugcheck;
//}
//cout<<"debug info 3: "<<speed  << maxSpeed << endl;

	stringstream ss5;
	temp.clear();
	getline(file, temp);
	string health;
	ss5.str(temp);
//debugcheck.assign(temp.begin(), temp.begin() + 17);
//if(debugcheck == "Max_Rand_Health: "){
//	temp.assign(temp.begin() + 17, temp.end());
//	maxHealth = atoi(temp.c_str());
	ss5 >> health >> maxHealth;
//}
//else{
//cout<<debugcheck;
//}
//cout<<"debug info 4: "<<health<< maxHealth<< endl;

	stringstream ss6;
	temp.clear();
	getline(file, temp);
//debugcheck.assign(temp.begin(), temp.begin() + 15);
//if(debugcheck == "Player_Health: "){
//	temp.assign(temp.begin() + 15, temp.end());
//	playerHealth = atoi(temp.c_str());
	string phealth;
	ss6.str(temp);
	ss6 >> phealth >> playerHealth;
//}
//else{
//cout<<debugcheck;
//}
//cout<<"debug info 5: "<<phealth<<playerHealth << endl;
}//setGameInfo
*/

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
