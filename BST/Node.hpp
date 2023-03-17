#ifndef NODE_HPP
#define NODE_HPP
#include <cstdlib>

template<typename T>
class Node {
public:
	Node(int key, T* value) : key(key), value(value), left(NULL), right(NULL) {}
	int getKey() const { return key; }
	void setKey(int newKey) { key = newKey; }
	T* getValue() const { return value; }
	void setValue(T* newValue) {
		delete this->value;
		this->value = newValue;
	}
	Node* getLeft() const { return left; }
	Node* getRight() const { return right; }
	void setLeft(Node* node) { left = node; }
	void setRight(Node* node) { right = node; }
	virtual ~Node() { delete this->value; }
private:
	int key;
	T* value;
	Node* left;
	Node* right;
};

#endif
