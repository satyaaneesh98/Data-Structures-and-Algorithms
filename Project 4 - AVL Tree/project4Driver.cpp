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


#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;



int main() {
	
	AVLTree tree;
	cout << tree.insert(50, "Fifty");
	// This should print 0, because it returns false (no duplicates allowed):
	cout << tree.insert(50, "Another fifty");
	cout << tree.insert(100, "One hundred");
	cout << tree.insert(200, "Two hundred");//single rotate left
	cout << "\n\n";
	cout << tree << endl;
	
	cout << tree.insert(40, "Fourty");
	cout << tree.insert(30, "Thirty");//single rotate right
	cout << tree.insert(150, "One hundred fifty");
	cout << tree.insert(175, "One hundred seventy-five");//double rotate right
	cout << tree.insert(35, "Thirty-five");
	cout << tree.insert(34,"Thirty-four");//double rotate left
	cout << tree.insert(50, "Fifty yet again");//should be 0
	cout << tree.insert(34, "Thirty-four again");//should be 0;
	cout << tree.insert(200, "Two hundred");//should be 0;
    //Expect: 1011111111000
	
	cout << "\n\n";
	
	cout << tree << endl;

	AVLTree newTree;

	cout << newTree.insert(33, "Thirty");
	cout << newTree.insert(13, "Thirteen");
	cout << newTree.insert(11, "Eleven");
	cout << newTree.insert(9, "Nine");
	cout << newTree.insert(0, "Zero");
	cout << newTree.insert(53, "Fifty Three");
	cout << newTree.insert(61, "Sixty One");
	cout << newTree.insert(21, "Twenty One");
	cout << endl;

	cout << "checking tree rightinorder print structure, size and height: " << endl;
	cout << newTree << endl;

	cout << tree.getSize() << endl;//9
	cout << tree.getHeight() << endl;//3

	cout << newTree.getSize() << endl;//8
	cout << newTree.getHeight() << endl;//3

	string result;

	cout << tree.find(50, result) << endl;//1
	cout << result << endl; //Fifty

	cout << tree.find(40, result) << endl;//1
	cout << result << endl; //Fourty

	cout << tree.find(175, result) << endl;//1
	cout << result << endl; //One hundred seventy-five

	cout << tree.find(600, result) << endl; //0

	vector<string> vec = tree.findRange(30, 200);//all of it
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {	
		cout << *it << endl;
	}
	cout << "\n\n" << endl;

	vec = tree.findRange(100, 200);//right subtree
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		cout << *it << endl;
	}
	cout << "\n\n" << endl;
	vec = tree.findRange(30, 100);//left subtree
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
		cout << *it << endl;
	}
	cout << "\n\n" << endl;

	AVLTree checkTreeCopy(tree);

	cout << "testing copy constructor of original tree rightinorder size of 9:" << endl;
	cout << checkTreeCopy << endl;
	cout << checkTreeCopy.getSize() << endl;
	cout << checkTreeCopy.getHeight() << endl;

	AVLTree assignmentTree;

	assignmentTree = newTree;

	cout << "Small tree created newly and testing the assignment operator" << endl;
	cout << assignmentTree << endl;
	cout << "printing all tree nodes from low to high:" << endl;

	vector<string> vec1 = assignmentTree.findRange(0, 500);//all of it
	for (vector<string>::iterator it = vec1.begin(); it != vec1.end(); ++it) {	
		cout << *it << endl;
	}
	cout << "\n\n" << endl;

	cout << "inserting 10 in the assignment tree, checking height and size and structure" << endl;
	cout << assignmentTree.insert(10, "Ten") << endl;
	cout << assignmentTree.insert(20, "Twenty") << endl;
	cout << assignmentTree.insert(5, "Five") << endl;
	cout << assignmentTree.insert(48, "Fourty Eight") << endl;
	cout << assignmentTree.insert(93, "Ninety Three") << endl;
	cout << assignmentTree << endl;
	cout << assignmentTree.getSize() << endl;
	cout << assignmentTree.getHeight() << endl;

	cout << "reassiging assignment to original big tree of size 9: checking tree rightinorderprintstruct, size and height: " << endl;
	assignmentTree = tree;
	cout << assignmentTree << endl;
	cout << assignmentTree.getSize() << endl;
	cout << assignmentTree.getHeight() << endl;

	cout << endl;
	cout <<"Small Tree: \n";
	AVLTree smallTree;
	cout << smallTree.insert(10, "Ten") << endl;
	cout << smallTree.insert(20, "Twenty") << endl;	
	cout << smallTree.insert(5, "Five") << endl;
	cout << smallTree << endl;
	cout << smallTree.getSize() << endl;
	cout << smallTree.getHeight() << endl;	

	return 0;

}