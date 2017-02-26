/*
 * NodeDL.h
 *
 *  Created on: Mar 5, 2015
 *      Author: jacobmb
 */

#ifndef NODEDL_H_
#define NODEDL_H_

using namespace std;

template<class T>
class Node {
public:
	Node(T data, Node<T>* next, Node<T>* prev) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
	~Node() {
	}
	T getData() const {
		return data;
	}

	void setData(T data) {
		this->data = data;
	}

	Node<T>* getNext() const {
		return next;
	}

	void setNext(Node<T>* next) {
		this->next = next;
	}

	Node<T>* getPrev() const {
		return prev;
	}

	void setPrev(Node<T>* prev) {
		this->prev = prev;
	}

private:
	T data;
	Node<T>* next;
	Node<T>* prev;

};

#endif /* NODEDL_H_ */
