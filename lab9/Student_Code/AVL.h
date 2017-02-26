/*
 * AVL.h
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#ifndef AVL_H_
#define AVL_H_

#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL: public AVLInterface {
private:
	int size;
	Node* root;
	bool increased;
	bool changed;
	void printR(Node* root);
	bool addR(Node*& root, int data);
	bool removeR(Node*& root, int data);
	void clearR(Node* root);
	void spinRight(Node*& root);
	void spinLeft(Node*& root);
	void rebalance(Node*& root);
public:
	AVL();
	~AVL();
	Node* getRootNode();
	void print();
	bool add(int data);
	bool remove(int data);
	void clear();

};


#endif /* AVL_H_ */
