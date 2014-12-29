#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include "zombie.h"
#include <string>
#include "eecs281priority_queue.h"
#include <algorithm>
#include "poorman_priority_queue.h"
#include <fstream>
#include "pairing_heap.h"
#include "config.h"
#include <sstream>
#include "gameInfo.h"
#include <climits>


using namespace std;

template<typename T>
struct compList{
	bool operator()(const T a, const T b) const{
		return **a < **b;
	}
};

struct Node{
	Node* pre;
	Node* next;
	Node* child;
	int data;
};

int main()

{
	vector<int> data, data2;
	for(int i = 0; i < 10; i++){
		data.push_back(2*i);
	}
	pairing_heap<int, std::less<int>>* heap
		 = new pairing_heap<int, std::less<int>>
			(data.begin(), data.end());
	//heap->print();
	for(int i = 10; i < 20; i++){
		data2.push_back(2*i);
	}
	pairing_heap<int, std::less<int>>* heap2
		 = new pairing_heap<int, std::less<int>>
			(data2.begin(), data2.end());
	*heap = *heap2;
	//cout << endl;
	//heap->print();
	pairing_heap<int, std::less<int>>* heap3
		 = new pairing_heap<int, std::less<int>>
			(*heap);
	//cout << endl;
	//heap3->print();
	
	int e1 = 27;
	pairing_heap<int, std::less<int> >::Node* a 
		= heap->add_node(e1);
	cout << "after addition: "<< endl;
	//heap->print();
	heap->updateElt(a, 27);
	cout << "after updating: "<< endl;
	for(int i = 0; i < 15; i++){
		heap->updateElt(a, i);
	}
	pairing_heap<int, std::less<int> >::Node* c = nullptr;
	//cout<<endl;
	heap->updateElt(c, -4);
	heap->print();
	delete heap;
	delete heap2;
	delete heap3;
}
