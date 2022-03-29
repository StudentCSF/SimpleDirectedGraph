#pragma once

template<class T>
class MySet
{

private:
	T* ptr;
	int sz;

public:
	MySet() : MySet(1024) {}

	MySet(const int capacity)
	{
		this->ptr = new T[capacity];
		this->sz = 0;
	}

	void add(T v)
	{
		if (!this->contains(v))
		{
			*(ptr + sz) = v;
			sz++;
		}
	}

	bool contains(T v)
	{
		for (unsigned int i = 0; i < this->sz; i++)
		{
			if (*(ptr + i) == v)
			{
				return true;
			}
		}
		return false;
	}

	int size()
	{
		return this->sz;
	}

	class Iterator
	{
		friend class MySet;

	private:
		T* curr;

	public:
		Iterator(T* v)
		{
			this->curr = v;
		}

		T& operator*()
		{
			return *this->curr;
		}

		Iterator operator++(int)
		{
			Iterator cp = *this;
			this->curr++;
			return cp;
		}

		Iterator& operator++()
		{
			this->curr++;
			return *this;
		}

		friend bool operator==(const MySet<T>::Iterator& it1, const MySet<T>::Iterator& it2)
		{
			return *it1.curr == *it2.curr;
		}

		friend bool operator!=(const MySet<T>::Iterator& it1, const MySet<T>::Iterator& it2)
		{
			return *it1.curr != *it2.curr;
		}
	};

	Iterator begin()
	{
		return Iterator(this->ptr);
	}

	Iterator end()
	{
		const int add = this->size() + 1;
		T tmp = *(this->ptr + add);
		return Iterator(&tmp);
	}
};