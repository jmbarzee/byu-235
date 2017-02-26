/*
 * Student.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: jacobmb
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Student.h"

Student::Student(unsigned long long int id, string name, string address,
		string phone) {
	this->id = id;
	this->name = name;
	this->address = address;
	this->phone = phone;
}
unsigned long long int Student::getID() {
	return id;
}
string Student::getName() {
	return name;
}
string Student::getGPA() {
	stringstream ss;
	ss << fixed << setprecision(2) << getGPAD();
	return ss.str();
}
double Student::getGPAD() {
	double gpa = 0;
	for(int i = 0; i < this->gpa.size(); i++) {
		gpa += this->gpa[i];
	}
	if (this->gpa.size() == 0)
		return 0;
	return gpa/this->gpa.size();
}
void Student::addGPA(double classGrade) {
	//cout << "addGPA(" << classGrade << ')' << endl;
	gpa.push_back(classGrade);
}
/*
 * toString()
 *
 * The student object will be put into string representation. Student info will be
 * ordered ID, name, address, phone number, and GPA. Each piece of information will
 * be on its own line. GPA will not have a newline following it and the precision
 * of the GPA will be rounded to two decimal places. For example,
 *
 * 123456789
 * Ben Thompson
 * 17 Russell St, Provo, UT 84606
 * 555-555-5555
 * 3.12
 *
 * Returns a string representation of the student object There is no trailing new line.
 */
string Student::toString() {
	stringstream ss;
	ss << id << endl;
	ss << name << endl;
	ss << address << endl;
	ss << phone << endl;
	ss << fixed << setprecision(2) << getGPAD();
	return ss.str();
}
