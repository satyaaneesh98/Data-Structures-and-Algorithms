/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/

#ifndef DATABASE_H //Defining conditional only if code is present, this will be allowed to pass when not present
#define DATABASE_H //brings this code into the pre processor when needed as it causing redefinition issues of hashTable
#pragma once //A directive for pre process to compile code only once
#include <string> //library that is used for defining/codes string
#include <iostream> // Header file library for input & output streams. Brings all C++ pre-processor code here.
#include <vector> //Library that allows vector acts like a container to store values dynamically during runtime
#include "hashTable.h" //Header file that contains the code declarations for the hashTable creation
#include "Record.h" //Header file that contains the code declarations for creating the student records.
#include "Slot.h" //Header file library that contains the code declarations for the hashTable array slot
 
class Database //declaring class database for storing the student records
{
private: //setting the attributes to private access specifier
    hashTable indexTable; //creating an indexTable object of class hashTable
    vector<Record> recordStore; //creating an vector of recordstore to store the student details

public: //setting attributes to public access specifier
    Record listOfRecords; //creating an object for class record
    int index; //index represents the position(integer)
    int collisions; //collisions representing the number of collisions happened during the probing
    int dbVectorIndex = 0; //integer that represents the indice of record in the vector

    bool insert(const Record &otherRecord, int &collisions); //insert the record into hashTable & vector
    int insertToVector(const Record &otherRecord); //inserts the record into the vector of database
    bool remove(int); //remove the student UID and its record from database
    void updateDataBase(size_t); //updates the database once the records is removed
    bool find(int uid, Record &otherRecord, int &collisions); //function used to find the record in the vector which executes when return true from hashTable
    float alpha(); //returns the alhpa loading factor of hashTable
    void printingHashTableOverload() const; //function used to print the contents of the hashTable
    int getTotalRecords(); //function to return the number of records present
    friend ostream &operator<<(ostream &os, const Database &otherDatabase); //overload operator that prints the database contents which is indeed the student records
};

#endif //ends the code in the pre processor and brings it out