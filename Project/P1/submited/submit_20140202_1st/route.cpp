#include <vector>
#include <deque>
#include "route.h"

using namespace std;

unsigned int stackRoute(vector<TerrainInfo>& ter, unsigned int start, unsigned int farmSize, unsigned int farmNum){
	deque<unsigned int> container;
	container.push_back(start);
	ter[start].store = 1;
	unsigned int current;
	while(1){
		/*when the container is empty, there is no way to B*/
		if(container.empty()){
			return start;
		}
		if(ter[container.back()].c == 'B'){
			return container.back(); 
		}
		current = container.back();
		container.pop_back();
		addNeighbor(container, ter, current, farmSize, farmNum);
	}
}

unsigned int queueRoute(vector<TerrainInfo>& ter, unsigned int start, unsigned int farmSize, unsigned int farmNum){
	deque<unsigned int> container;
	container.push_back(start);
	ter[start].store = 1;
	unsigned int current;
	while(1){
		/*when the container is empty, there is no way to B*/
		if(container.empty()){
			return start;
		}
		if(ter[container.front()].c == 'B'){
			return container.front();
		}
		current = container.front();
		container.pop_front();
		addNeighbor(container, ter, current, farmSize, farmNum);
		}
}

void addNeighbor(deque<unsigned int>& container, vector<TerrainInfo>& ter,
 unsigned int current, unsigned int farmSize, unsigned int farmNum){
	unsigned int next;

	/*ladder up*/
	if (ter[current].c == '>'){
		/*a next terrain exists if current is not at the highest level*/
		if (ter[current].l != farmNum - 1){
			next = current + farmSize*farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 'd';
			}
		}
	}
	/*ladder down*/
	else if (ter[current].c == '<'){
		/*a next terrain exists if current is not at the lowest level*/
		if (ter[current].l != 0){
			next = current - farmSize*farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 'u';
			}
		}

	}
	/*field and starting point*/
	else{
		/*north*/
		/*a next terrain exists if current is not at the top line*/
		if (ter[current].x != 0){
			next = current - farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 's';
			}
		}
		/*east*/
		/*a next terrain exists if current is not at the right line*/
		if (ter[current].y != farmSize-1){
			next = current + 1;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 'w';
			}
		}
		/*south*/
		/*a next terrain exists if current is not at the bottom line*/
		if (ter[current].x != farmSize-1){
			next = current + farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 'n';
			}
		}
		/*west*/
		/*a next terrain exists if current is not at the left line*/
		if (ter[current].y != 0){
			next = current-1;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].store == 0){
				container.push_back(next);
				ter[next].store = 1;
				ter[next].parent = 'e';
			}
		}
	}
}
