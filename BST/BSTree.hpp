#ifndef BS_TREE_HPP
#define BS_TREE_HPP
#include "Node.hpp"
#include <iostream>

class BSTree {
public:
	BSTree() : root(NULL) {}
	~BSTree() {
		deleteTree(root);
	}

	void insert(int key, void *value) { this->root = insertHelper(this->root, key, value); }
	bool remove(int key) { return removeHelper(this->root, key); }
	Node* getNode(int key) const { return getNodeHelper(this->root, key); }
	bool contains(int key) const { return getNodeHelper(this->root, key) != NULL; }
private:
	Node* root;

	Node* insertHelper(Node* node, int key, void* value) {
		if (node == NULL) {
			node = new Node(key, value);
		} else if (key < node->getKey()) {
			node->setLeft(insertHelper(node->getLeft(), key, value));
		} else if (key > node->getKey()) {
			node->setRight(insertHelper(node->getRight(), key, value));
		} else {
			node->setValue(value);
		}
		return node;
	}

	bool removeHelper(Node* node, int key) {
		if (node == NULL)
			return false;
		if (key < node->getKey())
			return removeHelper(node->getLeft(), key);
		if (key > node->getKey())
			return removeHelper(node->getRight(), key);

		if (node->getLeft() == NULL && node->getRight() == NULL) {
			delete node;
			node = NULL;
		} else if (node->getLeft() == NULL) {
			Node* temp = node;
			node = node->getRight();
			delete temp;
		} else if (node->getRight() == NULL) {
			Node* temp = node;
			node = node->getLeft();
			delete temp;
		} else {
			Node* minNode = findMin(node->getRight());
			node->setKey(minNode->getKey());
			node->setValue(minNode->getValue());
			removeHelper(node->getRight(), minNode->getKey());
		}
		return true;
	}

	Node* findMin(Node* node) {
		while (node->getLeft() != NULL) {
			node = node->getLeft();
		}
		return node;
	}

	Node* getNodeHelper(Node* node, int key) const {
		if (node == NULL)
			return NULL;
		if (key < node->getKey())
			return getNodeHelper(node->getLeft(), key);
		if (key > node->getKey())
			return getNodeHelper(node->getRight(), key);
		return node;
	}

	void deleteTree(Node* node) {
		if (node == NULL)
			return;
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}


};

#endif
