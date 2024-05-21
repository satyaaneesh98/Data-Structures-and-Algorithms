//----------------------------------------------------
/*Project Description:
The project is to implement an AVL tree that serves as a map in general which stores keys and retrieves them when queried.
An AVL tree is used as data structure as the time complexity is cut by half in each. In this AVL tree we are inserting the integers and the
string values of the integers into each node. Insert should create a new node and inserts the integer key and string value by ensuring no
duplicates are allowed. Finding the value present in AVL Tree or not using find functions and print out range of values if present in tree
using findRange function. At each insertion, we calculcate size and height to ensure the tree stays balanced using the rotation methods.
In the findRange we manipulate the printing way and print it in tree form where the values list from high to low as we will be using the
rightChildFirst Inorder traversal method.
Apart from given must needed functions that are needed for BST Tree, we have declared and defined required functions to change the BST tree into
AVL Tree. Our avlTree.h file consists of file declaration and avlTree.cpp consists of function declarations.
project4Driver.cpp file is the main .cpp to check the insertions, printing and search happens correctly as per our implmentations.*/
//-------------------------------------------------------

#include <iostream>  // Header file library to carry out input and output streams. Brings all the C++ pre-processor code here.
#include <vector>    //Library that allows vector acts like a container to store values dynamically during runtime.
#include <string>    //Header as we are using string data types
#include <iomanip>   //Header file library to manipulate output as we are using setw in the tree printing method.
using namespace std; // standard library that contains namespaces like cout by default

// Declaring class AVLTree
class AVLTree
{
private:               // setting attributes of class AVLTree to private
    class AVLTreeNodes // Declaring the class AVLTreeNodes - This class creates the nodes in the AVLTree which stores keys & values.
    {
    public:                     // setting attributes of class AVLTree to public
        int key;                // integer to be stored in the node.
        string value;           // string of the key to be stored in the node
        AVLTreeNodes *parent;   // creating a pointer of class AVLTreeNodes that helps point its node to the parentnode of it(previous node of this node)
        AVLTreeNodes *leftPtr;  // creating a pointer to connect to the left node, which acts as left child of this node
        AVLTreeNodes *rightPtr; // creating a pointer to connect to the right node, which acts as right child of this node
        int leftTreeHeight;     // an integer that is initally sets leftTreeheight to -1 representing there is no child and later modified as tree grows
        int rightTreeHeight;    // an integer that is initally sets rightTreeheight to -1 representing there is no child and later modified as tree grows
        int height;             // integer that defines the height of this node in the tree and helps in calculating the balance for rotations

        // Parameterized constructor called AVLTreeNodes used to create node of class AVLTreeNodes.
        // Takes 2 inputs when constructor is called and rest of the parameters are initialized and later modified in the functions as new nodes are inserted
        // Parameters:
        // newKey(integer): stores the key while a new node/object is created.
        // newValue(string): stores the value string when a new node/object is created.
        /*Member initalizers: While a node is created, the data members are initialized to given input as the new nodes holds the same data for these
        members*/
        // key(newKey) (integer) - inserts the newKey passed to the key variable
        // leftPtr, rightPtr are initialised to nullptr as a new node will not have any child at that point.
        // parent is initialised as null for root purpose and will be modified from second node insertion.
        // leftTreeHeight and rightTreeHeight are set to -1 as it represents no child hence sub-tree's height.
        AVLTreeNodes(int newKey, string newValue) : key(newKey), value(newValue), parent(nullptr), leftPtr(nullptr), rightPtr(nullptr), leftTreeHeight(-1), rightTreeHeight(-1){};
    };
    int size;               // integer that gives the number of nodes in the AVLTree
    int count = 0;          // created an integer to increment size of AVLTree after each insert and passed to size using setter.
    AVLTreeNodes *root;     // created pointer root that defines as the head of the AVLTree
    AVLTreeNodes *prevNode; // created pointer prevNode that represents it is the previous node of the new node, used along with parent.

public: // Declaring the member functions as public access specifiers.
    // Default constructor when just an object of class AVLTree is created
    AVLTree();

    // Copy constructor that performs a deep copy of the AVLTree object
    // Parameter copyTreePtr is the object to be copied from, keeping it as constant and passing by refernce
    AVLTree(const AVLTree &copyTreePtr);

    // An helper function declared for performing the copy constructor as it have to iterate through whole tree recursively.
    // Parameters: newTreePtr - points to the newobject which is being deep copied using copy constructor
    // copyTreePtr - pointer that acts as an alias to the passing paramter, where this is points to object being copied from
    void treeNodesCopy(AVLTreeNodes *&newTreePtr, const AVLTreeNodes *copyTreePtr);

    // Destructor that deletes all nodes in class AVLTree to avoid memory leaks as the new nodes inserted on heap
    ~AVLTree();

    // helper function in the destructor that is called recrusively to delete all nodes in class AVLTree
    // Parameter - pointer that points to the passing parameter which is a root initially and later gets modified as it iterates in tree
    void deletingNodes(AVLTreeNodes *deletePtr);

    // Assignment operator that releases the current AVLTree data and replaced by deep copy of class AVLTree object
    // A reference to the copied AVLTree object is returned
    // parameter - object - AVLTree data to be copied
    AVLTree &operator=(const AVLTree &object);

    // Insert method to insert a new node in AVLTree object when function is called no duplicates allowed
    // Patameters - key(integer), value(string)
    // returns boolean value, false if key is not inserted and true if inserted
    // helper function takes additional parameter as we state the object root is null and new node starts from root.
    bool insert(int key, string value)
    {
        return insert(key, value, root);
    }

    // Insert helper function declared above which takes parameters passed from above insert method/
    //*& currentPtr - recieved as reference to a pointer that points to the passed current node. from helper function above, initally root is passed to this
    bool insert(int newkey, string newValue, AVLTreeNodes *&currentPtr);

    // Setter to update the size of AVLTree
    // Parameter - integer
    void setSize(int);

    // Getter to return size of AVLTree
    int getSize();

    // Method to checkNode balance and perform rotation in Tree when needed
    // Parameter - currentPtr that points to the current location node in the tree
    void checkNodeBalance(AVLTreeNodes *currentPtr);

    // Method that verifies the balancefactor and peform rotations in AVLTree
    // Parameter - currentPtr - recieved as reference to a pointer that points to the passed current node.
    void balancingTree(AVLTreeNodes *&currentPtr);

    // Method that calculates and update the height of node
    // Parameter - currentPtr - a reference to a pointer that points to the passed parameter.
    int UpdateNodeHeight(AVLTreeNodes *&currentPtr);

    // Method that calculates the balancefactor of each node which decides the rotations needed or not for balance
    // Parameter - currentPtr - recieved as reference to a pointer that points to the passed current node.
    int nodeBalanceFactor(AVLTreeNodes *&currentPtr);

    // Getter that returns the height of the tree
    // returns an integer
    int getHeight();

    // Method that does double right rotation, one single left and one single right
    // Parameter - problemNode - recieved as reference to a pointer that points to the passed current node which is a problemNode that has deepest & highhest unbalance
    void doubleRightRotation(AVLTreeNodes *&problemNode);

    // Perform one leftrotation
    // Parameter - currentPtr - reference to a pointer that points to the problem node passed in the function call
    void leftRotation(AVLTreeNodes *&problemNode);

    // Method that does double left rotation, one single right and one single left
    // Parameter - problemNode - reference to a pointer that points to the problem node passed in the function call
    void doubleLeftRotation(AVLTreeNodes *&problemNode);

    // Perform one right rotation
    // Parameter - currentPtr - reference to a pointer that points to the problem node passed in the function call
    void rightRotation(AVLTreeNodes *&problemNode);

    // Operator overloading(<<),this is used to print and calls the other method
    // Parameters - os ostream - reference to the output AVLTree
    // me - AVLTree object of the data printed, keeping constant since it should not modify the object
    // returns the reference passed in the ostream(os)
    friend ostream &operator<<(ostream &os, const AVLTree &me);

    // A printing function which is called in operator overloading.
    // the logic here used is rightChildFirst inorder traversal as mentioned
    // Parameters - display ostream - reference to the output AVLTree. Which finally gives the display data to OS in operator overload
    // traversalPtr - pointers that points to current located node and iterates thru whole tree
    // whiteSpace(integer) - used to print the output which looks like a tree , based on the deepest location the node is located in tree.
    // const - to modify the object at any cost
    void rightChildInorderTraversal(ostream &display, AVLTreeNodes *traversalPtr, int whiteSpace) const;

    // Find method that checks the queried key present in the AVLtree or not.
    // return - an helper function is defined as we need to pass the node position initially.
    // Params - key(integer) - value to be found
    //&value - a reference to the value is passed which stores the value present in the founded node.
    // return true or false and the string stored in the value reference.
    bool find(int key, string &value)
    {
        return find(key, value, root);
    }

    // helper find method
    // params - findPtr - recieves a reference to the pointer passed from the helper funcion in main find method
    bool find(int key, string &value, AVLTreeNodes *&findPtr);

    // Method to stores and return all the values within that range in the AVLTree
    // Parameters - lowKey(integer) - the lower bound to be found in the rangelist of AVLtree
    // highKey(integer) - the higher bound to be found in the rangelist of AVLtree
    // returns an vector that stored the list of values in this range
    vector<string> findRange(int lowKey, int highKey);

    // An vector container is created to store the values in it
    vector<string> rangeListOfTree;

    // Method that iterates through the AVLTree recursively and stores the values in the container
    void addValuesToRangeList(int lowKey, int highKey)
    {
        addValuesToRangeList(lowKey, highKey, root);
    }

    // Helper function where the root is passed as an initial refernece to the pointer currentPtr.
    void addValuesToRangeList(int lowKey, int highKey, AVLTreeNodes *&currentPtr);
};