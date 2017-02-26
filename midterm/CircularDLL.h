#ifndef CIRCULARDLL_H_
#define CIRCULARDLL_H_

#include <string>
#include "CircularDLLInterface.h"
#include "NodeDL.h"

using namespace std;
/**
 * The CircularDLLInterface defines basic operations performed on a circular double-linked list.
 * Your implementation of this interface must be a circular double-linked list.
 *
 * For this list, the word "invalid" is used as the return value of for atFromHead(int) and atFromTail(int)
 * for invalid indices. You may check and reject the word "invalid" if you would like to make sure it is
 * never a value in your list, but it is not necessary.  We will not attempt to insert "invalid".
 */
class CircularDLL: public CircularDLLInterface {
private:
	//check to prevent duplicates
	Node<string>* inList(string name);
	Node<string>* head;
	Node<string>* tail;
	int Size;
public:
	// used for josephus appproach
	string remove(Node<string>* crnt);
	// used for josephus appproach
	Node<string>* getNode(int index);
	void printPointers();
	CircularDLL();
	~CircularDLL() {
		clear();
	}

	/**
	 * Adds the given name to the beginning of the list so that
	 * atFromHead(0) == name and atFromTail(size() - 1) == name.
	 * After the operation, the size should have increased by 1.
	 *
	 * returns true if successful.
	 * returns false if the same name already exists.
	 */
	bool insertHead(string name);

	/**
	 * Adds the given name to the end of the list so that
	 * atFromHead(size() - 1) == name and atFromTail(0) == name.
	 * After the operation, the size should have increased by 1.
	 *
	 * returns true if successful, false otherwise.
	 * returns false if the same name already exists.
	 */
	bool insertTail(string name);

	/**
	 * Inserts the given name into the given index of the list so that
	 * atFromHead(index) == name.  All values should shift down one index
	 * to accommodate the new value.  After the operation, the size should
	 * have increased by 1.
	 *
	 * returns true if insert was successful.
	 * returns false if the same name already exists.
	 * returns false if the given index was out of range.
	 */
	bool insertAt(string name, int index);

	/**
	 * Removes the value at the beginning of the list.  After this operation
	 * size() should return a value 1 less than before and all values should
	 * shift 1 index forward. If only one item remains, the head and tail
	 * pointers should be returned a NULL state.
	 *
	 * returns true if the removal occurred successfully.
	 * returns false if attempting to remove from an empty list.
	 */
	bool removeHead();

	/**
	 * Removes the value at the end of the list.  After this operation
	 * size() should return a value 1 less than before and all index values
	 * should remain unchanged. If only one item remains, the head and tail
	 * pointers should be returned a NULL state.
	 *
	 * returns true if the removal occurred successfully.
	 * returns false if attempting to remove from an empty list.
	 */
	bool removeTail();

	/**
	 * Removes the value at the given index measured from the beginning.
	 * index 0 is the beginning of the list.  After this removal the list size
	 * should be 1 less and all following values should shift forward by 1.
	 * If only one item remains and index 0 is given, the head and tail
	 * pointers should be returned a NULL state.
	 *
	 * returns true if the removal occurred successfully.
	 * returns false attempting to remove from an empty list.
	 * returns false if the index was out of the range.
	 */
	bool removeAt(int index);

	/**
	 * Removes all nodes from the list and resets the state of the data structure
	 * to empty.  size() should return 0 after this operation.
	 */
	void clear();

	/**
	 * As a reminder, size() and the at functions are used to read the contents
	 * of your list.  Without these we will not be able to determine the functionaliy
	 * of you list.
	 *
	 * returns the number of items in the list.
	 */
	int size();

	/**
	 * Measured from the head, where the beginning is indexed as 0,
	 * and the end is indexed as size() - 1.
	 *
	 * returns the string located at the given index.
	 * returns the string "invalid" if an invalid index is given. See top comment.
	 */
	string atFromHead(int index);

	/**
	 * Measured from the tail, where the end is indexed as 0,
	 * and the beginning is indexed as size() - 1.
	 *
	 * returns the string located at the given index.
	 * returns the string "invalid" if an invalid index is given. See top comment.
	 */
	string atFromTail(int index);
};

#endif /* CIRCULARDLL_H_ */
