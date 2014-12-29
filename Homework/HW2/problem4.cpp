#include <vector>
#include <utility>
#include <iostream>

using namespace std;

pair<vector<double>::const_iterator, vector<double>::const_iterator>
get_range(const vector<double> & arr, double diff){
	pair<vector<double>::const_iterator, vector<double>::const_iterator> range;
	unsigned int left = 0;
	unsigned int right = 0;
	unsigned int myLeft = left;
	unsigned int myRight = right;
	double tempDiff = arr[right] - arr[left];
	double myDiff = arr[right] - arr[left];
	while (right < arr.size() && left < arr.size()){
		if (tempDiff <= diff){
			right++;
			tempDiff = arr[right] - arr[left];
			if ((tempDiff - diff) * (tempDiff - diff) 
			< (myDiff - diff) * (myDiff - diff)){
				myDiff = tempDiff;
				myLeft = left;
				myRight = right;
			}
		}
		else if (arr[right] - arr[left] > diff){
			left++;
			tempDiff = arr[right] - arr[left];
			if ((tempDiff - diff) * (tempDiff - diff) < 
				             (myDiff - diff) * (myDiff - diff)){
				myDiff = tempDiff;
				myLeft = left;
				myRight = right;
			}
		}
		else{
			range.first = arr.begin() + left;
			range.second = arr.begin() + right;
			return range;
		}
	}
	range.first = arr.begin() + myLeft;
	range.second = arr.begin() + myRight;
	return range;
}


