#pragma once

#include "MySet.h"


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
	/*
	~MyDirectedGraph()
	{
		for (MySet<Vertex>::Iterator it = this->from_vertices.begin(); it != this->from_vertices->end(); it++)
		{
			for (MySet<Vertex>::Iterator it2 = it->to_vertices.begin(); it2 != it->to_vertices->end(); it2++)
			{
				delete it2->second
			}
		}
	}
	*/
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

	}
	/*
	void remove_vertex(T v)
	{

	}
	*/
	size_t size()
	{
		MySet<Vertex*> all;
		cout << this->from_vertices->size() << endl;
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

	T* adjacent_of(T v)
	{

	}

	/*
	* Iterator with:
	* begin_bfs(T value	)
	* begin_dfs(T value)
	* 
	* =
	* ==
	* 
	*/


};