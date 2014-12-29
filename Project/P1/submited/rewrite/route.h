#ifndef GUARD_route_h
#define GUARD_route_h

#include "terrainInfo.h"
#include <deque>
#include <vector>

int stackRoute(std::vector<TerrainInfo>&, int, int, int);
int queueRoute(std::vector<TerrainInfo>&, int, int, int);
void addNeighbor(std::deque<int>&,
 std::vector<TerrainInfo>&, int, int, int);

#endif
