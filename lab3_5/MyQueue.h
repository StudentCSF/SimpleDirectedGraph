#pragma once


template<class T>
class MyQueue
{

private:
	T* head;
	T* ptr;

public:
	MyQueue() : MyQueue(1024){}

	MyQueue(const int capacity)
	{
		this->ptr = new T[capacity];
		this->head = ptr;
	}

	~MyQueue()
	{
		delete head;
		delete ptr;
	}

	void push(T v)
	{
		*ptr = v;
		ptr++;
	}

	T pop()
	{
		T res = *head;
		head++;
		return res;
	}

	T top()
	{
		return *head;
	}

	bool empty()
	{
		return this->head == this->ptr;
	}
};