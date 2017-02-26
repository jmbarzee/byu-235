/*
 * IR.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#ifndef IR_H_
#define IR_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

class IR {
private:
	int length;
	Node* head;

	Node* findInList(int data);
	void placeAfter(Node* crntNode, Node* newNode);
	void placeAtHead(Node* newNode);
public:
	IR(void);
	~IR(void);
	void insertHead(int value);
	int getHead();
	int removeHead();
	int getTail();
	int removeTail();
	void remove(int value);
	bool contains(int data);
	int at(int index);
	int size();
};

#endif /* IR_H_ */
