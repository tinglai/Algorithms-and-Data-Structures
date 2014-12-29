#include "config.h"
#include <iostream>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

Config::Config():isRouteQueue(), isOutputMap(1){}

bool Config::get_RouteConfig(){
	return isRouteQueue;
}

bool Config::get_OutputConfig(){
	return isOutputMap;
}

void Config::setup(int argc, char *const *argv){
	bool isQ = 0;
	bool isS = 0;
	const struct option longopts[] = {
		{"stack", no_argument, 0, 's'},
		{"queue", no_argument, 0, 'q'},
		{"output", optional_argument, 0, 'o'},
		{"help", no_argument, 0, 'h'},
	};
	int option_index = 0;
	int c = getopt_long(argc, argv, "sqo:h", longopts, &option_index);
	while (c != -1)
	{
		switch(c){
			case 'h':
				cout << "output help!! \n";
				exit(0);
				break;
			case 's':
				if (isS != 1)
					isS = 1;
				else{ 
					cerr << "More than one S argument in the command line!!\n";
					exit(1);
				}
				break;
			case 'q':
				if (isQ != 1)
					isQ = 1;
				else{ 
					cerr << "More than one Q argument in the command line!!\n";
					exit(1);
				}
				break;
			case 'o':
				if (*optarg == 'M')
					isOutputMap = 1;
				else if(*optarg == 'L')
					isOutputMap = 0;
				break;
			case '?':
				break;
			default:
				abort();
		}
		c = getopt_long(argc, argv, "sqo:h",longopts, &option_index);
	}
	if (isS && isQ){
		cerr << "There should be exact one of S and Q!!!\n" << flush;
		exit(1);
		}
	if (!(isS || isQ)){
		cerr << "Route config cannot be empty!!!\n";
		exit(1);
		}
        	isRouteQueue = isQ;
}
