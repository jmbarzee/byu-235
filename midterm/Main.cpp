/*
 * Main.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: jacobmb
 */

#include <string>
#include <iostream>
#include <fstream>
#include "CircularDLL.h"
#include "NodeDL.h"
#include <stdlib.h>
#include <sstream>

using namespace std;
// used only for testing... see giant note below
string intToString(int in) {
	stringstream ss;
	ss << in;
	string out = ss.str();
	return out;
}
int main() {
	string command;
	CircularDLL list;
	while (command != "Quit") {
		// menu... need I say more?... really?
		// all areas without notes are considered self descriptive due to "couts" that are often near by.
		cout << "please enter a command:" << endl;
		cout << "    Import" << endl;
		cout << "    Display" << endl;
		cout << "    Prepend" << endl;
		cout << "    Append" << endl;
		cout << "    Remove" << endl;
		cout << "    Shuffle" << endl;
		cout << "    Calculate" << endl;
		cout << "    Dispatch" << endl;
		cout << "    Quit" << endl;
		cin >> command;
		cout << endl;
		if (command == "Quit") {
			break;
		} else if (command == "Import") {
			string filename;
			cout << "Please enter the file name:";
			cin >> filename;
			std::ifstream ifs;
			ifs.open(filename.c_str());
			if (!ifs.is_open()) {
				cout << "The file did not open..." << endl;
			} else {
				cout << "Filling list..." << endl;
				list.clear();
				string name;
				while (ifs >> name) {
					list.insertTail(name);
				}
			}
		} else if (command == "Display") {
			if (list.size() < 1) {
				cout << "The list is empty" << endl;
			} else {
				cout << "The list contains:" << endl;
				for (int i = 0; i < list.size(); i++)
					cout << "  " << i << " - " << list.atFromHead(i) << endl;
			}
		} else if (command == "Prepend") {
			cout << "Please enter a name to add to the front of the list"
					<< endl;
			string name;
			cin >> name;
			if (!list.insertHead(name))
				cout << "That name is already in the list" << endl;
		} else if (command == "Append") {
			cout << "Please enter a name to add to the back of the list"
					<< endl;
			string name;
			cin >> name;
			if (!list.insertTail(name))
				cout << "That name is already in the list" << endl;
		} else if (command == "Remove") {
			cout << "Please enter an index to be removed" << endl;
			int index;
			cin >> index;
			//prevents etarnal loop when a non-integer is entered
			while (cin.fail()) {
				cout << "not an integer, please input an integer." << endl;
				cin.clear();
				cin.ignore(100,'\n');
				cin >> index;
			}
			if (list.atFromHead(index) == "invalid") {
				cout << "That index is out of bounds" << endl;
			} else {
				cout << "removed " << list.atFromHead(index) << endl;
				list.removeAt(index);
			}
		} else if (command == "Shuffle") {
			//shuffles by randomly selecting a position moving it to the front of the list
			for (int i = 0; i < list.size() * 3; i++) {
				int pos = rand() % list.size();
				string name = list.atFromHead(pos);
				list.removeAt(pos);
				list.insertHead(name);
			}
			cout << "Shuffled!" << endl;
		} else if (command == "Calculate") {
			int num = 0;
			int size = 0;
			//prevents a bad size selection
			 do {
				cout << "Please enter the number in Josephus' band:";
				cin >> size;
				//prevents etarnal loop when a non-integer is entered
				while (cin.fail()) {
					cout << "not an integer, please input an integer." << endl;
					cin.clear();
					cin.ignore(100,'\n');
					cin >> size;
				}
				if (size < 1)
					cout
							<< "Number is not in the allowed, bounds: 1 <= number <= people"
							<< endl;
			} while (size < 1);
			// prevents a bad number selection
			do {
				cout << "Enter THE NUMBER OF DEATH" << endl;
				cin >> num;
				//prevents eternal loop when a non-integer is entered
				while (cin.fail()) {
					cout << "not an integer, please input an integer." << endl;
					cin.clear();
					cin.ignore(100,'\n');
					cin >> num;
				}
				if (num < 1 || num > size)
					cout
							<< "Number is not in the allowed, bounds: 1 <= number <= people"
							<< endl;
			} while (num < 1 || num > size);
			CircularDLL listtemp;
			stringstream ss;
			//all numbers are added to list and then removed using josephus approach
			for (int i = 0; i <= size - 1; i++) {
				ss.clear();
				ss << i;
				string temp;
				ss >> temp;
				listtemp.insertTail(temp);
			}
			num--;
			Node<string>* crnt = listtemp.getNode(0);
			Node<string>* next = crnt->getNext();
			// josephus approach uses direct access to the nodes of the list and then politley asks the list to kill the guy its looking at
			while (listtemp.size() > 1) {
				for (int i = 0; i < num; i++) {
					crnt = crnt->getNext();
				}
				next = crnt->getNext();
				cout << "Killed: " << listtemp.remove(crnt) << endl;
				crnt = next;
			}
			// remaning NAME is the safe number.
			cout << "The safe position is: " << listtemp.atFromHead(0) << endl;
		} else if (command == "Dispatch") {
			int num = 0;
			// prevents a bad number selection
			 do {
				cout << "Enter THE NUMBER OF DEATH";
				cin >> num;
				//prevents etarnal loop when a non-integer is entered
				while (cin.fail()) {
					cout << "not an integer, please input an integer." << endl;
					cin.clear();
					cin.ignore(100,'\n');
					cin >> num;
				}
				if (num < 1 || num > list.size())
					cout
							<< "Number is not in the allowed, bounds: 1 <= number <= people"
							<< endl;
			} while (num < 1 || num > list.size());
			int count = 0;
			num--;
			// josephus approach uses direct access to the nodes of the list and then politley asks the list to kill the guy its looking at
			Node<string>* crnt = list.getNode(0);
			Node<string>* next = crnt->getNext();
			while (list.size() > 1) {
				for (int i = 0; i < num; i++) {
					crnt = crnt->getNext();
				}
				next = crnt->getNext();
				cout << "Killed: " << list.remove(crnt) << endl;
				crnt = next;
			}
			cout << "  " << list.atFromHead(0) << " only remains" << endl;
			list.clear();
		/*} else if (command == "test") {
			CircularDLL temp;
			cout << "***** INSERTING (head) a,b,c,d,e *****" << endl;
			cout << "insertHead(\"a\")" << endl;
			if (temp.insertHead("a"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"b\")" << endl;
			if (temp.insertHead("b"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"c\")" << endl;
			if (temp.insertHead("c"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"d\")" << endl;
			if (temp.insertHead("d"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"e\")" << endl;
			if (temp.insertHead("e"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			cout << "***** REMOVING (tail) a,b,c,d,e *****" << endl;
			cout << "removeTail()" << endl;
			if (temp.removeTail())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeTail()" << endl;
			if (temp.removeTail())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeTail()" << endl;
			if (temp.removeTail())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeTail()" << endl;
			if (temp.removeTail())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeTail()" << endl;
			if (temp.removeTail())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			cout << "***** INSERTING (tail) a,b,c,d,e *****" << endl;
			cout << "insertTail(\"a\")" << endl;
			if (temp.insertTail("a"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"b\")" << endl;
			if (temp.insertTail("b"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"c\")" << endl;
			if (temp.insertTail("c"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"d\")" << endl;
			if (temp.insertTail("d"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"e\")" << endl;
			if (temp.insertTail("e"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from tail): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromTail(i);
			}
			cout << endl;
			cout << "***** REMOVING (head) a,b,c,d,e *****" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from tail): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromTail(i);
			}
			cout << endl;
			cout << "***** INSERTING (head) a,b,c,d,e *****" << endl;
			cout << "insertHead(\"a\")" << endl;
			if (temp.insertHead("a"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"b\")" << endl;
			if (temp.insertHead("b"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"c\")" << endl;
			if (temp.insertHead("c"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"d\")" << endl;
			if (temp.insertHead("d"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertHead(\"e\")" << endl;
			if (temp.insertHead("e"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from tail): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromTail(i);
			}
			cout << endl;
			cout << "***** REMOVING (head) a,b,c,d,e *****" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeHead()" << endl;
			if (temp.removeHead())
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			cout << "***** INSERTING (tail) a,b,c,d,e *****" << endl;
			cout << "insertTail(\"a\")" << endl;
			if (temp.insertTail("a"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"b\")" << endl;
			if (temp.insertTail("b"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"c\")" << endl;
			if (temp.insertTail("c"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"d\")" << endl;
			if (temp.insertTail("d"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertTail(\"e\")" << endl;
			if (temp.insertTail("e"))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			cout << "***** INSERTING (from head) a,b,c,d,e *****" << endl;
			cout << "insertAt(\"f\",0)" << endl;
			if (temp.insertAt("f", 0))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"g\",1)" << endl;
			if (temp.insertAt("g", 1))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"h\",2)" << endl;
			if (temp.insertAt("h", 2))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"i\",3)" << endl;
			if (temp.insertAt("i", 3))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"j\",4)" << endl;
			if (temp.insertAt("j", 4))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			cout << "***** REMOVE (from head) a,b,c,d,e *****" << endl;
			cout << "removeAt(0)" << endl;
			if (temp.removeAt(0))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeAt(1)" << endl;
			if (temp.removeAt(1))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeAt(2)" << endl;
			if (temp.removeAt(2))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeAt(3)" << endl;
			if (temp.removeAt(3))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "removeAt(4)" << endl;
			if (temp.removeAt(4))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << "    " << i << " : " << temp.atFromHead(i);
			}
			cout << endl;
			temp.insertHead("hold");
			cout << "***** INSERT (from head) 0 - 99 *****" << endl;
			for (int i = 0; i < 100; i++) {
				temp.insertAt(intToString(i), i);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** REMOVE (from head) 99 - 0 *****" << endl;
			for (int i = 99; i > -1; i--) {
				temp.removeAt(i);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** INSERT (from head) 0 - 99 *****" << endl;
			for (int i = 0; i < 100; i++) {
				temp.insertAt(intToString(i), i);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** INSERTING (from head) a,b,c,d,e *****" << endl;
			cout << "insertAt(\"f\",0)" << endl;
			if (temp.insertAt("f", 0))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"g\",1)" << endl;
			if (temp.insertAt("g", 1))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"h\",2)" << endl;
			if (temp.insertAt("h", 2))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"i\",3)" << endl;
			if (temp.insertAt("i", 3))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "insertAt(\"j\",4)" << endl;
			if (temp.insertAt("j", 4))
				cout << "    success" << endl;
			else
				cout << "    Failure" << endl;
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** REMOVE (from head) 99 - 0 *****" << endl;
			for (int i = 99; i > -1; i--) {
				temp.removeAt(i);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** INSERT (head) 0 - 99 *****" << endl;
			for (int i = 0; i < 100; i++) {
				temp.insertHead(intToString(i));
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** REMOVE (from head) 99 - 0 *****" << endl;
			for (int i = 99; i > -1; i--) {
				temp.removeAt(i);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** INSERT (head) 0 - 99 *****" << endl;
			for (int i = 0; i < 100; i++) {
				temp.insertHead(intToString(i));
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** REMOVE (from head) rand *****" << endl;
			for (int i = 0; i < 49; i++) {
				temp.removeAt(rand() % 50);
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "***** INSERT (head) 0 - 99 *****" << endl;
			for (int i = 0; i < 100; i++) {
				temp.insertHead(intToString(i));
			}
			cout << "list holds (from head): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromHead(i) << ' ';
			}
			cout << endl;
			cout << "list holds (from tail): " << endl;
			for (int i = 0; i < temp.size(); i++) {
				cout << temp.atFromTail(i) << ' ';
			}
			cout << endl;
			cout << "size is " << temp.size() << endl;
			temp.clear();
			cout << "size is " << temp.size() << endl;*/
		} else {
			cout << "Sorry, you're command wasn't recognized" << endl;
		}
		cout << endl;
	}
}

