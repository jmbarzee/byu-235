/*
 * Queue.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

class Queue {
private:
	int length;
	Node* head;

	Node* findInList(int data);
	void placeAfter(Node* crntNode, Node* newNode);
	void placeAtHead(Node* newNode);
public:
	Queue(void);
	~Queue(void);
	void insertHead(int value);
	int getTail();
	int removeTail();
	void remove(int value);
	bool contains(int data);
	int at(int index);
	int size();
};

#endif /* QUEUE_H_ */
