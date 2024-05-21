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
using namespace std; // standard library for namespaces cout,cin by default

Database newDatabase; //creating a newDatabase object
void insertingRecordToDB(); //function to insert a record into Database
void deletingRecordFromDb(); //function to delete a record from Database
void searchingRecordinDB(); //function to search a record in Database
void printingTheDatabase(); //function that prints the contents in the database

int collisions1; //declaring an integer variable for collisions

int main() //main function
{

    string inputAction; //declaring a string that stores the input passed on display
    string arrayInputs[5] = {"I", "D", "S", "P", "Q"}; //declaring an string array which contains only acceptable inputs
    bool inputPassed = true; //decalring an boolean variable for if conditions below

    while (inputPassed) //executes as longs as the input passed is correct and until want to quit
    {
        cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, (P)rint the database, or (Q)uit?" << endl;
        cout << "Enter action: ";
        cin >> inputAction; //takes the input from display that user passes

        bool passedInputValid = false; //setting the variable to false so if input action is correct it is changed to true
        for (int i = 0; i < 5; i++) //iterates thru 5 acceptable inputs
        {
            if (arrayInputs[i] == inputAction) //executes if the passed input action is valid
            {
                passedInputValid = true;
                break;
            }
        }

        //if passed input action is not valid
        if (passedInputValid == false)
        {
            cout << "Action passed doesnot exist. Enter actions: I or D or P or S or Q: " << endl;
            continue;
        }


        //switch for 5 conditions of input
        switch (inputAction[0])
        {
        case 'I': //when the passed input is I, executes the insert function
            insertingRecordToDB();
            break;
        case 'D': //when the passed input is D, executes the delete function
            deletingRecordFromDb();
            break;
        case 'S': //when the passed input is S, executes the search function
            searchingRecordinDB();
            break;
        case 'P': //when the passed input is P, executes the print function
            printingTheDatabase();
            break;
        case 'Q':
            cout << "Exiting. \n\n";
            inputPassed = false; //when the user wants to quit, it changes the boolean variable to false so while wont execute
            break;
        }
    }

    return 0;
}

//Function - printingTheDatabase - prints the database contents.
//shows the alpha loading factor and also no records if the alpha is zero or number of records is zero
//return - no explicit return defined as inertion is happening
void printingTheDatabase()
{
    cout << endl;
    cout << "Hash table loading factor is : " << newDatabase.alpha() << endl;
    if (newDatabase.alpha() == 0 && newDatabase.getTotalRecords() == 0) //if no records are present
    {
        cout << "No records inserted or present as alpha is 0. Check the print after records are present. \n";
    }
    cout << endl;
    if (newDatabase.alpha() != 0 && newDatabase.getTotalRecords() != 0) //if atleast one record is present
    {
        newDatabase.printingHashTableOverload(); //calls the function to print hashTable contents
        cout << newDatabase << endl; //overloaded operator that prints the database contents of the object
    }
}

//Function - insertingRecordToDB - inserts the records into database
//return - no explicit return defined
void insertingRecordToDB()
{
    int UID; //declaring the variable that send the student UID

    string lastName, firstName, year; //defining the string data types that takes the student record details
    if (newDatabase.getTotalRecords() < MAXHASH) //excutes the insert condition only if records are less than 21
    {
        cout << "Inserting a new record. \n";
        cout << "Last name:  ";
        cin >> lastName;

        cout << "First name: ";
        cin >> firstName;

        cout << "UID : ";
        cin >> UID;

        cout << "Year: ";
        cin >> year;

        //creating a new record object
        Record newRecord(firstName, lastName, UID, year);

        //excutes if true records is inserted
        if (newDatabase.insert(newRecord, collisions1))
        {
            cout << "Record Inserted "
                 << "(" << collisions1 << " collisions during insert)." << endl;
            cout << endl;
        }
        else //if not inserted
        {
            cout << "Unable to insert record ,UID already exists." << endl;
            cout << endl;
        }
    }
    else
    {
        cout << "Unable to insert record, As records limit / Hash table is full ." << endl;
        cout << endl;
    }
}

//function - deletingRecordFromDb - delete the record from the database
//return - no explicit defined
void deletingRecordFromDb()
{

    int key; //integer student variable value that needs to be deleted

    cout << "Enter UID to Delete : ";
    cin >> key;

    //executes if the student UID record is removed from database object
    if (newDatabase.remove(key))
    {
        cout << "Deleted the record with UID:" << key << ", successfully!! " << endl;
        cout << endl;
    }
    else    //if unable to delete
    {
        cout << "Record with UID - " << key << " not found." << endl;
        cout << endl;
    }
}

//Function - searchingRecordinDB - to search the records in the database
//return - no explicit return defined
void searchingRecordinDB()
{
    int key; //declaring the integer variable that has to be searched

    Record getExistingRecord; //creating an object

    cout << "Enter UID to search for : ";
    cin >> key;

    //executes if the key is found
    if (newDatabase.find(key, getExistingRecord, collisions1))
    {
        cout << "Searching....record found (" << collisions1 << " collisions during search)." << endl;
        cout << "----------------------\n";
        cout << "Last name: " << getExistingRecord.getLastName() << endl;
        cout << "First name: " << getExistingRecord.getFirstName() << endl;
        cout << "UID: " << getExistingRecord.getUID() << endl;
        cout << "Year: " << getExistingRecord.getYear() << endl;
        cout << "----------------------\n";
        cout << endl;
    }
    else
    {
        cout << "Searching....Record not found \n";
        cout << endl;
    }
}