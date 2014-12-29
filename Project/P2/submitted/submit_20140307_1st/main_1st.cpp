#include "config.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "gameInfo.h"
#include <cstdlib>
#include "zombie.h"
#include "eecs281priority_queue.h"
#include "poorman_priority_queue.h"
#include "binary_heap.h"
#include "verbose.h"
#include "determine.h"
#include "readin.h"

using namespace std;

int main(int argc, char *const* argv){

//*************setup by command line*****************
	Config config;
	config.setup(argc, argv);

//*************read game info from the input file**************
	GameInfo liguang;
	ifstream file;
	file.open(config.getFileName().c_str());//****remember to close!!****
	liguang.setGameInfo(file);
	liguang.setDeathtouch(config);
	srand(liguang.getRandomSeed());
	string nothing;
	getline(file, nothing);//get rid of the slashes

//*************game starts!!!*************************
	int roundCount = 0;//record current round
	int numArrow = 0;//record how many arrows in quiv=or
	int costArrow = 0; // record cost of Arrow to kill next zombie
	ZombieWave wave;
	wave.readin(file);
	file.close();
	file.open(config.getFileName().c_str());
	for (int i = 0; i < 7; i ++){
		getline(file, nothing);
	}
	list<Zombie*> actZombies;
	list<Zombie*> inactZombies;
	
	eecs281priority_queue<list<Zombie*>::iterator, 
                               compList<list<Zombie*>::iterator>>* heap = 
					        determine(config.getContainer());
	int zombieRound = 0;//record when new zombies coming
	int zombieNum = 0;//record how many new zombies generate randomly
	list<Zombie*>::iterator killer;//record who kill the player
	list<Zombie*>::iterator act;

//*************round begins!!!************************
	while (1){

		//********************
		//refill quiver, a new round begins
		//********************
		numArrow = liguang.getQuiverCap();
		roundCount++;
		if(config.getDe() == 1)
			cout << "Round: " << roundCount << '\n';

		//***************************************************
		//update zombies & print out if in debug mode & bite if possible
		//***************************************************
		act = actZombies.begin();
		while(act != actZombies.end()){
			bool ifDead = (*act)->move2player(liguang);
			if(ifDead == 1) killer = act;
			act++;
		}
		if(config.getDe() == 1){ 
			act = actZombies.begin();
			while (act != actZombies.end()){
				cout << "Moved: " << (*act)->getName() << ' ' 
				     << (*act)->getDistance() <<'\n';
				act++;
			}//while
		}//if

		//**********************************
		//new zombies round
		//**********************************
		//
		//readin roundInfo from input file
		if (zombieRound < roundCount){
			string temp;
			getline(file, temp);
			temp.assign(temp.begin() + 7, temp.end());
			zombieRound = atoi(temp.c_str());
			getline(file, temp);
			temp.assign(temp.begin() + 13, temp.end());
			zombieNum = atoi(temp.c_str());
		}

		//new zombies coming!!
		if (zombieRound == roundCount){
			if(actZombies.empty()) act = actZombies.begin();
			else{
				act = actZombies.end();
				act--;
			}
			//randomly generated new zombies
			for (int i = 0; i < zombieNum; i++){
				Zombie* newZombie = new Zombie(liguang);
				actZombies.push_back(newZombie);
				list<Zombie*>::iterator temp = actZombies.end();
				temp--;
				heap->push(temp);
				wave.sum = wave.sum - 1;
			}
			//specificly generated new zombies
			string temp;
			while (getline(file, temp)){
				//if(temp == "---" || temp.fail()) break;
				if(temp == "---") break;
				Zombie* newZombie = new Zombie(temp);
				actZombies.push_back(newZombie);
				list<Zombie*>::iterator temp = actZombies.end();
				temp--;
				heap->push(temp);
				wave.sum = wave.sum - 1;
			}//while
			if(config.getDe() == 1){
				while(++act != actZombies.end()){
					cout << "Created: " << (*act)->getName()
				          << ' ' << (*act)->getDistance() << '\n';
				}//while
			}//if getDe
		}//if zombieRound == roundCount

		//********************************
		//Is the player dead???
		//********************************
		if (liguang.getPlayerHealth() <= 0){
			cout << "DEFEAT IN ROUND " << roundCount << "! "
                           << (*killer)->getName() << " ate your brains!" << '\n';
			if(config.getV() > 0){
				verbose(actZombies, inactZombies, 
				         config.getV(), roundCount); 
				return 0;
			}
			delete heap;
			list<Zombie*>::iterator temp = actZombies.begin();
			while(temp != actZombies.end()){
				delete *temp;
				temp++;
			}
			temp = inactZombies.begin();
			while(temp != inactZombies.end()){
				delete *temp;
				temp++;
			}
			file.close();
			return 0;
		}


		//***************************************
		//player shoots!!!!!!!!!
		//******************************
		if (actZombies.empty()){
			continue;
		}
		list<Zombie*>::iterator nextZombie = heap->top();
		costArrow = (1 - liguang.getDeathtouch()) * 
			  ((*nextZombie)->getHealth() - 1) + 1;
		while (numArrow >= costArrow){	
			numArrow = numArrow - costArrow;
			if(config.getV() > 0) inactZombies.push_back(*nextZombie);
			actZombies.erase(nextZombie);
			heap->pop();
			if (actZombies.empty()){
				if (wave.sum == 0){
					cout << "VICTORY IN ROUND " << roundCount << "! " 
					   << (*nextZombie)->getName()
					   << " was the last zombie. You survived with "
					   << liguang.getPlayerHealth()
					   << " health left.\n";
					if(config.getV() > 0){
						verbose(actZombies, inactZombies, 
					 	   config.getV(), roundCount);
						return 0;
					}
					delete heap;
					list<Zombie*>::iterator temp = actZombies.begin();
					while(temp != actZombies.end()){
						delete *temp;
						temp++;
					}
					temp = inactZombies.begin();
					while(temp != inactZombies.end()){
						delete *temp;
						temp++;
					}
					file.close();
					return 0;
				}
				break;
			}//if	
			nextZombie = heap->top();
			costArrow = (1 - liguang.getDeathtouch()) *
				  ((*nextZombie)->getHealth() - 1) + 1;
		}//while
		if (!actZombies.empty())
			(*nextZombie)->attacked(numArrow);
		
	}//while for outer loop
	return 0;
}