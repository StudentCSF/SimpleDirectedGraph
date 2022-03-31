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
		delete this->from_vertices;
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

	void remove_edge(T from, T to)
	{
		Vertex* v = this->find_from_vertex(from);
		Vertex* v2 = this->find_to_vertex(to);

		if (v && v2 && this->from_vertex_contains_to_vertex(from, to))
		{
			this->remove_edge(v, v2);
		}
	}
	/*
	void remove_vertex(T value)
	{
		Vertex* v = this->find_vertex(value);
		if (v)
		{
			this->remove_vertex(v);
		}
	}
	*/
private:

	void remove_edge(Vertex* from, Vertex* to)
	{
		for (typename MySet<Vertex*>::Iterator it = from->to_vertices->begin(); it != from->to_vertices->end(); it++)
		{
			if (to == *it)
			{
				from->to_vertices->erase(it);
				break;
			}
		}
		if (!this->find_vertex(to->value))
		{
			delete to;
		}
		if (from->to_vertices->empty())
		{
			for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
			{
				if (*it == from)
				{
					this->from_vertices->erase(it);
				}
			}
			if (!this->find_to_vertex(from->value))
			{
				delete from;
			}
		}
		/*
		for (typename MySet<Vertex*>::Iterator it = from->to_vertices->begin(); it != from->to_vertices->end(); it++)
		{
			Vertex* curr = *it;
			if (curr == to)
			{
				from->to_vertices->erase(it);
				Vertex* v = this->find_to_vertex(curr->value);
				if (!v)
				{
					if (!curr->to_vertices->size())
					{
						for (typename MySet<Vertex*>::Iterator it2 = this->from_vertices->begin(); it2 != this->from_vertices->end(); it2++)
						{
							if (curr == *it2)
							{
								this->from_vertices->erase(it2);
								break;
							}
						}
						delete curr;
					}
				}
				break;
			}
		}
		if (from->to_vertices->empty())
		{
			Vertex* v = this->find_to_vertex(from->value);
			if (!v)
			{
				for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
				{
					if (*it == from)
					{
						this->from_vertices->erase(it);
						break;
					}
				}
				delete from;
			}
		}
		*/
	}
	/*
	void remove_vertex(Vertex* v)
	{*/
		/*
		T val = v->value;
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* curr = *it;
			if (this->from_vertex_contains_to_vertex(curr->value, v->value))
			{
				this->remove_edge(curr, v);
			}
		}
		if (this->find_vertex(val))
		{
		*//*
		MySet<Vertex*> buf;
		for (typename MySet<Vertex*>::Iterator it = v->to_vertices->begin(); it != v->to_vertices->end(); it++)
		{
			//this->remove_edge(v, *it);
			Vertex* curr = *it;
			buf.add(curr);
			v->to_vertices->erase(it);
		}

		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			Vertex* curr = *it;
			if (v != curr)
			{
				for (typename MySet<Vertex*>::Iterator it2 = curr->to_vertices->begin(); it2 != curr->to_vertices->end(); it2++)
				{
					if (v == *it2)
					{
						curr->to_vertices->erase(it2);
					}
				}
			}
		}
		for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
		{
			if (v == *it)
			{
				this->from_vertices->erase(it);
			}
		}
		delete v;

		for (typename MySet<Vertex*>::Iterator it = buf.begin(); it != buf.end(); it++)
		{
			Vertex* curr = *it;
			Vertex* v = this->find_vertex(curr->value);
			if (!v)
			{
				buf.erase(it);
				delete curr;
			}
			else
			{
				v = this->find_to_vertex(curr->value);
				if (!v)
				{
					for (typename MySet<Vertex*>::Iterator it2 = this->from_vertices->begin(); it2 != this->from_vertices->end(); it2++)
					{
						if (curr == *it2)
						{
							this->from_vertices->erase(it2);
							delete curr;
							break;
						}
					}
				}
			}
		}
		*/
		/*
		const size_t n = this->size() + 1;
		MySet<Vertex*>* for_delete = new MySet<Vertex*>(n);

		Vertex* to = this->find_to_vertex(v->value);
		if (to)
		{
			for (typename MySet<Vertex*>::Iterator it = this->from_vertices->begin(); it != this->from_vertices->end(); it++)
			{
				Vertex* curr_from = *it;
				for (typename MySet<Vertex*>::Iterator it2 = curr_from->to_vertices->begin(); it2 != curr_from->to_vertices->end(); it2++)
				{
					if (*it == v)
					{
						curr_from->to_vertices->erase(it);
						break;
					}
				}

				if (curr_from->to_vertices->empty())
				{
					Vertex* is_to = this->find_to_vertex(curr_from->value);
					if (!is_to)
					{
						for_delete->add(curr_from);
					}
				}
			}
		}

		Vertex* from = this->find_from_vertex(v->value);
		if (from)
		{
			for (typename MySet<Vertex*>::Iterator it = from->to_vertices->begin(); it != from->to_vertices->end(); it++)
			{
				Vertex* curr_to = *it;
				from->to_vertices->erase(it);
				Vertex* curr_exist = this->find_vertex(curr_to->value);
				if (!curr_exist)
				{
					for_delete->add(curr_to);
				}
			}
		}
		for_delete->add(v);

		for (typename MySet<Vertex*>::Iterator it = for_delete->begin(); it != for_delete->end(); it++)
		{
			Vertex* curr = *it;
			for_delete->erase(it);
			delete curr;
		}
		*/
	//}

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

	/*
	Iterator begin()
	{
		MySet<Vertex*> all;
		Vertex** seq;
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
		const size_t n = all.size() + 1;
		seq = new Vertex*[n];
		unsigned int i = 0;
		for (typename MySet<Vertex*>::Iterator it = all.begin(); it != all.end(); it++)
		{
			*(seq + i) = *it;
		}
		return seq;
	}
	*/
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