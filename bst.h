#pragma once
#include <iostream>

class BST
{
private:
	struct Node
	{
		int m_data;
		Node* m_left;
		Node* m_right;
	};

	Node* m_root;

	void addLeafPrviate(int key, Node* ptr);
	int findSmallestPrivate(Node* ptr);
	void removeNodePrivate(int data, Node* parent);
	void removeRootMatch();
	void removeMatch(Node* parent, Node* match, bool left);
	void removeSubtree(Node* ptr);

	Node* createLeaf(int key);

	void printInOrderPrivate(Node* ptr);
	void printPostorderPrivate(Node* ptr);
	void printPreorderPrivate(Node* ptr);

public:

	BST();
	~BST();

	int findSmallest();
	void addLeaf(int key);
	void removeNode(int data);
	
	void printInOrder();
	void printPostOrder();
	void printPreOrder();
};
