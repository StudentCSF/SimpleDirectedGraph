#pragma once

template<class T>
class MyQueue
{

private:
	T* init;
	T* head;
	T* ptr;

public:
	MyQueue() : MyQueue(1024){}

	MyQueue(const int capacity)
	{
		this->init = new T[capacity];
		this->ptr = init;
		this->head = init;
	}

	~MyQueue()
	{
		delete[] init;
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