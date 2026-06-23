#include <cstdlib>
#include "stack.h"

using namespace std;

Stack::Stack()
	: stackPtr(nullptr)
{
}

Stack::~Stack()
{
	item* p1;
	item* p2;

	p1 = stackPtr;
	while (p1 != nullptr)
	{
		p2 = p1;
		p1 = p1->m_prev;
		p2->m_prev = nullptr;
		delete p2;
	}
}

void Stack::push(string name, int value)
{
	item* n = new item;
	n->m_name = name;
	n->m_value = value;

	if (stackPtr == nullptr)
	{
		stackPtr = n;
		stackPtr->m_prev = nullptr;
	}
	else
	{
		n->m_prev = stackPtr;
		stackPtr = n;
	}
}

void Stack::readItem(item* data)
{
	cout << "------------\n";
	cout << "name: " << data->m_name << endl;
	cout << "value: " << data->m_value << endl;
	cout << "------------\n";
}

void Stack::pop()
{
	if (stackPtr == nullptr)
	{
		cout << "You do not have any items in your stack!" << endl;
	}
	else
	{
		item* temp = stackPtr;
		stackPtr = stackPtr->m_prev;
		temp->m_prev = nullptr;
		delete temp;
	}
}

void Stack::print()
{
	if (stackPtr == nullptr)
	{
		cout << "You do not have any items in your stack!" << endl;
	}
	else
	{
		item* temp = stackPtr;
		while (temp != nullptr)
		{
			readItem(temp);
			temp = temp->m_prev;
		}
	}
}

bool Stack::isEmpty()
{
	if (stackPtr == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Stack::size()
{
	if (stackPtr == nullptr)
	{
		std::cout << "There are no items in your stack" << std::endl;
		return 0;
	}
	else
	{
		item* temp = stackPtr;
		int count = 0;
		while (temp != nullptr)
		{
			temp = temp->m_prev;
			++count;
		}
		return count;
	}
}

void Stack::clear()
{
	if (stackPtr == nullptr)
	{
		cout << "You do not have any items in your stack!" << endl;
	}
	else
	{
		while (stackPtr != nullptr)
		{
			item* temp = stackPtr;
			stackPtr = stackPtr->m_prev;
			delete temp;
		}
	}
}

void Stack::peek()
{
	if (stackPtr == nullptr)
	{
		cout << "You do not have any items in your stack!" << endl;
	}
	else
	{
		cout << "The top item in your stack is " << stackPtr->m_value << endl;
	}
}
