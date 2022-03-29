#pragma once


template<class T>
class MyDirectedGraph
{
private:
	struct Vertex
	{
		T value;
		Vertex* to_vertices[];
	};

	Vertex* from_vertices[];

private:
	
	int contains_from_vertex(Vertex* v)
	{
		for (unsigned int i = 0; i < this->from_vertices.size(); i++)
		{
			if (this->from_vertices.at(i)->value == v->value)
			{
				return i;
			}
		}
		return -1;
	}

public:
	MyDirectedGraph()
	{

	}

	~MyDirectedGraph()
	{

	}

	void add_edge(T v1, T v2)
	{

	}

	void remove_edge(T v1, T v2)
	{

	}

	void remove_vertex(T v)
	{

	}

	int size()
	{

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