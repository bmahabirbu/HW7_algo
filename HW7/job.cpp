//https://www.youtube.com/watch?v=rKQaZuoUR4M
//https://www.geeksforgeeks.org/detect-cycle-undirected-graph/?ref=rp
#include "job.h"
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

class Graph
{
	
public:
	int v;

	list<int> *adj;
	
	Graph(int v)
	{
		this->v = v;
		adj = new list<int>[v];
	}

	void addEdge(int i, int j)
	{
		adj[i].push_back(j);
		
	}

};


bool isCyclicUtil(int v, bool visited[], Graph g, bool *recStack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack 
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i;
		for (i = g.adj[v].begin(); i != g.adj[v].end(); ++i)
		{
			//save an array to keep track of nodes
			if (!visited[*i] && isCyclicUtil(*i, visited, g, recStack))
				return true;
			else if (recStack[*i])
				return true;
		}

	}
	recStack[v] = false;  // remove the vertex from recursion stack 
	return false;
}

bool isCyclic(int v, Graph g)
{
	// Mark all the vertices as not visited and not part of recursion 
   // stack 
	bool *visited = new bool[v];
	bool *recStack = new bool[v];
	for (int i = 0; i < v; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	// Call the recursive helper function to detect cycle in different 
	// DFS trees 
	for (int i = 0; i < v; i++)
		if (isCyclicUtil(i, visited, g, recStack))
			return true;

	return false;
}


bool canFinish(int n, vector<pair<int, int>> &dependencies)
{
	Graph g(n);
	
	for(int i = 0; i < dependencies.size(); i++)
	{
		g.addEdge(dependencies[i].first-1, dependencies[i].second-1);
	}
	
	isCyclic(n,g) ? cout << "Graph contains cycle\n" :
		cout << "Graph doesn't contain cycle\n";
	
	return (isCyclic(n,g));
	
	
}

bool canRun(int n, vector<pair<int, int>> &dependencies, int j, int i)
{
	Graph g(n);
	
	for (int i = 0; i < dependencies.size(); i++)
	{
		g.addEdge(dependencies[i].first - 1, dependencies[i].second - 1);
	}
	
	if(isCyclic(n, g))
	{
		return false;
	}
	
		for (auto i = g.adj[j-1].begin(); i != g.adj[j-1].end(); ++i)
		{
			cout << *i+1 << endl;
		}
}

