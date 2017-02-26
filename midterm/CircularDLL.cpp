/*
 * CircularDLL.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: jacobmb
 */
#include <string>
#include "NodeDL.h"
#include "CircularDLL.h"
#include <iostream>

using namespace std;
CircularDLL::CircularDLL() {
	head = NULL;
	tail = NULL;
	Size = 0;
}
string CircularDLL::remove(Node<string>* crnt) {
	string name = crnt->getData();
	if (Size == 1) {
		head = NULL;
		tail = NULL;
	} else {
		crnt->getNext()->setPrev(crnt->getPrev());
		crnt->getPrev()->setNext(crnt->getNext());
	}
	if (crnt == head) {
		head = crnt->getNext();
	} else if (crnt == tail) {
		tail = crnt->getPrev();
	}
	Size--;
	delete crnt;
	return name;
}
Node<string>* CircularDLL::getNode(int index) {
	if (index >= Size)
		return NULL;
	Node<string>* crnt = head;
	for (int i = 0; i < index; i++)
		crnt = crnt->getNext();
	return crnt;
}


void CircularDLL::printPointers() {
	Node<string>* crnt = head;
	cout << "    ******Head: " << head << endl;
	cout << "    ******Tail: " << tail << endl;
	for (int i = 0; i < Size; i++) {
		cout << endl;
		cout << "    ******Pointers are:****" << endl;
		cout << "    ******Crnt: " << crnt << endl;
		cout << "    ******Next: " << crnt->getNext() << endl;
		cout << "    ******Prev: " << crnt->getPrev() << endl;
		crnt = crnt->getNext();
	}
}
Node<string>* CircularDLL::inList(string name) {
	//cout << "    ****inList()****" << endl;
	if (Size < 1) {
		return NULL;
	}
	Node<string>* crnt = head;
	for (int i = 0; i < Size; i++) {
		if (crnt->getData() == name) {
			return crnt;
		}
		crnt = crnt->getNext();
	}
	return NULL;
}
/**
 * Adds the given name to the beginning of the list so that
 * atFromHead(0) == name and atFromTail(size() - 1) == name.
 * After the operation, the size should have increased by 1.
 *
 * returns true if successful.
 * returns false if the same name already exists.
 */
bool CircularDLL::insertHead(string name) {
	//cout << "    ****insertHead()****" << endl;
	if (inList(name) != NULL)
		return false;
	if (Size > 0) {
		Node<string>* newN = new Node<string>(name, head, tail);
		head = newN;
		newN->getNext()->setPrev(newN);
		newN->getPrev()->setNext(newN);
	} else {
		Node<string>* newN = new Node<string>(name, NULL, NULL);
		head = newN;
		tail = newN;
		newN->setNext(newN);
		newN->setPrev(newN);
	}
	Size++;
	return true;
}

/**
 * Adds the given name to the end of the list so that
 * atFromHead(size() - 1) == name and atFromTail(0) == name.
 * After the operation, the size should have increased by 1.
 *
 * returns true if successful, false otherwise.
 * returns false if the same name already exists.
 */
bool CircularDLL::insertTail(string name) {
	//cout << "    ****insertTail()****" << endl;
	if (inList(name) != NULL)
		return false;
	if (Size > 0) {
		Node<string>* newN = new Node<string>(name, head, tail);
		head->setPrev(newN);
		tail->setNext(newN);
		tail = newN;
	} else {
		Node<string>* newN = new Node<string>(name, NULL, NULL);
		head = newN;
		tail = newN;
		newN->setNext(newN);
		newN->setPrev(newN);
	}
	Size++;
	return true;
}

/**
 * Inserts the given name into the given index of the list so that
 * atFromHead(index) == name.  All values should shift down one index
 * to accommodate the new value.  After the operation, the size should
 * have increased by 1.
 *
 * returns true if insert was successful.
 * returns false if the same name already exists.
 * returns false if the given index was out of range.
 */
bool CircularDLL::insertAt(string name, int index) {
	//cout << "    ****insertAt()****" << endl;
	if (index < 0)
		return false;
	if (index >= Size)
		return false;
	if (inList(name) != NULL)
		return false;
	Node<string>* crnt = head;
	for (int i = 0; i < index; i++)
		crnt = crnt->getNext();
	Node<string>* newN = new Node<string>(name, crnt, crnt->getPrev());
	newN->getNext()->setPrev(newN);
	newN->getPrev()->setNext(newN);
	if (head == crnt)
		head = newN;
	Size++;
	return true;
}

/**
 * Removes the value at the beginning of the list.  After this operation
 * size() should return a value 1 less than before and all values should
 * shift 1 index forward. If only one item remains, the head and tail
 * pointers should be returned a NULL state.
 *
 * returns true if the removal occurred successfully.
 * returns false if attempting to remove from an empty list.
 */
bool CircularDLL::removeHead() {
	//cout << "    ****removeHead()****" << endl;
	if (Size < 1)
		return false;
	Node<string>* temp = head;
	if (Size == 1) {
		head = NULL;
		tail = NULL;
	} else {
		head = temp->getNext();
		if (Size == 2)
			tail = head;
		temp->getNext()->setPrev(temp->getPrev());
		temp->getPrev()->setNext(temp->getNext());
	}
	Size--;
	delete temp;
	return true;
}

/**
 * Removes the value at the end of the list.  After this operation
 * size() should return a value 1 less than before and all index values
 * should remain unchanged. If only one item remains, the head and tail
 * pointers should be returned a NULL state.
 *
 * returns true if the removal occurred successfully.
 * returns false if attempting to remove from an empty list.
 */
bool CircularDLL::removeTail() {
	//cout << "    ****removeTail()****" << endl;
	if (Size < 1)
		return false;
	Node<string>* temp = tail;
	if (Size == 1) {
		head = NULL;
		tail = NULL;
	} else {
		tail = temp->getPrev();
		if (Size == 2)
			head = tail;
		temp->getNext()->setPrev(temp->getPrev());
		temp->getPrev()->setNext(temp->getNext());

	}
	Size--;
	delete temp;
	return true;
}

/**
 * Removes the value at the given index measured from the beginning.
 * index 0 is the beginning of the list.  After this removal the list size
 * should be 1 less and all following values should shift forward by 1.
 * If only one item remains and index 0 is given, the head and tail
 * pointers should be returned a NULL state.
 *
 * returns true if the removal occurred successfully.
 * returns false attempting to remove from an empty list.
 * returns false if the index was out of the range.
 */
bool CircularDLL::removeAt(int index) {
	//cout << "    ****RemoveAt(" << index << ")****" << endl;
	if (Size < 1)
		return false;
	if (index >= Size)
		return false;
	Node<string>* crnt = head;
	for (int i = 0; i < index; i++)
		crnt = crnt->getNext();
	if (Size == 1) {
		head = NULL;
		tail = NULL;
	} else {
		crnt->getNext()->setPrev(crnt->getPrev());
		crnt->getPrev()->setNext(crnt->getNext());
	}
	if (crnt == head) {
		head = crnt->getNext();
	} else if (crnt == tail) {
		tail = crnt->getPrev();
	}
	Size--;
	delete crnt;
	return true;
}

/**
 * Removes all nodes from the list and resets the state of the data structure
 * to empty.  size() should return 0 after this operation.
 */
void CircularDLL::clear() {
	//cout << "    ****Clear()****" << endl;
	for (int i = Size; i > 0; i--)
		removeAt(0);
}

int CircularDLL::size() {
	return Size;
}
/**
 * Measured from the head, where the beginning is indexed as 0,
 * and the end is indexed as size() - 1.
 *
 * returns the string located at the given index.
 * returns the string "invalid" if an invalid index is given. See top comment.
 */
string CircularDLL::atFromHead(int index) {
	//cout << "    ****atFromHead()****" << endl;
	if (index < 0)
		return "invalid";
	if (index >= Size)
		return "invalid";
	Node<string>* crnt = head;
	for (int i = 0; i < index; i++)
		crnt = crnt->getNext();
	return crnt->getData();
}

/**
 * Measured from the tail, where the end is indexed as 0,
 * and the beginning is indexed as size() - 1.
 *
 * returns the string located at the given index.
 * returns the string "invalid" if an invalid index is given. See top comment.
 */
string CircularDLL::atFromTail(int index) {
	//cout << "    ****atFromTail()****" << endl;
	if (index < 0)
		return "invalid";
	if (index >= Size)
		return "invalid";
	Node<string>* crnt = tail;
	for (int i = 0; i < index; i++)
		crnt = crnt->getPrev();
	return crnt->getData();
}

