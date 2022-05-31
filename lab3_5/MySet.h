#pragma once

template<class T>
class MySet
{

private:
	T* ptr;
	size_t sz;

public: 
	MySet() : MySet(1023) {}

	MySet(const size_t capacity)
	{
		this->ptr = new T[capacity + 1];
		this->sz = 0;
	}

	~MySet()
	{
		delete[] this->ptr;
	}

	void add(T v)
	{
		if (!this->contains(v))
		{
			*(this->ptr + this->sz) = v;
			this->sz++;
		}
	}

	bool contains(T v)
	{
		for (unsigned int i = 0; i < this->sz; i++)
		{
			if (*(this->ptr + i) == v)
			{
				return true;
			}
		}
		return false;
	}

	size_t size()
	{
		return this->sz;
	}

	bool empty()
	{
		return this->sz == 0;
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

		Iterator operator=(const Iterator& src)
		{
			return Iterator(src.curr);
		}
	};

	Iterator begin()
	{
		return Iterator(this->ptr);
	}

	Iterator end()
	{
		const int add = this->size();
		T tmp = *(this->ptr + add);
		return Iterator(&tmp);
	}

	Iterator erase(Iterator where_)
	{
		unsigned int i = 0, ind;
		Iterator it = this->begin();
		for (; it != where_; it++, i++) {}
		ind = i;
		for (; i < this->sz; i++)
		{
			*(this->ptr + i) = *(this->ptr + i + 1);
		}
		this->sz--;
		it = this->begin();
		i = 0;
		for (; i < ind; i++, it++) {}
		return it;
	}

	Iterator find(T value)
	{
		for (Iterator radar = this->begin(); radar != this->end(); radar++)
		{
			if (*radar == value) {
				return radar;
			}
		}
		return this->end();
	}
};