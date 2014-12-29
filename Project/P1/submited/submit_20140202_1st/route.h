#ifndef GUARD_route_h
#define GUARD_route_h

#include "terrainInfo.h"
#include <deque>
#include <vector>

unsigned int stackRoute(std::vector<TerrainInfo>&, unsigned int, unsigned int, unsigned int);
unsigned int queueRoute(std::vector<TerrainInfo>&, unsigned int, unsigned int, unsigned int);
void addNeighbor(std::deque<unsigned int>&,
 std::vector<TerrainInfo>&, unsigned int, unsigned int, unsigned int);

#endif
