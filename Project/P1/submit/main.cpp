#include "config.h"
#include <sstream>
#include <deque>
#include "terrainInfo.h"
#include <vector>
#include <iostream>
#include "route.h"
#include "out.h"

using namespace std;
//std::ios_base::sync_with_stdio(false);

int main(int argc, char *argv[]){
	/*setup route form and output form main*/
	Config config;
	config.setup(argc, argv);

	/*read the first three lines of input file*/
	char inputForm; //record the form of input, M or L
	int farmSize; //record the size of farms
	int farmNum; //record the total number of farms
	cin >> inputForm >> farmSize >> farmNum;
	cin.get(); //discard newline on the third line

	/*read the following information about terrains*/
	vector<TerrainInfo> terrain(farmSize * farmSize * farmNum);
	int start = -1; //start is used to record where the starting point is
	if (inputForm == 'L')
		start = listRead(cin, terrain, farmSize, farmNum);
	else 
		start = mapRead(cin, terrain);

	/*find where the buck is*/
	int buck = -1; //buck is used to record where the buck is
	terrain[start].parent = '1';
	if (config.get_RouteConfig() == 1){
		buck = queueRoute(terrain, start, farmSize, farmNum);
	}		
	else
		buck = stackRoute(terrain, start, farmSize, farmNum);

	/*output*/
	stringstream ss;
	if (config.get_OutputConfig() == 1)
		 mapOutput(ss, terrain, buck, farmSize, farmNum);
	else
		 listOutput(ss, terrain, buck, farmSize, farmNum);
	cout << ss.str();
	return 0;
}
