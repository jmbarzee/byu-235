/*
 * BST.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#include "BST.h"
#include "Node.h"

using namespace std;

BST::BST() {
	this->root = NULL;
	this->size = 0;
}
BST::~BST() {
	this->clear();
}
Node* BST::find(Node* root, int data) {
	if (root == NULL) {
		return NULL;
	} else if (root->getData() > data) {
		return find(root->getLeftChild(), data);
	} else if (root->getData() < data) {
		return find(root->getRightChild(), data);
	} else {
		return root;
	}
}
void BST::replace(Node* oldChild, Node* newChild) {
	if (oldChild->getParent() != NULL) {
		if (oldChild->getParent()->getRightChild() == oldChild) {
			oldChild->getParent()->setRightChild(newChild);
		} else {
			oldChild->getParent()->setLeftChild(newChild);
		}
	} else {
		this->root = newChild;
	}
	if (newChild != NULL) {
		newChild->setParent(oldChild->getParent());
		if (!(oldChild->getLeftChild() == newChild || oldChild->getRightChild() == newChild)) {
			newChild->setLeftChild(oldChild->getLeftChild());
			if (newChild->getLeftChild() != NULL)
				newChild->getLeftChild()->setParent(newChild);
			newChild->setRightChild(oldChild->getRightChild());
			if (newChild->getRightChild() != NULL)
				newChild->getRightChild()->setParent(newChild);
		}
	}
}
void BST::prune(Node* root) { // NEVER GREATER HAVE I NAMED A FUNCTION... JUST IMAGINE THIS... "SNIP, SNIP, SNIP, SNIP.... AWW MAN NOW ITS A STUMP...."
	if (root != NULL) {
		prune(root->getLeftChild());
		prune(root->getRightChild());
		delete root;
	}
}
void BST::print(Node* root) {
	if (root != NULL) {
		cout << root->getData();
		if (root->getParent() == NULL)
			cout << " is root" << endl;
		else
			cout << " of " << root->getParent()->getData() << endl;
		print(root->getLeftChild());
		print(root->getRightChild());
	}
}
Node * BST::getRootNode() {
	return this->root;
}
bool BST::add(int data) {
	if (this->size == 0) {
		this->root = new Node(data);
		this->size++;
		return true;
	}
	Node* crnt = this->root;
	while (crnt != NULL) {
		if (crnt->getData() > data) {
			if (crnt->getLeftChild() == NULL) {
				crnt->setLeftChild(new Node(data, NULL, NULL, crnt));
				this->size++;
				return true;
			} else {
				crnt = crnt->getLeftChild();
			}
		} else if (crnt->getData() < data) {
			if (crnt->getRightChild() == NULL) {
				crnt->setRightChild(new Node(data, NULL, NULL, crnt));
				this->size++;
				return true;
			} else {
				crnt = crnt->getRightChild();
			}
		} else {
			// DATA WAS FOUND IN TREE
			return false;
		}
	}
	// TREE IS EMPTY
	root = new Node(data);
	this->size++;
	return true;
}
bool BST::remove(int data) {
	Node * crnt = find(this->root, data);
	if (crnt == NULL)
		return false;
	if (crnt->getLeftChild() == NULL) {
		replace(crnt, crnt->getRightChild());
		delete crnt;
		this->size--;
		return true;
	}
	if (crnt->getRightChild() == NULL) {
		replace(crnt, crnt->getLeftChild());
		delete crnt;
		this->size--;
		return true;
	} else {
		// CASES 2, 3, 4
		Node* temp = crnt->getLeftChild();
		while (temp->getRightChild() != NULL)
			temp = temp->getRightChild();
		replace(temp, temp->getLeftChild());
		replace(crnt, temp);
		delete crnt;
		this->size--;
		return true;
	}
}
void BST::clear() {
	prune(this->root);
	this->root = NULL;
	this->size = 0;
}
