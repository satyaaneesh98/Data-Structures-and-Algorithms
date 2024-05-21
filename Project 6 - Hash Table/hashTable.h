/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/

#ifndef HASHTABLE_H //Defining conditional only if code is present, this will be allowed to pass when not present
#define HASHTABLE_H //brings this code into the pre processor when needed as it causing redefinition issues of hashTable
#include "hashfunction.h" //header file that consists the definition of the hashkey function.
#include <string> //library that is used for defining/codes string
#include <vector> //Library that allows vector acts like a container to store values dynamically during runtime
#include "Slot.h" //Header file that contains the declarations of the slot which contains the key value pairs and also type of slot.
#include "Database.h" //Header file that contains the declarations for creating the database of student records
#include "shuffle.h" //Header file that is used to create a shuffle of numbers which is then used for psuedo random probing

//Setting the max hash table size = 20. Data type constant unsigned integer(non negative integer)
const unsigned int MAXHASH = N;

using namespace std; // standard library for namespaces cout,cin by default

//Declaring class hashTable
class hashTable
{
//Defining access specifier to public attributes
public:
    int key; //Integer value that represents the student UID
    int index; //integer value that stores the index
    int collisions; //integer value represents the number of collisions happened during probing
    int hashKey2; //second hash key value integer used in psuedo random probing
    Slot hashTableArray[MAXHASH]; //creating an 20 slots of hashTableArray
    array<int, N - 1> shuffledArray; //declares an shuffledArray with 0 to 19 elements used to store the sequence of probing
    size_t numberOfRecords; //stores the number of records created, size_type data type
    int hashTableBucketsProbed;  //number of buckets/slots probed in the hashTable
    size_t shuffleArrayPosition; //represents the location to be pointed in the hashTable array, integer value

    hashTable(); //default constructor of hashTable class

    bool insert(int key, int index, int &collisions); //Insert records into hashTable with key value pairs & gives collisions happened for insert

    bool find(int key, int &index, int &collisions); //Find the records in hashTable and shows how many collisions happened when finding record

    bool remove(int key); //removes the UID from hashTable
 
    int totalRecords() const; //represents the number of records(integer) present in the hashTable

    float alpha() const; //gives the loading factor of the hashTable

    void reHashingHashTable(int, int); //updates the hashTable after removing any records from the database

    friend ::ostream &operator<<(ostream &os, const hashTable &otherTable); //overload operator to print the hashTable contents
};

#endif //closes and brings out the code which is started by ifndef. So it gets compiled only once.