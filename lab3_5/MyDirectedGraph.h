#pragma once

#include "MySet.h"
#include "MyStack.h"
#include "MyQueue.h"

template<class T>
class MyDirectedGraph
{

private:
	class Vertex
	{
	public:
		T value;
		MySet<Vertex*>* arcs_to;

		Vertex(T v)
		{
			this->value = v;
			this->arcs_to = new MySet<Vertex*>();
			std::cout << "add: " << v << '\n';
		}

		~Vertex()
		{
			std::cout << "rm: " << this->value << "\n";
			delete this->arcs_to;
		}

		bool operator==(const Vertex& v)
		{
			return this->value == v.value;
		}

		bool operator!=(const Vertex& v)
		{
			return this->value != v.value;
		}

		Vertex& operator=(const Vertex& src)
		{
			this->value = src.value;
			this->arcs_to = src.arcs_to;
			return *this;
		}
	};

	MySet<Vertex*>* vertices;

public:
	MyDirectedGraph()
	{
		this->vertices = new MySet<Vertex*>();
	}

	~MyDirectedGraph()
	{
		this->clear();
		delete this->vertices;
	}

public:
	void add_edge(T from, T to)
	{
		Vertex* pfv;
		pfv = this->find_vertex(from);
		if (!pfv)
		{
			pfv = new Vertex(from);
			this->vertices->add(pfv);
		}

		Vertex* ptv;
		ptv = this->find_vertex(to);
		if (!ptv)
		{
			ptv = new Vertex(to);
			this->vertices->add(ptv);
		}
		pfv->arcs_to->add(ptv);
	}

	void remove_edge(T from, T to)
	{
		Vertex* v = this->find_vertex(from);
		Vertex* v2 = this->find_vertex(to);
		if (v && v2)
		{
			this->remove_edge(v, v2);
		}
	}

	void remove_vertex(T value)
	{
		Vertex* v;
		if (v = this->find_vertex(value))
		{
			Vertex* curr;
			MySet<Vertex*>* buf = new MySet<Vertex*>(this->size());
			for (typename MySet<Vertex*>::Iterator it = v->arcs_to->begin(); it != v->arcs_to->end(); it++)
			{
				buf->add(*it);
			}

			for (typename MySet<Vertex*>::Iterator it = buf->begin(); it != buf->end();)
			{
				curr = *it;
				buf->erase(it);
				this->remove_edge(v, curr);
			}

			for (typename MySet<Vertex*>::Iterator it = this->vertices->begin(); it != this->vertices->end(); it++)
			{
				curr = *it;
				for (typename MySet<Vertex*>::Iterator it2 = curr->arcs_to->begin(); it2 != curr->arcs_to->end(); it2++)
				{
					if (*it2 == v)
					{
						buf->add(curr);
						break;
					}
				}
			}

			for (typename MySet<Vertex*>::Iterator it = buf->begin(); it != buf->end();)
			{
				curr = *it;
				buf->erase(it);
				this->remove_edge(curr, v);
			}

			delete buf;
		}
	}

	size_t size()
	{
		return this->vertices->size();
	}

	void clear()
	{
		MySet<Vertex*>* all = new MySet<Vertex*>(this->size());
		for (typename MySet<Vertex*>::Iterator it = this->vertices->begin(); it != this->vertices->end();)
		{
			Vertex* v = *it;
			all->add(v);
			for (typename MySet<Vertex*>::Iterator it2 = v->arcs_to->begin(); it2 != v->arcs_to->end();)
			{
				Vertex* v2 = *it2;
				all->add(*it2);
				v->arcs_to->erase(it2);
			}
			this->vertices->erase(it);
		}

		for (typename MySet<Vertex*>::Iterator it = all->begin(); it != all->end();)
		{
			Vertex* curr = *it;
			all->erase(it);
			delete curr;
		}
		delete all;
	}

	MyDirectedGraph& operator=(const MyDirectedGraph& src)
	{
		this->clear();
		for (typename MySet<Vertex*>::Iterator it = src.vertices->begin(); it != src.vertices->end(); it++)
		{
			Vertex* curr = *it;
			T v1 = curr->value;
			for (typename MySet<Vertex*>::Iterator it2 = curr->arcs_to->begin(); it2 != curr->arcs_to->end(); it2++)
			{
				Vertex* curr2 = *it2;
				T v2 = curr2->value;
				this->add_edge(v1, v2);
			}
		}
		return *this;
	}

private:
	Vertex* find_vertex(T v)
	{
		Vertex* curr;
		for (typename MySet<Vertex*>::Iterator it = this->vertices->begin(); it != this->vertices->end(); it++)
		{
			curr = *it;
			if (curr->value == v)
			{
				return curr;
			}
		}
		return nullptr;
	}
	
	void remove_edge(Vertex* from, Vertex* to)
	{
		typename MySet<Vertex*>::Iterator it = from->arcs_to->find(to);

		if (it != from->arcs_to->end())
		{
			from->arcs_to->erase(it);

			if (to->arcs_to->empty() && !this->exists_arcs_to(to))
			{
				typename MySet<Vertex*>::Iterator it2 = this->vertices->find(to);
				this->vertices->erase(it2);

				delete to;
			}
			if (from->arcs_to->empty() && !this->exists_arcs_to(from))
			{
				typename MySet<Vertex*>::Iterator it2 = this->vertices->find(from);
				this->vertices->erase(it2);

				delete from;
			}
		}
	}

	bool exists_arcs_to(Vertex* v)
	{
		for (typename MySet<Vertex*>::Iterator it = this->vertices->begin(); it != this->vertices->end(); it++)
		{
			Vertex* cf = *it;
			for (typename MySet<Vertex*>::Iterator it2 = cf->arcs_to->begin(); it2 != cf->arcs_to->end(); it2++)
			{
				if (*it2 == v) return true;
			}
		}
		return false;
	}

public:
	
	class Iterator
	{
		friend class MyDirectedGraph;

	private:
		Vertex** ptr;
		Vertex** init;
		Vertex* curr;
		
		Iterator(Vertex** seq)
		{
			this->init = seq;
			this->ptr = init;
			this->curr = *init;
		}

		Iterator()
		{
			this->curr = nullptr;
			this->init = nullptr;
			this->ptr = nullptr;
		}

		void update()
		{
			*this->ptr = nullptr;
			this->ptr++;
			this->curr = *this->ptr;

			if (!curr) delete[] init;
		}

	public:
		T operator*() const
		{
			return curr->value;
		}

		Iterator& operator++()
		{
			this->update();
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator copy = *this;
			this->update();
			return copy;
		}

		friend bool operator==(const MyDirectedGraph<T>::Iterator& i1, const MyDirectedGraph<T>::Iterator& i2)
		{
			return i1.curr == i2.curr;
		}

		friend bool operator!=(const MyDirectedGraph<T>::Iterator& i1, const MyDirectedGraph<T>::Iterator& i2)
		{
			return i1.curr != i2.curr;
		}
	};

	Iterator begin_bfs(T start)
	{
		Vertex* v = this->find_vertex(start);

		if (!v) return this->end();

		const size_t n = this->size() + 1;

		MyQueue<Vertex*>* q = new MyQueue<Vertex*>(n);
		MySet<Vertex*>* visited = new MySet<Vertex*>(n);
		Vertex** seq = new Vertex*[n];

		q->push(v);
		visited->add(v);

		unsigned int i = 0;
		while (!q->empty())
		{
			Vertex* curr = q->pop();
			*(seq + i) = curr;
			i++;
			for (typename MySet<Vertex*>::Iterator it = curr->arcs_to->begin(); it != curr->arcs_to->end(); it++)
			{
				if (!visited->contains(*it))
				{
					q->push(*it);
					visited->add(*it);
				}
			}
		}
		
		delete q;

		for (typename MySet<Vertex*>::Iterator it = visited->begin(); it != visited->end();)
		{
			visited->erase(it);
		}
		delete visited;

		*(seq + i) = nullptr;
		return Iterator(seq);
	}

	Iterator begin_dfs(T start) 
	{
		Vertex* v = this->find_vertex(start);

		if (!v) return this->end();

		const size_t n = this->size() + 1;

		MyStack<Vertex*>* stack = new MyStack<Vertex*>(n);
		MySet<Vertex*>* visited = new MySet<Vertex*>(n);
		Vertex** seq = new Vertex*[n];

		stack->push(v);
		visited->add(v);

		unsigned int i = 0;

		while (!stack->empty())
		{
			Vertex* curr = stack->pop();
			*(seq + i) = curr;
			i++;
			for (typename MySet<Vertex*>::Iterator it = curr->arcs_to->begin(); it != curr->arcs_to->end(); it++)
			{
				if (!visited->contains(*it))
				{
					stack->push(*it);
					visited->add(*it);
				}
			}
		}

		delete stack;

		for (typename MySet<Vertex*>::Iterator it = visited->begin(); it != visited->end();)
		{
			visited->erase(it);
		}
		delete visited;

		*(seq + i) = nullptr;
		return Iterator(seq);
	}

	Iterator end()
	{
		return Iterator();
	}
};