/*
 * Deque.h
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

class Deque {
private:
	int length;
	Node* head;

	Node* findInList(int data);
	void placeAfter(Node* crntNode, Node* newNode);
	void placeAtHead(Node* newNode);
public:
	Deque(void);
	~Deque(void);
	void insertHead(int value);
	int getHead();
	int removeHead();
	void insertTail(int value);
	int getTail();
	int removeTail();
	void remove(int value);
	bool contains(int data);
	int at(int index);
	int size();
};

#endif /* DEQUE_H_ */
