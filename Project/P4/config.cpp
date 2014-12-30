#include "config.h"
#include <iostream>
#include <getopt.h>
#include <stdlib.h>

using namespace std;

void Config::setup(int argc, char *const *argv){
	const struct option longopts[] = {
		{"mode", required_argument, 0, 'm'},
		{"help", no_argument, 0, 'h'},
	};
	int option_index = 0;
	int c = getopt_long(argc, argv, "m:h", longopts, &option_index);
	while (c != -1)
	{
		switch(c){
			case 'h':
				cout << "wo you yi zhi xiao mao lv wo cong lai ye bu qi ^_^ \n";
				exit(0);
				break;
			case 'm':
				if (isMSet == false){
					isMSet = true;
					if(string(optarg) == "MST"){
						mode = 'm';
					}
					else if(string(optarg) == "OPTTSP")
						mode = 'o';
					else if(string(optarg) == "FASTTSP")
						mode = 'f';
					else{
						cerr << "Error in mode arguement!\n";
						exit(1);
					}
				}
				else{
					cerr << "Mode has been set!\n";
					exit(1);
				}
				break;
			case '?':
				break;
			default:
				abort();
		}//switch
		c = getopt_long(argc, argv, "m:h",longopts, &option_index);
	}//while
	if (isMSet == false){
		cerr << "Mode has not been set yet!!!\n";
		exit(1);
	}
}//func


