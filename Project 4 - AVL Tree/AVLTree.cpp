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
#include "AVLTree.h" //Header file that contains the function declarations that are needed for the AVLTree build
#include <vector>    //Library that allows vector acts like a container to store values dynamically during runtime.
#include <string>    //Header as we are using string data types
#include <iomanip>   //Header file library to manipulate output as we are using setw in the tree printing method.
using namespace std; // standard library that contains namespaces like cout by default

// Function - AVLTree - Constructor to create an object of class AVLTree
// Creates the object with, stating tree size is now 0, root is null and prevNode is null.
// returns - no return as this states that object is just created and has following members set to these values.
AVLTree::AVLTree()
{
   size = 0;
   root = nullptr;
   prevNode = nullptr;
}

// Function - AVLTree -- copy constructor to create a deep copy of AVLTree class object, a new object is created and gets copied.
// Parameter - copyTreePtr - reference to object from the data to be copied. Keeping this as constant to not modify the object.
// return - no return defined
// Member variables initialisation - root and prevNode - to nullpointer - stating initially the new objects are pointed to these
AVLTree::AVLTree(const AVLTree &copyTreePtr) : size(0), root(nullptr), prevNode(nullptr)
{
   // Calls the treeNodesCopy function which performs the copy of tree
   // Params - root - passing new object first pointing pointer to root as a reference
   // copyTree.root - passing the root of object to be copied from to a pointer
   treeNodesCopy(root, copyTreePtr.root);
}

// Function - treeNodesCopy - performs the copy of all nodes in tree by recursive calling.
// Params - newTreePtr - recieves the reference to pointer(root from above) and later acts as a pointer of new nodes and reference as well.
// copyTreePtr - keeping this as constant as original object cant be changed, and this points to the located node in the object to be copied from
// return - no return defined, creates the tree and returns back if pointer is pointed to null location.
void AVLTree::treeNodesCopy(AVLTreeNodes *&newTreePtr, const AVLTreeNodes *copyTreePtr)
{
   // checks if the pointer pointed to object AVLTree to be copied from is not null, where we are passing root of object initially from above
   if (copyTreePtr != nullptr)
   {
      // creates a new AVLTree node with the original object poistioned pointer to its key and value pair
      newTreePtr = new AVLTreeNodes(copyTreePtr->key, copyTreePtr->value);
      count++;                                  // increment number of nodes as they get created
      setSize(count);                           // calls setter to update size of tree
      newTreePtr->parent = prevNode;            // Updates the parent of the newnode is the previous node
      newTreePtr->height = copyTreePtr->height; // gets and saves the height from the original pointed object node

      // recalls the function and points the pointers to the right side of the node in both original and copying object
      treeNodesCopy(newTreePtr->rightPtr, copyTreePtr->rightPtr);
      // recalls the function and points the pointers to the left side of the node in both original and copying object
      treeNodesCopy(newTreePtr->leftPtr, copyTreePtr->leftPtr);
   }
   else // if the pointer is pointed to null, exit and return this call
   {
      return;
   }
}

// Function - ~AVLTree - destructor to destroy all nodes in tree to avoid memory leaks
// returns - no return defined
// Iterates though all nodes of tree and deletes them one by one
AVLTree::~AVLTree()
{
   if ((root != nullptr && getSize() != 0)) // runs if the root is not null or size is >0 stating tree is exising
   {
      deletingNodes(root); // calling method to delete the nodes and passing the root as parameter or starting position.
   }
   if (getSize() == 0) // If function deleted all nodes and size is now updated to zero, make the root as nullpointer.
   {
      root = nullptr;
   }
}

// Function - deletingNodes - Perfroms deletion of all nodes in the AVLTree one by one as they are created on heap.
// return - no return defined
// Params - deletePtr - a pointer to position to the passed location node, it gets moved to each node throught recursive calls in this function
// until all the nodes are deleted
// recursive call happens and here using the Inorder type traversal method to delete nodes
void AVLTree::deletingNodes(AVLTreeNodes *deletePtr)
{
   if (deletePtr == nullptr) // returns from function if the pointer is pointed to null location
      return;

   if (deletePtr != nullptr) // runs the deletion operation when deletePtr is pointing a real node
   {
      AVLTreeNodes *leftChild = deletePtr->leftPtr;   // creating a pointer leftChild to store the address of the leftChild/subtree of the currentnode
      AVLTreeNodes *rightChild = deletePtr->rightPtr; // creating pointer rightChild to store address of  rightChild/subtree of the currentnode
      deletingNodes(leftChild);                       // do a function call again to delete nodes by moving pointer to the leftTree or child of currentNode
      delete deletePtr;                               // delete the current pointing node
      count--;                                        // decrementing the number of nodes by 1 as node gets removed
      setSize(count);                                 // using setter to update size
      deletingNodes(rightChild);                      // do a function call again to delete nodes by moving pointer to the rightTree or child of currentNode
   }
}

// Function - operator= :Assignment operator method to release the exising object data and replace by the deep copy of the refernece object.
// Params - object - reference object passed from which data has to be assigned
// returns - *this - returns the object of the current copied AVLTree object.
AVLTree &AVLTree::operator=(const AVLTree &object)
{
   deletingNodes(root);                    // Calling the delete nodes method to clear all the nodes initially. This is also used a destructor above
   AVLTreeNodes *currentPtr = object.root; // creating a pointer that points to root of the passed reference object and gets iterates thru tree
   if (currentPtr != nullptr)              // run if referenced object tree root is not null pointer.
   {
      treeNodesCopy(root, currentPtr); // calling the copy function to copy key/value pair of all nodes in the tree.
   }
   return *this;
}

// Function - insert - method to create a new node when a key value pair needs to be inserted.Duplicates are not allowed hence if conditions
// only gets satisfied on less and greater than passed keys. a node is created and pointed to root initially and function gets called recursively
// to insert the following keyvalue pairs
// return - boolean values - true if node is created with key value pair, false if duplicate is passed.
// params - newKey(integer) - key to be inserted in AVLTree
// newValue(string) - value to be inserted in AVLtree in the node
// currentPtr - reference to the pointer passed, initially root and later iterates through the tree
bool AVLTree::insert(int newKey, string newValue, AVLTreeNodes *&currentPtr)
{
   // inserts a new node when the pointer is at null location
   if (currentPtr == nullptr)
   {
      currentPtr = new AVLTreeNodes(newKey, newValue); // creates a new AVLTreeNode object
      count++;                                         // incrementing count variable to keep track of size of AVLTree
      setSize(count);                                  // setter to update size, passing count variable
      currentPtr->parent = prevNode;                   // updating the parent of currentNode as previous node
      checkNodeBalance(currentPtr);                    // calls balance function to check height, balance and do rotations

      return true;
   }
   else if (newKey > currentPtr->key) // runs if passed key is greater than current pointed node key
   {
      prevNode = currentPtr;                                 // updates the previous node
      return insert(newKey, newValue, currentPtr->rightPtr); // inserts the node in the right side as a child
   }
   else if (newKey < currentPtr->key) // runs if passed key is less than current pointed node key
   {
      prevNode = currentPtr;
      return insert(newKey, newValue, currentPtr->leftPtr); // inserts the node in the left side as a child
   }
   else
   {
      return false; // returns 0 if the duplicate is passed
   }
}

// Function - setSize - setter to update the size of AVLTree
// return - no return
// params - count - takes integer as input
void AVLTree::setSize(int)
{
   size = count; // sets the size as count value
}

// Function - getSize - getter to get the size of AVLTree
// return(inetger) - returns the size of AVLTree
int AVLTree::getSize()
{
   return size;
}

// Function - checkNodeBalance - method that does the balancing of AVLTree and rechecks the balance of parent node after performing balance.
// return - no return needed as it perform rotations in tree only if needed
// params - currentPtr - pointer that points to the current poisition node in AVLTree, which is passed from the insert function
void AVLTree::checkNodeBalance(AVLTreeNodes *currentPtr)
{
   if (currentPtr != nullptr) // executes when the passed location is not null pointer
   {
      balancingTree(currentPtr);            // performs height calculation and does balancing of tree
      checkNodeBalance(currentPtr->parent); // checks and performs balance of parent Node.
   }
}

// Function - balancingTree - method to perform balancing when the balancefactor is other than -1, 0 and 1.
// calls the functions to calculate height of the node before performing balancing.
// return - no return
// params - currentPtr - reference to the pointer passed from the insert function
void AVLTree::balancingTree(AVLTreeNodes *&currentPtr)
{
   UpdateNodeHeight(currentPtr); // function that calculates the height of the node

   // does a function in the condition to check balance factor and if it is -2 and rightchild is 1 it does double Right rotation
   // 2 rotations needed, one left and one right
   // if not only left rotation is performed stating that the right subtree is heavy
   if (nodeBalanceFactor(currentPtr) == -2)
   {
      if (nodeBalanceFactor(currentPtr->rightPtr) == 1)
      {
         doubleRightRotation(currentPtr); // calls the doublerightrotation method and passes the current location node which is from insert function
      }
      leftRotation(currentPtr); // Left rotation method, passes the current location node which is from insert function
   }

   // if balance factor is 2 and -1 of the current node and it left child, it does double left rotation
   // 2 rotations needed, one left and one right
   // if not only right rotation is performed as left subtree is heavt
   else if (nodeBalanceFactor(currentPtr) == 2)
   {
      if (nodeBalanceFactor(currentPtr->leftPtr) == -1)
      {
         doubleLeftRotation(currentPtr); // calls the doubleleftrotation method and passes the current location node which is from insert function
      }
      rightRotation(currentPtr); // right rotation method, passes the current location node which is from insert function
   }
}

// Function - updateNodeHeight - calculates the height of the node
// return(inetger) - returns the current node height value back into the balancingTree function
// params - reference to the pointer passed from the insert function
int AVLTree::UpdateNodeHeight(AVLTreeNodes *&currentPtr)
{
   // if the node donot have any childs
   if (currentPtr->leftPtr == nullptr && currentPtr->rightPtr == nullptr)
   {
      // current node height = (lefttree height - righttree height)
      return currentPtr->height = currentPtr->leftTreeHeight - currentPtr->rightTreeHeight;
   }
   // if node have child either left or right
   else
   {
      if (currentPtr->rightPtr != nullptr) // if node has a right child or a tree in its right
      {
         currentPtr->rightTreeHeight = currentPtr->rightPtr->height; // updates the current node righttree height. Retrieves height of its righttree
      }
      if (currentPtr->leftPtr != nullptr) // if node has a left child or a tree in its right
      {
         currentPtr->leftTreeHeight = currentPtr->leftPtr->height; // updates the current node lefttree height. Retrieves height of its lefttree
      }

      // returns the maximum integer value of the node's left Tree and right Tree height and adding 1, saying even tree with height 0 when there is one node in AVLTree.
      return currentPtr->height = max(currentPtr->rightTreeHeight, currentPtr->leftTreeHeight) + 1;
   }
}

// Function - nodeBalanceFactor - calculates the balance factor of the node
// return (integer) - returns the current node balance factor which is leftTree height - rightTree height.
// params - currentPtr - reference to the pointers passed from the insert/checkNodeBalance function
int AVLTree::nodeBalanceFactor(AVLTreeNodes *&currentPtr)
{
   if (currentPtr->leftPtr != nullptr)                              // runs if current pointing node does have a left child
      currentPtr->leftTreeHeight = currentPtr->leftPtr->height;     // retrieves tree height from its child
   if (currentPtr->rightPtr != nullptr)                             // runs if current pointing node does have a right child
      currentPtr->rightTreeHeight = currentPtr->rightPtr->height;   // retrieves tree height from its child
   return currentPtr->leftTreeHeight - currentPtr->rightTreeHeight; // balance factor value
}

// Function - getHeight - gets the height of AVLTree
// return (integer) - returns the root node height which represents the AVLTree height
int AVLTree::getHeight()
{
   return root->height;
}

// Function - DoubleRightRotation - Performs one single left and single right rotation when balance of current node is -2 and hook node is 1
// params - problemNode - reference to the pointer of the current pointing node from the insert function
// local variables:
// hookNode - pointers that points to the rightchild of the problemNode
// secondHookNode - pointer that points to the leftchild of hooknode
void AVLTree::doubleRightRotation(AVLTreeNodes *&problemNode)
{
   AVLTreeNodes *hookNode = problemNode->rightPtr;
   AVLTreeNodes *secondHookNode = hookNode->leftPtr;

   problemNode->rightPtr = secondHookNode; // updating rightchild of problem node as secondHookNode
   secondHookNode->parent = problemNode;   // updating secondHookNode parent as problemNode
   hookNode->parent = secondHookNode;      // updating parent of hooknode to secondHookNode
   hookNode->parent->rightPtr = hookNode;  // setting hookNode parent's rightChild as hooknode
   hookNode->leftPtr = nullptr;            // making hookNode leftchild as null as once it is rotated it lost the child
   problemNode->rightTreeHeight = -1;      // updating problemNode rightTree to -1 as the node child is removed
   hookNode->leftTreeHeight = -1;          // updating hookNode left tree to -1 as its left child is removed
   UpdateNodeHeight(hookNode);             // recaluclate height of hook node and update
   UpdateNodeHeight(secondHookNode);       // recalculate height of secondhooknode and update
}

// Function - leftRotation - Method to perform left rotation at the problemNode where the balancefactor is -2
// returns - no return
// params - problem - reference to the pointer passed from the insert function
void AVLTree::leftRotation(AVLTreeNodes *&problemNode)
{
   AVLTreeNodes *hookNode = problemNode->rightPtr; // creating pointer to pointer to rightchild/Tree of problemNode

   if (problemNode->parent == nullptr) // executes this logic set only if the parent of problem node is null, means this is root node
   {

      if (hookNode->leftPtr == nullptr) // executes if the leftchild or leftsubtree of hooknode is empty
      {
         hookNode->parent = nullptr;                     // updates parent of hook node as parent as we make it as root
         root = hookNode;                                // updating root as hooknode
         hookNode->leftPtr = problemNode;                // updates hooknode leftchild/subtree as problemnode
         problemNode->parent = hookNode;                 // updates parent of problemnode as hooknode
         problemNode->rightPtr = nullptr;                // updates problemnode rightchild/rightTree to nullpointer as it is removed
         problemNode->rightTreeHeight = -1;              // updating problem node rightTree height to -1 saying there is no sub tree
         hookNode->leftTreeHeight = problemNode->height; // updates the hookNode left subtree height to problemNode's height.
      }
      else // if hookNode has a leftchild node
      {
         AVLTreeNodes *tmpPtr = hookNode->leftPtr;       // creating a temporary pointer to save the hookNode left child
         hookNode->parent = problemNode->parent;         // updates parent of hookNode as problemNod's parent
         hookNode->leftPtr = problemNode;                // updates hooknode leftchild/subtree as problemnode
         problemNode->parent = hookNode;                 // updates parent of problemnode as hooknode
         problemNode->rightPtr = tmpPtr;                 // updates problemnode rightchild/rightTree to temporary pointer which is hookNode leftChild
         tmpPtr->parent = problemNode;                   // updates temporary pointer parent to problemNode
         problemNode->rightTreeHeight = tmpPtr->height;  // updates the problemNode right subtree height to hookNode left child height.
         hookNode->leftTreeHeight = problemNode->height; // updates the hookNode left subtree height to problemNode height.
      }
   }
   else // if problemnode parent is not null(problemnode is a child of other node)
   {
      if (hookNode->leftPtr == nullptr) // executes if the leftchild or leftsubtree of hooknode is empty
      {
         hookNode->parent = problemNode->parent;          // updates parent of hookNode as problemNod's parent
         if (problemNode->parent->leftPtr == problemNode) // verifies if problemNode parent node left child is problem node
         {
            problemNode->parent->leftPtr = hookNode; // updates it to hooknode
         }
         else // otherwise updates it hooknode as right child of problemNode parent node.
         {
            problemNode->parent->rightPtr = hookNode;
         }
         hookNode->leftPtr = problemNode;                // updates hooknode leftchild/subtree as problemnode
         problemNode->parent = hookNode;                 // updates parent of problemnode as hooknode
         problemNode->rightPtr = nullptr;                // updates problemnode rightchild/rightTree to nullpointer as it is removed
         problemNode->rightTreeHeight = -1;              // updating problem node rightTree height to -1 saying there is no sub tree
         hookNode->leftTreeHeight = problemNode->height; // updates the hookNode left subtree height to problemNode height.
      }
      else // executes if the leftchild or leftsubtree of hooknode has a child
      {
         AVLTreeNodes *tmpPtr = hookNode->leftPtr;        // creating a temporary pointer to save the hookNode left child
         hookNode->parent = problemNode->parent;          // updates parent of hookNode as problemNode's parent
         if (problemNode->parent->leftPtr == problemNode) // verifies if problemNode parent node left child is problem node
         {
            problemNode->parent->leftPtr = hookNode; // updates it to hooknode
         }
         else // otherwise updates it hooknode as right child of problemNode parent node.
         {
            problemNode->parent->rightPtr = hookNode;
         }
         hookNode->leftPtr = problemNode;                // updates hooknode leftchild/subtree as problemnode
         problemNode->parent = hookNode;                 // updates parent of problemnode as hooknode
         problemNode->rightPtr = tmpPtr;                 // updates problemnode rightchild/rightTree to temporary pointer which hookNode leftChild
         tmpPtr->parent = problemNode;                   // updates temporary pointer parent to problemNode
         problemNode->rightTreeHeight = tmpPtr->height;  // updates the problemNode right subtree height to hookNode left child height.
         hookNode->leftTreeHeight = problemNode->height; // updates the hookNode left subtree height to problemNode height.
      }
   }
   UpdateNodeHeight(hookNode->leftPtr); // recalculates height of leftChild/LeftsubTree height of hooknode
   UpdateNodeHeight(hookNode);          // recalculates height of hooknode
}

// Function - doubleLeftRotation - Performs one single right and single left rotation when balance of current node is 2 and hook node is -1
// params - problemNode - reference to the pointer of the current pointing node from the insert function
// local variables:
// hookNode - pointers that points to the leftchild of the problemNode
// secondHookNode - pointer that points to the rightchild of hooknode
void AVLTree::doubleLeftRotation(AVLTreeNodes *&problemNode)
{
   AVLTreeNodes *hookNode = problemNode->leftPtr;
   AVLTreeNodes *secondHookNode = hookNode->rightPtr;

   problemNode->leftPtr = secondHookNode; // updating leftchild of problem node as secondHookNode
   secondHookNode->parent = problemNode;  // updating secondHookNode parent as problemNode
   hookNode->parent = secondHookNode;     // updating parent of hooknode to secondHookNode
   hookNode->parent->leftPtr = hookNode;  // setting hookNode parent's leftChild as hooknode
   hookNode->rightPtr = nullptr;          // making hookNode rightchild as null as once it is rotated it lost the child
   hookNode->rightTreeHeight = -1;        // updating problemNode rightTree to -1 as the node child is removed
   problemNode->leftTreeHeight = -1;      // updating hookNode left tree to -1 as its left child is removed
   UpdateNodeHeight(hookNode);            // recaluclate height of hook node and update
   UpdateNodeHeight(secondHookNode);      // recalculate height of secondhooknode and update
}

// Function - rightRotation - Method to perform right rotation at the problemNode where the balancefactor is 2
// returns - no return
// params - problem - reference to the pointer passed from the insert function
void AVLTree::rightRotation(AVLTreeNodes *&problemNode)
{
   AVLTreeNodes *hookNode = problemNode->leftPtr; // creating pointer to pointer to leftchild/Tree of problemNode

   if (problemNode->parent == nullptr) // executes this logic set only if the parent of problem node is null, means this is root node
   {

      if (hookNode->rightPtr == nullptr) // executes if the rightchild or rightsubtree of hooknode is empty
      {
         hookNode->parent = nullptr;                      // updates parent of hook node as nullpointer
         root = hookNode;                                 // updating root as hooknode
         hookNode->rightPtr = problemNode;                // updates hooknode rightchild/subtree as problemnode
         problemNode->parent = hookNode;                  // updates parent of problemnode as hooknode
         problemNode->leftPtr = nullptr;                  // updates problemnode leftchild/leftTree to nullpointer as it is removed
         problemNode->leftTreeHeight = -1;                // updating problem node leftTree height to -1 saying there is no sub tree
         hookNode->rightTreeHeight = problemNode->height; // updates the hookNode right subtree height to problemNode's height.
      }
      else // if hookNode has a right child node
      {
         AVLTreeNodes *tmpPtr = hookNode->rightPtr;       // creating a temporary pointer to save the hookNode right child
         hookNode->parent = nullptr;                      // updates parent of hookNode as nullpointer as we move it to root
         root = hookNode;                                 // updating root as hooknode
         hookNode->rightPtr = problemNode;                // updates hooknode rightchild/subtree as problemnode
         problemNode->parent = hookNode;                  // updates parent of problemnode as hooknode
         problemNode->leftPtr = tmpPtr;                   // updates problemnode leftchild/leftTree to hooknode right child
         tmpPtr->parent = problemNode;                    // updates temporary pointer parent to problemNode
         problemNode->leftTreeHeight = tmpPtr->height;    // updates the problemNode left subtree height to hookNode right child height.
         hookNode->rightTreeHeight = problemNode->height; // updates the hookNode right subtree height to problemNode height.
      }
   }
   else // if problemnode parent is not null(problemnode is a child of other node)
   {
      if (hookNode->rightPtr == nullptr) // executes if the rightchild or rightsubtree of hooknode is empty
      {
         hookNode->parent = problemNode->parent;           // updates parent of hookNode as problemNode parent
         if (problemNode->parent->rightPtr == problemNode) // verifies if problemNode parent node right child is problem node
         {
            problemNode->parent->rightPtr = hookNode; // updates it to hooknode
         }
         else // otherwise updates it hooknode as left child of problemNode parent node.
         {
            problemNode->parent->leftPtr = hookNode;
         }
         hookNode->rightPtr = problemNode;                // updates hooknode rightchild/subtree as problemnode
         problemNode->parent = hookNode;                  // updates parent of problemnode as hooknode
         problemNode->leftPtr = nullptr;                  // updates problemnode leftchild/leftTree to nullpointer as it is removed
         problemNode->leftTreeHeight = -1;                // updating problem node leftTree height to -1 saying there is no sub tree
         hookNode->rightTreeHeight = problemNode->height; // updates the hookNode right subtree height to problemNode height.
      }
      else // executes if the rightchild or rightsubtree of hooknode has a child
      {
         AVLTreeNodes *tmpPtr = hookNode->rightPtr;        // creating a temporary pointer to save the hookNode right child
         hookNode->parent = problemNode->parent;           // updates parent of hookNode as problemNod's parent
         if (problemNode->parent->rightPtr == problemNode) // verifies if problemNode parent node right child is problem node
         {
            problemNode->parent->rightPtr = hookNode; // updates it to hooknode
         }
         else // otherwise updates it hooknode as left child of problemNode parent node.
         {
            problemNode->parent->leftPtr = hookNode;
         }
         hookNode->rightPtr = problemNode;                // updates hooknode rightchild/subtree as problemnode
         problemNode->parent = hookNode;                  // updates parent of problemnode as hooknode
         problemNode->leftPtr = tmpPtr;                   // updates problemnode leftchild/leftTree to temporary pointer which hookNode rightChild
         tmpPtr->parent = problemNode;                    // updates temporary pointer parent to problemNode
         problemNode->leftTreeHeight = tmpPtr->height;    // updates the problemNode left subtree height to hookNode right child height.
         hookNode->rightTreeHeight = problemNode->height; // updates the hookNode right subtree height to problemNode height.
      }
   }
   UpdateNodeHeight(hookNode->rightPtr); // recalculates height of rightChild/rightsubTree height of hooknode
   UpdateNodeHeight(hookNode);           // recalculates height of hooknode
}

// Function - Operator overloading(<<) - method to print the AVLTree object
// Parameters - os ostream - reference to the output AVLTree
// me - AVLTree object of the data printed, keeping constant since it should not modify the object
// returns the reference passed in the ostream(os)
//  calls the function rightChildInorderTraversal which returns the data to print
ostream &operator<<(ostream &os, const AVLTree &me)
{
   me.rightChildInorderTraversal(os, me.root, 0); // passed the root of AVLTreeobject(me) to traversalPtr below. Initilaises the whitespace to zero.
   return os;
}

// Function - rightChildInorderTraversal - function that returns the outstream to the operator overloading. The outstream output return is
// in the form of rightChild First inorder traversal
// Parameters - display ostream - reference to the output AVLTree. Which finally gives the display data to OS in operator overload
// traversalPtr - pointers that points to current located node and iterates thru whole tree
// whiteSpace(integer) - used to print the output which looks like a tree , based on the deepest location the node is located in tree.
// const - to modify the object at any cost
// returns the outstream display to the operator overloading
void AVLTree::rightChildInorderTraversal(ostream &display, AVLTreeNodes *traversalPtr, int whiteSpace) const
{
   if (traversalPtr == nullptr) // exits the function and returns to the calling function if nullpointer
   {
      return;
   }

   whiteSpace = whiteSpace + 1;    // incrementing each time the rightChildInorderTraversal is called in recursive manner
   int printNodeData = whiteSpace; // creating a new variable to save as it is used in style printing(looks like a tree)

   rightChildInorderTraversal(display, traversalPtr->rightPtr, whiteSpace); // calls the function by updating pointer to rightSubtree or rightchild

   while (printNodeData != 0)
   {
      display << setw(4) << "";          // using setw manipulator to set the field width. it creates the width number of time the while is executed
      printNodeData = printNodeData - 1; // decrementing
   }
   display << traversalPtr->key << ", " << traversalPtr->value << endl; // return the key and value date to the outstream display

   rightChildInorderTraversal(display, traversalPtr->leftPtr, whiteSpace); // calls the function by updating pointer to leftSubtree or leftchild
}

// Function - find - checks the key present in the AVLtree or not.
// Params - key(integer) - value to be found
//&value - a reference to the value is passed which stores the value present in the founded node.
// findPtr - recieves a reference to the pointer passed from the helper funcion in main find method
// return true or false and the string stored in the value reference.
bool AVLTree::find(int key, string &value, AVLTreeNodes *&findPtr)
{
   // returns false if the pointer positioned is nullpointer
   if (findPtr == nullptr)
   {
      return false;
   } // executes when pointers points to a real node
   else if (!(findPtr == nullptr))
   {
      if (findPtr->key == key) // if checking value is found at pointer positioned node
      {
         value = findPtr->value; // stores the string
         return true;            // returns 1
      }
      else if (findPtr != nullptr && findPtr->key > key) // check in the left sub tree only if key to be checked is less than pointed node key
      {
         return find(key, value, findPtr->leftPtr); // calls the find function again recursively, and updates the pointer to left child node of current node
      }
      else if (findPtr != nullptr && findPtr->key < key) // check in the left sub tree only if key to be checked is less than pointed node key
      {
         return find(key, value, findPtr->rightPtr); // calls the find function again recursively, and updates the pointer to right child node of current node
      }
      else // if the key to be found is not found in the AVLTree
      {
         return false; // returns 0
      }
   }
   return false;
}

// Function - findRange - stores and return all the values within that range in the AVLTree
// Parameters - lowKey(integer) - the lower bound to be found in the rangelist of AVLtree
// highKey(integer) - the higher bound to be found in the rangelist of AVLtree
// returns an container vector that stored the list of values in this range
vector<string> AVLTree::findRange(int lowKey, int highKey)
{
   if (rangeListOfTree.empty()) // excutes only if the container is empty
   {
      addValuesToRangeList(lowKey, highKey); // calls the function to check the tree and add values to the vector container
      return rangeListOfTree;                // returns the vector list
   }
   else // if vector container is not empty
   {
      rangeListOfTree.clear();               // clears the container before performing function call
      addValuesToRangeList(lowKey, highKey); // calls the function to check the tree and add values to the vector container
      return rangeListOfTree;                // returns the vector list
   }
}

// Function - addValuesToRangeList - Method that iterates through the AVLTree recursively and stores the values in the container
// Params - lowKey(integer) - the lower bound to be found in the rangelist of AVLtree
// highKey(integer) - the higher bound to be found in the rangelist of AVLtree
// currentPtr -reference to a pointer passed, starts at root initially and iterates through AVLtree throught recursive calling
// return - no return since values are stored in the vector
void AVLTree::addValuesToRangeList(int lowKey, int highKey, AVLTreeNodes *&currentPtr)
{
   if (currentPtr != nullptr) // not positioned to nullpointer
   {
      addValuesToRangeList(lowKey, highKey, currentPtr->leftPtr); // reursive function call by updating pointer to leftChild or leftTree of currentNode

      // If the passed lower bounds and upper bound values are less than higher bound and greater than lower bound at the current positioned node key data
      if (currentPtr->key <= highKey && currentPtr->key >= lowKey)
      {
         rangeListOfTree.push_back(currentPtr->value);
      }

      addValuesToRangeList(lowKey, highKey, currentPtr->rightPtr); // reursive function call by updating pointer to rightChild or rightTree of currentNode
   }
   else
      return; // exits the current function and returns to the calling function
}