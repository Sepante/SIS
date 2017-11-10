#include "global.h"
#include "SIR.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <ctime>
#include <math.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/properties.hpp>
#include <boost/config.hpp>
#include <boost/graph/connected_components.hpp>

using namespace boost;
using std::cout;
using std::endl;
using std::vector;



float r = 0.5, p = 0.25, q = 1;
float percol_prob = 0;
//int actives = 0;
std::set <int> actives={};
int runNum = 400;

//int infect_cluster;



//typedef enum { neither, dis_one, dis_two, both } State;

class Interaction
{
	public:
	int present = 1;
};


//typedef adjacency_list<listS, vecS, undirectedS, SIR> Network;
typedef adjacency_list<listS, vecS, undirectedS, SIR, Interaction> Network;
typedef graph_traits<Network>::edges_size_type Edge_Num;
typedef graph_traits<Network>::vertices_size_type Vertex_Num;
typedef graph_traits<Network>::vertex_iterator Vertex_iter;
typedef graph_traits<Network>::vertex_descriptor Vertex;
typedef graph_traits<Network>::edge_descriptor Edge;
typedef graph_traits<Network>::edge_iterator Edge_iter;
//Vertex_Num vert_num = 131072;
Vertex_Num vert_num = 256;
//float cnct_prob = (float)4/(float)vert_num;
//float cnct_prob = 1;

//Network society(vert_num);
Network society;
Network society_origin;

void init_states()
{
	for( Vertex vd : make_iterator_range( vertices(society) ) )
	{
		society[vd].health = 1;
		society[vd].future = 1;
	}
	int seed = rand() % vert_num;
	//int seed = 2;
	Vertex v = vertex(seed, society);
	society[v].health = 6;
	society[v].future = 6;
	//society[v].health = 2;
	//society[v].future = 2;
	society_origin = Network(society);
	actives = {};
	actives.insert(seed);
}

int cluster_size()
{
	int infect_cluster = 0;
	for( Vertex vd : make_iterator_range( vertices(society) ) )
		if (society[vd].health != 1)
		{
			infect_cluster++;
		}
	return infect_cluster;
}
/*
void kill_some_edges(float p)
{
	society = society_origin;
	Edge_iter vi, vi_end, next;
	boost::tie(vi, vi_end) = edges(society);
	for (next = vi; vi != vi_end; vi = next)
	{
		++next;
		if(dice (p) )
			remove_edge(*vi, society);
	}
}
*/
void cons_Erdos(int n)
{
	float cnct_prob = (float)4/(float)n;
	society.clear();
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = i+1; j < n; j++)
		{
			if ( dice(cnct_prob) )
			{
				add_edge(i, j, society);
				//add_edge(j, i, society);
			}
		}
	}
	//std::cout << "Erdos running" << '\n';
}

int main()
{
	clock_t begin = clock();
	std::ofstream fout;
	fout.open("cdata.txt");

	srand(time(0));
	//std::vector<int> n_set={128, 256, 512,1024, 2048, 4096, 8192, 16384};
	//std::vector<int> n_set={16384};
	std::vector<int> n_set={8192};
	std::vector<float> p_set={0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.5, 0.6, 1};
	//	std::vector<float> p_set={0.8, 0.9, 1};
	std::vector<float> q_set={0.1 ,0.5, 0.8, 1};

	q_set={1};
	//p_set={0.25};
	//write system properties to file, for later use in python.
	fout<<n_set.size()<<"\n";
	fout<<p_set.size()<<"\n";
	fout<<q_set.size()<<"\n";
	fout<<runNum<<"\n";


	for(int nindex=0; nindex<=n_set.size()-1; nindex++)
		fout<<n_set[nindex]<<"\n";
	for(int pindex=0; pindex<=p_set.size()-1; pindex++)
		fout<<p_set[pindex]<<"\n";
	for(int qindex=0; qindex<=q_set.size()-1; qindex++)
		fout<<q_set[qindex]<<"\n";

	//Edge_Num edge_num = 0;
	//Network society(ERGen(gen, vert_num, edge_num), ERGen(), vert_num);
//cout << "cnct_prob: "<< cnct_prob << endl;
/*
	std::ifstream  fin;
	fin.open("input_matrix.txt");
	if (!fin)
	{
		std::cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}
	std::string text;
	int i, j;
	while (fin >> i && fin >>j)
	{
		if(i>=0)
			add_edge(i, j, society);
		else
			remove_edge(-i, j ,society);
		//std::cout << i << '-';
		//std::cout << j << '\n';
		fin>>text;
	}
*/
	//boost::print_graph(society);
	for (size_t pindex = 0; pindex < p_set.size(); pindex++)
	{
		p = p_set[pindex];
		for (size_t qindex = 0; qindex < q_set.size(); qindex++)
		{
			q = q_set[qindex];
			for(int nindex=0; nindex<n_set.size(); nindex++)
			{
				vert_num = n_set[nindex];
				cons_Erdos(vert_num);
				for (size_t run = 0; run < runNum; run++)
				{
					//std::cout << "run: " << run << '\n';
					init_states();

					for (size_t t = 0; t <= 1000000 && actives.size() >= 1 ; t++)
					{
						//kill_some_edges(percol_prob);
						//infect_cluster = 0;
						//for( Vertex vd : make_iterator_range( vertices(society) ) )
						Vertex vd;
						for (std::set<int>::iterator it=actives.begin(); it!=actives.end(); it++)
					  {
							vd = *it;
							//std::cout << "iterating vd: " << vd << '\n';
							if (society[vd].supply() != 1)
							{
								for ( Vertex vi : make_iterator_range( adjacent_vertices(vd, society) ) )
								{
									society[vi].turn_I( society[vd].supply() );
								}
							}
					  }
						for (std::set<int>::iterator it=actives.begin(); it!=actives.end(); it++)
						{
							vd = *it;
							//cout << "set item: " << vd << ",  health: " << society[vd].health << endl;
						}

						actives = {};
						for( Vertex vd : make_iterator_range( vertices(society) ) )
						{
							if(society[vd].update() != 1)
							{
								actives.insert(vd);
							}
							//cout << vd << ": " << society[vd].health << endl;
						}
						//std::cout << '\n';
					//	std::cout << "t: " << t << '\n';
					}
					if(run % 200 == 0)
						std::cout << "n: " << vert_num << ", p: " << p << ", q: " << q << ", run: " << run << std::endl;
					fout << cluster_size() << '\n';

				}
			}
		}
	}


	clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time: " << elapsed_secs << '\n';



	//cout<<cnct_prob<<endl;
//	boost::print_graph(society);
//	std::cout << "next:" << '\n';
//	boost::print_graph(society_origin);
}