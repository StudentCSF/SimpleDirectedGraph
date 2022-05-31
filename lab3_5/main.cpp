#include <iostream>

#include "MyDirectedGraph.h"

using namespace std;

int main()
{
	
	MyDirectedGraph<int> g, g2;
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(1, 4);
	g.add_edge(4, 5);
	g.add_edge(3, 8);
	g.add_edge(5, 6);
	g.add_edge(6, 7);
	g.add_edge(2, 6);

	cout << "BFS:\n";
	for (MyDirectedGraph<int>::Iterator it = g.begin_bfs(1); it != g.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	cout << "--------\n";

	g2 = g;
	g.clear();
	
	g2.remove_edge(2, 6);
	/*
	g2.remove_edge(1, 2);
	g2.remove_edge(2, 3);
	g2.remove_edge(1, 4);
	g2.remove_edge(4, 5);
	g2.remove_edge(3, 8);
	g2.remove_edge(5, 6);
	g2.remove_edge(6, 7);
	g2.remove_edge(2, 6);
	*/
	cout << "BFS:\n";
	for (MyDirectedGraph<int>::Iterator it = g2.begin_bfs(1); it != g2.end(); it++)
	{
		cout << "out: " << *it << endl;
	}

	cout << endl << "----------------------------" << endl << endl;

	MyDirectedGraph<string>* mg2 = new MyDirectedGraph<string>();
	mg2->add_edge("1s", "2s");
	mg2->add_edge("2s", "3s");
	mg2->add_edge("1s", "4s");
	mg2->add_edge("4s", "5s");
	mg2->add_edge("3s", "8s");
	mg2->add_edge("5s", "6s");
	mg2->add_edge("6s", "7s");
	mg2->add_edge("2s", "6s");

	cout << "DFS:\n";
	for (MyDirectedGraph<string>::Iterator it = mg2->begin_dfs("1s"); it != mg2->end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	mg2->remove_vertex("6s");
	/*
	mg2->remove_vertex("7s");
	mg2->remove_vertex("8s");
	mg2->remove_vertex("3s");
	mg2->remove_vertex("2s");
	mg2->remove_vertex("1s");
	mg2->remove_vertex("4s");
	mg2->remove_vertex("5s");
	*/
	cout << "--------\n";
	cout << "DFS:\n";
	for (MyDirectedGraph<string>::Iterator it = mg2->begin_dfs("1s"); it != mg2->end(); it++)
	{
		cout << "out: " << *it << endl;
	}
	delete mg2;
	cout << endl;
	return 0;
}