/*
 * Node3D.h
 *
 *  Created on: Mar 11, 2015
 *      Author: jacobmb
 */

#ifndef NODE3D_H_
#define NODE3D_H_

using namespace std;

class Node3D {
private:
	int x,y,z;
	int cost;
	bool open;
	Node3D* prev;
public:
	Node3D() {};
	Node3D(int cost, bool open, Node3D* prev);
	~Node3D() {};
	void setXYZ(int x, int y, int z);
	int getX() const;
	int getY() const;
	int getZ() const;
	int getCost() const;
	void setCost(int cost);
	bool isOpen() const;
	void setOpen(bool open);
	Node3D* getPrev() const;
	void setPrev(Node3D* prev);
};

#endif /* NODE3D_H_ */
