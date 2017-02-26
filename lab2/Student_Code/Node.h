#include <iostream>
using namespace std;

template<class T>
class Node {
	private:
		T data;
		Node<T>* next;
	public:
		Node(T newData, Node<T>* newNext = NULL) {
			data = newData;
			next = newNext;
		}
		Node<T>* getNext() {
			return next;
		}
		T getData() {
			return data;
		}
		void setNext(Node<T>* newNext) {
			next = newNext;
		}
};
