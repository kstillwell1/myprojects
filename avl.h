#pragma once
#include <iostream>

struct Node
{
	int key;
	int height;
	Node* left;
	Node* right;

	Node(int val);
};

class AVL
{
private:
	Node* root;

	int height(Node* node);
	Node* rightRotate(Node* y);
	Node* leftRotate(Node* x);
	int getBalance(Node* n);
};
