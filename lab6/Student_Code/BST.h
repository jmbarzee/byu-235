/*
 * BST.h
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#ifndef BST_H_
#define BST_H_

#include "BSTInterface.h"
#include "Node.h"

using namespace std;

class BST: public BSTInterface {
private:
	int size;
	Node* root;
public:
	BST();
	~BST();
	Node* find(Node* tree, int data);
	void print(Node* root);
	void replace(Node* oldChild, Node* newChild);
	void prune(Node* root);
	Node* getRootNode();
	bool add(int data);
	bool remove(int data);
	void clear();
};


#endif /* BST_H_ */
