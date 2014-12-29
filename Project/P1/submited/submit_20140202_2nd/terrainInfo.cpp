#include "terrainInfo.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <stdlib.h>

using namespace std;

int listRead(istream& in, vector<TerrainInfo>& ter, int farmSize, int farmNum){
	TerrainInfo rec;
	int start = 0;
	/*initial all the terrains as walkable fields by default*/
	for (int i = 0; i < farmNum*farmSize*farmSize; i++){
		rec.c = '.';
		rec.parent = '0';
		ter.push_back(rec);
	}

	/*read the lines after the first three lines*/
	string s;
	char t, c;
	int x; 
	int count = 0;
	while(in){
		in.get(t);

		/*ignore the comment lines*/
		while(t == '/'){
			getline(in, s);
			in.get(t);
		}

		/*when encounter to blank line, stop reading*/
		if (t == ' ' || t == '\n'){
			in.ignore(INT_MAX);
			//ignore the rest of input if it comes to a blank line
			return start;
		}

		/*read the 1st coordinate*/
		in >> x >> t; 
		/*illegal coordinates check*/
		if (x >= farmSize || x < 0){
			cerr << "Row of index " << x << " does not exit!\n";
			exit(1);
		}
		count += x * farmSize;
		
		/*read the 2nd coordinate*/
		in >> x >> t;
		/*illegal coordinates check*/
		if (x >= farmSize || x <0){
			cerr << "Column of index " << x << " does not exit!\n";
			exit(1);
		}
		count += x;

		/*read the 3rd coordinate*/
		in >> x >> t;
		if (x >= farmSize || x <0){
			cerr << "Fram " << x << " does not exit!\n";
			exit(1);
		}
		count += x*farmSize*farmSize;

		/*read character*/
		in >> c >> t;
		in.get();//discard newline

		/*check illegal input characters*/
		if (c != '.' && c != '>' && c != '<' && c != '#'
 		    && c != 'B' && c != 'S'){
			cerr << "illegal input characters!!\n";
			exit(1);
		}

		/*change the character of corresponding terrain*/
		ter[count].c = c;

		if (c == 'S'){
			start = count;
		}

		count = 0;
	}
	return start;
}

int mapRead(istream& in, vector<TerrainInfo>& ter){
	TerrainInfo rec;
	string s;
	char c;
	int count = 0;
	int start = 0;
	while(in){
		in.get(c);
		/*ignore the comment lines*/
		while(c == '/'){
			getline(in,s);
			in.get(c);
		}

		/*when encounter to blank line, stop reading*/
		if (c == ' ' || c == '\n'){
			in.ignore(INT_MAX);
			//ignore the rest of input if it comes to a blank line
			return start;
		}

		/*read non-empty non-comment line*/
		while (c != '\n'){
			/*check illegal input characters*/
			if (c != '.' && c != '>' && c != '<' && c != '#'
 		    	    && c != 'B' && c != 'S'){
				cerr << "illegal input characters!!\n";
				exit(1);
			}

			rec.c = c;
			rec.parent = '0';
			ter.push_back(rec);

			if (c == 'S'){
				start = count;
			}
			in.get(c);
			count++;
		}
	}
	return start;
}
