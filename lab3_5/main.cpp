#include <iostream>

#include "MyDirectedGraph.h"

using namespace std;

class Node
{
public:
	int v;
	MySet<int> set;
};

int main()
{
	if (false)
	{
		MySet<Node*>* set = new MySet<Node*>();
		Node* n1 = new Node(), * n2 = new Node();
		n1->v = 1;
		n2->v = 2;
		n1->set.add(3);
		n1->set.add(4);
		n2->set.add(5);
		n2->set.add(6);
		set->add(n1);
		set->add(n2);
		cout << set->size();
		for (MySet<Node*>::Iterator it = set->begin(); it != set->end();)
		{
			cout << 8;
			Node* c = *it;
			for (MySet<int>::Iterator it2 = c->set.begin(); it2 != c->set.end();)
			{
				cout << 9;
				c->set.erase(it2);
				cout << (it2 == c->set.end());
			}
			set->erase(it);
			delete c;
			break;
			cout << "\n" << (it == set->end());
		}
		for (MySet<Node*>::Iterator it = set->begin(); it != set->end(); it++)
		{
			cout << *it;
		}
		cout << set->size();
		if (true) return 0;
		MySet<int> s;
		s.add(1);
		s.add(2);
		s.add(3);
		for (MySet<int>::Iterator iter = s.begin(); iter != s.end(); iter++)
		{
			cout << -1;
		}
		cout << s.size();
		MySet<int>::Iterator it = s.find(3);
		s.erase(it);
		it = s.find(2);
		s.erase(it);
		it = s.find(1);
		s.erase(it);
		for (MySet<int>::Iterator iter = s.begin(); iter != s.end(); iter++)
		{
			cout << -1;
		}
		cout << s.size();
		if (true) return 0;
	}/*
	MyDirectedGraph<int> g, g2;// = new DirectedGraph<int>();
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(5, 1);
	g.add_edge(4, 8);
	g.add_edge(8, 7);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(6, 4);
	g.add_edge(7, 5);
	g.add_edge(1, 7);
	g.add_edge(6, 9);
	g2 = g;
	g.clear();
	cout << "BFS:\n";// << (g2.saiz() == g2.size()) << endl;
	for (MyDirectedGraph<int>::Iterator it = g2.begin_bfs(1); it != g2.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	cout << "--------\n";
	
	g2.remove_edge(1, 4);
	g2.remove_edge(1, 5);
	g2.remove_edge(4, 8);
	for (MyDirectedGraph<int>::Iterator it = g2.begin_bfs(1); it != g2.end(); it++)
	{
		cout << "out: " << *it << endl;
	}
	//if (true) return 0;
	cout << endl;
	g2.remove_edge(8, 7);
	g2.remove_edge(5, 6);
	g2.remove_edge(6, 4);
	//cout << "qeqeqeqe";
	g2.remove_edge(7, 5);
	g2.remove_edge(1, 7);
	g2.remove_edge(6, 9);
	//cout << "----------------------\n";
	cout << "BFS:\n";
	for (MyDirectedGraph<int>::Iterator it = g2.begin_bfs(1); it != g2.end(); it++)
	{
		cout << "out: " << *it << endl;
	}

	cout << endl << "----------------------------" << endl << endl;*/
	//if (true) return 0;
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
	mg2->remove_vertex("6s");
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