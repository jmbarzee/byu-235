/*
 * QS.cpp
 *
 * Created on: Apr 2, 2015
 * Author: jacobmb
 */
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "QS.h"

using namespace std;

QS::QS() {
	capacity = 0;
	size = 0;
	first = NULL;
}
QS::~QS() {
	clear();
}

/*
 * sortAll()
 *
 * Sorts elements of the array.  After this function is called, every
 * element in the array is less than or equal its successor.
 *
 * Does nothing if the array is empty.
 */
void QS::sort(int left, int right) {
	if (left < right) {
		if (right - left < 2) {
			if (first[left] > first[right])
				swap(right, left);
		} else if (right - left == 2) {
			medianOfThree(left, right);
		} else if (right - left > 2) {
			int pivot = medianOfThree(left, right);
			pivot = partition(left, right, pivot);
			sort(left, pivot - 1);
			sort(pivot + 1, right);
		}
	}
}
void QS::swap(int pos1, int pos2) {
	int temp = first[pos1];
	first[pos1] = first[pos2];
	first[pos2] = temp;
}
void QS::sortAll() {
	if (size < 2)
		return;
	sort(0, size - 1);
}

int QS::medianOfThree(int left, int right) {
	if (capacity < 1)
		return -1;
	if (!(right < size))
		return -1;
	if (!(left < right))
		return -1;
	if (!(-1 < left))
		return -1;
	int pivot = (left + right) / 2;
	if (first[left] > first[pivot]) {
		swap(left, pivot);
	}
	if (first[pivot] > first[right]) {
		swap(pivot, right);
	}
	if (first[left] > first[pivot]) {
		swap(left, pivot);
	}
	return pivot;
}
int QS::partition(int left, int right, int pivotIndex) {
	if ((capacity < 1))
		return -1;
	if (!(right < size))
		return -1;
	if (!(pivotIndex < right))
		return -1;
	if (!(left < pivotIndex))
		return -1;
	if (!(-1 < left))
		return -1;
	int pivot = first[pivotIndex];
	swap(pivotIndex, right);
	int boundry = left;
	for (int i = left; i < right; i++) {
		if (first[i] < pivot) {
			swap(i, boundry);
			boundry++;
		}
	}
	swap(boundry, right);
	return boundry;
}
string QS::getArray() {
	stringstream ss;
	for (int i = 0; i < size; i++) {
		ss << first[i];
		if (i < size - 1)
			ss << ',';
	}
	return ss.str();
}
int QS::getSize() {
	return size;
}
void QS::addToArray(int value) {
	if (capacity > size) {
		first[size] = value;
		size++;
	}
}
bool QS::createArray(int capacity) {
	if (capacity < 0)
		return false;
	clear();
	first = new int[capacity];
	this->capacity = capacity;
	return true;
}
void QS::clear() {
	delete[] first;
	first = NULL;
	size = 0;
	capacity = 0;
}

