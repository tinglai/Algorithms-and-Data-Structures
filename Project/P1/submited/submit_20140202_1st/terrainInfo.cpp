#include "terrainInfo.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <stdlib.h>

using namespace std;

unsigned int listRead(istream& in, vector<TerrainInfo>& ter, unsigned int farmSize, unsigned int farmNum){
	TerrainInfo rec;
	unsigned int start = 0;
	/*initial all the terrains as walkable fields by default*/
	for (unsigned int h = 0; h < farmNum; h++){
			for (unsigned int i = 0; i < farmSize; i++){
				for (unsigned int j = 0; j < farmSize; j++){
					rec.x = i;
					rec.y = j;
					rec.l = h;
					rec.c = '.';
					rec.parent = '0';
					rec.store = 0;
					ter.push_back(rec);
				}
			}
		}

	/*read the lines after the first three lines*/
	string s;
	char t, c;
	unsigned int x, y, l; 
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

		/*read x, y, l*/
		in >> x >> t >> y >> t >> l >> t;

		/*illegal coordinates check*/

		if (x >= farmSize){
			cerr << "Row of index " << x << " does not exit!\n";
			exit(1);
		}

		if (y >= farmSize){
			cerr << "Column of index " << y << " does not exit!\n";
			exit(1);
		}

		if (l >= farmSize){
			cerr << "Fram " << l << " does not exit!\n";
			exit(1);
		}
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
		if (c != '.')
		ter[l * (farmSize*farmSize) + x * farmSize + y].c = c;
		if (c == 'S'){
			start = l * (farmSize*farmSize) + x * farmSize + y;
		}
	}
	return start;
}

unsigned int mapRead(istream& in, vector<TerrainInfo>& ter, unsigned int farmSize){
	TerrainInfo rec;
	string s;
	char c;
	unsigned int count = 0;
	unsigned int start = 0;
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
			rec.l = count / (farmSize * farmSize);
			rec.x = (count - rec.l * (farmSize * farmSize)) / farmSize;
			rec.y = count % farmSize;
			rec.parent = '0';
			rec.store = 0;
			ter.push_back(rec);

			if (c == 'S'){
				start = rec.l * (farmSize*farmSize) + rec.x * farmSize + rec.y;
			}
			in.get(c);
			count++;
		}
	}
	return start;
}
