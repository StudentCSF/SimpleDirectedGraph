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
		MySet<Vertex*>* to_vertices;

		Vertex(T v)
		{
			this->value = v;
			this->to_vertices = new MySet<Vertex*>();
			std::cout << "add: " << v << '\n';
		}

		~Vertex()
		{
			std::cout << "rm: " << this->value << "\n";
			delete this->to_vertices;
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
			this->to_vertices = src.to_vertices;
			return *this;
		}
	};

	MySet<Vertex*>* from_vertices;

public:

	MyDirectedGraph()
	{
		this->from_vertices = new MySet<Vertex*>();
	}

	~MyDirectedGraph()
	{
		this->clear();
		delete this->from_vertices;
	}

public:

	void add_edge(T from, T to)
	{
		Vertex* pfv;
		pfv = this->find_vertex(from);
		if (!pfv)
		{
			pfv = new Vertex(from);
			this->from_vertices->add(pfv);
		}

		Vertex* ptv;
		ptv = this->find_vertex(to);
		if (!ptv)
		{
			ptv = new Vertex(to);
			this->from_vertices->add(ptv);
		}
		pfv->to_vertices->add(ptv);
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
			for (typename MySet<Vertex*>::Iterator it = v->to_vertices->begin(); it != v->to_vertices->end(); it++)
			{
				buf->add(*it);
			}

			for (typename MySet<Vertex*>::Iterator it = buf->begin(); it != buf->end();)
			{
				curr = *it;
				buf->erase(it);
				this->remove_edge(v, curr);
			}

			for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
			{
				curr = *it;
				for (typename MySet<Vertex*>::Iterator it2 = curr->to_vertices->begin(); it2 != curr->to_vertices->end(); it2++)
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

	/*
	void remove_vertex(T value)
	{
		Vertex* v;
		if (v = this->find_vertex(value))
		{
			Vertex* curr;
			MySet<Vertex*>* tbuf = new MySet<Vertex*>(this->size());
			MySet<Vertex*>* fbuf = new MySet<Vertex*>(this->size());
			for (typename MySet<Vertex*>::Iterator it = v->to_vertices->begin(); it != v->to_vertices->end(); it++)
			{
				tbuf->add(*it);
			}

			for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
			{
				curr = *it;
				for (typename MySet<Vertex*>::Iterator it2 = curr->to_vertices->begin(); it2 != curr->to_vertices->end(); it2++)
				{
					if (*it2 == v)
					{
						fbuf->add(curr);
						break;
					}
				}
			}

			for (typename MySet<Vertex*>::Iterator it = tbuf->begin(); it != tbuf->end();)
			{
				curr = *it;
				tbuf->erase(it);
				this->remove_edge(v, curr);
			}

			for (typename MySet<Vertex*>::Iterator it = fbuf->begin(); it != fbuf->end();)
			{
				curr = *it;
				fbuf->erase(it);
				this->remove_edge(curr, v);
			}

			delete tbuf;
			delete fbuf;
		}
	}
	*/
	size_t size()
	{
		size_t res = 0;
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++, res++) {}
		return res;

	}

	void clear()
	{
		MySet<Vertex*>* all = new MySet<Vertex*>();
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end();)
		{
			Vertex* v = *it;
			if (!all->contains(v))
			{
				all->add(v);
			}
			for (typename MySet<Vertex*>::Iterator it2 = v->to_vertices->begin(); it2 != v->to_vertices->end();)
			{
				Vertex* v2 = *it2;
				if (!all->contains(*it2))
				{
					all->add(*it2);
				}
				v->to_vertices->erase(it2);
			}
			this->from_vertices->erase(it);
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
		for (typename MySet<Vertex*>::Iterator it = src.from_vertices->begin(); it != src.from_vertices->end(); it++)
		{
			Vertex* curr = *it;
			T v1 = curr->value;
			for (typename MySet<Vertex*>::Iterator it2 = curr->to_vertices->begin(); it2 != curr->to_vertices->end(); it2++)
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
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			curr = *it;
			if (curr->value == v)
			{
				return curr;
			}
		}
		return nullptr;
	}
	/*
	bool from_vertex_contains_to_vertex(T from, T to)
	{
		Vertex* pfv = this->find_vertex(from);
		if (pfv)
		{
			for (typename MySet<Vertex*>::Iterator it = pfv->to_vertices->begin(); it != pfv->to_vertices->end(); it++)
			{
				Vertex* cptv = *it;
				if (cptv->value == to)
				{
					return true;
				}
			}
		}
		return false;
	}
	*/
	void remove_edge(Vertex* from, Vertex* to)
	{
		typename MySet<Vertex*>::Iterator it = from->to_vertices->find(to);

		if (it != from->to_vertices->end())
		{
			from->to_vertices->erase(it);

			if (to->to_vertices->empty() && !this->exists_from_for(to))
			{
				typename MySet<Vertex*>::Iterator it2 = this->from_vertices->find(to);
				this->from_vertices->erase(it2);

				delete to;
			}
			if (from->to_vertices->empty() && !this->exists_from_for(from))
			{
				typename MySet<Vertex*>::Iterator it2 = this->from_vertices->find(from);
				this->from_vertices->erase(it2);

				delete from;
			}
		}
	}

	bool exists_from_for(Vertex* v)
	{
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* cf = *it;
			for (typename MySet<Vertex*>::Iterator it2 = cf->to_vertices->begin(); it2 != cf->to_vertices->end(); it2++)
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
		size_t i = 0;
		while (!q->empty())
		{
			Vertex* curr = q->pop();
			visited->add(curr);
			*(seq + i) = curr;
			i++;
			for (typename MySet<Vertex*>::Iterator it = curr->to_vertices->begin(); it != curr->to_vertices->end(); it++)
			{
				if (!visited->contains(*it))
				{
					q->push(*it);
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
		size_t i = 0;
		while (!stack->empty())
		{
			Vertex* curr = stack->pop();
			*(seq + i) = curr;
			i++;
			for (typename MySet<Vertex*>::Iterator it = curr->to_vertices->begin(); it != curr->to_vertices->end(); it++)
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