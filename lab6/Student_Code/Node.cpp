/*
 * Node.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#include "NodeInterface.h"
#include "Node.h"
#include <cstdlib>

using namespace std;

Node::Node(int data, Node* left, Node* right, Node* parent) {
	this->data = data;
	this->left = left;
	this->right = right;
	this->parent = parent;
}

int Node::getData() {
	return data;
}
Node* Node::getLeftChild() {
	return left;
}
Node* Node::getRightChild() {
	return right;
}
Node* Node::getParent() {
	return parent;
}
void Node::setLeftChild(Node* left) {
	this->left = left;
}
void Node::setRightChild(Node* right) {
	this->right = right;
}
void Node::setParent(Node* parent) {
	this->parent = parent;
}

