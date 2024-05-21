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

// There are three types of slots in a closed hash:
// Normal slots, empty (since start) slots, and emptyAfterRemovals (i.e. tombstones)
enum SlotType
{
	normalSlot,
	emptySinceStart,
	emptyAfterRemoval
};

// Each slot holds an integer key and an integer vector index.
// The integer index will be used as to find the record in the
// record store.

class Slot
{
private:
	int key;
	int index;
	SlotType type;

public:
	// The default constructor produces an empty slot.
	Slot()
	{
		key = -1;
		index = -1;
		type = emptySinceStart;
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Slot(int newKey, int newIndex)
		: key(newKey), index(newIndex)
	{
		type = normalSlot;
	}

	// Place a key and an index into a slot, convert the type to normalSlot
	void load(int newKey, int newIndex)
	{
		key = newKey;
		index = newIndex;
		type = normalSlot;
	}

	// Convert a slot to a emptyAfterRemoval
	void kill()
	{
		type = emptyAfterRemoval;
	}

	// Get the integer key of a slot
	int getKey() const
	{
		return key;
	}

	// Get the index of a slot
	int getIndex() const
	{
		return index;
	}

	// Set the index of a slot to a new value
	void setIndex(int newIndex)
	{
		index = newIndex;
	}

	// Check if a slot is emptySinceStart
	bool isEmptySinceStart() const
	{
		return (type == emptySinceStart);
	}

	// Check if a slot is a normal slot
	bool isNormal() const
	{
		return (type == normalSlot);
	}

	// Check if a slot is a emptyAfterRemoval
	bool isEmptyAfterRemoval() const
	{
		return (type == emptyAfterRemoval);
	}

	// Check if a slot is empty
	bool isEmpty() const
	{
		return ((type == emptySinceStart) || (type == emptyAfterRemoval));
	}

	// Overload the << operator for printing slots
	friend ostream &operator<<(ostream &os, const Slot &me)
	{
		if (me.isEmptyAfterRemoval())
			os << "<<emptyAfterRemoval>>";
		else if (me.isEmptySinceStart())
			os << "<<Empty>>";
		else
			os << "Key = " << me.key << ", Index = " << me.index;
		return os;
	}

	// No destructor is needed as Slots don't use any dynamically
	// allocated memory
	~Slot()
	{
	}
};
