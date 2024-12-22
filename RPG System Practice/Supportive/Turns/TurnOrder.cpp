#include "TurnOrder.h"




/**
 * Constructor to make sure it initializes first
 */
TurnOrder::TurnOrder()
{
    head = nullptr;
    tail = nullptr;
}


/**
 * Adds a node at the beginning of the circular list.
 * @param characterRef A reference to the character to be entered in the list
 */
void TurnOrder::InsertAtBeginning(Character& characterRef)
{
    Node* newNode = new Node();
    newNode->character = &characterRef; // Get the data from the node, and insert the data we just got given
    // if it's the first entry, set up the circle.
    if (head == nullptr)
    {
        head = newNode;       // Place new node at start of list,
        tail = newNode;       // Place new node at end of list,
        newNode->next = head; // Declare the next node in the list is the head. Establishing a circle.
    }
    else
    {
        newNode->next = head; // set the new nodes next link to be the head,
        head = newNode;       // Set the head equal to the newly created node,
        tail->next = head;    // set the tails next link to be the newly made head.
    }
}

/**
 * Adds a node at the end of the circular list.
 * @param characterRef A reference to the character to be entered in the list
 */
void TurnOrder::InsertAtEnd(Character& characterRef)
{
    Node* newNode = new Node();
    newNode->character = &characterRef; // Get the data from the node, and insert the data we just got given
    // if it's the first entry, set up the circle.
    if (tail == nullptr)
    {
        head = newNode;       // Place new node at start of list,
        tail = newNode;       // Place new node at end of list,
        newNode->next = head; // Declare the next node in the list is the head. Establishing a circle.
    }
    else
    {
        tail->next = newNode; // set the new nodes next link to be the tail,
        tail = newNode;       // Set the tail equal to the newly created node,
        tail->next = head;    // set the tails next link to be the existing head.
    }
}


/**
 * Prints out the list if not empty using a Do while loop.
 */
void TurnOrder::PrintList()
{
    Node* temp = head;
    if (head == nullptr)
        std::cout << "List is empty, cannot be printed\n";
    else
    {
        do
        {
            std::cout << temp->character->name << " "; // Dereference temp to access character, and dereference to access name.
            temp = temp->next;  // Temp becomes the next node in the link
        }
        while (temp != head); // if the data isn't the same as the start, keep going
        std::cout << "\n";
    }
}

void TurnOrder::AdvanceTurn()
{
    
}


