#ifndef GUARD_readin_h
#define GUARD_readin_h
#include <fstream>
#include "zombie.h"

struct ZombieWave{
	int sum;
	void readin(std::ifstream&);
};

#endif
