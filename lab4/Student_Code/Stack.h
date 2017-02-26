/*
 * Stack.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#ifndef STACK_H_
#define STACK_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

class Stack {
private:
	int length;
	Node* head;

	Node* findInList(int data);
	void placeAfter(Node* crntNode, Node* newNode);
	void placeAtHead(Node* newNode);
public:
	Stack(void);
	~Stack(void);
	void insertHead(int value);
	int getHead();
	int removeHead();
	void remove(int value);
	bool contains(int data);
	int at(int index);
	int size();
};

#endif /* STACK_H_ */
