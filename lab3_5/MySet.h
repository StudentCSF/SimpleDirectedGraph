#pragma once

template<class T>
class MySet
{

private:
	T* ptr;
	size_t sz;

	size_t capacity;

public:
	MySet() : MySet(1024) {}

	MySet(const size_t capacity)
	{
		this->capacity = capacity;
		this->ptr = new T[this->capacity];
		this->sz = 0;
	}

	~MySet()
	{
		delete ptr;
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
		const int add = this->size() + 1;
		T tmp = *(this->ptr + add);
		return Iterator(&tmp);
	}
	
	Iterator erase(Iterator where_)
	{
		T* new_ptr = new T[this->capacity];
		unsigned int i = 0;
		for (Iterator it = this->begin(); it != where_; it++, i++)
		{
			*(new_ptr + i) = *it;

		}
		unsigned int ind = i;
		where_++;
		for (Iterator it = where_; it != this->end(); it++, i++)
		{
			*(new_ptr + i) = *it;
		}
		sz--;
		this->ptr = new_ptr;
		i = 0;
		Iterator it = this->begin();
		for (; i < ind; it++, i++) {}
		return it;
	}

	Iterator find(T value)
	{
		Iterator radar = this->begin();
		while (radar != this->end())
		{
			if (*radar == value) {
				return radar;
			}
			radar++;
		}
		return this->end();
	}
};