#include "list.h"
#include <iostream>

// Inserts node at the front of the list
Node* insertFront(Node* list, int num)
{
	// Dynamic Allocation on the heap of a Node
    Node *nd = new Node;
    nd->data = num;
    nd->next = list; // Sets new node to point to first node in the list
    
    return nd;
}

// Creates a new node
Node * createNode(int num)
{
	Node* nd = new Node;
	nd->data = num;
	nd->next = NULL;
	return nd;
}

Node* removeFront(Node *list)
{
	// Check if list is empty
	if(list == NULL)
		return NULL;
	
	Node* nxt = list->next; // Set node to be the second element in the list
	delete list;			// Delete first element
	return nxt;
}

// Can arbitrarly remove a node based on a number
Node* removeNode(Node *list, int num)
{
	Node* prev = NULL;
	Node* cur = list;

	// Check first element in list
	if(cur->data == num)
	{
		list = cur->next;
		delete cur;
		return list;
	}

	// Must track both the current and previous nodes
	prev = cur;
	cur = cur->next;
	while(cur != NULL)
	{
		if(cur->data == num)
		{
			prev->next = cur->next;
			delete cur;
			return list;
		}
		prev = cur;
		cur = cur->next;		
	}
	return list;
}

// Can detemine if a node with the data num exists
Node* findNode(Node *list, int num)
{
	while(list != NULL)
    {
        if(list->data == num)
			return list;
        list = list->next;
    }  
	return NULL;
}

// Prints list
void printList(Node *list)
{
	// Traverses each node in the list printing the data
    while(list != NULL)
    {
        std::cout << list->data << " ";
        list = list->next;
    }     
    std::cout << std::endl;
}

// Empties list by deleting all the nodes
Node* clearList(Node *list)
{
	while(list != NULL)
		list = removeFront(list);
	return list;
}

// Inserts a node at the end of the list
Node* insertBack(Node *list, int num)
{	
	// Is List Empty?
	if(list == NULL)
		return insertFront(list, num);

	
	Node* nd = createNode(num);	// Generate a node

	// Navigate to the last Node
	Node* cur = list;	
	while(cur->next != NULL)
		cur = cur->next;
	
	// Add node to the end of the list
	cur->next = nd;
	return list;
}

// Removes last node in  the list
Node * removeBack(Node* list)
{
	Node* prev = NULL;
	Node* cur = list;

	// Is list empty?
	if(list == NULL)
		return list;

	// Is there only one element in the list?
	if(list->next == NULL)
	{
		delete list;
		return NULL;
	}

	// Traverse to the end of the list
	// both the current and previous node must be
	// tracked to determine perform a proper deletion
	prev = cur;
	cur = cur->next;
	while(cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;		
	}

	// delete current
	delete cur;
	// set previous to point to NULL
	prev->next = NULL;
	
	return list;
}
