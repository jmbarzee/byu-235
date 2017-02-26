/*
 * Student.h
 *
 *  Created on: Mar 27, 2015
 *      Author: jacobmb
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "StudentInterface.h"
#include <string>
#include <vector>

using namespace std;

class Student: public StudentInterface {
public:
	Student(unsigned long long int id, string name, string address,
			string phone);
	~Student(){};
	unsigned long long int getID();
	string getName();
	string getGPA();
	double getGPAD();
	void addGPA(double classGrade);
	string toString();
private:
	unsigned long long int id;
	string name;
	string address;
	string phone;
	vector <double> gpa;
};
#endif /* STUDENT_H_ */
