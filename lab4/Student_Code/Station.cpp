/*
 * Station.cpp
 *
 *  Created on: Feb 23, 2015
 *      Author: jacobmb
 */
#include <iostream>
#include <string>
#include "Station.h"
using namespace std;

/**
 * Let another car arrive at the station and become the current car.
 * Do not allow a new car to arrive if any of the following conditions apply:
 * 1.	There is already a current car
 * 2.	The new car's ID already exists in any structure
 * 3.	The new car's ID is negative
 *
 * @param car the ID of the car arriving at the station
 * @return true if the car successfully arrived; false otherwise
 */
bool Station::addToStation(int car) {
	if (car < 0)
		return false;
	if (held != -1)
		return false;
	if (stack.contains(car))
		return false;
	if (queue.contains(car))
		return false;
	if (deque.contains(car))
		return false;
	if (Ir.contains(car))
		return false;
	if (Or.contains(car))
		return false;
	held = car;
	return true;
}

/**
 * Returns the ID of the current car.
 * Return -1 if there is no current car.
 *
 * @return the ID of the current car; -1 if there is no current car
 */
int Station::showCurrentCar() {
	return held;
}

/**
 * Removes the current car from the station.
 * Does nothing if there is no current car.
 *
 * @return true if the current car successfully left; false otherwise
 */
bool Station::removeFromStation() {
	if (held == -1)
		return false;
	held = -1;
	return true;
}

/**
 * Adds the current car to the stack.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the stack is already full.
 *
 * @return true if the car is successfully added to the stack; false otherwise
 */
bool Station::addToStack() {
	if (held == -1)
		return false;
	if (stack.size() >= 5)
		return false;
	stack.insertHead(held);
	held = -1;
	return true;
}

/**
 * Removes the first car in the stack and makes it the current car.
 * Does nothing if there is already a current car or if the stack already empty.
 *
 * @return true if the car is successfully removed from the stack; false otherwise
 */
bool Station::removeFromStack() {
	if (held != -1)
		return false;
	if (stack.size() == 0)
		return false;
	held = stack.removeHead();
	return true;
}

/**
 * Returns the ID of the first car in the stack.
 *
 * @return the ID of the first car in the stack; -1 if the stack is empty
 */
int Station::showTopOfStack() {
	if (stack.size() < 1)
		return -1;
	return stack.getHead();
}

/**
 * Returns the number of cars in the stack.
 *
 * @return the number of cars in the stack
 */
int Station::showSizeOfStack() {
	return stack.size();
}

/**
 * Adds the current car to the queue.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the queue is already full.
 *
 * @return true if the car is successfully added to the queue; false otherwise
 */
bool Station::addToQueue() {
	if (held == -1)
		return false;
	if (queue.size() >= 5)
		return false;
	queue.insertHead(held);
	held = -1;
	return true;
}

/**
 * Removes the first car in the queue and makes it the current car.
 * Does nothing if there is already a current car or if the queue already empty.
 *
 * @return true if the car is successfully removed from the queue; false otherwise
 */
bool Station::removeFromQueue() {
	if (held != -1)
		return false;
	if (queue.size() == 0)
		return false;
	held = queue.removeTail();
	return true;
}

/**
 * Returns the ID of the first car in the queue.
 *
 * @return the ID of the first car in the queue; -1 if the queue is empty
 */
int Station::showTopOfQueue() {
	if (queue.size() < 1)
		return -1;
	return queue.getTail();
}

/**
 * Returns the number of cars in the queue.
 *
 * @return the number of cars in the queue
 */
int Station::showSizeOfQueue() {
	return queue.size();
}

/**
 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the deque is already full.
 *
 * @return true if the car is successfully added to the deque; false otherwise
 */
bool Station::addToDequeLeft() {
	if (held == -1)
		return false;
	if (deque.size() >= 5)
		return false;
	deque.insertHead(held);
	held = -1;
	return true;
}

/**
 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the deque is already full.
 *
 * @return true if the car is successfully added to the deque; false otherwise
 */
bool Station::addToDequeRight() {
	if (held == -1)
		return false;
	if (deque.size() >= 5)
		return false;
	deque.insertTail(held);
	held = -1;
	return true;
}

/**
 * Removes the leftmost car in the deque and makes it the current car.
 * Does nothing if there is already a current car or if the deque already empty.
 *
 * @return true if the car is successfully removed from the deque; false otherwise
 */
bool Station::removeFromDequeLeft() {
	if (held != -1)
		return false;
	if (deque.size() == 0)
		return false;
	held = deque.removeHead();
	return true;
}

/**
 * Removes the rightmost car in the deque and makes it the current car.
 * Does nothing if there is already a current car or if the deque already empty.
 *
 * @return true if the car is successfully removed from the deque; false otherwise
 */
bool Station::removeFromDequeRight() {
	if (held != -1)
		return false;
	if (deque.size() == 0)
		return false;
	held = deque.removeTail();
	return true;
}

/**
 * Returns the ID of the leftmost car in the deque.
 *
 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
 */
int Station::showTopOfDequeLeft() {
	if (deque.size() < 1)
		return -1;
	return deque.getHead();
}

/**
 * Returns the ID of the rightmost car in the deque.
 *
 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
 */
int Station::showTopOfDequeRight() {
	if (deque.size() < 1)
		return -1;
	return deque.getTail();
}

/**
 * Returns the number of cars in the deque.
 *
 * @return the number of cars in the deque
 */
int Station::showSizeOfDeque() {
	return deque.size();
}

//Input-Restricted Deque----------------------------------------------
/**
 * Adds the current car to the IrDeque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the IrDeque is already full.
 *
 * @return true if the car is successfully added to the IrDeque; false otherwise
 */
bool Station::addToIRDequeLeft() {
	if (held == -1)
		return false;
	if (Ir.size() >= 5)
		return false;
	Ir.insertHead(held);
	held = -1;
	return true;
}

/*
 * Removes the leftmost car in the IrDeque and makes it the current car.
 * Does nothing if there is already a current car or if the IrDeque already empty.
 *
 * @return true if the car is successfully removed from the IrDeque; false otherwise
 */
bool Station::removeFromIRDequeLeft() {
	if (held != -1)
		return false;
	if (Ir.size() == 0)
		return false;
	held = Ir.removeHead();
	return true;
}

/**
 * Removes the rightmost car in the IrDeque and makes it the current car.
 * Does nothing if there is already a current car or if the IrDeque already empty.
 *
 * @return true if the car is successfully removed from the IrDeque; false otherwise
 */
bool Station::removeFromIRDequeRight() {
	if (held != -1)
		return false;
	if (Ir.size() == 0)
		return false;
	held = Ir.removeTail();
	return true;
}

/**
 * Returns the ID of the leftmost car in the IrDeque.
 *
 * @return the ID of the leftmost car in the IrDeque; -1 if the IrDeque is empty
 */
int Station::showTopOfIRDequeLeft() {
	if (Ir.size() < 1)
		return -1;
	return Ir.getHead();
}

/**
 * Returns the ID of the rightmost car in the IrDeque.
 *
 * @return the ID of the rightmost car in the IrDeque; -1 if the IrDeque is empty
 */
int Station::showTopOfIRDequeRight() {
	if (Ir.size() < 1)
		return -1;
	return Ir.getTail();
}

/**
 * Returns the number of cars in the IrDeque.
 *
 * @return the number of cars in the IrDeque
 */
int Station::showSizeOfIRDeque() {
	return Ir.size();
}

//Output-Restricted Deque---------------------------------------------
/**
 * Adds the current car to the OrDeque on the left side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the OrDeque is already full.
 *
 * @return true if the car is successfully added to the OrDeque; false otherwise
 */
bool Station::addToORDequeLeft() {
	if (held == -1)
		return false;
	if (Or.size() >= 5)
		return false;
	Or.insertHead(held);
	held = -1;
	return true;
}

/**
 * Adds the current car to the OrDeque on the right side.  After this operation, there should be no current car.
 * Does nothing if there is no current car or if the OrDeque is already full.
 *
 * @return true if the car is successfully added to the OrDeque; false otherwise
 */
bool Station::addToORDequeRight() {
	if (held == -1)
		return false;
	if (Or.size() >= 5)
		return false;
	Or.insertTail(held);
	held = -1;
	return true;
}

/**
 * Removes the leftmost car in the OrDeque and makes it the current car.
 * Does nothing if there is already a current car or if the OrDeque already empty.
 *
 * @return true if the car is successfully removed from the OrDeque; false otherwise
 */
bool Station::removeFromORDequeLeft() {
	if (held != -1)
		return false;
	if (Or.size() == 0)
		return false;
	held = Or.removeHead();
	return true;
}

/**
 * Returns the ID of the leftmost car in the OrDeque.
 *
 * @return the ID of the leftmost car in the OrDeque; -1 if the OrDeque is empty
 */
int Station::showTopOfORDequeLeft() {
	if (Or.size() < 1)
		return -1;
	return Or.getHead();
}

/**
 * Returns the number of cars in the OrDeque.
 *
 * @return the number of cars in the OrDeque
 */
int Station::showSizeOfORDeque() {
	return Or.size();
}
