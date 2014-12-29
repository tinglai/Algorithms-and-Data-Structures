#include <vector>
#include <list>
#include <fstream>
#include "zombie.h"
#include "readin.h"
#include <iostream>
#include <sstream>

using namespace std;

void ZombieWave::readin(ifstream& file){
	string temp;
	int zombieNum = 0;//record how many new zombies generate randomly
	sum = 0;
	while(getline(file, temp)){	
		if(temp[0] == 'N'){
			stringstream ss;
			ss.str(temp);
			string name;
			ss >> name>> zombieNum;
			sum = sum + zombieNum;
		}
		else if(temp[0] == '-' || temp[0] == 'R')continue;
		else sum++;
	}//while for outer loop
}//readin
