#include <iostream>
#include <cstdlib>

using namespace std;

int **Multiply(int *m1[], int *m2[], int n){
	int **result;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				result[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	return result;
}

int main(){
	cout << "Please enter the size of matrices: " << endl;
	int n;
	cin >> n;
	int m1[n][n], m2[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m1[i][j] = rand() % 1 + 100;
			m2[i][j] = rand() % 1 + 100;
		}
	}
	int **result;
	result = Multiply(&m1,&m2,n);
}
