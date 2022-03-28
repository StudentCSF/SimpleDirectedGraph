#include <iostream>

#include "DirectedGraph.h"

typedef unordered_map<int, unordered_set<int>*> IntMap;

int main()
{
	DirectedGraph<int> g;// = new DirectedGraph<int>();
	g.add_edge(2, 3);
	g.add_edge(3, 4);
	for (DirectedGraph<int>::DFSIterator it = g.begin(2); it != g.end(); it++)
	{
		cout << "out: " << *it << endl;
	}
	//delete g;
	return 0;
}