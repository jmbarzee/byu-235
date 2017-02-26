/*
 * Node3D.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: jacobmb
 */
#include <cstdlib>
#include "Node3D.h"

using namespace std;

Node3D::Node3D(int cost = -1, bool open = false, Node3D* prev = NULL) {
	this->cost = cost;
	this->open = open;
	this->prev = prev;
	x = 0;
	y = 0;
	z = 0;
}
void Node3D::setXYZ(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
int Node3D::getX() const {
	return x;
}
int Node3D::getY() const {
	return y;
}
int Node3D::getZ() const {
	return z;
}
int Node3D::getCost() const {
	return cost;
}

void Node3D::setCost(int cost) {
	this->cost = cost;
}

bool Node3D::isOpen() const {
	return open;
}

void Node3D::setOpen(bool open) {
	this->open = open;
}

Node3D* Node3D::getPrev() const {
	return prev;
}

void Node3D::setPrev(Node3D* prev) {
	this->prev = prev;
}

