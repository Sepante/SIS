#include <iostream>
#include <vector>
using namespace std;

int L = 4;
int n = 4;
float cnct_prob = (float)4/(float)n;
vector<vector<int>>  adj_matrix(n, vector<int>(n));

void constr_erdos(float cnct_prob) //construct adjacency matrix in the case of erdos renyi graph.
{
	float r;
	for (int i=0; i<= n-1; i++)
		for (int j=i+1; j<= n-1; j++)
		{
			r = ((float) rand() / (RAND_MAX));
			if(r <= cnct_prob)
				adj_matrix[i][j] = adj_matrix[j][i] = 1;
			else
				adj_matrix[i][j] = adj_matrix[j][i] = 0;
		}

		
						//output				
				/*
		for(int i=0; i<=n-1; i++)
		{
			for(int j=0; j<=n-1; j++)
				cout<<adj_matrix[i][j]<<"\t";
			cout<<endl;
		}
*/

}



int main()
{
	for(int temp=0;temp<=2;temp++)
	{
		cout<<temp<<endl<<endl;
		constr_erdos(0.5);
		cout<<endl;
			//output				
	
		for(int i=0; i<=n-1; i++)
		{
			for(int j=0; j<=n-1; j++)
				cout<<adj_matrix[i][j]<<"\t";
			cout<<endl;
		}
	cout<<endl;
	}
}
