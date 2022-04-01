#pragma once

template<class T>
class MyStack
{

private:
	T* head;
	T* ptr;

public:
	MyStack() : MyStack(1024) {}

	MyStack(const int capacity)
	{
		this->ptr = new T[capacity];
		this->head = ptr;
	}

	~MyStack()
	{
		delete ptr;
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
		return this->head == this->ptr;
	}
};