#include "terrainInfo.h"
#include <sstream>
#include "out.h"
#include <deque>
#include <vector>
#include "terrainInfo.h"

using namespace std;

void mapOutput(stringstream& ss, vector<TerrainInfo>& ter, int buck,
 int farmSize, int farmNum){
	deque<int> backPath;
	char t = ter[buck].c;
	if (t != 'S'){
		backPath.push_back(buck);
		while(t != 'S'){
			switch (ter[backPath.back()].parent){
				case 'u': 
					backPath.push_back(backPath.back()
 							   + farmSize*farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'd';
					break;
				case 'd':
					backPath.push_back(backPath.back()
 							   - farmSize*farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'u';
					break;
				case 'e':
					backPath.push_back(backPath.back() + 1);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'w';
					break;
				case 's':
					backPath.push_back(backPath.back() + farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'n';
					break;
				case 'w':
					backPath.push_back(backPath.back() - 1);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'e';
					break;
				case 'n':
					backPath.push_back(backPath.back() - farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 's';
					break;
				default: break;
			}
		}
	}

	ss << farmSize << '\n' << farmNum << '\n';
	int k, i, j;
	for(k = 0; k < farmNum; k++){
		ss << "//farm " << k << '\n';
		for(i = 0; i < farmSize; i++){
			for(j = 0; j < farmSize; j++){
				ss << ter[k*farmSize*farmSize + i*farmSize + j].c;
			}
			ss << '\n';
		}
	}
}

void listOutput(stringstream& ss, vector<TerrainInfo>& ter, int buck,
 int farmSize, int farmNum){
	deque<int> backPath;
	char t = ter[buck].c;
	if (t != 'S'){
		backPath.push_back(buck);
		while(t != 'S'){
			switch (ter[backPath.back()].parent){
				case 'u': 
					backPath.push_back(backPath.back()
 							   + farmSize*farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'd';
					break;
				case 'd':
					backPath.push_back(backPath.back()
 							   - farmSize*farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'u';
					break;
				case 'e':
					backPath.push_back(backPath.back() + 1);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'w';
					break;
				case 's':
					backPath.push_back(backPath.back() + farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'n';
					break;
				case 'w':
					backPath.push_back(backPath.back() - 1);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 'e';
					break;
				case 'n':
					backPath.push_back(backPath.back() - farmSize);
					t = ter[backPath.back()].c;
					ter[backPath.back()].c = 's';
					break;
				default: break;
			}
		}
	}
	ss << farmSize << '\n' << farmNum << '\n'
 << "//path taken \n";
	int a;
	while(!backPath.empty()){
		a = backPath.back();
		backPath.pop_back();
		ss << '(' << a%(farmSize*farmSize)/farmSize << ',' << a%farmSize << ','
 << a%(farmSize*farmSize) << ',' << ter[a].c << ')' << '\n';
 	}
}
