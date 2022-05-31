#pragma once

template<class T>
class MyQueue
{

private:
	T* init;
	T* head;
	T* ptr;

public:
	MyQueue() : MyQueue(1023){}

	MyQueue(const int capacity)
	{
		this->init = new T[capacity + 1];
		this->ptr = init;
		this->head = init;
	}

	~MyQueue()
	{
		delete[] this->init;
	}

	void push(T v)
	{
		*this->ptr = v;
		this->ptr++;
	}

	T pop()
	{
		T res = this->top();
		this->head++;
		return res;
	}

	T top()
	{
		return *this->head;
	}

	bool empty()
	{
		return this->head == this->ptr;
	}
};