#include <getopt.h>
#include "config.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

Config::Config(): container(0), arrow("n"), v(0), de(0), fileName(){}

int Config::getContainer(){
	return container;
}

string Config::getArrow() const{
	return arrow;
}

unsigned int Config::getV(){
	return v;
}

bool Config::getDe() const{
	return de;
}

string Config::getFileName(){
	return fileName;
}

void Config::setup(int argc, char *const* argv){
	bool isArrowSet = 0;
	bool isVSet = 0;
	const struct option longopt[] = {
		{"help", no_argument, 0, 'h'},
		{"container", required_argument, 0, 'c'},
		{"arraw", required_argument, 0, 'a'},
		{"verbose", required_argument, 0, 'v'},
		{"debug", no_argument, 0, 'd'}
	};
	int option_index = 0;
	int c = getopt_long(argc, argv, "hc:a:v:d", longopt, &option_index);
	while (c != -1){
		switch (c){
			case 'h':
				cout << "info from Appendix: A\n";
				exit(0);
				break;
			case 'c':
	   if (container == 0){
		if(string(optarg) == "BINARY") container = 1;
		else{ 
			if(string(optarg) == "POOR_MAN") container = 2;
			else{
				if(string(optarg) == "SORTED") container = 3;
 				else{ 
					if(string(optarg) == "PARING") container = 4;
					else {
						cerr << "error in container option!\n";
						exit(1);
					}
				}
			}
		}
	   }
				else{
					cerr << "error in container option!\n";
					exit(1);
				}
				break;
			case 'a':
				if (isArrowSet == 0 && (string(optarg)== "LIGHT"
						       ||string(optarg) == "NORMAL")){
					arrow = string(optarg);
					isArrowSet = 1;
				}
				else{
					cerr << "error in arrow option!\n";
					exit(1);
				}
				break;
			case 'v':
				if (isVSet == 0 && atoi(optarg) >= 0){
					v = atoi(optarg);
					isVSet = 1;
				}
				else{
					cerr << "error in verbose option!\n";
					exit(1);
				}
				break;
			case 'd':
				de = 1;
				break;
			case '?':
				break;
			default:
				abort();
			}
		c = getopt_long(argc, argv, "hc:a:v:d", longopt, &option_index);
	}//while
	if (container == 0){
		cerr << "No container setup yet!!\n";
		exit(1);
	}
	if (isArrowSet == 0){
		cerr << "No arrow setup yet!!\n";
		exit(1);
	}
	if (optind == argc - 1)
		fileName = argv[optind];
	else{
		cerr<< "no input file can be found!!\n";
		exit(1);
	}
}//setup
