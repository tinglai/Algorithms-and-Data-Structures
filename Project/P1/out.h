#ifndef GUARD_out_h
#define GUARD_out_h

#include <deque>
#include "terrainInfo.h"
#include <sstream>

void mapOutput(std::stringstream&, std::vector<TerrainInfo>&,
 int, int, int);
void listOutput(std::stringstream&, std::vector<TerrainInfo>&,
 int, int, int);

#endif
