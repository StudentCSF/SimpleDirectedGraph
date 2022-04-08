#pragma once

template<class T>
class MyStack
{

private:
	T* init;
	T* head;

public:
	MyStack() : MyStack(1024) {}

	MyStack(const int capacity)
	{
		this->init = new T[capacity];
		this->head = init;
	}

	~MyStack()
	{
		delete[] init;
	}

	void push(T value)
	{
		this->head++;
		*this->head = value;
	}

	T pop()
	{
		T res = this->top();
		this->head--;
		return res;
	}

	T top()
	{
		return *this->head;
	}

	bool empty()
	{
		return this->head == this->init;
	}
};