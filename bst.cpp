#include <cstdlib>
#include "bst.h"

BST::BST()
 :	m_root(nullptr)
{
}

BST::~BST()
{
	removeSubtree(m_root);
}

BST::Node* BST::createLeaf(int key)
{
	Node* temp = new Node;
	temp->m_data = key;
	temp->m_left = nullptr;
	temp->m_right = nullptr;

	return temp;
}

void BST::addLeaf(int key)
{
	addLeafPrviate(key, m_root);
}

void BST::addLeafPrviate(int key, Node* ptr)
{
	if (m_root == nullptr)
	{
		m_root = createLeaf(key);
	}
	else if (key < ptr->m_data)
	{
		if (ptr->m_left != nullptr)
		{
			addLeafPrviate(key, ptr->m_left);
		}
		else
		{
			ptr->m_left = createLeaf(key);
		}
	}
	else if (key > ptr->m_data)
	{
		if (ptr->m_right != nullptr)
		{
			addLeafPrviate(key, ptr->m_right);
		}
		else
		{
			ptr->m_right = createLeaf(key);
		}
	}
	else
	{
		std::cout << "The key " << key << " has already been added to the tree\n";
	}
}


// Find functions

int BST::findSmallest()
{
	return findSmallestPrivate(m_root);
}

int BST::findSmallestPrivate(Node* ptr)
{
	if (m_root == nullptr)
	{
		std::cout << "Tree is empty\n" << std::endl;
		return -1000;
	}
	else
	{
		if (ptr->m_left != nullptr)
		{
			return findSmallestPrivate(ptr->m_left);
		}
		else
		{
			return ptr->m_data;
		}
	}
}


//Remove functions

void BST::removeNode(int data)
{
	removeNodePrivate(data, m_root);
}

void BST::removeNodePrivate(int data, Node* parent)
{
	if (m_root != nullptr)
	{
		if (m_root->m_data == data)
		{
			removeRootMatch();
		}
		else
		{
			if (data < parent->m_data && parent->m_left != nullptr)
			{
				if (parent->m_left->m_data == data)
				{
					removeMatch(parent, parent->m_left, true);
				}
				else
				{
					removeNodePrivate(data, parent->m_left);
				}
			}
			else if (data > parent->m_data && parent->m_right != nullptr)
			{
				if (parent->m_right->m_data == data)
				{
					removeMatch(parent, parent->m_right, false);
				}
				else
				{
					removeNodePrivate(data, parent->m_right);
				}
			}
			else
			{
				std::cout << "The key " << data << " was not found in the tree\n";
			}
		}
	}
	else
	{
		std::cout << "The tree is empty\n";
	}
}

void BST::removeRootMatch()
{
	if (m_root != nullptr)
	{
		Node* temp = m_root;
		int rootData = m_root->m_data;
		int smallestInRightSubtree;

		// Zero Children
		if (m_root->m_left == nullptr && m_root->m_right == nullptr)
		{
			m_root = nullptr;
			delete temp;
		}

		// 1 Child - right
		else if (m_root->m_left == nullptr && m_root->m_right != nullptr)
		{
			m_root = m_root->m_right;
			temp->m_right = nullptr;
			delete temp;
			std::cout << "The root node with key " << rootData << " was delete. The new root contains key " << m_root->m_data << std::endl;
		}

		// 1 Child - left
		else if (m_root->m_left != nullptr && m_root->m_right == nullptr)
		{
			m_root = m_root->m_left;
			temp->m_left = nullptr;
			delete temp;
			std::cout << "The root node with key " << rootData << " was delete. The new root contains key " << m_root->m_data << std::endl;
		}
		
		// 2 Children
		else
		{
			smallestInRightSubtree = findSmallestPrivate(m_root->m_right);
			removeNodePrivate(smallestInRightSubtree, m_root);
			m_root->m_data = smallestInRightSubtree;
			std::cout << "The root key containing key " << rootData << " was overwritten with key " << m_root->m_data;
		}
	}
	else
	{
		std::cout << "Can not remove root, tree is empty\n";
	}
}

void BST::removeMatch(Node* parent, Node* match, bool left)
{
	if (m_root != nullptr)
	{
		Node* temp;
		int matchData = match->m_data;
		int smallestInRightSubtree;

		// Zero Children
		if (m_root->m_left == nullptr && m_root->m_right == nullptr)
		{
			temp = match;
			if (left == true)
			{
				parent->m_left = nullptr;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";
			}
			else
			{
				parent->m_right = nullptr;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";
			}
		}

		// 1 Child - right
		else if (match->m_left == nullptr && match->m_right != nullptr)
		{
			if (left == true)
			{
				parent->m_left = match->m_right;
				match->m_right = nullptr;
				temp = match;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";

			}
			else
			{
				parent->m_right = match->m_right;
				match->m_right = nullptr;
				temp = match;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";
			}
		}

		// 1 Child - left
		else if (match->m_left != nullptr && match->m_right == nullptr)
		{
			if (left == true)
			{
				parent->m_left = match->m_left;
				match->m_left = nullptr;
				temp = match;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";

			}
			else
			{
				parent->m_right = match->m_left;
				match->m_left = nullptr;
				temp = match;
				delete temp;
				std::cout << "The node containing key " << matchData << " was removed\n";
			}
		}

		// 2 Children
		else
		{
			smallestInRightSubtree = findSmallestPrivate(match->m_right);
			removeNodePrivate(smallestInRightSubtree, match);
			match->m_data = smallestInRightSubtree;
		}
	}
	else
	{
		std::cout << "Can not remove match. The tree is empty\n";
	}
}

void BST::removeSubtree(Node* ptr)
{
	if (ptr != nullptr)
	{
		if (ptr->m_left != nullptr)
		{
			removeSubtree(ptr->m_left);
		}
		if (ptr->m_right != nullptr)
		{
			removeSubtree(ptr->m_right);
		}
		//std::cout << "Deleting the node containing key " << ptr->m_data << std::endl;
		delete ptr;
	}
}


// printing functions

//print inorder - left root right
void BST::printInOrder()
{
	if (m_root == nullptr)
	{
		std::cout << "The tree is empty\n";
		return;
	}
	printInOrderPrivate(m_root);
}

void BST::printInOrderPrivate(Node* ptr)
{
	if (ptr == nullptr) { return; }
	printInOrderPrivate(ptr->m_left);
	std::cout << ptr->m_data << " ";
	printInOrderPrivate(ptr->m_right);
}

//print preorder - root left right
void BST::printPreOrder()
{
	if (m_root == nullptr)
	{
		std::cout << "The tree is empty\n";
		return;
	}
	printPreorderPrivate(m_root);
}

void BST::printPreorderPrivate(Node* ptr)
{
	if (ptr == nullptr) { return; }
	std::cout << ptr->m_data << " ";
	printPreorderPrivate(ptr->m_left);
	printPreorderPrivate(ptr->m_right);
}

//print post order - left right root
void BST::printPostOrder()
{
	if (m_root == nullptr)
	{
		std::cout << "The tree is empty\n";
		return;
	}
	printPostorderPrivate(m_root);
}

void BST::printPostorderPrivate(Node* ptr)
{
	if (ptr == nullptr) { return; }
	printPostorderPrivate(ptr->m_left);
	printPostorderPrivate(ptr->m_right);
	std::cout << ptr->m_data << " ";
}
