#include <string>
#include <iostream>

using namespace std;

void fixDown(string& s, int n, int k){
	char temp;
	while (2 * k <= n){
		int j = 2 * k;
		if (j < n && s[j-1] < s[j])
			j++;
		if (s[k-1] >= s[j-1])
			break;
		temp = s[k-1];
		s[k-1] = s[j-1];
		s[j-1] = temp;
		k = j;
	}
}

void buildHeap(string& s, int n){
	int k = n;
	while (k/2 > 0){
		fixDown(s, n, k/2);
		k = k - 2;
	}
}

void count_chars(string s){
	int n = s.size();
	buildHeap(s, n);
	char temp;
	while (n > 1){
		temp = s[0];
		s[0] = s[n-1];
		s[n-1] = temp;
		n = n - 1;
		fixDown(s, n, 1);
	}

	int count = 0;
	char out = s[0];
	
	for(unsigned int i = 0; i <= s.size(); i++){
		if (s[i] != out){
			cout << '(' << out << ',' << count << ')'; 
			count = 0;
			out = s[i];
			if (i != s.size()){
				cout << ',';
			}
		}
		count++;
	}
}
