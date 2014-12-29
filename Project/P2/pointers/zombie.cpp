#include "zombie.h"
#include <cstdlib>
#include <string>
#include <climits>
#include <iostream>

using namespace std;

string Zombie::getName(){return name;}

int Zombie::getSpeed(){return speed;}

int Zombie::getDistance(){return distance;}

int Zombie::getHealth(){return health;}

int Zombie::getActRound(){return actRound;}


bool Zombie::move2player(GameInfo& liguang){
	actRound++;
	distance = distance - speed - (rand() % speed) / 2;
	if(distance < 0) 
		distance = 0;
	if(distance == 0 && liguang.getPlayerHealth() > 0){
		liguang.playerBiten(health);
		if(liguang.getPlayerHealth() <= 0){
			return 1;
		}//if
	}//if
	return 0;
}//move2player

void Zombie::attacked(int damage){
	health -= damage;
}

Zombie::Zombie(string& temp){
	size_t i = 0;
	i = temp.find_first_of(' ');
	distance = atoi(temp.substr(0, i).c_str());
	temp = temp.substr(i + 1);
	i = temp.find_first_of(' ');
	speed = atoi(temp.substr(0, i).c_str());
	temp = temp.substr(i + 1);
	i = temp.find_first_of(' ');
	health = atoi(temp.substr(0, i).c_str());
	temp = temp.substr(i + 1);
	name = temp;
	actRound = 1;
}

Zombie::Zombie(GameInfo& liguang){
	distance = rand() % liguang.getMaxDistance() + 1;
	speed = rand() % liguang.getMaxSpeed() + 1;
	health = rand() % liguang.getMaxHealth() + 1;
	name = "AI";
	name += to_string(liguang.getCounter());
	actRound = 1;
}

Zombie::Zombie(string name, int speed, int distance, int health, int actRound):
name(name),speed(speed),distance(distance),health(health),actRound(actRound){}

int Zombie::getETA(){
	return distance / speed;
}



