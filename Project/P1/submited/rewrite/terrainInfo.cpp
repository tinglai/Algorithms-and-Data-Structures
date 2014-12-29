#include "terrainInfo.h"
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <stdlib.h>

using namespace std;

int listRead(istream& in, vector<TerrainInfo>& ter, int farmSize, int farmNum){
	int start = -1;

	/*read the lines after the first three lines*/
	string s;
	char t, c;
	int x, y, l; 
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
		if (x >= farmSize || x< 0){
			cerr << "Row of index " << x << " does not exit!\n";
			exit(1);
		}
		if (y >= farmSize || y< 0){
			cerr << "Column of index " << y << " does not exit!\n";
			exit(1);
		}
		if (l >= farmNum || l< 0){
			cerr << "Farm " << l << " does not exit!\n";
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
		if (c != '.'){
			ter[l * (farmSize*farmSize) + x * farmSize + y].c = c;
		}

		if (c == 'S'){
			start = l * (farmSize*farmSize) + x * farmSize + y;
		}
	}
	return start;
}

int mapRead(istream& in, vector<TerrainInfo>& ter){
	string s;
	char c;
	int count = 0;
	int start = -1;
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

			if (c != '.'){
			ter[count].c = c;
			}

			if (c == 'S'){
				start = count;
			}
			in.get(c);
			count++;
		}
	}
	return start;
}
