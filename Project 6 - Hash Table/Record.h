/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/

#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


// Each record holds a student's first and
// last names, their UID (an integer), and
// their year (a string)

class Record
{
private:
	string firstName;
	string lastName;
	int uid;
	string year;
	int recordsCount;

public:

	// The default constructor produces a "test" student
	Record()
	{
		firstName = "Test";
		lastName = "Student";
		uid = 0;
		year = "Freshman";
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Record(string newFirstName, string newLastName, int newUID, string newYear)
		: firstName(newFirstName), lastName(newLastName), uid(newUID), year(newYear)
	{
	
		recordsCount ++;
	}


	// Get the student's name
	string getName() const {
		string result = lastName + ", " + firstName;
		return result;
	}

	// Get the student's id
	int getUID() const {
		return uid;
	}
	
	// Get the student's year
	string getYear() const {
		return year;
	}
	
	// Change the student's year
	void setYear(string newYear) {
		year = newYear;
	}

	// Overload the << operator for printing a student
	friend ostream& operator<<(ostream& os, const Record& me) {
		os << me.getName() << " (U" << setw(8) << setfill('0') << me.getUID() << "): " << me.getYear();
		return os;
	}

	// No destructor is needed as Records don't use any dynamically
	// allocated memory
	~Record()
	{
	}

	int getrecordsTotal(){
		return recordsCount;
	}

	string getFirstName() const{
		return firstName;
	}

	string getLastName() const{
		return lastName;
	}
};