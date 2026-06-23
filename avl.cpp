#include <cstdlib>
#include <algorithm>
#include "avl.h"

Node::Node(int data)
	: key(data)
	, height(1)
	, left(nullptr)
	, right(nullptr)
{
}

int AVL::height(Node* node)
{
	return node == nullptr ? 0 : node->height;
}

Node* AVL::rightRotate(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	return x;
}

Node* AVL::leftRotate(Node* x)
{
	Node* y = x->left;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	return y;
}

int AVL::getBalance(Node* node)
{
	return node == nullptr ? 0 : height(node->left) - height(node->right);
}
