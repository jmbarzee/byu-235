/*
 * School.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: jacobmb
 */

#include <set>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "StudentInterface.h"
#include "Student.h"
#include "School.h"
#include "GPAInterface.h"

using namespace std;

/*
 * getMap()
 *
 * Returns the map storing the student information.
 * The key of the map should be the student ID.
 */
map<unsigned long long int, StudentInterface*> School::getMap() {
	return this->studentMap;
}

/*
 * getSet()
 *
 * Returns the set storing the student information.
 */
set<StudentInterface*, Comparator> School::getSet() {
	return this->studentSet;
}

/*
 * importStudents()
 *
 * Read in and parse through the given files. Each part of an entry in a
 * file is given on a separate line in the file. Student ID is first, name is
 * second, address is third, and phone is last. There are no blank lines between
 * students. The following is an example file:
 *
 *	 5291738600
 * 	 Dick B. Smith
 * 	 879 Maple Road, Centralia, Colorado 24222
 * 	 312-000-1000
 * 	 9251738707
 *	 Harry C. Anderson
 *	 635 Main Drive, Midville, California 48444
 * 	 660-050-2200
 *
 * If a valid file is given, the new Students should be added to the existing
 * map and set.
 *
 * If an invalid file name is given or if there is a missing entry for a student,
 * return false. Duplicate student ID numbers and duplicate students will not be
 * tested for. There will never be a student that exists in the map and set. If
 * the function returns false, then no changes should have been made to the
 * existing map or set.
 *
 * The key of the map should be the student ID.
 *
 * Returns false if an invalid filename is given or if there is a missing entry for a
 * student, otherwise true.
 */
bool School::importStudents(string mapFileName, string setFileName) {
	map<unsigned long long int, StudentInterface*> tempMap;
	set<StudentInterface*, Comparator> tempSet;
	fstream mapFile(mapFileName.c_str());
	if (!mapFile.is_open())
		return false;
	fstream setFile(setFileName.c_str());
	if (!setFile.is_open())
		return false;
	try {
		while (!mapFile.eof()) {
			//get the ID
			string idString;
			getline(mapFile, idString);
			if (mapFile.fail()) {
				throw 1;
			}
			stringstream ss(idString);
			unsigned long long int id;
			ss >> id;
			if (ss.fail() || ss.bad()) {
				throw 1;
			}

			//get the name
			string name;
			getline(mapFile, name);
			if (mapFile.fail()) {
				throw 1;
			}

			//get the address
			string address;
			getline(mapFile, address);
			if (mapFile.fail()) {
				throw 1;
			}

			//get the phone
			string phone;
			getline(mapFile, phone);
			if (mapFile.fail()) {
				throw 1;
			}
			tempMap.emplace(id, new Student(id, name, address, phone)); //this is right, just ignore the error.
			mapFile.peek();

		}
		while (!setFile.eof()) {
			//get the ID
			string idString;
			getline(setFile, idString);
			if (setFile.fail()) {
				throw 1;
			}
			stringstream ss(idString);
			unsigned long long int id;
			ss >> id;
			if (ss.fail() || ss.bad()) {
				throw 1;
			}

			//get the name
			string name;
			getline(setFile, name);
			if (setFile.fail()) {
				throw 1;
			}

			//get the address
			string address;
			getline(setFile, address);
			if (setFile.fail()) {
				throw 1;
			}

			//get the phone
			string phone;
			getline(setFile, phone);
			if (setFile.fail()) {
				throw 1;
			}
			tempSet.insert(new Student(id, name, address, phone)); //this is right, just ignore the error.
			setFile.peek();
		}
	} catch (int e) {
		mapFile.close();
		std::map<unsigned long long int, StudentInterface*>::iterator mapIt;
		for (mapIt = tempMap.begin(); mapIt != tempMap.end(); mapIt++)
			delete mapIt->second;
		tempMap.clear();
		std::set<StudentInterface*, Comparator>::iterator setIt;
		for (setIt = tempSet.begin(); setIt != tempSet.end(); setIt++) {
			delete *setIt;
		}
		tempSet.clear();
		return false;
	}
	clear();
	studentMap.swap(tempMap);
	studentSet.swap(tempSet);
	setFile.close();
	mapFile.close();

	return true;
}

/*
 * importGrades()
 *
 * Read in and parse through the given file. Each part of an entry in the file
 * is given on a separate line in the file. Student ID is first, course is
 * second, and grade is last. There are no blank lines between entries. The
 * following is an example file:
 *
 * 	5291738860
 * 	CHEM134
 * 	A
 * 	9251734870
 * 	BOT180
 * 	B
 * 	9251733870
 * 	PE273
 * 	D+
 * 	5291738760
 * 	HIS431
 *  	A-
 *
 * Compute the GPA by finding the average of all the grades with a matching student ID
 * in the Grade file. The GPA is calculated by taking a Student's total sum GPA and
 * dividing by the number of classes taken. If the given student ID has no matching
 * grades in the Grade file, the GPA is 0.00. It is not necessary to store the course
 * names so long as the total number of courses taken is counted.
 *
 * You may assume that the given student ID exists in the map or set.
 *
 * Use the following point values for each grade.
 *
 *			  A = 4.0  A- = 3.7
 *	B+ = 3.4  B = 3.0  B- = 2.7
 *	C+ = 2.4  C = 2.0  C- = 1.7
 *	D+ = 1.4  D = 1.0  D- = 0.7
 *			  E = 0.0
 *
 * Returns false if an invalid filename is given, otherwise true.
 */
bool School::importGrades(string fileName) {
	fstream inFile(fileName.c_str());
	while (!inFile.eof()) {

		//get the ID
		string idString;
		getline(inFile, idString);
		if (inFile.fail()) {
			inFile.close();
			return false;
		}
		stringstream ss(idString);
		unsigned long long int id;
		ss >> id;
		if (ss.fail()) {
			inFile.close();
			return false;
		}

		//get  the course
		string course;
		getline(inFile, course);
		if (inFile.fail()) {
			inFile.close();
			return false;
		}

		//get the grade
		string grade;
		getline(inFile, grade);
		if (inFile.fail()) {
			inFile.close();
			return false;
		}
		char letter = grade[0];
		char sign = grade[1];
		double gpa = 0;
		switch (letter) {
		case 'A':
			gpa = 4;
			break;
		case 'B':
			gpa = 3;
			break;
		case 'C':
			gpa = 2;
			break;
		case 'D':
			gpa = 1;
			break;
		case 'E':
			gpa = 0;
			break;
		default:
			gpa = 0;
		}
		switch (sign) {
		case '-':
			gpa -= 0.3;
			break;
		case '+':
			gpa += 0.4;
			break;
		}
		std::map<unsigned long long int, StudentInterface*>::iterator mapIt =
				studentMap.find(id);
		if (mapIt != studentMap.end()) {
			mapIt->second->addGPA(gpa);
		}
		std::set<StudentInterface*, Comparator>::iterator setIt;
		for (setIt = studentSet.begin(); setIt != studentSet.end(); setIt++) {
			if ((*setIt)->getID() == id) {
				(*setIt)->addGPA(gpa);
			}
		}
		inFile.peek();
	}
	inFile.close();
	return true;
}
/*
 * querySet()
 *
 * Read in and parse through the given file. The 'Query' file contains a list of
 * student ID numbers. Each entry in the Query file is a student ID given on a
 * line by itself. You are to compute and report the GPA for each of the students
 * listed in the Query file. The following is an example Query file:
 *
 * 	5291738860
 * 	9251733870
 *
 * For each student ID given in the Query file, use the student information stored in
 * your set to compute the GPA for the student and create an output string which
 * contains the student ID, GPA, and name. If the given student ID does not match any
 * student, do not give any output for that student ID. Each line of the output string
 * contains student ID, GPA, and name as shown:
 *
 * 	5291738860 2.85 Dick B. Smith
 *	9251733870 3.00 Harry C. Anderson
 *
 * Return a string representation of the given query. If an invalid file name is given,
 * then return an empty string. The precision of the GPA will be rounded to two decimal places.
 * There will be a trailing new line.
 */
string School::querySet(string fileName) {
	fstream inFile(fileName.c_str());
	stringstream ss;
	while (!inFile.eof()) {

		//get the ID
		string idString;
		getline(inFile, idString);
		if (inFile.fail()) {
			inFile.close();
			return "";
		}
		stringstream sstemp(idString);
		unsigned long long int id;
		sstemp >> id;
		if (sstemp.fail()) {
			inFile.close();
			return "";
		}
		std::set<StudentInterface*, Comparator>::iterator setIt;
		for (setIt = studentSet.begin(); setIt != studentSet.end(); setIt++) {
			if ((*setIt)->getID() == id) {
				ss << (*setIt)->getID() << ' ' << (*setIt)->getGPA() << ' '
						<< (*setIt)->getName() << endl;
				break;
			}
		}
		inFile.peek();
	}
	inFile.close();
	return ss.str();
}

/*
 * queryMap()
 *
 * Read in and parse through the given file. The 'Query' file contains a list of
 * student ID numbers. Each entry in the Query file is a student ID given on a
 * line by itself. You are to compute and report the GPA for each of the students
 * listed in the Query file. The following is an example Query file:
 *
 * 	5291738860
 * 	9251733870
 *
 * For each student ID given in the Query file, use the student information stored in
 * your map to compute the GPA for the student and create an output string which
 * contains the student ID, GPA, and name. If the given student ID does not match any
 * student, do not give any output for that student ID. Each line of the output string
 * contains student ID, GPA, and name as shown:
 *
 * 	5291738860 2.85 Dick B. Smith
 *	9251733870 3.00 Harry C. Anderson
 *
 * Return a string representation of the given query. if an ivalid file name is given,
 * then return an empty string. The precision of the GPA will be rounded to two decimal places.
 * There will be a trailing new line.
 */
string School::queryMap(string fileName) {
	fstream inFile(fileName.c_str());
	stringstream ss;
	while (!inFile.eof()) {

		//get the ID
		string idString;
		getline(inFile, idString);
		if (inFile.fail()) {
			inFile.close();
			return "";
		}
		stringstream sstemp(idString);
		unsigned long long int id;
		sstemp >> id;
		if (sstemp.fail()) {
			inFile.close();
			return "";
		}
		ss.clear();
		std::map<unsigned long long int, StudentInterface*>::iterator mapIt =
				studentMap.find(id);
		if (mapIt != studentMap.end()) {
			ss << mapIt->second->getID() << ' ' << mapIt->second->getGPA()
					<< ' ' << mapIt->second->getName() << endl;
		}
		inFile.peek();
	}
	inFile.close();
	return ss.str();
}

/*
 * Clears the students from the map and set.
 */
void School::clear() {
	std::set<StudentInterface*, Comparator>::iterator setIt;
	for (setIt = studentSet.begin(); setIt != studentSet.end(); setIt++) {
		delete *setIt;
	}
	studentSet.clear();
	std::map<unsigned long long int, StudentInterface*>::iterator mapIt;
	for (mapIt = studentMap.begin(); mapIt != studentMap.end(); mapIt++)
		delete mapIt->second;
	studentMap.clear();
}
