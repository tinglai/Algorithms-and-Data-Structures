#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include "zombie.h"
#include <string>
#include <algorithm>
#include <fstream>
#include "config.h"
#include <sstream>


using namespace std;

template<typename T>
struct compList{
	bool operator()(const T a, const T b) const{
		return **a < **b;
	}
};

int main(int argc, char *const* argv){
		cout << "Quiver_Capacity: 10000\n"
<<"Random_Seed: 2049231"<<'\n'
<<"Max_Rand_Distance: 50"<<'\n'
<<"Max_Rand_Speed: 60"<<'\n'
<<"Max_Rand_Health: 1"<<'\n'
<<"Player_Health: 10"<<'\n';
	for (int i = 0; i < 150000; i++){
		cout << "---"<<'\n' << "Round: " << i+1 <<'\n'<<"Num_Zombies: "<<rand()%10+1<<'\n'
		   <<rand()%150+1<<' '<<rand()%150+1<<' '<<rand()%150+1<<' '<<"spec1**"<<i<<'\n'
		 <<rand()%150+1<<' '<<rand()%150+1<<' '<<rand()%150+1<<' '<<"spec2**"<<i<<'\n'
		 <<rand()%150+1<<' '<<rand()%150+1<<' '<<rand()%150+1<<' '<<"spec3**"<<i<<'\n';

	}
	//string temp;
	//ss >> temp;
	//cout << temp;
}

