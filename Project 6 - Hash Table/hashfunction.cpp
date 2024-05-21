/*
Project Description - Building an hash Table as an index to a database store which stores the records of student details in it.
This project is mainly of 2 parts, database which is a vector of unsorted student records and an index of the student IDs created
in the close Hash table of Size 20. The student records is accessed using this index or student UID.
The hash table will be used to map these student UIDs to the indexes of the vector of student records which is a faster way to retrieve
student details.
There are pre-implemented files slot.h, record.h, hashfunction.h, hashfunction.cpp, shuffle.h, shuffle.cpp
The codes written for implementation of this project are in hashTable.h, hashTable.cpp, dataBase.h, dataBase.cpp, project6.cpp
*/#pragma once

// A bitwise hash function written by Justin Sobel
// Code adapted from http://www.partow.net/programming/hashfunctions/#RSHashFunction

unsigned int jsHash(const int key)
{
   const char* kptr = (char *)&key;
   unsigned int length = sizeof(int);
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++kptr, ++i)
   {
      hash ^= ((hash << 5) + (*kptr) + (hash >> 2));
   }

   return hash;
}