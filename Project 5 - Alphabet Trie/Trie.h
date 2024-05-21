/*
Project Description: Building an uncompressed alphabet trie using trie data structure. Initially to test the code, I have inserted and
tested few words. Later, written the code in main.cpp to autocomplete the words insertion given in the text document which is english
dictionary. The poject consists of 4 files in total, Trie.h is header which contains function declarations and Trie.cpp contains all
the function definitions and main.cpp has the autocomplete program and main program to run the project. And the last file is the words
text document which contain 62887 words in it that will be inserted in a separate Trie using autocomplete logic in main.cpp*/
#include <iostream>       // Header file library for input & output streams. Brings all C++ pre-processor code here.
#include <string>         //Header for string data types
#include <vector>         //Library that allows vector acts like a container to store values dynamically during runtime
#define totalAlphabets 26 // pre defining the integer value of totalAlphabets variable
using namespace std;      // standard library for namespaces cout,cin by default

// Declaring class Trie
class Trie
{
private:                   // Setting attributes to private mode
    class alphabetTrieNode // declaring a class alphabetTrieNode for creating nodes in alphabetTrie
    {
    public:                                                 // Access specifier to public
        bool wordEnd;                                       // a boolean variable to update its value in node when insertion of word is done(word is ended).
        alphabetTrieNode *arrayOfAlphabets[totalAlphabets]; // a pointer that points to an array of size 26 which represents 26letters a-b
        int wordsCounter = 0;                               // Integer variable that is used to track number of words have with that prefix
        int totalWordsCounter = 0;                          // duplicate used to store the values, as i use to pull these for copy constructor and assignment operator
        int totalNodesCounter = 0;                          // duplicate used to store the values, as i use to pull these for copy constructor and assignment operator
        alphabetTrieNode();                                 // function to create a new alphabetTrie Node when a letter is inserted in a trie.
    };

    int numberOfNodes;      // integer variable to store number of nodes created in trie
    int totalNumberOfWords; // integer variable to store number of words present in trie
    alphabetTrieNode *root; // pointer that points to root of alphabet trie

public:                                                                   // setting methods to public mode
    Trie();                                                               // default constructor for aplhabetTrie, creates when a object of class is created
    ~Trie();                                                              // desctructor for alphabetTrie
    void deleteAlphabetTrie(alphabetTrieNode *);                          // helper function for destructor that deletes all nodes in alphabetTrie. Takes a pointer as parameter input
    bool insert(string);                                                  // insert function to insert letters in trie. Takes words as input string. boolean type
    bool insert(alphabetTrieNode *&, string);                             // helper insert function. Takes words as input from parent and a pointing reference location as input. boolean type
    int count();                                                          // integer variable that returns number of words in trie
    int getSize();                                                        // integer variable that returns number of nodes in trie
    bool find(string);                                                    // method that finds if words is present or not, input string and returns 0 or 1
    int completeCount(string);                                            // integer variable that returns number of words found in a trie with passed prefix
    vector<string> complete(string);                                      // vector that gives words list present in trie with passed prefix
    vector<string> wordsList;                                             // declared a vector container
    Trie &operator=(const Trie &);                                        // assignment operator method. Takes reference to object and kept as constant
    Trie(const Trie &);                                                   // copy constructor. Takes reference to object and kept as constant
    void copyConstuctor(alphabetTrieNode *&, alphabetTrieNode *);         // helper for copy constructor to copy all nodes & data to new object.
    void searchPrefixWords(alphabetTrieNode *, vector<string> &, string); // helper function for complete method. Contains 3 parameters
};