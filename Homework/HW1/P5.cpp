#include <iostream>
#include <cstdlib>

using namespace std;

int **Multiply(int **m1, int **m2, int n){
	int **result = new int*[n];
	for (int i = 0; i < n; i++)
	{
		result[i] = new int(0);
	}
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

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	int **m1 = new int*[n];
	int **m2 = new int*[n];
	for (int i = 0; i < n; i++)
	{
		m1[i] = new int[n];
		m2[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			m1[i][j] = rand() % 100 + 1; 
			m2[i][j] = rand() % 100 + 1;
		}

	}

	int **result;
	result = Multiply(m1,m2,n);
	cout << "The result is : " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i < n; i++)
		{
			//delete[] result[i];
			delete[] m1[i];
			delete[] m2[i];
		}
	//delete[] result;
	//delete[] m1;
	delete[] m2;
	
	return 0;
}
