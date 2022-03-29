#include <iostream>

#include "DirectedGraph.h"

typedef unordered_map<int, unordered_set<int>*> IntMap;

int main()
{
	DirectedGraph<int> g;// = new DirectedGraph<int>();
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(4, 8);
	g.add_edge(8, 7);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(7, 5);
	g.add_edge(1, 7);
	for (DirectedGraph<int>::DFSIterator it = g.begin(2); it != g.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	//delete g;
	return 0;
}