#ifndef GUARD_verbose_h
#define GUARD_verbose_h
#include "zombie.h"
#include <list>

void verbose(std::list<Zombie*>&, std::list<Zombie*>&,
	      unsigned int, int);
void listInsert(std::list<Zombie*>&, Zombie*);
#endif
