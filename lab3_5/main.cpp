#include <iostream>

#include "DirectedGraph.h"
#include "MyDirectedGraph.h"
#include "MyStack.h"
#include "Test.h"
#include "MyQueue.h"
#include "MySet.h"

typedef unordered_map<int, unordered_set<int>*> IntMap;

int main()
{
	MySet<int> set2;
	set2.add(1);
	set2.add(2);
	set2.add(3);
	set2.add(4);
	cout << set2.size() << "\n------" << endl;
	for (MySet<int>::Iterator it = set2.begin(); it != set2.end(); it++)
	{
		//cout << *it << endl;
		if (*it == 3)
		set2.erase(it);
	}
	set2.add(2);
	cout << "\n++++++\n";
	//cout << endl << set2.contains(2);
	for (MySet<int>::Iterator it = set2.begin(); it != set2.end(); it++)
	{
		cout << *it << endl;
	}
	cout << set2.size();

	if (true) return 0;

	MyDirectedGraph<int> mdg;
	mdg.add_edge(1, 2);
	mdg.add_edge(2, 3);
	mdg.add_edge(1, 4);
	mdg.add_edge(4, 1);
	mdg.add_edge(5, 1);
	cout << mdg.size();

	if (true) return 0;
	//MyDirectedGraph<int> mdg;
	MyStack<string>* s  = new MyStack<string>();
	cout << s->empty() << endl;
	s->push("2d");
	s->push("d3");
	s->push("4d");
	cout << s->pop() << endl;
	cout << s->pop() << endl;
	cout << s->pop() << endl;
	cout << s->empty();
	cout << "---------------\n";
	MyStack<Test*>* st = new MyStack<Test*>();
	cout << st->empty() << endl;
	st->push(new Test(2));
	st->push(new Test(3));
	st->push(new Test(4));
	cout << st->pop()->v << endl;
	cout << st->pop()->v << endl;
	cout << st->pop()->v << endl;
	cout << st->empty();

	cout << "\n\n---------------------\n\n";

	MyQueue<int>* q = new MyQueue<int>();
	cout << q->empty() << endl;
	q->add(2);
	q->add(3);
	q->add(4);
	cout << q->poll() << endl;
	cout << q->poll() << endl;
	cout << q->poll() << endl;
	cout << q->empty() << endl;
	cout << "---------------\n";
	MyQueue<Test*>* q2 = new MyQueue<Test*>();
	cout << q2->empty() << endl << endl;
	q2->add(new Test(2));
	q2->add(new Test(3));
	q2->add(new Test(4));
	cout << q2->poll()->v << endl;
	cout << q2->poll()->v << endl;
	cout << q2->poll()->v << endl << endl;
	cout << q2->empty();

	cout << "\n\n\#########################n\n";

	MySet<int>* set = new MySet<int>();
	set->add(2);
	set->add(3);
	set->add(2);
	cout << set->size();

	for (MySet<int>::Iterator it = set->begin(); it != set->end(); it++)
	{
		cout << endl << *it;
	}
	cout << set->contains(1);
	/*
	DirectedGraph<int> g;// = new DirectedGraph<int>();
	g.add_edge(1, 4);
	g.add_edge(1, 5);
	g.add_edge(4, 8);
	g.add_edge(8, 7);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(7, 5);
	g.add_edge(1, 7);
	for (DirectedGraph<int>::DFSIterator it = g.begin(1); it != g.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	cout << "-----------------\n";
	g.remove_vertex(7);
	for (DirectedGraph<int>::DFSIterator it = g.begin(1); it != g.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	if (1) return 0;
	DirectedGraph<string> g2;// = new DirectedGraph<int>();
	g2.add_edge("1s", "4s");
	g2.add_edge("1s", "5s");
	g2.add_edge("4s", "8s");
	g2.add_edge("8s", "7s");
	g2.add_edge("5s", "6s");
	g2.add_edge("6s", "4s");
	g2.add_edge("7s", "5s");
	g2.add_edge("1s", "7s");
	for (DirectedGraph<string>::DFSIterator it = g2.begin("1s"); it != g2.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	cout << "-----------------";
	g2.remove_vertex("7s");
	for (DirectedGraph<string>::DFSIterator it = g2.begin("1s"); it != g2.end(); ++it)
	{
		cout << "out: " << *it << endl;
	}
	*/
	//delete g;
	return 0;
}