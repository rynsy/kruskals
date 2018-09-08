/*
	To do:
		Sanitize input
		Add try/catch
		handle variety of input
		Add features from Milestone 3
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define edge pair <int, int>
#define weighted pair<int, edge>
#define F first
#define S second


map <string, int> city_indexer;
vector< weighted > graph;

const int MAX = 10000;
const bool DATA_COLLECTION = true;

int num_cities, direct_links, num_edges, comp;

class Union_Find 
{
	public: 
	
	int id[MAX], rank[MAX], edges, w;
	set<int> nodes;
	
	Union_Find(int x)
	{
		for (int i = 0; i < x; i++)
		{
			id[i] = i;
			rank[i] = 1;
		}
		edges = w = 0;	
	}

	bool Complete_Path()
	{
		set<int> complete;
		for(int i = 0; i < num_cities; i++)
			complete.insert(i);
		return complete == nodes;	
	}

	int Get_Root(int x)
	{
		while(x != id[x])
		{
			comp += 1;
			id[x] = id[id[x]];
			x = id[x];
		}
		return x;
	}
	

	int Find(int u, int v)
	{
		comp += 1;
		return Get_Root(u) == Get_Root(v);
	}

	void Union(int u, int v)
	{
		int i = Get_Root(u);
		int j = Get_Root(v);
		
		nodes.insert(u);
		nodes.insert(v);		

		if(rank[i] < rank[j])
		{
			id[i] = j;
			rank[j] += rank[i];
		}		
		else
		{
			id[j] = i;
			rank[i] += rank[j];
		}
		edges += 1;
		comp += 1;
	}
};

void write_results(double runtime)
{
	ofstream results;
	results.open("results.txt", ios::app);
	results << num_cities << ":" << num_edges << ":" << comp << ":" << runtime << "\n";
	results.close();
}

void create_graph() 
{ 
	int weight;
	weight = 0;
	for (int i = 0; i < num_cities; i++) 
	{
		for( int j = i; j < num_cities; j++) 
		{
			cin >> weight;
			if( weight > 0 )	//Don't add edges with weight <= 0 
			{
				graph.push_back(weighted(weight, edge(i,j)));
			}
		}
	}
}

void load_indexer() 
{ 
	string city_name;
	cin.ignore( 256 , '\n' );
	for (int i = 0; i < num_cities; i++) 
	{ 
		cin.sync();
		getline(cin,city_name);
		city_indexer[city_name] = i;
	}
}

bool compare_pair(edge x, edge y)
{
	return ((x.F == y.F) && (x.S == y.S)) || ((x.S == y.F) && (x.F == y.S));
}

struct CompareEdge
{
	CompareEdge(edge val) : val_(val) {}
	bool operator()(const weighted elem) const 
	{
		return compare_pair(val_,elem.S);
	}
	private:
		edge val_;
};

void load_links( Union_Find &MST) 
{ 
	string city_name, temp;
	int i = 0;
	edge e;
	cin.ignore( 256, '\n' );
	for(int i=0; i < direct_links; i++) 
	{
		cin.sync();
		getline(cin,city_name);
		getline(cin,temp);
		e = edge(city_indexer[city_name],city_indexer[temp]);
		auto weight = find_if(graph.begin(), graph.end(), CompareEdge(e));
	
		num_edges--;
		MST.w += weight->F;
		MST.Union(e.F,e.S);
		graph.erase(weight);		
	}	
}


int Kruskal()
{
	Union_Find DS(num_cities);
	int u, v;
	sort(graph.begin(), graph.end());

	if (direct_links > 0) 
		load_links(DS);

	for(int i = 0; i < graph.size(); i++)
	{
		u = graph[i].S.F;
		v = graph[i].S.S;
		
		if( !DS.Find(u, v) )
		{
			DS.Union(u,v);
			DS.w += graph[i].F;
		}
	}
	if(DS.Complete_Path())
	{
		cout << endl << DS.edges
	     		<< endl << DS.w
	     		<< endl << endl; 
	}
	else
	{
		cout << endl << "IMPOSSIBLE" << endl << endl;
	}
}

int main() 
{
	clock_t start;
	double runtime = 0.0;

	comp = 0;
	cin >> num_cities;
	cin >> direct_links;
	num_edges = (num_cities * (num_cities + 1) / 2); //Estimated number of edges. sum = n(n+1)/2
	load_indexer();
	create_graph();

	start = clock();
	Kruskal();
	runtime = (clock() - start) / (double) (CLOCKS_PER_SEC / 1000);

	if (DATA_COLLECTION) write_results(runtime);

	return 0;
}
