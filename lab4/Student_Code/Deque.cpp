/*
 * Deque.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: jacobmb
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include "Deque.h"

Node* Deque::findInList(int data) {
	Node* temp = head;
	while (temp != NULL) {
		if (temp->getData() == data) {
			return temp;
		}
		temp = temp->getNext();
	}
	return NULL;
}

void Deque::placeAfter(Node* crntNode, Node* newNode) {
	newNode->setNext(crntNode->getNext());
	crntNode->setNext(newNode);
}

void Deque::placeAtHead(Node* newNode) {
	newNode->setNext(head);
	head = newNode;
}

Deque::Deque(void) {
	head = NULL;
	length = 0;
}

Deque::~Deque(void) {
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

void Deque::insertHead(int value) {
	if (findInList(value) == NULL) {
		length++;
		placeAtHead(new Node(value));
	}
}

int Deque::getHead() {
	return head->getData();
}

int Deque::removeHead() {
	Node* temp = head;
	int tempData = temp->getData();
	head = head->getNext();
	delete temp;
	length--;
	return tempData;
}

void Deque::insertTail(int value) {
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

int Deque::getTail() {
	return at(length - 1);
}

int Deque::removeTail() {
	int tempData = at(length - 1);
	remove(tempData);
	return tempData;
}

void Deque::remove(int value) {
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

bool Deque::contains(int data) {
	if (findInList(data) != NULL) {
		return true;
	}
	return false;
}

int Deque::at(int index) {
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

int Deque::size() {
	return length;
}
