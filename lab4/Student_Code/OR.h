/*
 * OR.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#ifndef OR_H_
#define OR_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

class OR {
private:
	int length;
	Node* head;

	Node* findInList(int data);
	void placeAfter(Node* crntNode, Node* newNode);
	void placeAtHead(Node* newNode);
public:
	OR(void);
	~OR(void);
	void insertHead(int value);
	int getHead();
	int removeHead();
	void insertTail(int value);
	void remove(int value);
	bool contains(int data);
	int at(int index);
	int size();
};

#endif /* OR_H_ */
