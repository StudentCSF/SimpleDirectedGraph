#include <iostream>

#include "MyDirectedGraph.h"

using namespace std;

int main()
{
	MyDirectedGraph<int> g, g2;// = new DirectedGraph<int>();
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(4, 8);
	g.add_edge(8, 7);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(7, 5);
	g.add_edge(1, 7);
	g.add_edge(6, 9);
	g2 = g;
	g.clear();
	cout << "DFS:\n";
	for (MyDirectedGraph<int>::Iterator it = g2.begin_dfs(1); it != g2.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	//g.remove_vertex(6);
	cout << "--------\n";
	/*
	g2.remove_edge(1, 4);
	g2.remove_edge(1, 5);
	g2.remove_edge(4, 8);
	g2.remove_edge(8, 7);
	g2.remove_edge(5, 6);
	g2.remove_edge(6, 4);
	g2.remove_edge(7, 5);
	g2.remove_edge(1, 7);
	g2.remove_edge(6, 9);
	*/
	//cout << "----------------------\n";
	cout << "BFS:\n";
	for (MyDirectedGraph<int>::Iterator it = g2.begin_bfs(1); it != g2.end(); it++)
	{
		cout << "out: " << *it << endl;
	}

	//cout << endl << g2.size() << endl << endl;

	MyDirectedGraph<string>* mg2 = new MyDirectedGraph<string>();
	mg2->add_edge("1s", "4s");
	mg2->add_edge("1s", "5s");
	mg2->add_edge("4s", "8s");
	mg2->add_edge("8s", "7s");
	mg2->add_edge("5s", "6s");
	mg2->add_edge("6s", "4s");
	mg2->add_edge("7s", "5s");
	mg2->add_edge("1s", "7s");
	mg2->add_edge("6s", "9s");
	cout << "DFS:\n";
	for (MyDirectedGraph<string>::Iterator it = mg2->begin_dfs("1s"); it != mg2->end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	//mg2->remove_vertex("6s");
	cout << "--------\n";
	cout << "BFS:\n";
	for (MyDirectedGraph<string>::Iterator it = mg2->begin_bfs("1s"); it != mg2->end(); it++)
	{
		cout << "out: " << *it << endl;
	}
	delete mg2;
	//cout << "\nEverything is OK!\n";
	cout << endl;
	return 0;
}