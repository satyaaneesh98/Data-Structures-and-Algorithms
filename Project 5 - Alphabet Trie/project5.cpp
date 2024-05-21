/*
Project Description: Building an uncompressed alphabet trie using trie data structure. Initially to test the code, I have inserted and
tested few words. Later, written the code in main.cpp to autocomplete the words insertion given in the text document which is english
dictionary. The poject consists of 4 files in total, Trie.h is header which contains function declarations and Trie.cpp contains all
the function definitions and main.cpp has the autocomplete program and main program to run the project. And the last file is the words
text document which contain 62887 words in it that will be inserted in a separate Trie using autocomplete logic in main.cpp*/
#include "Trie.h"   //Header file that contains all the function declared
#include <iostream> // Header file library for input & output streams. Brings all C++ pre-processor code here.
#include <string>   //Header for string data types
#include <vector>   //Library that allows vector acts like a container to store values dynamically during runtime
#include <fstream>  //to get capabtility for reading, writing from file.
#include <iomanip>  //Header file library to manipulate output as we are using setw in the tree printing method.

using namespace std; // standard library for namespaces cout,cin by default

// Main function
int main()
{
    // Initially creating a trie with few words and testing the methods

    cout << "First trie:" << endl;
    cout << "-----------" << endl;
    Trie trie1; // creating an object Trie1 of class Trie
    cout << "Inserting 1st time and all should return true: " << endl;

    // Inserts the below words into the trie
    cout << trie1.insert("a") << endl;
    cout << trie1.insert("an") << endl;
    cout << trie1.insert("ant") << endl;
    cout << trie1.insert("aneesh") << endl;
    cout << trie1.insert("add") << endl;
    cout << trie1.insert("adding") << endl;
    cout << trie1.insert("be") << endl;
    cout << trie1.insert("because") << endl;
    cout << trie1.insert("become") << endl;
    cout << trie1.insert("beyond") << endl;

    // Now testing the methods
    cout << "Number of nodes created in Trie: " << trie1.getSize() << endl;               // gives number of nodes in trie
    cout << "Number of words in Trie: " << trie1.count() << endl;                         // gives number of words in trie
    cout << "Searching ant: " << trie1.find("ant") << endl;                               // return true if found
    cout << "Searching aneesh: " << trie1.find("aneesh") << endl;                         // return true if found
    cout << "Searching add: " << trie1.find("add") << endl;                               // return true if found
    cout << "Searching because: " << trie1.find("because") << endl;                       // return true if found
    cout << "Counting all words starting with a: " << trie1.completeCount("a") << endl;   // returns integer value of how many words found with prefix
    cout << "Counting all words starting with an: " << trie1.completeCount("an") << endl; // returns integer value of how many words found with prefix
    cout << "Counting all words starting with b: " << trie1.completeCount("b") << endl;   // returns integer value of how many words found with prefix

    // Prints all the words present in trie with the passed prefix
    cout << "Show all words that start with prefix a: " << trie1.completeCount("a") << endl;
    vector<string> vec = trie1.complete("a");
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix b: " << trie1.completeCount("b") << endl;
    vector<string> vec1 = trie1.complete("b");
    for (vector<string>::iterator it = vec1.begin(); it != vec1.end(); ++it)
    {
        cout << *it << endl;
    }

    // Testing the same words insert again to see return status
    cout << "Inserting words 2nd time and should return false: " << endl;
    cout << trie1.insert("a") << endl;
    cout << trie1.insert("an") << endl;
    cout << trie1.insert("ant") << endl;
    cout << trie1.insert("aneesh") << endl;
    cout << trie1.insert("add") << endl;
    cout << trie1.insert("adding") << endl;
    cout << trie1.insert("be") << endl;
    cout << trie1.insert("because") << endl;
    cout << trie1.insert("beyond") << endl;

    cout << endl;

    Trie trie2(trie1); // creating a trie2 object of class trie
    cout << "Second Trie using copy constructor: " << endl;
    cout << "------------------------------------" << endl;
    cout << "Inserting 1st time and all should return false: " << endl;

    // Inserts the below words into the trie and should not insert because its a copy constructor and all will be present
    cout << trie2.insert("a") << endl;
    cout << trie2.insert("an") << endl;
    cout << trie2.insert("ant") << endl;
    cout << trie2.insert("aneesh") << endl;
    cout << trie2.insert("add") << endl;
    cout << trie2.insert("adding") << endl;
    cout << trie2.insert("be") << endl;
    cout << trie2.insert("because") << endl;
    cout << trie2.insert("become") << endl;
    cout << trie2.insert("beyond") << endl;

    // Now testing the methods
    cout << "Number of nodes created in Trie: " << trie2.getSize() << endl;                  // gives number of nodes in trie
    cout << "Number of words in Trie: " << trie2.count() << endl;                            // gives number of words in trie
    cout << "Searching ant: " << trie2.find("ant") << endl;                                  // return true if found
    cout << "Searching aneesh: " << trie2.find("aneesh") << endl;                            // return true if found
    cout << "Searching add: " << trie2.find("add") << endl;                                  // return true if found
    cout << "Searching because: " << trie2.find("because") << endl;                          // return true if found
    cout << "Counting all words starting with a: " << trie2.completeCount("a") << endl;      // returns integer value of how many words found with prefix
    cout << "Counting all words starting with an: " << trie2.completeCount("an") << endl;    // returns integer value of how many words found with prefix
    cout << "Counting all words starting with b: " << trie2.completeCount("b") << endl;      // returns integer value of how many words found with prefix
    cout << "Show all words that start with prefix a: " << trie2.completeCount("a") << endl; // returns integer value of how many words found with prefix

    // Prints all the words present in trie with the passed prefix
    vector<string> vec2 = trie2.complete("a");
    for (vector<string>::iterator it = vec2.begin(); it != vec2.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix b: " << trie2.completeCount("b") << endl;
    vector<string> vec3 = trie2.complete("b");
    for (vector<string>::iterator it = vec3.begin(); it != vec3.end(); ++it)
    {
        cout << *it << endl;
    }

    // Testing the same words insert again to see return status
    cout << "Inserting words 2nd time and should return false: " << endl;
    cout << trie2.insert("a") << endl;
    cout << trie2.insert("an") << endl;
    cout << trie2.insert("ant") << endl;
    cout << trie2.insert("aneesh") << endl;
    cout << trie2.insert("add") << endl;
    cout << trie2.insert("adding") << endl;
    cout << trie2.insert("be") << endl;
    cout << trie2.insert("because") << endl;
    cout << trie2.insert("beyond") << endl;

    cout << endl;

    Trie assignmentTrie; // created an object called assignment Trie of class Trie
    cout << "creating an assignment trie initially and using assign operator to update the new values: " << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Inserting 1st time and all should return true: " << endl;

    // Inserts the below words into the trie insert works as this is new trie
    cout << assignmentTrie.insert("race") << endl;
    cout << assignmentTrie.insert("radio") << endl;
    cout << assignmentTrie.insert("redbull") << endl;
    cout << assignmentTrie.insert("ferrari") << endl;
    cout << assignmentTrie.insert("fast") << endl;
    cout << assignmentTrie.insert("feature") << endl;

    // Now testing the methods
    cout << "Number of nodes created in Trie: " << assignmentTrie.getSize() << endl;                  // gives number of nodes in trie
    cout << "Number of words in Trie: " << assignmentTrie.count() << endl;                            // gives number of words in trie
    cout << "Searching stock: " << assignmentTrie.find("race") << endl;                               // return true if found
    cout << "Searching radio: " << assignmentTrie.find("radio") << endl;                              // return true if found
    cout << "Searching ferrari: " << assignmentTrie.find("ferrari") << endl;                          // return true if found
    cout << "Counting all words starting with r: " << assignmentTrie.completeCount("r") << endl;      // returns integer value of how many words found with prefix
    cout << "Counting all words starting with f: " << assignmentTrie.completeCount("f") << endl;      // returns integer value of how many words found with prefix
    cout << "Show all words that start with prefix r: " << assignmentTrie.completeCount("r") << endl; // returns integer value of how many words found with prefix

    // Prints all the words present in trie with the passed prefix
    vector<string> vec4 = assignmentTrie.complete("r");
    for (vector<string>::iterator it = vec4.begin(); it != vec4.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix f: " << assignmentTrie.completeCount("f") << endl;
    vector<string> vec5 = assignmentTrie.complete("f");
    for (vector<string>::iterator it = vec5.begin(); it != vec5.end(); ++it)
    {
        cout << *it << endl;
    }

    // Testing the same words insert again to see return status
    cout << "Inserting words 2nd time and should return false: " << endl;
    cout << assignmentTrie.insert("race") << endl;
    cout << assignmentTrie.insert("radio") << endl;
    cout << assignmentTrie.insert("redbull") << endl;
    cout << assignmentTrie.insert("ferrari") << endl;
    cout << assignmentTrie.insert("fast") << endl;
    cout << assignmentTrie.insert("feature") << endl;

    cout << "Now Assignment Operator" << endl;
    cout << "-----------------------" << endl;
    assignmentTrie = trie2; // Assignment operator that shld remove current trie and insert with trie2 values
    cout << "Show all words that start with prefix r: " << assignmentTrie.completeCount("r") << endl;

    // Prints all the words present in trie with the passed prefix
    // Since initial assignment trie is deleted now, will not find any words with 'r' and 'f'.
    // the 3rd print vector shows the words from trie2 that starts with 'a' prefix
    vector<string> vec9 = assignmentTrie.complete("r");
    for (vector<string>::iterator it = vec9.begin(); it != vec9.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix f: " << assignmentTrie.completeCount("f") << endl;
    vector<string> vec6 = assignmentTrie.complete("f");
    for (vector<string>::iterator it = vec6.begin(); it != vec6.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix a: " << trie2.completeCount("a") << endl;
    vector<string> vec7 = trie2.complete("a");
    for (vector<string>::iterator it = vec7.begin(); it != vec7.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Show all words that start with prefix b: " << trie2.completeCount("b") << endl;
    vector<string> vec8 = trie2.complete("b");
    for (vector<string>::iterator it = vec8.begin(); it != vec8.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl;

    // Autocomplete program to take words from text document and build a trie
    cout << "AutoComplete WordsList: AlphabetTrie:" << endl;
    cout << "-------------------------------------" << endl;

    Trie autoCompleteTrie;                        // creating an object of class Trie for autocomplete
    string wordsFromFile;                         // creating a string that stores words from text document
    ifstream readingFile("wordlist_windows.txt"); // opens and read data from file
    while (getline(readingFile, wordsFromFile))   // stores each line data into the string. runs until end of end of line
    {
        autoCompleteTrie.insert(wordsFromFile); // performs insert at each iteration to the trie
    }
    readingFile.close(); // closing the file opened

    // cross checking how many words created in trie from txt document
    cout << "Total Number of words created in the autoCompleteTrie: " << autoCompleteTrie.count() << endl;

    // Checks if the words queired is present in the autoCompleted Trie or not
    cout << "Check the word: ";
    string checkingWord;
    getline(cin, checkingWord);
    cout << "The word is present or not in Trie: " << autoCompleteTrie.find(checkingWord) << endl;

    bool run = true; // declared bool variable to stop the while iteration when users dont want to continue further
    while (run)      // Iterates until passed value run is false
    {
        string takingPrefixInput; // creating string variable
        cout << "Please enter a word prefix (or press enter to exit): ";
        getline(cin, takingPrefixInput); // take the input from user and stores it in string

        // boolean used to perform operations
        // If string is not empty, it will gives the count and asks for showing words present
        // If no input passed, it will be empty(false) and exits the operation
        bool empty = takingPrefixInput.empty();
        if (empty == false) // if string is not empty
        {
            // stores the integer value which is returned from the completeCount method
            int prefixWordsFound = autoCompleteTrie.completeCount(takingPrefixInput);
            cout << "\n"
                 << "There are " << prefixWordsFound << " completions for the prefix "
                 << "'" << takingPrefixInput << "'. ";

            if (prefixWordsFound == 0) // If there are no words present in the trie
            {
                cout << "No words found with the passed prefix. \n"
                     << endl;
            }
            else // If words are present in trie below code is performed that shows list of words
            {
                cout << "Show Completions? ";

                string takingInputForPrintingList;        // String to store user input
                getline(cin, takingInputForPrintingList); // inputs user value to string
                // creating an array of different case sensitive "yes"
                // using this as passed input is not yes, it exits and comes back to enter prefix again
                string array[3] = {"YES", "yes", "Yes"};
                for (int i = 0; i < 3; i++) // iterates and checks if user input matches
                {
                    if (takingInputForPrintingList == array[i])
                    {
                        cout << endl;
                        cout << "Completions: " << endl;
                        cout << "------------" << endl;
                        // Prints the list of words that are found with passed prefix.
                        vector<string> completeVector = autoCompleteTrie.complete(takingPrefixInput);
                        for (vector<string>::iterator it = completeVector.begin(); it != completeVector.end(); it++)
                        {
                            cout << *it << endl;
                        }
                        cout << endl;
                    }
                }
            }
        }
        else // if the user passed no input at prefix query, the bool is set to false and while loop ends and exits
        {
            run = false;
            cout << endl;
        }
    }
    return 0;
}