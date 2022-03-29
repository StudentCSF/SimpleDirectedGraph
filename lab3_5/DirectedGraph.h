#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

template<class T>
class DirectedGraph
{

private:
	unordered_map<T, unordered_set<T>*>* g;

public:
	DirectedGraph()
	{
		this->g = new unordered_map<T, unordered_set<T>*>();
	}

	~DirectedGraph()
	{
		for (typename unordered_map<T, unordered_set<T>*>::iterator it = this->g->begin(); it != this->g->end();)
		{
			unordered_set<T>* tmp = it->second;
			for (typename unordered_set<T>::iterator it2 = tmp->begin(); it2 != tmp->end();)
			{
				tmp->erase(it2++);
			}
			this->g->erase(it++);
		}
		delete g;
	}

public:
	void add_edge(T from, T to)
	{
		if (!this->g->contains(from))
		{
			this->g->insert(unordered_map<T, unordered_set<T>*>::value_type(from, new unordered_set<T>()));
		}
		this->g->at(from)->insert(to);
	}

	void remove_edge(T from, T to)
	{
		if (this->g->contains(from))
		{
			typename unordered_set<T>::iterator iter = this->g->at(from)->find(to);
			if (iter != this->g->at(from)->end())
			{
				this->g->at(from)->erase(iter);
			}
		}
	}

	void remove_vertex(T v)
	{
		for (typename unordered_map<T, unordered_set<T>*>::iterator it = this->g->begin(); it != this->g->end();)// ++it)
		{
			if (it->first == v)
			{
				this->g->erase(it++);
			}
			else
			{
				for (typename unordered_set<T>::iterator it2 = it->second->begin(); it2 != it->second->end();)// ++it2)
				{
					if (*it2 == v)
					{
						it->second->erase(it2++);
					}
					else
					{
						it2++;
					}
				}
				it++;
			}
		}
	}
	

public:
	class DFSIterator
	{
		friend class DirectedGraph;

	private:
		stack<T> stack;
		unordered_set<T> visited;
		unordered_map<T, unordered_set<T>*>* map;

		DFSIterator()
		{
			empty();
		}

		DFSIterator(unordered_map<T, unordered_set<T>*>* map, T v)
		{
			if (map->contains(v)) {
				//cout << v << "  - asdasda" << endl;
				this->stack.push(v);
				//cout << stack.top() << "  - aaaa" << endl;
				visited.insert(v);
				this->map = map;
			}
			else {
				empty();
			}
		}

	private:
		void empty()
		{
			this->map = nullptr;
			this->stack.push(NULL);
		}

		void update(T curr)
		{
			if (this->map->contains(curr)) {
				unordered_set<T>* set = this->map->at(curr);
				for (typename unordered_set<T>::iterator it = set->begin(); it != set->end(); it++)
				{
					if (!this->visited.contains(*it))
					{
						visited.insert(*it);
						this->stack.push(*it);
					}
				}
			}
			if (this->stack.empty()) {
				stack.push(NULL);
			}
		}

	public:
		DFSIterator& operator++()
		{
			T curr = stack.top();
			stack.pop();
			//visited.insert(curr);
			this->update(curr);
			return *this;
		}

		DFSIterator operator++(int)
		{
			DFSIterator copy = *this;
			T curr = stack.top();
			stack.pop();
			//visited.insert(curr);
			this->update(curr);
			return copy;
		}

		T operator*() const
		{
			return this->stack.top();
		}

		friend bool operator==(const DirectedGraph<T>::DFSIterator& i1, const DirectedGraph<T>::DFSIterator& i2)
		{
			return i1.stack.top() == i2.stack.top();
		}

		friend bool operator!=(const DirectedGraph<T>::DFSIterator& i1, const DirectedGraph<T>::DFSIterator& i2)
		{
			return i1.stack.top() != i2.stack.top();
		}
	};


	DFSIterator begin(T start) const
	{
		return DFSIterator(this->g, start);
	}

	DFSIterator end() const
	{
		return DFSIterator();
	}
};
