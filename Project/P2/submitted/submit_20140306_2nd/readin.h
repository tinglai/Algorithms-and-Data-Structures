#ifndef GUARD_readin_h
#define GUARD_readin_h
#include <vector>
#include <list>
#include <fstream>
#include "zombie.h"

struct ZombieWave{
	std::list<Zombie*> specZombies;
	std::vector<int> numRam;
	std::vector<int> numSpec;
	int sum;
	void readin(std::ifstream&);
};

#endif
