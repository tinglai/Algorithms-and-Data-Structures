#include <vector>
#include <iostream>
#include <utility>

using namespace std;

pair<vector<double>::const_iterator, vector<double>::const_iterator>
get_range(const vector<double>&, double);

int main(){
	double diff = -0.5;
	vector<double> arr(1,0);
	/*arr[1] = 2.7;
	arr[2] = 2.7;
	arr[3] = 3.8;
	arr[4] = 5.5;
	arr[6] = 6.3476;
	arr[5] = 6.22;
	arr[7] = 8.152;
	*/
	pair<vector<double>::const_iterator,vector<double>::const_iterator> range = get_range(arr, diff);
	vector<double>::iterator debug = arr.begin();
	cout << *range.first << ' ' << *range.second << endl;
	return 0;
}
