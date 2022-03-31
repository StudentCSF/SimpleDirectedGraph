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
			for (typename MySet<Vertex*>::Iterator it = this->to_vertices->begin(); it != this->to_vertices->end(); )
			{
				this->remove_vertex(*it);
			}
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

private:

	MySet<Vertex*>* from_vertices;

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

public:

	MyDirectedGraph()
	{
		this->from_vertices = new MySet<Vertex*>();
	}
	
	~MyDirectedGraph()
	{
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* v = *it;
			this->remove_vertex(v->value);
		}
		delete this->from_vertices;
	}
	
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
		Vertex* pfv = this->find_from_vertex(from);
		if (pfv)
		{
			for (typename MySet<Vertex*>::Iterator it = pfv->to_vertices->begin(); it != pfv->to_vertices->end(); it++)
			{
				Vertex* ptv = *it;
				if (ptv->value == to)
				{
					pfv->to_vertices->erase(it);
					break;
				}
			}
			if (pfv->to_vertices->empty())
			{
				Vertex* ptv = this->find_to_vertex(from);
				if (!ptv)
				{
					for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
					{
						Vertex* curr = *it;
						if (curr->value == from)
						{
							this->from_vertices->erase(it);
							break;
						}
					}
				}
			}
		}
	}
	
	void remove_vertex(T v)
	{
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* pfv = *it;
			if (pfv->value == v)
			{
				this->from_vertices->erase(it);
			}
			else
			{
				for (typename MySet<Vertex*>::Iterator it2 = pfv->to_vertices->begin(); it2 != pfv->to_vertices->end(); it2++)
				{
					Vertex* ptv = *it2;
					if (ptv->value == v)
					{
						pfv->to_vertices->erase(it2);
					}
				}
				if (pfv->to_vertices->empty())
				{
					this->from_vertices->erase(it);
				}
			}
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
		*(seq + i) = nullptr;

		return Iterator(seq);
	}

	Iterator begin_dfs(T start) 
	{
		Vertex* v = this->find_vertex(start);

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
		*(seq + i) = nullptr;
		return Iterator(seq);
	}

	Iterator end()
	{
		Vertex** seq = new Vertex* [1];
		*seq = nullptr;
		return Iterator(seq);
	}

};