#ifndef GUARD_readin_h
#define GUARD_readin_h

#include <iostream>
#include <vector>

struct TerrainInfo{
	char c; 
	// c is used to record the character of the terrain
	char parent;
};

int listRead(std::istream&, std::vector<TerrainInfo>&, int, int);

int mapRead(std::istream&, std::vector<TerrainInfo>&);

#endif
