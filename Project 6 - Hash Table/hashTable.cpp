/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/

#include "hashfunction.h" //
#include <string>         //library that is used for defining/codes string
#include <vector>         //Library that allows vector acts like a container to store values dynamically during runtime
#include "Slot.h"         //Header file library that contains the code declarations for the hashTable array slot
#include "Database.h"     //header file that contains the code declaration for the database
#include "shuffle.h"      //header file that contains the code for shuffling array index values
#include "hashTable.h"    //Header file that contains the code for creating hashTable

using namespace std; // standard library for namespaces cout,cin by default

//Default constructor that executes when the class hashTable object is created\
//return no explicit defined as it is a default constructor
// integer - initilaizes to number of records to zero
// this initiates the shuffle array code and saves the random for positiong the probing
hashTable::hashTable() : numberOfRecords(0)
{
    shuffledArray = makeShuffledArray(); // calls the shuffle function and stores the values to the shuffled array
}

// Function - Insert - Inserts the records key/value pairs into the hashTable
// Calculates the collisions occured during the insertion into the hashTable
// return - boolean - true if inserted or false if not
// Parameters - key(inetger) - student UID, Index(integer) - saves the position, collisions(integer)
bool hashTable ::insert(int key, int index, int &collisions)
{
    size_t hashKey = jsHash(key) % MAXHASH; // hashKey value which is home value for inserting into position
    hashTableBucketsProbed = 0;             // probes until the size of hashTable
    shuffleArrayPosition = 0;               // shuffled index to access random value stored for hashTable position
    hashKey2 = hashKey;                     // second hashKey as it used to psuedo random probing
    if (numberOfRecords < MAXHASH)          // only if number of records
    {
        while (hashTableBucketsProbed < MAXHASH) // checks and does insertion until value is inserted as long as buckets probed are less than 20
        {
            // inserts only if slot is empty
            if (hashTableArray[hashKey].isEmptyAfterRemoval() || hashTableArray[hashKey].isEmptySinceStart())
            {

                hashTableArray[hashKey] = Slot(key, index); // updates the slot with key/value pairs
                numberOfRecords++;                          // increment
                return true;                                // return true if inserted
            }
            else if (hashTableArray[hashKey].getKey() != key && hashTableArray[hashKey].isNormal()) // if slot is not empty
            {
                collisions++; // increment collisions as record is not inserted
            }
            hashKey = (hashKey2 + shuffledArray[shuffleArrayPosition]) % MAXHASH; // psuedo random [probing]
            hashTableBucketsProbed++;                                             // increments the buckets probed
            shuffleArrayPosition++;                                               // increments the position to be accessed
        }
    }
    return false; // false if not inserted
}

// Function - find - function if the student data is present in the hashTable
// return - boolean - return true or false
// Parameters - key(integer) - student UID, Index(int) - position, collisions(inetger) - number of collisions during finding
bool hashTable ::find(int key, int &index, int &collisions)
{
    size_t hashKey = jsHash(key) % MAXHASH; // hashKey value which is home value for inserting into position
    hashTableBucketsProbed = 0;             // probes until the size of hashTable
    shuffleArrayPosition = 0;               // shuffled index to access random value stored for hashTable position
    hashKey2 = hashKey;                     // second hashKey as it used to psuedo random probing

    while (hashTableBucketsProbed < MAXHASH) // checks and does insertion until value is inserted as long as buckets probed are less than 20
    {
        // checks if hashTable position has the same key and type is normal slot
        if ((hashTableArray[hashKey].getKey() == key) && hashTableArray[hashKey].isNormal())
        {
            index = hashTableArray[hashKey].getIndex(); // retrieves the index in the hashTable
            return true;
        }
        // if the slot is empty from start and the hashkeys donot match
        else if (!hashKey == hashKey2 && !hashTableArray[hashKey].isEmptySinceStart())
        {
            collisions++; // increment collisions
        }

        if (hashTableArray[hashKey].isEmptySinceStart()) // if the slot is empty from starting return false
        {
            return false;
        }

        hashKey = (hashKey2 + shuffledArray[shuffleArrayPosition]) % MAXHASH; // pseudo random probing
        hashTableBucketsProbed++;                                             // increments the buckets probed
        shuffleArrayPosition++;                                               // increments the position to be accessed
    }
    return false;
}

//Function - remove - removes the student UID from the hashTable
//return - boolean - return true or false
//Parameter - key(integer) - student UID
bool hashTable ::remove(int key)
{
    size_t hashKey = jsHash(key) % MAXHASH; // hashKey value which is home value for inserting into position
    hashTableBucketsProbed = 0;             // probes until the size of hashTable
    shuffleArrayPosition = 0;               // shuffled index to access random value stored for hashTable position
    hashKey2 = hashKey;                     // second hashKey as it used to psuedo random probing

    while (hashTableBucketsProbed < MAXHASH) // checks and does insertion until value is inserted as long as buckets probed are less than 20
    {
        //if key is found & slot is normal
        if ((hashTableArray[hashKey].getKey() == key) && hashTableArray[hashKey].isNormal())
        {

            hashTableArray[hashKey].kill(); //calls the kill function to convert the slot to empty after normal
            numberOfRecords--; //decrements the record count
            return true; //return true if student UID data is successfully removed
        }
        //if the array slot is empty from start returns false
        if (hashTableArray[hashKey].isEmptySinceStart())
        {
            return false;
        }
        hashKey = (hashKey2 + shuffledArray[shuffleArrayPosition]) % MAXHASH; // pseudo random probing
        hashTableBucketsProbed++;                                             // increments the buckets probed
        shuffleArrayPosition++;                                               // increments the position to be accessed
    }
    return false; //false if not removed the record
}

//Function - reHashingHashTable - reupdates the hashTable after removal of a record from the database
//void - no return needed
//Parameters - index(integer), key(integer) - the student UID
void hashTable ::reHashingHashTable(int index, int key)
{

    int hashKey = jsHash(key) % MAXHASH; // hashKey value which is home value for inserting into position
    hashTableBucketsProbed = 0; // probes until the size of hashTable
    shuffleArrayPosition = 0; // shuffled index to access random value stored for hashTable position
    hashKey2 = hashKey; // second hashKey as it used to psuedo random probing

    //probes until 20 number of slots
    while (hashTableBucketsProbed < MAXHASH)
    {
        //executes when the slot is normal & matches the key
        if (hashTableArray[hashKey].isNormal() && (hashTableArray[hashKey].getKey() == key))
        {

            hashTableArray[hashKey] = Slot(key, index);
            return;
        }

        hashKey = (hashKey2 + shuffledArray[shuffleArrayPosition]) % MAXHASH; // pseudo random probing
        hashTableBucketsProbed++;                                             // increments the buckets probed
        shuffleArrayPosition++;                                               // increments the position to be accessed
    }
}

//Function - alpha - returns the loading factor of the hashTable
//return float data type
//keeps the object values constant so modifications happens
float hashTable ::alpha() const
{
    return float(numberOfRecords) / float(MAXHASH);
}

//Function - returns(integer) - totalRecords - number of records loaded in the hashTable
int hashTable ::totalRecords() const
{
    return numberOfRecords;
}

//Function - overload operator - to print the contents of the hashTable
//returns - the display of the contents
//Parameters - os - output stream, hashTable - the object being passed as reference, keeping the object constant so cant be modified
ostream &operator<<(ostream &os, const hashTable &othertable)
{
    os << "HashTable contents:" << endl;

    for (size_t i = 0; i < MAXHASH; i++) //iterates until the size of hashTable
    {
        if (othertable.hashTableArray[i].isNormal()) //check if the passed object hashTable slot is not empty
        {
            os << "HashTable Slot " << i << ": "
               << "Key = " << othertable.hashTableArray[i].getKey() << ", Index = " << othertable.hashTableArray[i].getIndex() << endl;
        }
    }
    return os; //returns the content to the output stream
}