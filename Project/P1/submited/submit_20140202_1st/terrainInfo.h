#ifndef GUARD_readin_h
#define GUARD_readin_h

#include <iostream>
#include <vector>

struct TerrainInfo{
	unsigned int x, y, l; 
	// (x, y) are the coordinates for every terrain, 
	// l is the level of the farm
	char c; 
	// c is used to record the character of the terrain
	char parent;
	bool store;
};

unsigned int listRead(std::istream&, std::vector<TerrainInfo>&, unsigned int, unsigned int);

unsigned int mapRead(std::istream&, std::vector<TerrainInfo>&, unsigned int);

#endif
