#ifndef GUARD_verbose_h
#define GUARD_verbose_h
#include "zombie.h"
#include <list>

void verbose(std::list<Zombie*>&, std::list<Zombie*>&,
	      unsigned int);
void listInsert(std::list<Zombie*>&, Zombie*);
template <typename T>
bool compare_less(const T&, const T&);
template <typename T>
bool compare_larger(const T&, const T&);

#endif
