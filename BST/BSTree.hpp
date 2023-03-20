#ifndef BS_TREE_HPP
#define BS_TREE_HPP
#include "Node.hpp"
#include <iostream>

template <typename T>
class BSTree {
public:
	BSTree() : root(NULL), listUpToDate(false) {}
	~BSTree() {
		deleteTree(root);
	}

	void insert(int key, T* value) {
		listUpToDate = false;
		this->root = insertHelper(this->root, key, value);
	}

	bool remove(int key) {
		listUpToDate = false;
		return removeHelper(NULL, this->root, key);
	}

	Node<T>* getNode(int key) const { return getNodeHelper(this->root, key); }
	bool contains(int key) const { return getNodeHelper(this->root, key) != NULL; }

	vector<T*> getAll() {
		if (listUpToDate)
			return allValues;
		allValues.clear();
		getAllHelper(root, allValues);
		listUpToDate = true;
		return allValues;
	}

private:
	Node<T>* root;
	bool listUpToDate;
	vector<T*> allValues;

	Node<T>* insertHelper(Node<T>* node, int key, T* value) {
		if (node == NULL) {
			node = new Node<T>(key, value);
		} else if (key < node->getKey()) {
			node->setLeft(insertHelper(node->getLeft(), key, value));
		} else if (key > node->getKey()) {
			node->setRight(insertHelper(node->getRight(), key, value));
		} else {
			delete node->getValue();
			node->setValue(value);
		}
		return node;
	}

	void getAllHelper(Node<T>* node, vector<T*>& result) {
		if (node == NULL)
			return;
		getAllHelper(node->getLeft(), result);
		result.push_back(node->getValue());
		getAllHelper(node->getRight(), result);
	}

	void setNodeHelper(Node<T>* parent, Node<T>* node, Node<T>* set) {
		if (parent != NULL && parent->getRight() == node)
			parent->setRight(set);
		else if (parent != NULL && parent->getLeft() == node)
			parent->setLeft(set);
		else
			this->root = set;
	}

	bool removeHelper(Node<T>* parent, Node<T>* node, int key) {
		if (node == NULL)
			return false;
		if (key < node->getKey())
			return removeHelper(node, node->getLeft(), key);
		if (key > node->getKey())
			return removeHelper(node, node->getRight(), key);

		if (node->getLeft() == NULL && node->getRight() == NULL) {
			setNodeHelper(parent, node, NULL);
			delete node;
		} else if (node->getLeft() == NULL) {
			setNodeHelper(parent, node, node->getRight());
			delete node;
		} else if (node->getRight() == NULL) {
			setNodeHelper(parent, node, node->getLeft());
			delete node;
		} else {
			Node<T>* minNode = findMin(node->getRight());
			node->setKey(minNode->getKey());
			node->setValue(minNode->getValue());
			removeHelper(node, node->getRight(), minNode->getKey());
		}
		return true;
	}

	Node<T>* findMin(Node<T>* node) {
		while (node->getLeft() != NULL) {
			node = node->getLeft();
		}
		return node;
	}

	Node<T>* getNodeHelper(Node<T>* node, int key) const {
		if (node == NULL)
			return NULL;
		if (key < node->getKey())
			return getNodeHelper(node->getLeft(), key);
		if (key > node->getKey())
			return getNodeHelper(node->getRight(), key);
		return node;
	}

	void deleteTree(Node<T>* node) {
		if (node == NULL)
			return;
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}


};

#endif
