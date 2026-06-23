#pragma once
#include <iostream>

using namespace std;

class Stack
{
private:
	struct item
	{
		string m_name;
		int m_value;
		item* m_prev;

	};

	item* stackPtr;

public:
	Stack();
	~Stack();

	void push(string name, int value);
	void readItem(item* data);
	void pop();
	void print();
	bool isEmpty();
	int size();
	void clear();
	void peek();
};
