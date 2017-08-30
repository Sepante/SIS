#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <numeric>
#include <ctime>
#include <math.h>
using namespace std;

int L = pow (2, 6);
//int n = L*L;
int n = 5;
vector<vector<bool> > adj_matrix(n);
void constr_erdos(float cnct_prob)
{
	float r;
	
	for (int i=0; i<= n-1; i++)
	{
		adj_matrix[i].resize(n); //the size of every row has to be initialized first.
	}
	for (int i=0; i<= n-1; i++)
		for (int j=i+1; j<= n-1; j++)
		{
			r = ((float) rand() / (RAND_MAX));
			if(r <= cnct_prob)
				adj_matrix[i][j] = adj_matrix[j][i] = 8;
		}

}

int main()
{
	srand(time(0));
	constr_erdos(0.5);
	for (int i=0; i<= n-1; i++)
	{
		for (int j=0; j<=n-1; j++)
			cout<<adj_matrix[i][j]<<"\t";
		cout<<endl;
	}
}

