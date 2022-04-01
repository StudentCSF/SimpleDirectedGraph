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
		}

		~Vertex()
		{
			std::cout << "rm - " << this->value << "\n";
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
		if (!this->from_vertex_contains_to_vertex(from, to))
		{
			Vertex* pfv;
			pfv = this->find_from_vertex(from);
			if (!pfv)
			{
				pfv = this->find_to_vertex(from);
				if (!pfv)
				{
					pfv = new Vertex(from);
				}
				this->from_vertices->add(pfv);
			}

			Vertex* ptv;
			ptv = this->find_vertex(to);
			if (!ptv)
			{
				ptv = new Vertex(to);
			}
			pfv->to_vertices->add(ptv);
		}
	}

	void remove_edge(T from, T to)
	{
		Vertex* v = this->find_from_vertex(from);
		Vertex* v2 = this->find_to_vertex(to);

		if (v && v2 && this->from_vertex_contains_to_vertex(from, to))
		{
			this->remove_edge(v, v2);
		}
	}

	size_t size()
	{
		MySet<Vertex*> all;
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* v = *it;
			if (!all.contains(v))
			{
				all.add(v);
			}
			for (typename MySet<Vertex*>::Iterator it2 = v->to_vertices->begin(); it2 != v->to_vertices->end(); it2++)
			{
				if (!all.contains(*it2))
				{
					all.add(*it2);
				}
			}
		}
		return all.size();
	}

	void clear()
	{
		MySet<Vertex*> all;
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* v = *it;
			if (!all.contains(v))
			{
				all.add(v);
			}
			for (typename MySet<Vertex*>::Iterator it2 = v->to_vertices->begin(); it2 != v->to_vertices->end(); it2++)
			{
				Vertex* v2 = *it2;
				if (!all.contains(*it2))
				{
					all.add(*it2);
				}
				v->to_vertices->erase(it2);
			}
			this->from_vertices->erase(it);
		}

		for (typename MySet<Vertex*>::Iterator it = all.begin(); it != all.end(); it++)
		{
			Vertex* curr = *it;
			all.erase(it);
			delete curr;
		}
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
	
	Vertex* find_from_vertex(T v)
	{
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* tpfv = *it;
			if (tpfv->value == v)
			{
				return tpfv;
			}
		}
		return nullptr;
	}

	Vertex* find_to_vertex(T v)
	{
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* tpfv = *it;
			for (typename MySet<Vertex*>::Iterator it2 = tpfv->to_vertices->begin(); it2 != tpfv->to_vertices->end(); it2++)
			{
				Vertex* tpfv2 = *it2;
				if (tpfv2->value == v)
				{
					return tpfv2;
				}
			}
		}
		return nullptr;
	}

	Vertex* find_vertex(T v)
	{
		Vertex* pv = this->find_from_vertex(v);
		if (!pv)
		{
			pv = this->find_to_vertex(v);
		}
		return pv;
	}

	bool from_vertex_contains_to_vertex(T from, T to)
	{
		Vertex* pfv = this->find_from_vertex(from);
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

	void remove_edge(Vertex* from, Vertex* to)
	{
		typename MySet<Vertex*>::Iterator it = from->to_vertices->find(to);
		if (it != from->to_vertices->end())
		{
			from->to_vertices->erase(it);
		}
		if (!this->find_vertex(to->value))
		{
			delete to;
		}

		if (from->to_vertices->empty())
		{
			it = this->from_vertices->find(from);
			if (it != this->from_vertices->end())
			{
				this->from_vertices->erase(it);
			}

			if (!this->find_to_vertex(from->value))
			{
				delete from;
			}
		}
	}

public:

	class Iterator
	{

	private:
		Vertex** ptr;

	public: 
		Iterator(Vertex** ptr)
		{
			this->ptr = ptr;
		}

		T operator*() const
		{
			Vertex* v = *(this->ptr);
			return v->value;
		}
		
		virtual Iterator& operator++()
		{
			this->ptr++;
			return *this;
		}

		virtual Iterator operator++(int)
		{
			Iterator copy = *this;
			this->ptr++;
			return copy;
		}

		friend bool operator==(const MyDirectedGraph<T>::Iterator& i1, const MyDirectedGraph<T>::Iterator& i2)
		{
			return *(i1.ptr) == *(i2.ptr);
		}

		friend bool operator!=(const MyDirectedGraph<T>::Iterator& i1, const MyDirectedGraph<T>::Iterator& i2)
		{
			return *(i1.ptr) != *(i2.ptr);
		}
	};

	Iterator begin_bfs(T start)
	{
		Vertex* v = this->find_vertex(start);
		if (!v) return this->end();
		MyQueue<Vertex*>* q = new MyQueue<Vertex*>();
		MySet<Vertex*>* visited = new MySet<Vertex*>();

		const size_t n = this->size() + 1;
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
		for (typename MySet<Vertex*>::Iterator it = visited->begin(); it != visited->end(); it++)
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
		MyStack<Vertex*>* stack = new MyStack<Vertex*>();
		MySet<Vertex*>* visited = new MySet<Vertex*>();

		const size_t n = this->size() + 1;
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
		for (typename MySet<Vertex*>::Iterator it = visited->begin(); it != visited->end(); it++)
		{
			visited->erase(it);
		}
		delete visited;

		*(seq + i) = nullptr;
		return Iterator(seq);
	}

	Iterator end()
	{
		Vertex** seq = new Vertex*[1];
		*seq = nullptr;
		return Iterator(seq);
	}
};