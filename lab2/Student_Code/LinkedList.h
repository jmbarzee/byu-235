#include "Node.h"
#include <stdexcept>
#include "LinkedListInterface.h"\
#include <iostream>

using namespace std;

template<class T>
class LinkedList : public LinkedListInterface <T> {
	private:
		int length;
		Node<T>* head;
		//findInList
		//lookes to check if data is in the list currently, 
		//if it is, the node containing the data is returned
		//otherwise, returns NULL
		Node<T>* findInList(T data) {
			Node<T>* temp = head;
			while(temp != NULL) {
				if(temp->getData() == data) {
					return temp;
				}
				temp = temp->getNext();
			}
			return NULL;
		}
		// placeAfter
		// takes a node in the list and a node to be inserted whose
		// next is NULL and adds the new node to the list
		void placeAfter(Node<T>* crntNode, Node<T>* newNode) {
			newNode->setNext(crntNode->getNext());
			crntNode->setNext(newNode);
		}
		void placeAtHead(Node<T>* newNode) {
			newNode->setNext(head);
			head = newNode;
		}
	public:
	LinkedList(void) {
		head = NULL;
		length = 0;
	}
	~LinkedList(void) {
		if(head != NULL) {
			Node<T>* crnt = head;
			Node<T>* next = crnt->getNext();
			while(next != NULL) {
				delete crnt;
				crnt = next;
				next = next->getNext();
			}
			delete crnt;
		}
	}
	void insertHead(T value) {
		if(findInList(value) == NULL) {
			length++;
			placeAtHead(new Node<T>(value));
		}
	}
	void insertTail(T value) {
		if(head == NULL) {
			placeAtHead(new Node<T>(value));
			length++;
		} else if(findInList(value) == NULL) {
			length++;
			Node<T>* crnt = head;
			while(crnt->getNext() != NULL) {
				crnt = crnt->getNext();
			}
			placeAfter(crnt, new Node<T>(value));
		}
	}
	void insertAfter(T value, T insertionNode) {
		Node<T>* prev = findInList(insertionNode);
		if(findInList(value) == NULL && prev != NULL) {
			length++;
			placeAfter(prev, new Node<T>(value));
		}
	}
	void remove(T value) {
		if(findInList(value) != NULL) {
			Node<T>* prev = head;
			if(prev->getData() == value) {
				head = head->getNext();
				delete prev;
				prev = NULL;
				length--;
			} else {
				Node<T>* crnt = prev->getNext();
				while(crnt->getData() != value) {
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
	void clear() {
		if(head != NULL) {
			Node<T>*crnt = head;
			Node<T>* next = crnt->getNext();
			while(next != NULL) {
				delete crnt;
				crnt = next;
				next = next->getNext();
			}
			delete crnt;
		}
		head = NULL;
		length = 0;
	}
	T at(int index) {
		if(index > length || index < 0) {
			throw out_of_range("past");
		}
		Node<T>* crnt = head;
		int pos = 0;
		while(pos < index) {
			crnt = crnt->getNext();
			pos++;
		}
		if(crnt != NULL){
			return crnt->getData();
		}
		throw out_of_range("past");
	}	
	int size() {
		return length;
	}
};
