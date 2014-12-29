#include <iostream>
#include <limits.h>

using namespace std;

int main(){
	unsigned int i;
	i = -1;
	bool t = (i == UINT_MAX)? 1: 0;
	bool p = (i == 4294967295)? 1: 0;
	cout << t << ' ' << p << ' ' << UINT_MAX+1 << endl;
}
