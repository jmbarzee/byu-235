/*
 * Node.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#include "Node.h"

using namespace std;

Node::Node(int newData, Node* newNext) {
	data = newData;
	next = newNext;
}
Node* Node::getNext() {
	return next;
}
int Node::getData() {
	return data;
}
void Node::setNext(Node* newNext) {
	next = newNext;
}

