#ifndef GUARD_readin_h
#define GUARD_readin_h

#include <iostream>
#include <vector>

struct TerrainInfo{
	char c; 
	char parent;
	TerrainInfo():c('.'), parent('0') {}
};

int listRead(std::istream&, std::vector<TerrainInfo>&, int, int);

int mapRead(std::istream&, std::vector<TerrainInfo>&);

#endif
