#ifndef GUARD_gameInfo_h
#define GUARD_gameInfo_h
#include <fstream>
#include <vector>
#include "config.h"

class GameInfo{
	int quiverCap;
	int randomSeed;
	int maxDistance;
	int maxSpeed;
	int maxHealth;
	int playerHealth;
	int counter;//count how many zombies randomly created
	int deathtouch;
public:
	GameInfo();
	int getQuiverCap()const;
	int getRandomSeed()const;
	int getMaxDistance()const;
	int getMaxSpeed()const;
	int getMaxHealth()const;
	int getPlayerHealth()const;
	int getCounter ();
	void setGameInfo(std::ifstream&);
	void setDeathtouch(const Config&);
	int getDeathtouch() const;
	void playerBiten(int);
};

#endif
