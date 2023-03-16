#ifndef NODE_HPP
#define NODE_HPP
#include <cstdlib>
class Node {
public:
	Node(int key, void* value) : key(key), value(value), left(NULL), right(NULL) {}
	int getKey() const { return key; }
	void setKey(int newKey) { key = newKey; }
	void* getValue() const { return value; }
	void setValue(void* newValue) { this->value = newValue; }
	Node* getLeft() const { return left; }
	Node* getRight() const { return right; }
	void setLeft(Node* node) { left = node; }
	void setRight(Node* node) { right = node; }
private:
	int key;
	void* value;
	Node* left;
	Node* right;
};

#endif
