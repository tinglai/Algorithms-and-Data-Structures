/*instead of using interger to locate the starting point, here I used 
 * pointer, start. However, in the queueRoute function, the value of start->c
 * changed to 0 after adding neighbours twice for some reason */
#include <vector>
#include <deque>
#include "route.h"

using namespace std;

TerrainInfo* stackRoute(vector<TerrainInfo>& ter, TerrainInfo*& start, int farmSize, int farmNum){
	deque<TerrainInfo*> container;
	container.push_back(start);
	TerrainInfo* current;
	while((*container.back()).c != 'B'){
		current = container.back();
		container.pop_back();
		addNeighbor(container, ter, current, farmSize, farmNum);
	}
	return container.back();
}

TerrainInfo* queueRoute(vector<TerrainInfo>& ter, TerrainInfo*& start, int farmSize, int farmNum){
	deque<TerrainInfo*> container;
	container.push_back(start);
	TerrainInfo* current;
	int count = 0;
	while((*container.front()).c != 'B'){
		current = container.front();
		//if(current==start)
			//cout<<"hahahahhahah"<<endl;
		//cout << "1 " << start->c<<endl<<endl;
		container.pop_front();
		addNeighbor(container, ter, current, farmSize, farmNum);
		cout << "0 " << start<<endl<<endl;
		cout << "1 " << ter[0].parent<<endl<<endl;
		cout << "2 " << &ter[1]<<endl<<endl;
		cout << "3 " << (*start).c<<endl<<endl;
		cout << "4 " << ter[1].c<<endl<<endl;
		cout << "5 " << ter[0].parent->c<<endl<<endl;
		}
	cout << start->c<<endl;
	return container.front();
}

void addNeighbor(deque<TerrainInfo*>& container, vector<TerrainInfo>& ter, TerrainInfo* current, int farmSize, int farmNum){
	TerrainInfo* next;

	/*ladder up*/
	//cout<<"debug infor in addNeighbor: "<<ter[1].c<<" "<<endl;
	if (current->c == '>'){
		/*a next terrain exists if current is not at the highest level*/
		if (current->l != farmNum - 1){
			next = &ter[(current->l+1) * (farmSize*farmSize) + current->x * farmSize + current->y];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}
	}
	/*ladder down*/
	else if (current->c == '<'){
		/*a next terrain exists if current is not at the lowest level*/
		if (current->l != 0){
			next = &ter[(current->l-1) * (farmSize*farmSize) + current->x * farmSize + current->y];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}

	}
	/*field and starting point*/
	else{
		/*north*/
		/*a next terrain exists if current is not at the top line*/
		if (current->x != 0){
			next = &ter[current->l * (farmSize*farmSize) + (current->x-1) * farmSize + current->y];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}
		/*east*/
		/*a next terrain exists if current is not at the right line*/
		if (current->y != farmSize-1){
			next = &ter[current->l * (farmSize*farmSize) + current->x * farmSize + current->y+1];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}
		/*south*/
		/*a next terrain exists if current is not at the bottom line*/
		if (current->x != farmSize-1){
			next = &ter[current->l * (farmSize*farmSize) + (current->x+1) * farmSize + current->y];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}
		/*west*/
		/*a next terrain exists if current is not at the left line*/
		if (current->y != 0){
			next = &ter[current->l * (farmSize*farmSize) + current->x * farmSize + current->y-1];
			/*check if the next terrain is walkable and if has ever been stored in the container*/
			if (next->c != '#' && next->store == 0){
				container.push_back(next);
				next->store = 1;
				next->parent = current;
			}
		}
	}
	//cout<<"debug infor in addNeighbor: "<<ter[1].c<<" "<<endl;
}
