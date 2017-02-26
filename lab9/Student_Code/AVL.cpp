/*
 * AVL.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: jacobmb
 */

#include <iostream>

#include "AVL.h"
#include "Node.h"

using namespace std;

AVL::AVL() {
	this->root = NULL;
	this->size = 0;
	this->increased = false;
	this->changed = false;
}
AVL::~AVL() {
	this->clear();
}
void AVL::printR(Node* root) {
	if (root != NULL) {
		cout << root->getData();
		printR(root->getLeftChild());
		printR(root->getRightChild());
	}
}
bool AVL::addR(Node*& root, int data) {
	if (root == NULL) {
		root = new Node(data);
		this->size++;
		this->increased = true;
		return true;
	}
	//cout << "addR(" << root->getData() << ", " << data << ')' << endl;
	//cout << "    bal: " << root->getBalance() << endl;
	bool added = false;
	int startHeight = root->getHeight();
	if (root->getData() == data)
		return false;
	else if (data < root->getData()) {
		added = addR(root->left, data);
		if (this->increased) {
			root->decBalance();
			if (root->getBalance() == -2) {
				if (root->left->getBalance() == 1) {
					// left right case
					spinLeft(root->left);
				}
				spinRight(root);
				this->increased = false;
			} else if (root->getBalance() == 0)
				this->increased = false;
		}

	} else if (data > root->getData()) {
		added = addR(root->right, data);
		if (this->increased) {
			root->incBalance();
			if (root->getBalance() == 2) {
				if (root->right->getBalance() == -1) {
					// right left case
					spinRight(root->right);
				}
				spinLeft(root);
				this->increased = false;
			} else if (root->getBalance() == 0)
				this->increased = false;
		}
	}
	return added;
}
bool AVL::removeR(Node*& root, int data) {
	if (root == NULL)
		return false;
	//cout << "removeR(" << root->getData() << ',' << data << ')' << endl;
	if (root->getData() == data) {
		Node** rep;
		if (root->left != NULL) {
			//cout << "use left" << endl;
			rep = &root->left;
			while ((*rep)->right != NULL)
				rep = &((*rep)->right);
			root->setData((*rep)->getData());
			Node* temp = (*rep)->left;
			delete *rep;
			*rep = temp;;
		} else if (root->right != NULL) {
			//cout << "use right" << endl;
			rep = &root->right;
			Node* temp = root;
			root = *rep;
			delete temp;
		} else {
			//cout << "use self" << endl;
			delete root;
			root = NULL;
		}
		size--;
		return true;
	} else if (data < root->getData())
		return removeR(root->left, data);
	else if (data > root->getData())
		return removeR(root->right, data);
}
void AVL::clearR(Node* root) {
	if (root != NULL) {
		clearR(root->left);
		cout << root->getData();
		clearR(root->right);
		delete root;
	}
}
void AVL::spinRight(Node*& root) {
	Node* pivot = root->left;
	root->left = pivot->right;
	pivot->right = root;
	root = pivot;
	root->incBalance();
	root->right->incBalance();
}
void AVL::spinLeft(Node*& root) {
	Node* pivot = root->right;
	root->right = pivot->left;
	pivot->left = root;
	root = pivot;
	root->decBalance();
	root->left->decBalance();
}
void AVL::rebalance(Node*& root) {
	if (root == NULL)
		return;
	rebalance(root->left);
	rebalance(root->right);
	if (root->getBalance() == -2) {

		if (root->left->getBalance() == 1) {
			//cout << "left right case" << endl;
			spinLeft(root->left);
		}
		//cout << "left left case" << endl;
		spinRight(root);
		changed = true;
	} else if (root->getBalance() == 2) {
		if (root->right->getBalance() == -1) {
			//cout << "right left case" << endl;
			spinRight(root->right);
		}
		//cout << "right right case" << endl;
		spinLeft(root);
		changed = true;
	}
}
Node * AVL::getRootNode() {
	return this->root;
}
void AVL::print() {
	printR(this->root);
}
bool AVL::add(int data) {
	this->increased = false;
	bool toReturn = addR(this->root, data);
	do {
		changed = false;
		if (root != NULL)
			root->refresh();
		rebalance(root);
	} while (changed);
	return toReturn;
}
bool AVL::remove(int data) {
	bool toReturn = removeR(this->root, data);
	do {
		changed = false;
		if (root != NULL)
			root->refresh();
		rebalance(root);
	} while (changed);
	return toReturn;
}

void AVL::clear() {
	clearR(this->root);
	this->root = NULL;
	this->size = 0;
}
