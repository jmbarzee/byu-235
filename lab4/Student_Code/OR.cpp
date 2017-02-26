/*
 * OR.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */



#include <string>
#include <stdexcept>
#include <iostream>
#include "OR.h"

Node* OR::findInList(int data) {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->getData() == data) {
			return temp;
		}
		temp = temp->getNext();
	}
	return NULL;
}

void OR::placeAfter(Node* crntNode, Node* newNode) {
	newNode->setNext(crntNode->getNext());
	crntNode->setNext(newNode);
}

void OR::placeAtHead(Node* newNode) {
	newNode->setNext(head);
	head = newNode;
}

OR::OR(void) {
	head = NULL;
	length = 0;
}

OR::~OR(void) {
	if (head != NULL) {
		Node* crnt = head;
		Node* next = crnt->getNext();
		while (next != NULL) {
			delete crnt;
			crnt = next;
			next = next->getNext();
		}
		delete crnt;
	}
}

void OR::insertHead(int value) {
	if (findInList(value) == NULL) {
		length++;
		placeAtHead(new Node(value));
	}
}

int OR::getHead() {
	return head->getData();
}

int OR::removeHead() {
	Node* temp = head;
	int tempData = temp->getData();
	head = head->getNext();
	delete temp;
	length--;
	return tempData;
}

void OR::insertTail(int value) {
	if (head == NULL) {
		placeAtHead(new Node(value));
		length++;
	} else if (findInList(value) == NULL) {
		length++;
		Node* crnt = head;
		while (crnt->getNext() != NULL) {
			crnt = crnt->getNext();
		}
		placeAfter(crnt, new Node(value));
	}
}


void OR::remove(int value) {
	if (findInList(value) != NULL) {
		Node* prev = head;
		if (prev->getData() == value) {
			head = head->getNext();
			delete prev;
			prev = NULL;
			length--;
		} else {
			Node* crnt = prev->getNext();
			while (crnt->getData() != value) {
				prev = crnt;
				crnt = crnt->getNext();
			}
			prev->setNext(crnt->getNext());
			delete crnt;
			crnt = NULL;
			length--;
		}
	}
}

bool OR::contains(int data) {
	if (findInList(data) != NULL) {
		return true;
	}
	return false;
}

int OR::at(int index) {
	if (index > length || index < 0) {
		throw out_of_range("past");
	}
	Node* crnt = head;
	int pos = 0;
	while (pos < index) {
		crnt = crnt->getNext();
		pos++;
	}
	if (crnt != NULL) {
		return crnt->getData();
	}
	throw out_of_range("past");
}

int OR::size() {
	return length;
}

