#include <vector>
#include <iostream>
#include "problem4.h"

using namespace std;

int main(){
	Router* A = new Router;
	Router* B = new Router;
	Router* C = new Router;
	Router* D = new Router;
	Router* E = new Router;
	Router* F = new Router;
	Router* G = new Router;

	/*A->source = nullptr;
	A->destination1 = B;
	A->destination2 = E;
	
	B->source = A;
	B->destination1 = C;
	B->destination2 = D;

	C->source = B;
	C->destination1 = nullptr;
	C->destination2 = nullptr;

	D->source = B;
	D->destination1 = F;
	D->destination2 = G;

	E->source = A;
	E->destination1 = nullptr;
	E->destination2 = nullptr;

	F->source = D;
	F->destination1 = nullptr;
	F->destination2 = nullptr;

	G->source = D;
	G->destination1 = nullptr;
	G->destination2 = nullptr;
*/
	A->source = nullptr;
	A->destination1 = nullptr;
	A->destination2 = nullptr;
	

	vector<const Router*> input;
	//input.push_back(G);
	//input.push_back(F);
	//input.push_back(E);
	//input.push_back(D);
	//input.push_back(C);
	//input.push_back(B);
	input.push_back(A);
	const Router* ans = potentiallyBrokenRouter(input);
	cout << (ans == A) << endl;

	delete A;
	delete B;
	delete C;
	delete D;
	delete E;
	delete F;
	delete G;
}
