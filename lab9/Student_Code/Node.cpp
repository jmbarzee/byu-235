/*
 * Node.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#include "NodeInterface.h"
#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Node::Node(const int& data, Node* left, Node* right, const int& balance, const int& height) {
	this->data = data;
	this->left = left;
	this->right = right;
	this->balance = balance;
	this->height = height;
}
int Node::getData() {
	return data;
}
int Node::getBalance() {
	return balance;
}
int Node::getHeight() {
	return height;
}
Node* Node::getLeftChild() {
	return left;
}
Node* Node::getRightChild() {
	return right;
}
void Node::setData(int data) {
	this->data = data;
}
void Node::incBalance() {
	this->balance++;
}
void Node::decBalance() {
	this->balance--;
}
void Node::incHeight() {
	this->height++;
}
void Node::decHeight() {
	this->height--;
}
int Node::refresh() {
	//cout << data << " was h:" << height << " b:" << balance << endl;
	if (right == NULL && left == NULL) {
		balance = 0;
		height = 1;
	} else if (right == NULL) {
		height = left->refresh() + 1;
		balance = 0 - left->getHeight();
	} else if (left == NULL) {
		height = right->refresh() + 1;
		balance = right->getHeight() - 0;
	} else {
		height = max(left->refresh(), right->refresh()) + 1;
		balance = right->getHeight() - left->getHeight();
	}
	//cout << data << " now h:" << height << " b:" << balance << endl;
	return height;
}




