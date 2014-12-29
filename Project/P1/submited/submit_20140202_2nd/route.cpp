#include <vector>
#include <deque>
#include "route.h"

using namespace std;

int stackRoute(vector<TerrainInfo>& ter, int start, int farmSize, int farmNum){
	deque<int> container;
	container.push_back(start);
	ter[start].parent = '1';
	int current;
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

int queueRoute(vector<TerrainInfo>& ter, int start, int farmSize, int farmNum){
	deque<int> container;
	container.push_back(start);
	ter[start].parent = '1';
	int current;
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

void addNeighbor(deque<int>& container, vector<TerrainInfo>& ter,
 int current, int farmSize, int farmNum){
	int next;

	/*ladder up*/
	if (ter[current].c == '>'){
		/*a next terrain exists if current is not at the highest level*/
		if (current/(farmSize*farmSize) != farmNum - 1){
			next = current + farmSize*farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 'd';
			}
		}
	}
	/*ladder down*/
	else if (ter[current].c == '<'){
		/*a next terrain exists if current is not at the lowest level*/
		if (current/(farmSize*farmSize) != 0){
			next = current - farmSize*farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 'u';
			}
		}

	}
	/*field and starting point*/
	else{
		/*north*/
		/*a next terrain exists if current is not at the top line*/
		if (current%(farmSize*farmSize)/farmSize != 0){
			next = current - farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 's';
			}
		}
		/*east*/
		/*a next terrain exists if current is not at the right line*/
		if (current%farmSize != farmSize-1){
			next = current + 1;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 'w';
			}
		}
		/*south*/
		/*a next terrain exists if current is not at the bottom line*/
		if (current%(farmSize*farmSize)/farmSize != farmSize-1){
			next = current + farmSize;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 'n';
			}
		}
		/*west*/
		/*a next terrain exists if current is not at the left line*/
		if (current%farmSize != 0){
			next = current-1;
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (ter[next].c != '#' && ter[next].parent == '0'){
				container.push_back(next);
				ter[next].parent = 'e';
			}
		}
	}
}
