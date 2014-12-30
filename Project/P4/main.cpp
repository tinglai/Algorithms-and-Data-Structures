#include "config.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include "mst.h"
#include "fastTSP.h"
#include "optTSP.h"

using namespace std;

int main(int argc, char *const *argv){
	cout << setprecision(2);
	cout << fixed;

	Config config;
	config.setup(argc, argv);

	if(config.mode == 'm'){
		MST mst;
		mst.readin();
		mst.build();
		/*for(int i = 0; i < config.M; i++){
			cout << classify(i, config) << endl;
		}
		*/
	}	
	else if(config.mode == 'o'){
		OptTSP optTSP;
		optTSP.readin();
		optTSP.build();
	}
	else{

		FastTSP fastTSP;
		fastTSP.readin();
		fastTSP.build();
	}
	return 0;
}//main
