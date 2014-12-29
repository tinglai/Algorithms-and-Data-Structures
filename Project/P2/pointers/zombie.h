#ifndef GUARD_zombie_h
#define GUARD_zombie_h
#include <string>
#include <fstream>
#include "gameInfo.h"

class Zombie{
private:
	std::string name;
	int speed;
	int distance;
	int health;
	int actRound;
public:
	std::string getName();
	int getSpeed();
	int getDistance();
	int getHealth();
	int getActRound();
	bool move2player(GameInfo&);
	void attacked(int);
	int getETA();
	Zombie(std::string&);
	Zombie(GameInfo&);
	Zombie(std::string, int, int, int, int);
};

#endif
