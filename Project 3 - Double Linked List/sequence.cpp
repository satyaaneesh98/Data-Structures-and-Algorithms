//----------------------------------------------------
/* Project Description: 
Here we are using an doubly-linked list structure to create an array like list which can be useful to do dynamic insert
and delete/removal of elements. Using class sequence and sequence node the doubly-linked list is created when each function is called, the
objects in class sequence are created and based on function calling, the nodes with its element values are either inserted, deleted or queried.
To ensure that the insert and removal works fine we are using error handling, where we use exception to ensure that the access of elements is 
not wrong. try, catch are used to see the exceptions generated while passing invalid arguments or values. All the values that are inserted will
create as a node in the heap and we use the destructor to delete the nodes in heap to avoid memory leaks. All the values inserted are created 
in form of chain in the heap connecting to and fro, and object in stack is connected to head and tail of this link thus allowing us for
dynamic insertion or removal at any position of the link.

This project contains three files. sequnce.h is the header file given by the professor which contains the
classes, functions declarations, its purposes saying what each function should do and attributes declarations.
sequence.cpp file contains the function definitions or implementation, the functions that should be used are listed by the professor,
we need to write the code or define the functions so their usage works well when called in the main program.
project3TestHarness.cpp is the mainprogram file written and shared by professor, once all our function definitions are correct and tested,
we will run the main harness file and ensure everything is working properly.*/
//------------------------------------------------------


#include "Sequence.h" //Header file where all the methods and class are declared which are required for creating this Doubly-linked list

//Function: Sequence -- Constructor to create the objects in Sequence class. Initializes member variables head,
//                      tail to nullptr and number of elements(numElts) to zero, when just object is created.
//                      This constructor creates nodes based on size passed and links to each other by initialising all values in nodes to 
//                      zero. When a node is created, it connects to next and previous(prev)nodes thus having 2 ways to query value or element.
//returns:  There are no return values, as we explicitly didnot define it. It just creates the nodes and stores elements in the heap
//          connecting to object.
//Inputs:   sz(unsigned int) -- This is size defined to create an object with, where size is equal to number of elements the object contains.
//                Creates an empty object with its head and tail pointing to Nullptr when size is zero.
//                If size is greater than zero, creates nodes with equals size in the object pointing to elements node in heap. Values are
//                stored in each node.
//Local variables: newNodePtr -- Pointer to a newly created node (SequenceNode object).
//                               This can be used to access and link the nodes when dynamically created.
Sequence::Sequence(size_type sz) : head(nullptr), tail(nullptr), numElts(0)
{
    //Creates new nodes until number of elements matches the size passed to create object with.
    //Each node is created in heap and connected to and fro, with object pointing to head and tail of the chain/linkedlist.
    while (numElts < sz)
    {
        SequenceNode *newNodePtr = new SequenceNode(value_type()); /*Creates a new node/SequenceNode object in heap with value zero.
                                                                    And initializes the next and prev variables to nullptr and is pointed
                                                                    by newNodePtr*/
        //Links the object to the first newly created node if head is nullptr if initally size is zero of created object or list is empty.
        if ((head == nullptr) && (numElts == 0))
        {
            head = newNodePtr; //Objects points to newly created node and make this node as head.
            tail = newNodePtr; //Objects points to newly created node and make this node as tail.
        }

        //If Sequence object already have nodes/SequenceNode objects, and pointed either as head or tail,
        //then link the new nodes with the previous nodes using the tail.
        //We use tail to link the newly created nodes/SequenceNode objects. Head will always point to the first node in heap.
        //All new ones are mapped as tail and previous ones are just linked to each other.
        else
        {
            tail->next = newNodePtr; //Points the last node(tail) to the newly created node using newNodePtr.
            newNodePtr->prev = tail; //Connects the newly created node to last node of the linkedlist using prev.
            tail = newNodePtr; //Updates the newly created SequenceNode object as the tail of the structure.
        }
        numElts = numElts + 1; //Used to keep track of how many elements or nodes are created in the class Sequence object.
    }
}


//Function:   Sequence -- This is a copy constructor used to copy the objects of the Class Sequence S(keep this as constant)
//                        into the new object created in this method.
//                        Creates a new object and initializes the member variables head, tail to nullptr and numElts(unsigned int) to zero.
//Parameters: s --        s is the object of class Sequence from where the data has to be copied. &s is used to refer to that object.
//& - pass by reference - &s is passed by reference given in the main logic.
//return:                 There is no return defined explicitly.
//Local variables: copyPtr --   Points to head node/ 1st element of list of the object from where data to be copied.
//                                           newNodePtr --Pointer to a newly created node(SequenceNode object).
Sequence::Sequence(const Sequence &s) : head(nullptr), tail(nullptr), numElts(0)
{
    SequenceNode *copyPtr = s.head; //creates and points copyPtr to head of referenced object

    //Executes when the referenced object head points to some node or element in list other than empty/nullptr.
    while (!(copyPtr == nullptr))
    {
        //new node with taking input as the element(value) that copyPtr points to. This is pointed by new created pointer newNodePtr
        SequenceNode *newNodePtr = new SequenceNode(copyPtr->elt); 

        //Executes and links the new nodes to each other when there is more than 1 element/node in the object.
        if (!(numElts == 0))
        {
            tail->next = newNodePtr; //Points the last node(next/tail) to the newly created node using newNodePtr.
            newNodePtr->prev = tail; //Connects the newly created node(prev) to last node(tail/next) of the linkedlist using prev.
            tail = newNodePtr; //Updates the newly created SequenceNode object as the tail of the structure.
        }

        //Executes when a new node is the first node in the copy construtor object means when the object initially has zero elements in it.
        //Head and tail of object are pointed to this new node.
        else
        {
            head = newNodePtr; //Make this node as list head of object.
            tail = newNodePtr; //Make this node as list tail of object
        }
        numElts = numElts + 1; //Updates number of nodes/list size created in the object.
        copyPtr = copyPtr->next; //Iterates or moves the position to other nodes one by one in the referenced(&s) object list.
    }
}


//Funtion: ~Sequence -- Destructor used to destroy the objects when they run out of scope, this used to avoid potential memory leak.
//                      If ignored, pointers can be used to access the elements in heap and causes potential issues.
//returns: there is no expilcit return defined, as we just delete the nodes in heap and makes the object back to nullptr and deletes objects.
Sequence::~Sequence()
{
    //Calls the function clear, the code or the logic for destroying the objects and its dynamic allocation is defined in the clear method.
    clear();
}


//Function: operator= -- Here we use this operator initally to clear the current sequence and then we replace it with copy of
//                       of the referenced sequence  object, the referenced object is kept constant and using asisgnment operator(=) the
//                       values from the  referenced object is copied to this* object. In our harness code, data2 = data1, means data1 sequence is copied
//                       into data2 object using =operator.
//parameters: s--        the sequence object to be copied into this* object.
//& - pass by reference - &s is passed by reference given in the main logic.
//return: *this(integer) -- return the object of the current copied sequence.
//Local variables(SequenceNode Constructor): currentPtr -- points to the head of referenced object.
Sequence &Sequence::operator=(const Sequence &s)
{
    clear(); // we are deleting all the nodes/elements in the object if there are any present.
    SequenceNode *currentPtr = s.head; //creates and points the pointer to head of referenced object.

    //When the pointer pointing to the referenced object is not nullptr and iterates through all elements in list
    //until reached tail where next is nullptr.
    while (!(currentPtr == nullptr))
    {
        push_back(currentPtr->elt); // calling push back function which inserts node with the passed value pointed to referenced object.
        currentPtr = currentPtr->next; //points to next node which is being pointed from current node. 
    }
    return *this;
}

//Function: operator[] -- Position or index operator that is used to identify SequenceNode object in list and return the value in that postion.
//                        This is also used to verify if that index/positioned element or item is present in the list or not & throws exception.
//Parameter: position(unsigned int) -- argument that is passed to verify if position is valid or not and return the value of item at that place
//return: currentPtr->elt(integer) -- gives the value in the item in the queried position in the sequence list.
//Local variables: currentPtr -- points to the list head of the object and gets iterated through items list and positions to the current node
//                               we are at                    
Sequence::value_type &Sequence::operator[](size_type position)
{
    //Throws exeception when queried place is below zero or greater than or equal to number of elements.
    if (numElts <= position || position < 0)
    {
        throw out_of_range("Passed position value is not present in the linked list index size's");
    }

    //Executes when the queried position is valid(i.e., from zero to (number of elements-1))
    SequenceNode *currentPtr = head; //creates and places pointer to head of the object list sequence.

    //Executes when the pointer is not pointing to nullptr, means the object has atleast one node in it.
    if (!(currentPtr == nullptr))
    {
        //Iterates through the list of items until it reaches the queried position
        for (size_type listIndex = 0; listIndex < position; listIndex++)
        {
            currentPtr = currentPtr->next; //Used to move pointer to next item
        }
        return currentPtr->elt;
    }
}


//Function: push_back -- Used to insert a new node/item at the end of the list/sequence only with given value.
//                       And updates the tail of the object to this newly created node in the sequence list.
//& - pass by reference. Here the value is kept constant so wont be modified and refers to passed value.
//Parameters: value(integer) -- takes the integer passed when function is called and places the value into the node/item.
//return: no return is needed, it is void, as we just want to insert the nodes/values in the items by creating at the end.
//Local variable: newNodePtr -- pointer that points to the new dynamically created node.
void Sequence::push_back(const value_type &value)
{
    //creates a new node in heap with passed value(integer) as a data element and gets accessed by pointer newNodePtr.

    SequenceNode *newNodePtr = new SequenceNode(value);

    //Executes when the object has more than 1 item or node created in it. Links the new node at the end, points to previous and updates
    //this to tail of object.
    if (!(numElts == 0))
    {
        newNodePtr->prev = tail; //connects the new node(prev) to previous node(tail of object).
        tail->next = newNodePtr; //links the previous node(tail of object - next) to the new node
        tail = newNodePtr; //updates this new node as tail of object.
    }

    //Executes if the object has an empty list and points the object to the new objects and make this node as head and tail of object.
    else
    {
        head = newNodePtr;
        tail = newNodePtr;
    }
    numElts = numElts + 1; //Updates the number of elements created in the object, which is size of sequence list.
}


//Function: pop_back() -- This is used to remove the item/node/last element from the list and update the object's head & tail and size of list.
//                        Throws exception if size of object or sequence list is empty.
//return -- no return as it is void.
//Local variables:
/* currentPtr -- Points head as current node, using this specifically if list has only only 1 item or node in it.
   deletingNodePtr -- pointer that is used to keep track of the node that needs to be deleted.
   prevNode -- pointer that is used to point to the previous node of tail item and then use this to update it as tail item.
*/
void Sequence::pop_back()
{
    //Throws exeception if size of object is zero or list is empty.
    if (numElts == 0)
    {
        throw out_of_range("The last element or node in list we are trying to delete is not possible as list is empty");
    }

    //Executes if list has 1 or more elements
    else
    {
        SequenceNode *currentPtr = head; //creates and points the currentPtr to the head node of the object.
        
        //Delete the current node if the node next points to nullptr which means the object has only one node/item in it.
        if (currentPtr->next == nullptr)
        {
            delete currentPtr; //delete current pointing node
            head = nullptr; //update head of object as nullptr means the object has no list.
            tail = nullptr; //update head of object as nullptr means the object has no list.
            numElts = 0; //marks list size as zero.
        }

        //Delete the tail item/node when there are more than 1 nodes in the sequence list.
        else
        {
            SequenceNode *deletingNodePtr = tail; //creating pointer and pointing it to tail
            SequenceNode *prevNode;               //creating the pointer
            prevNode = deletingNodePtr->prev;     //points the prevNode pointer to node before the tail item(prev).
            delete deletingNodePtr;               //delete the tail node
            prevNode->next = nullptr;             //updates the previous node has no next node and end of chain.
            tail = prevNode;                      //update the tail is now previous node
            numElts = numElts - 1;                //update count of list when function is called.
        }
    }
}

//function: insert -- Creates a new node with passed value(data element) and inserts in the passed position.
//                    Insert throws error when the passed parameters are not valid.
//return: there is no return as it is void.
//Parameters: position(unsigned int) -- defines the index place or list position where the node or value has to be inserted.
//            value(integer) -- the integer value to be inserted in that node.
//local variables: currentPtr -- pointer to point the currentNode we are accessing or pointing to.
//                 newNodePtr -- pointer to point to the newly created node
void Sequence::insert(size_type position, value_type value)
{
    //Throws exeception if position to insert the value/node is not between zero or size-1.
    if (position < 0 || position > numElts)
    {
        throw out_of_range("Position passed to insert value is either below or greater than Linked list size(No. of Elements)");
    }

    //Inserts the value of item at position zero.
    else if (position == 0)
    {
        SequenceNode *currentPtr = head; //creates and points the currentPtr to head of object
        SequenceNode *newNodePtr = new SequenceNode(value); //creates new node with passed value and gets pointed by newNodePtr
        newNodePtr->next = currentPtr; //connects the new inserted node(next) to the head item of object
        currentPtr->prev = newNodePtr; //connects the head item to the new inserted node(next).
        head = newNodePtr; //updates the new node is now head of object.
    }
    
    //executes if position is greater than zero and less than number of items in list.
    else if ((position > 0 && position < numElts))
    {
        SequenceNode *currentPtr = head; //creates and points currentPtr pointer to head of object

        //moves the pointer till it identifies the index where the node has to be inserted
        for (size_type listIndex = 0; listIndex < position; listIndex++)
        {
            currentPtr = currentPtr->next;
        }
        SequenceNode *newNodePtr = new SequenceNode(value); //creates a new node with passed value and gets identified by newNodePtr.
        newNodePtr->next = currentPtr; //links the new node(next) to the currentPtr node(position place node)
        newNodePtr->prev = currentPtr->prev; //links the new node(prev) to the previous node of currentPtr node. 
        currentPtr->prev->next = newNodePtr; //links the previous node of currentPtr to the new node(next)
        currentPtr->prev = newNodePtr; //connects the currentPtr(prev) to the new node.
    }

    //If the insertion position is at the tail position of the sequence list.
    else
    {
        push_back(value); //Called the push_back function to insert the value in the last of list and update this new insert as tail of object
    }
    numElts = numElts + 1; //since inserting we increase the size of list by 1 everytime it is called.
}


//Function: front -- used to query the value of the item present in the top of the list or front of the list and since its const its read only
//                   will throw error if there are no items in list or list is empty.
//return: head->elt(integer) -- returns the value present in the head node and kept constant.
const Sequence::value_type &Sequence::front() const
{
    //throws error if size is zero or list is empty
    if (numElts == 0)
    {
        throw out_of_range("Query of first or head element is failed as linkedlist size is zero");
    }
    return head->elt;
}


//Function: back -- used to query the value of the item present in the bottom of the list or rear of the list and since its const its read only
//                   will throw error if there are no items in list or list is empty.
//return: tail->elt(integer) -- returns the value present in the tail node of the object and kept constant.
const Sequence::value_type &Sequence::back() const
{
    //throws error if size is zero or list is empty
    if (numElts == 0)
    {
        throw out_of_range("Query of last or tail element is failed as linkedlist size is zero");
    }
    return tail->elt;
}


//Function: empty -- Checks the sequence object list size if its empty or not and returns boolean values.
//return -- boolean -- true if the list is having zero elements
//                     false if there are elements
//                     here this function ensures that nothing is modified by saying const
bool Sequence::empty() const
{
    //checks if number of elements in the object is zero or not.
    if (numElts == 0)
    {
        return true;
    }
    else
        return false;
}


//Function: size -- to know the size of the list or number of elements or nodes present.
//return: numElts(unsigned int) -- number of elements present in the object list and wont modify the values when called
Sequence::size_type Sequence::size() const
{
    return numElts;
}


//Function: clear -- used to clear all the nodes in the list and also memory allocated due to dynamic allocation.
//return: no return since its void.
//local variable: ptrToRemoveNode -- points to the node which we are deleting, traverses until the end of the list or node(next) is nullptr
//                nextNodePtr -- points to the next node of the node we are deleting. As we delete in forward manner, we store the memory address
//                               of upcoming node in this pointer and updates it to the deleting pointer.
void Sequence::clear()
{
    //runs when list has elements and not empty list
    while (!(size() == 0))
    {
        SequenceNode *ptrToRemoveNode = head; //points to the head of object

        //run only if the object has elements and head of object is not nullptr
        while (!(ptrToRemoveNode == nullptr))
        {
            SequenceNode *nextNodePtr = ptrToRemoveNode->next; //points to the next node we are going to delete after.
            delete ptrToRemoveNode; //delete current pointing node
            ptrToRemoveNode = nextNodePtr; //update the memory of address of next node to be deleted into the pointer that has to delete current node
            numElts = numElts - 1; //decrease the list size by one each time funtion is called.
        }
    }
}


//Function: erase -- delete the node or items from the list from passed position until the defined count of nodes to be removed.
//                   throws error is position to delete is out of bounds or total no. of nodes to be removed is not valid.
//                   update the size after deletion and move the remaining nodes to forward indexes.
// return: void there is no return
// Parameters: posiiton(unsigned int) -- index from where the nodes has to be removed
//             count(unsigned int) -- no. of nodes to be removed
//Local variables: ptrToRemoveNode -- points to the node which has to be removed from until count.
void Sequence::erase(size_type position, size_type count)
{
    //throws exception
    if (position < 0 || position + count > numElts)
    {
        throw out_of_range("Position is invalid or total count of elements to be deleted is not possible. Hence, erase failed.");
    }

    //iterates until passed number of nodes gets deleted.
    for (size_type i = 0; i < count; i++)
    {
        SequenceNode *ptrToRemoveNode = head; //points to head node of object
        if (!(ptrToRemoveNode == nullptr))    //runs only if object has elements in it.
        {
            //iterates until the pointer is moved to position from which the nodes has to be deleted
            for (size_type listIndex = 0; listIndex < position; listIndex++)
            {
                ptrToRemoveNode = ptrToRemoveNode->next;
            }
            if (!(ptrToRemoveNode->prev == nullptr)) //if current pointing node(prev) is not nullptr, means when its not head node.
            {
                ptrToRemoveNode->prev->next = ptrToRemoveNode->next; //points the previous node(next) to next node of current node
            }
            if (!(ptrToRemoveNode->next == nullptr)) //if current node is not tail node
            {
                ptrToRemoveNode->next->prev = ptrToRemoveNode->prev; //pointsthe nextnode(prev) to previous node of currentnode
            }
            if (ptrToRemoveNode->prev == nullptr) //runs when the pointer is at the head node of object
            {
                head = ptrToRemoveNode->next; //moves object head to second node of the list
            }
            if (ptrToRemoveNode->next == nullptr) //runs when the pointer is at tail node
            {
                tail = ptrToRemoveNode->prev; //makes tail of object as the previous node of current node.
            }
            delete ptrToRemoveNode; //remove the current pointing node
            numElts = numElts - 1; //decrease the count of list by 1 each time the function is called(executes equal to count number of values)
        }
    }
}


//Function: print -- prints the values present in each node of the sequnece class object linkedlist. Const ensures that object is not modifiable
//return : void and no return is expected. 
//local variable: currentPtr -- points to the current node we are trying to retrieve the value of item.
//ostream - output stream to perform output operations
//& - passby refernce
// Parameter: os - means the function can modify the "output" stream directly
void Sequence::print(ostream &os) const
{
    SequenceNode *currentPtr = head; //points the currentPtr to head of object

    //run and print only if the object has list therefore head points to atleast one node
    if (!(currentPtr == nullptr))
    {
        os << "<";

        //print the values from head to tail
        for (size_type listIndex = 0; listIndex < numElts; listIndex++)
        {
            os << currentPtr->elt; //gives the value present in the node where the currenPtr is pointing to

            //using this condition just to satisfy the ouput match, when the pointer reaches tail, the next has nullptr and wont print ","
            if (!(currentPtr->next == nullptr))
            {
                os << ", ";
            }
            currentPtr = currentPtr->next; //updates the pointer to next node.
        }
        os << ">" << endl;
    }
}


// Function: overloaded operator<< -- used for creating custom output of sequence class object and const ensures the referenced object s is not changed
// Parameters:
// ostream - output stream to perform output operations
// &s - passby reference to object s
ostream &operator<<(ostream &os, const Sequence &s)
{
    s.print(os); //calls print method for object s.
    return os; //returns the output
}