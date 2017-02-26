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
	Node(const int& data, Node* left = NULL, Node* right = NULL, const int& balance = 0, const int& height = 1);
	~Node() {};
	int getData();
	int getBalance();
	int getHeight();
	Node* getLeftChild();
	Node* getRightChild();
	void setData(int data);
	void incBalance();
	void decBalance();
	void incHeight();
	void decHeight();
	int refresh();
	Node* left;
	Node* right;
private:
	int height;
	int balance;
	int data;
};

#endif /* NODE_H_ */
