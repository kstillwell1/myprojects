#include <iostream>

using namespace std;

template <typename T>
class Node
{
private:

	T m_data;
	Node<T>* m_next;
	template <typename U>
	friend class SimpleLinkedList;

public:

	Node(T data)
		: m_data(data)
		, m_next(nullptr)
	{
	}

	~Node()
	{
	}
};

template <typename T>
class SimpleLinkedList
{

private:

	Node<T>* m_head;

public:

	SimpleLinkedList()
		: m_head(nullptr)
	{
	}

	~SimpleLinkedList()
	{
	}


public:
	//functions
	int size() {
		int count = 0;
		Node<T>* aux = m_head;
		while (aux != nullptr)
		{
			count++;
			aux = aux->m_next;
		}
		return count;
	}

	void addFirst(T data) {
		Node<T>* newest = new Node<T>(data);
		if (m_head == nullptr)
		{
			m_head = newest;
		}
		else
		{
			newest->m_next = m_head;
			m_head = newest;
		}
	}

	void addLast(T data)
	{
		Node<T>* newest = new Node<T>(data);

		if (m_head == nullptr)
		{
			m_head = newest;
		}
		else
		{
			Node<T>* aux = m_head;
			while (aux->m_next != nullptr)
			{
				aux = aux->m_next;
			}
			aux->m_next = newest;
		}
	}

	void printList() const
	{
		Node<T>* aux = m_head;
		if (aux == nullptr)
		{
			cout << "No data Found" << endl;
		}
		while (aux != nullptr)
		{
			cout << aux->m_data << endl;
			aux = aux->m_next;
		}
	}

	void find(T data)
	{
		Node<T>* aux = m_head;
		int count = 0;
		bool found = false;
		if (aux == nullptr)
		{
			cout << "No data Found" << endl;
		}
		while (aux != nullptr)
		{
			if (aux->m_data == data)
			{
				cout << "Found at index " << count << endl;
				found = true;
			}
			count++;
			aux = aux->m_next;
		}
		if (!found)
		{
			cout << "No data found" << endl;
		}
	}

	void insertAt(int index, T data)
	{
		Node<T>* temp = new Node<T>(data);
		Node<T>* aux = m_head;

		if (index == 0)
		{
			addFirst(data);
			return;
		}

		int count = 0;
		while (aux->m_next != nullptr && count < index - 1)
		{
			aux = aux->m_next;
			++count;
		}
		temp->m_next = aux->m_next;
		aux->m_next = temp;
	}

	void reverse()
	{
		Node<T>* prev = nullptr;
		Node<T>* aux = m_head;
		Node<T>* next;

		while (aux != nullptr)
		{
			next = aux->m_next;
			aux->m_next = prev;
			prev = aux;
			aux = next;
		}
		m_head = prev;
	}

	void removeFirst()
	{
		if (m_head == nullptr)
		{
			cout << "List is empty" << endl;
			return;
		}
		Node<T>* aux = m_head;
		m_head = m_head->m_next;
		delete aux;
	}

	void deleteAt(int index)
	{
		if (index == 0)
		{
			removeFirst();
			return;
		}

		Node<T>* aux = m_head;
		Node<T>* temp = m_head;
		int count = 0;

		while (aux->m_next != nullptr && count < index)
		{
			++count;
			aux = aux->m_next;
			if (index == count)
			{
				temp->m_next = aux->m_next;
				delete aux;
				return;
			}
			temp = aux;
		}

		if (aux->m_next == nullptr)
		{
			cout << "List does not contain this index" << endl;
		}
	}

	void removeLast()
	{
		if (m_head == nullptr)
		{
			cout << "List is empty" << endl;
		}
		Node<T>* aux = m_head;
		Node<T>* temp = m_head;
		while (aux != nullptr)
		{
			aux = aux->m_next;
			if (aux->m_next == nullptr)
			{
				temp->m_next = nullptr;
				delete aux;
				return;
			}
			temp = aux;
		}
	}
};

int main()
{
	SimpleLinkedList<int> linkedList;


	linkedList.addFirst(1);
	linkedList.addLast(2);
	linkedList.addLast(3);
	linkedList.addLast(4);
	linkedList.addLast(5);

	linkedList.insertAt(1, 100);
	linkedList.reverse();
	linkedList.removeFirst();
	linkedList.deleteAt(4);
	linkedList.removeLast();
	linkedList.printList();

	return 0;
}
