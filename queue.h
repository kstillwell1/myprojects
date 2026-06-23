#pragma once
#include <iostream>


struct Node
{
	int m_value;
	Node* m_next;

	Node(int value);
	~Node();
};

class Queue
{
private:
	Node* m_front;
	Node* m_back;
	
public:
	Queue();
	~Queue();

	bool isEmpty();
	void enQueue(int value);
	void deQueue();
	void printQueue();
	void front();
	void back();
	int size();
	void clear();
};
