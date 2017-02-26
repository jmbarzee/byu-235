

#ifndef NODE_H_
#define NODE_H_


#include <iostream>
using namespace std;

class Node {
	private:
		int data;
		Node* next;
	public:
		Node(int newData, Node* newNext = NULL);
		Node* getNext();
		int getData();
		void setNext(Node* newNext);
};

#endif /* NODE_H_ */
