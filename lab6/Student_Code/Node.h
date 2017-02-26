/*
 * Node.h
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#ifndef NODE_H_
#define NODE_H_

#include "NodeInterface.h"

using namespace std;

class Node: public NodeInterface {
public:
	Node(int data, Node* left = NULL, Node* right = NULL, Node* parent = NULL);
	~Node() {};
	int getData();
	Node* getLeftChild();
	Node* getRightChild();
	Node* getParent();
	void setLeftChild(Node* left);
	void setRightChild(Node* right);
	void setParent(Node* parent);
private:
	int data;
	Node* left;
	Node* right;
	Node* parent;

};

#endif /* NODE_H_ */
