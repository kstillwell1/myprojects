#include <cstdlib>
#include "queue.h"

Node::Node(int value)
	: m_value(value)
	, m_next(nullptr)
{
}

Node::~Node()
{
}

Queue::Queue()
	: m_front(nullptr)
	, m_back(nullptr)
{
}

Queue::~Queue()
{
	Node* current = m_front;
	while (current != nullptr)
	{
		Node* next = current->m_next;
		delete current;
		current = next;
	}
}

bool Queue::isEmpty()
{
	return m_front == nullptr;
}

void Queue::enQueue(int value)
{
	Node* temp = new Node(value);
	if (isEmpty())
	{
		m_front = m_back = temp;
	}
	else
	{
		m_back->m_next = temp;
		m_back = temp;
	}
}

void Queue::deQueue()
{
	if (isEmpty())
	{
		std::cout << "There is nothing in the queue" << std::endl;
	}
	else
	{
		Node* temp = m_front;
		m_front = m_front->m_next;
		if (m_front == nullptr)
		{
			m_back = nullptr;
		}
		delete temp;
	}
}

void Queue::printQueue()
{
	if (isEmpty())
	{
		std::cout << "There are no items in your queue" << std::endl;
	}
	else
	{
		Node* temp = m_front;
		std::cout << "Current queue: " << std::endl;
		while (temp != nullptr)
		{
			std::cout << temp->m_value << std::endl;
			temp = temp->m_next;
		}
	}
}

void Queue::front()
{
	if (isEmpty())
	{
		std::cout << "There are no items in your queue" << std::endl;
	}
	else
	{
		std::cout << "Front item in your Queue is " << m_front->m_value << std::endl;
	}
}

void Queue::back()
{
	if (isEmpty())
	{
		std::cout << "There are no items in your queue" << std::endl;
	}
	else
	{
		std::cout << "Back item in your Queue is " << m_back->m_value << std::endl;
	}
}

int Queue::size()
{
	if (isEmpty())
	{
		std::cout << "There are no items in your queue" << std::endl;
		return 0;
	}
	else
	{
		Node* temp = m_front;
		int count = 0;
		while (temp != nullptr)
		{
			temp = temp->m_next;
			++count;
		}
		return count;
	}
}

void Queue::clear()
{
	if (isEmpty())
	{
		std::cout << "There are no items in your queue" << std::endl;
	}
	else
	{
		while (m_front != nullptr)
		{
			Node* temp = m_front;
			m_front = m_front->m_next;
			if (m_front == m_back)
			{
				m_back = nullptr;
			}
			delete temp;
		}
	}
}
