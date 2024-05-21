/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/

#include <iostream> // Header file library for input & output streams. Brings all C++ pre-processor code here.
#include "Database.h" //header file that contains the code declaration for the database
#include "hashTable.h" //Header file that contains the code for creating hashTable
using namespace std; // standard library for namespaces cout,cin by default

//Function - insert - That inserts the records into the hashTable array and into the vector of student recordstore
//Returns - boolean value, true - if records is inserted or false
//Parameteres - other record - vector object where the records is inserted. collisions(integer) - number of collisions occured
bool Database ::insert(const Record &otherRecord, int &collisions)
{
    int key = otherRecord.getUID(); //stores the object UID

    //checks if it finds the records in hashTable or already there are 20 records and return false saying insert is not done
    if (indexTable.find(key, index, collisions) || indexTable.totalRecords() == MAXHASH)
    {
        return false;
    }
    //if record is not found, it inserts the student records details.
    else{
    index = insertToVector(otherRecord);
    bool isInserted = indexTable.insert(key, index, collisions);
    return isInserted; //returns true if inserted.
    }
}

//Function - insertToVector - insert the records into the database of unsorted vector
//return (integer) - return the index of the vector where the record is stored
//Parameter - other records - passed the object as refernece
int Database ::insertToVector(const Record &otherRecord)
{

    recordStore.push_back(otherRecord); //inserts the record in the last place
    return dbVectorIndex++; //returns the incremented psotion
}

//Function - remove - removes the record from the database & hashTable.
//return - boolean - return true if removed or false if failed
//Parameter - key(integer) - the student UID which has to be removed
bool Database ::remove(int key)
{

    if (indexTable.find(key, index, collisions)) //executes if the find function return true
    {

        indexTable.remove(key); //removes
        updateDataBase(index); //calls the function to update the database
        return true;
    }
    return false;
}

//Function - updateDataBase - updates the vector and re hashes the hashTable
//return(void) - no explicit defined
//Parameter - position - place where the record has to be removed
void Database ::updateDataBase(size_t position)
{

    recordStore[position] = recordStore[recordStore.size() - 1];
    recordStore.pop_back(); //calls the pop back function and removes the last element in the vector
    dbVectorIndex--; //decrement
    indexTable.reHashingHashTable(position, recordStore[position].getUID());
}
//Function - find - searches fot the record
//return - boolean - true if found or false if not
//Parameters - uid(integer) - student UID, otherRecord - object passed kept constant, collision(integer)
bool Database ::find(int uid, Record &otherRecord, int &collisions)
{
    //finds the element in the hashTable
    if (indexTable.find(uid, index, collisions))
    {
        otherRecord = recordStore[index];
        return true;
    }
    return false;
}

//Function - alpha - returns the loading factor of the database present in the hashTable
//return float data type
//keeps the object values constant so modifications happens
float Database ::alpha()
{
    return indexTable.alpha();
}

//Function - overload operator - that is used to print the database contents
//return - returns the content to be displayed in the output stream
//Parameters - os(ouput stream) -  acts like a cout reference, otherDatabase(object) - passed object and kept constant
ostream &operator<<(ostream &os, const Database &otherDatabase)
{
    os << "Database Contents: " << endl;

    //iterates the size of hashTable
    for (size_t i = 0; i < MAXHASH; i++)
    {   
        //executes only if the hashTable array slot is not empty
        if (otherDatabase.indexTable.hashTableArray[i].isNormal())
        {
            os << "HashTable Slot: " << i << ", recordStore slot ";
            os << otherDatabase.indexTable.hashTableArray[i].getIndex();
            os << " --- " << otherDatabase.recordStore[otherDatabase.indexTable.hashTableArray[i].getIndex()];
            os << endl;
        }
    }
    return os;
}

//Function - printing hashTable - prints the content of hashTable
//return - no explicit return defined
//Parameter - access the oject for printing the data but kept it constant
void Database::printingHashTableOverload() const
{
    cout << indexTable; //object is overloaded to the cout
}

//Function - returns(integer) - totalRecords - getter that returns the number of records loaded in the hashTable
int Database::getTotalRecords()
{
    return indexTable.totalRecords();
}