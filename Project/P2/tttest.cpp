#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Node{
	Node* next;
	int data;
};

int main(){
	vector<Node*> dd;
	Node* in = new Node;;
	in->data = 9;
	in->next = nullptr;
	dd.push_back(in);
	cout << (!dd.back()->next) << endl;
}
