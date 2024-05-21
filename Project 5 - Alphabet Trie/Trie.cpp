/*
Project Description: Building an uncompressed alphabet trie using trie data structure. Initially to test the code, I have inserted and
tested few words. Later, written the code in main.cpp to autocomplete the words insertion given in the text document which is english
dictionary. The poject consists of 4 files in total, Trie.h is header which contains function declarations and Trie.cpp contains all
the function definitions and main.cpp has the autocomplete program and main program to run the project. And the last file is the words
text document which contain 62887 words in it that will be inserted in a separate Trie using autocomplete logic in main.cpp*/
#include "Trie.h"  //Header that contains all the function declarations for this alphabetTrie
#include <string>  //Header for string data types
#include <vector>  //Library that allows vector acts like a container to store values dynamically during runtime
#include <iomanip> //Header file library to manipulate output as we are using setw in the tree printing method.

// Function - Trie - Default constructor that creates the objects of class Trie
// Return - no return as this only creates the objects
// Initializes numberofNodes and total number of words to zero, as when object is created there is no data in it yet.
Trie::Trie() : numberOfNodes(0), totalNumberOfWords(0)
{
    root = new alphabetTrieNode(); // creating a blank or empty node in heap with all null pointers in it and assiging it to root of Trie in the object
}

// Function - AlphabetTrieNode - Creates the nodes each time the function
// It is an object of class alphabetTrieNode
// Creates an array of size 26 as aplhabets are 26 and initalizes all to null pointers
// return - no return is expected
// Member variables:
// Initializes the bool variable to false stating that the node is not the end of the word
// Words Counter - variable to keep track of how many words created in the aplhabetTrie
// array index - variable for iterating and creating an array of size 26 inside the node
Trie::alphabetTrieNode::alphabetTrieNode() : wordEnd(false)
{
    // For loop of 26 size as aplhabets are 26
    for (int arrayIndex = 0; arrayIndex < totalAlphabets; arrayIndex++)
    {
        arrayOfAlphabets[arrayIndex] = nullptr;
    }
    wordsCounter++;
}

// Function - Insert method that inserts the word in the trie letter by letter
// Parameter - takes the string word as input to the string method
// return - boolean value - true if word is inserted or false if word is already present
// Member variables:
// currentPtr - Points to the current located node
// wordlength(size_type) - stores the value of input word length
// wordIndex(integer) - stores the value of alphabet(for example a represents 0, b means 1)
bool Trie::insert(string inputWord)
{

    alphabetTrieNode *currentPtr = root;  // Creating the pointer and pointing it to the root of the trie
    size_t wordLength = inputWord.size(); // size type variable
    size_t i;                             // size type variable for doing iteration
    int wordIndex;
    for (i = 0; i < wordLength; i++) // Iterates the size of the word to be inserted
    {
        // Getting the value of alphabet being passed, 'a' means 97 and inserting a means 97 - 97 = 0 and a will be inserted in array[0]
        wordIndex = inputWord[i] - 'a';

        if (currentPtr->arrayOfAlphabets[wordIndex] == nullptr) // if current pointing array index value is null, insert the next alphabet in word
        {

            return insert(root, inputWord); // Helper function inserting the word
        }

        currentPtr = currentPtr->arrayOfAlphabets[wordIndex]; // Moves the pointer from the previous position to current word index
    }

    // If the current pointing node has boolean value of true for word end and not nullpointer it returns false
    if (currentPtr->wordEnd == true && currentPtr != nullptr)
    {
        return false;
    }

    return false; // return false if the word is not inserted
}

// Method - insert function that traverses and input the word
// returns - true or false for word insertion
// Parameters - pointer reference - nodePtrLocation - points to the referncing location passed
// inputWord(string) - takes the input as passed from the parent insert function
// currentPtr - Points to the current located node
// wordlength1(size_type) - stores the value of input word length
// wordIndex1(integer) - stores the value of alphabet
bool Trie::insert(alphabetTrieNode *&nodePtrLocation, string inputWord)
{

    alphabetTrieNode *currentPtr = nodePtrLocation; // points to the location passed from the parent insert method

    size_t wordLength1 = inputWord.size();
    size_t j;
    int wordIndex1;
    for (j = 0; j < wordLength1; j++)
    {
        // Getting the value of alphabet being passed, 'a' means 97 and inserting a means 97 - 97 = 0 and a will be inserted in array[0]
        wordIndex1 = inputWord[j] - 'a';
        if (currentPtr->arrayOfAlphabets[wordIndex1] == nullptr)
        {
            // creates a new node when the current pointer pointing to an array index of nullpointer
            currentPtr->arrayOfAlphabets[wordIndex1] = new alphabetTrieNode();
            numberOfNodes++; // increments the node count whenever node is created
        }
        else // if current pointer is not pointing to an null index position
        {
            currentPtr->arrayOfAlphabets[wordIndex1]->wordsCounter++; // increases the word counter at this index
        }
        currentPtr = currentPtr->arrayOfAlphabets[wordIndex1]; // traverses the pointer to the next position
    }

    currentPtr->wordEnd = true; // updates the boolean value to true stating word is inserted and also its end of word
    totalNumberOfWords++;       // icrements the actual word count

    return true; // states the word is inserted successfully
}

// Method - count - returns the total words created in the alphabetTrie
// return - integer value
int Trie::count()
{
    // updates the count of words present in trie into the root node in totalWordsCounter. Using this for next methods copy constructor, assignment operator
    root->totalWordsCounter = totalNumberOfWords;
    return totalNumberOfWords; // returns the number of words present in trie
}

// Method - size - returns the total number of nodes created in the alphabetTrie
// returns - integer value
int Trie::getSize()
{
    // updates the count of nodes present in trie into the root node in totalNodesCounter. Using this for next methods copy constructor, assignment operator
    root->totalNodesCounter = numberOfNodes;
    return numberOfNodes; // returns the number of nodes present in trie
}

// Function - find - searches for the word present in the trie or not
// return(boolean)  - true or false, true if word is present or not
// parameter - inputWord(string) - the word that needs to be searched
// Member variables:
// currentPtr(pointer) - points to the current node array location the trie
// wordFound(boolean) - stores true or false and returns that on function call
bool Trie::find(string inputWord)
{
    alphabetTrieNode *currentPtr = root;  // points to the root of the alphabetTrie
    size_t wordLength = inputWord.size(); // variable that stores the size of the inputWord
    size_t i;
    int wordIndex;
    for (i = 0; i < wordLength; i++) // Iterates until the length of the word
    {
        // Getting the value of alphabet being passed, 'a' means 97 and inserting a means 97 - 97 = 0 and a will be inserted in array[0]
        wordIndex = inputWord[i] - 'a';                         //
        if (currentPtr->arrayOfAlphabets[wordIndex] == nullptr) // If the current pointing node array index is null, return false stating word is not found
        {
            return false;
        }
        currentPtr = currentPtr->arrayOfAlphabets[wordIndex]; // else move the pointer to the next node array index
    }
    bool wordFound = currentPtr->wordEnd; // stores the boolean value of the current node array index wordEnd value
    return wordFound;                     // gives status of word found or not
}

// Method - completeCount - Gives the number of words present in the Trie with the passed prefix
// returns - integer value
// Parameter - completeCount(string) - takes the string input from the user
int Trie::completeCount(string inputWordPrefix)
{
    alphabetTrieNode *currentPtr = root;        // points to the root of the alphabetTrie
    size_t wordLength = inputWordPrefix.size(); // variable that stores the size of the inputWord
    size_t i;                                   // size_type variable used for iterating the loop
    int wordIndex;
    for (i = 0; i < wordLength; i++) // Iterates until the length of the word
    {
        // Getting the value of alphabet being passed, 'a' means 97 and inserting a means 97 - 97 = 0 and a will be inserted in array[0]
        wordIndex = inputWordPrefix[i] - 'a';
        if (currentPtr->arrayOfAlphabets[wordIndex] == nullptr) // If the current pointing node array index is null, return false stating word is not found
        {
            return 0; // return 0 words found in the trie
        }
        currentPtr = currentPtr->arrayOfAlphabets[wordIndex]; // move the pointer to the next node array index
    }
    return currentPtr->wordsCounter; // returns the integervalue stored at the current node pointing array
}

// Method - complete - vector that stores and returns all the words stored during the function call
// Finds and stores the words that are present in the trie with the queried prefix
// Parameter - prefix(string) - passes the word to be queried to find how many words present in the Trie with this prefix
vector<string> Trie::complete(string prefix)
{
    alphabetTrieNode *currentPtr = root; // points the current pointer to the root

    size_t wordLength = prefix.size(); // variable that stores the size of the prefix string
    size_t i;                          // size_type variable used for iterating the loop
    int wordIndex;
    for (i = 0; i < wordLength; i++) // Iterates until the length of the word
    {
        // Getting the value of alphabet being passed, 'a' means 97 and inserting a means 97 - 97 = 0 and a will be inserted in array[0]
        wordIndex = prefix[i] - 'a';
        if (currentPtr->arrayOfAlphabets[wordIndex] == nullptr) // if current pointer pointing node array index is null return.
        {
            return {};
        }

        currentPtr = currentPtr->arrayOfAlphabets[wordIndex]; // moves to the next location
    }

    if (wordsList.empty()) // checks if the vector is empty or not
    {
        searchPrefixWords(currentPtr, wordsList, prefix); // helper function that traverses the trie and stores the variables
        return wordsList;                                 // returns the list of words
    }
    else
    { // if the vector is not empty, it will clear the vector and calls the helper function
        wordsList.clear();
        searchPrefixWords(currentPtr, wordsList, prefix);
        return wordsList;
    }
}
// Method - searchPrefixWords - function that traverses the trie and stores the words present in the trie
// return - no return explicitly but the function updates and stores the words and end and goes the function call code
// Parameters:
// curentPtr - Pointer to the passed location
// newWordList - pass by reference to the vector string
// prefixCurrentWord(string) - string being queried passed from the parent function
void Trie::searchPrefixWords(alphabetTrieNode *currentPtr, vector<string> &newWordsList, string prefixCurrentWord)
{
    if (currentPtr->wordEnd) // if current locating node array index states word is ended, the words is store to the vector
    {
        newWordsList.push_back(prefixCurrentWord);
    }

    // iterates 26 times
    for (int i = 0; i < totalAlphabets; i++)
    {
        if (currentPtr->arrayOfAlphabets[i] != nullptr) // if current poiniting node array index is not null pointer
        {
            string concatenateWord; // variable to store the word
            // char(97) - represents a
            // char(i + 97) - which means i is the value of the iteration value
            concatenateWord = prefixCurrentWord + (char)(i + 'a');                             // adds the previous word + current word to the string
            searchPrefixWords(currentPtr->arrayOfAlphabets[i], newWordsList, concatenateWord); // recursive call of the function
        }
    }
}

// Method - copy constructor - Creates a deep copy of alphabetTrie object, creates a new object and copies the referenced object
// Paramater - copyTriePtr - reference to the object being passed from which the trie has to be copied
// return - no explicit return defined
Trie::Trie(const Trie &copyTriePtr)
{
    // updates the total number of words from the referenced object trie root
    totalNumberOfWords = copyTriePtr.root->totalWordsCounter;
    // updates the total number of nodes from the referenced object trie root
    numberOfNodes = copyTriePtr.root->totalNodesCounter;
    copyConstuctor(root, copyTriePtr.root); // helper function that does the creation of nodes and copies the data from the referenced trie
}

// Method - copyConstructor - copies the data from the referenced object trie to the new trie
// Parameter - newTriePtr - referenece to the location being passed from the parent function. This is the new trie pointer initialized to root
// oldTriePtr - pointer to the referenced object, initialized to the root of the original trie
// return - no return is expected
void Trie::copyConstuctor(alphabetTrieNode *&newTriePtr, alphabetTrieNode *oldTriePtr)
{
    // If original trie root is not null pointer an new trie node is created and the new pointer is pointed to it initially.
    if (oldTriePtr != nullptr)
    {
        newTriePtr = new alphabetTrieNode();
    }
    // If number of nodes is -1
    if (numberOfNodes == -1)
    {
        totalNumberOfWords = oldTriePtr->totalWordsCounter; // update the total words count from original tree words counter variable which is from root
        numberOfNodes = oldTriePtr->totalNodesCounter;      // update the total nodes count from original tree nodes counter variable which is from root
    }
    newTriePtr->wordsCounter = oldTriePtr->wordsCounter; // updates the new trie words count of that node from the original trie node
    newTriePtr->wordEnd = oldTriePtr->wordEnd;           // updates the new trie nodes count of that node from the original trie node

    for (int i = 0; i < totalAlphabets; i++) // iterates thru size of 26
    {
        if (oldTriePtr->arrayOfAlphabets[i] != nullptr) // if old trie pointing pointer array index is not null
        {
            // create a new node at the current pointing index in the new trie
            newTriePtr->arrayOfAlphabets[i] = new alphabetTrieNode();
            // recursive calling of the method, updates the pointer position in each call from index to index
            copyConstuctor(newTriePtr->arrayOfAlphabets[i], oldTriePtr->arrayOfAlphabets[i]);
        }
    }
}

// Method - destructor - delete all the nodes created in the trie as they are in heap to avoid the memory leaks
// Initiates once the object has completed its functionality and exits
Trie::~Trie()
{
    // If the trie object root is not null and there are >0 nodes in the trie object
    // Execute the helper function to delete the nodes one by one
    if (root != nullptr && numberOfNodes != 0)
    {
        deleteAlphabetTrie(root); // doing the function call from root
    }
    // If the nodes in Trie object are zero, set the root to null pointer so there will be no way to access data in heap
    if (numberOfNodes == 0)
    {
        root = nullptr;
    }
}

// Method - deleteAlphabetTrie - Method that iterates throught the whole trie and deletes the node one by one and does recursive calling
// return - no return defined
// Parameter - currentPtr - pointer to the passed location from the destructor call and gets traversed/updated through out the trie
void Trie::deleteAlphabetTrie(alphabetTrieNode *currentPtr)
{
    if (currentPtr == nullptr) // If the current pointer pointing node array index is null pointer return
    {
        return;
    }
    if (currentPtr != nullptr) // if it is not null pointer
    {
        // Iterates through the node array index which is of 26 size
        for (int i = 0; i < totalAlphabets; i++)
        {
            // If the current pointer pointing node array index is not null
            if (currentPtr->arrayOfAlphabets[i] != nullptr)
            {
                deleteAlphabetTrie(currentPtr->arrayOfAlphabets[i]); // do recursive call by updating the pointer to the next array node index
                currentPtr->arrayOfAlphabets[i] = nullptr;           // update the position index to null pointer
            }
        }
        delete currentPtr; // delete current pointing node
        numberOfNodes--;   // decrement the node count as we delete the node
    }
}

// Method - operator= - Assignment operator - remove all the data from exisiting object and
// and gets replaced by the deep copy of the referenced object.
// Parameter - newTrie - takes the parameter as the referenced object that has to be deep copied and kept constant so it wont be modified
// return - no return is defined
Trie &Trie::operator=(const Trie &newTrie)
{

    totalNumberOfWords = this->root->totalWordsCounter; // updates the total number of words from the referenced object root
    numberOfNodes = this->root->totalNodesCounter;      // updates the total number of words from the referenced object root
    if (root != nullptr)                                // if the root is not null pointer
    {
        deleteAlphabetTrie(root); // calls the method to delete the alphabetTrie and passes the root as starting position
    }
    alphabetTrieNode *currentPtr = newTrie.root; // new pointer points to the new trie object root
    if (currentPtr != nullptr)                   // if current pointer is not pointing to null pointer
    {
        copyConstuctor(root, currentPtr); // calls the copy constructor to create the data in the object
    }
    return *this; // returns this object data
}