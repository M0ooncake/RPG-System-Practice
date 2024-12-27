#include "TurnOrder.h"
#include "../../Characters/Character.h"

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
 * Insert a character either ahead, or in front of another character based off speed.
 * @param characterRef Reference to character to insert
 */
void TurnOrder::InsertBasedOffSpeed(Character& characterRef)
{
    Node* newNode = new Node();
    newNode->character = &characterRef;

    // Handle empty list
    if (head == nullptr)
    {
        InsertAtBeginning(characterRef);
        return;
    }

    Node* currentNode = head;
    Node* previousNode = nullptr;

    // Traverse the list to find the correct insertion point
    do
    {
        // Dereference currentNode to access character, dereference character to access stats, get stats speed.
        // If the currentNode speed is slower than the new character, we have our entry`
        if (currentNode->character->stats.speed <= characterRef.stats.speed)
            break;                       // Found the position to insert, the previous node!
        previousNode = currentNode;      // Previous node is now the node we just checked
        currentNode = currentNode->next; // Change the current node to point to the next node in the link
    }
    while (currentNode != head); // Stop when we loop back to the head

    // Insert at the beginning if faster than all others
    if (previousNode == nullptr)
    {
        InsertAtBeginning(characterRef);
    }
    else
    {
        // Insert between previousNode and currentNode
        previousNode->next = newNode;
        newNode->next = currentNode;

        // Update tail if inserting at the end
        if (currentNode == head)
            tail = newNode;
    }
}

void TurnOrder::RemoveNode(Character& characterRef)
{
    Node* temp = head;
    Node* previousNode = nullptr;
    Node* start = temp; // Keep track of the starting node
    if (head == nullptr)
    {
        std::cout << "List is empty. uh oh...\n";
        return;
    }
    
    // Check if the head node matches the character to remove
    if (temp->character->name == characterRef.name)
    {
        // Special case: Removing the head
        if (temp->next == temp) { 
            // Only one node in the list
            head = nullptr;
        } else {
            head = temp->next; // Update the head
            Node* last = temp;
            while (last->next != temp) {
                last = last->next;
            }
            last->next = head; // Update the last node's next pointer
        }
        delete temp; // Free memory
        std::cout << characterRef.name << " has been removed from the list.\n";
        return;
    }
    
    // Traverse the circular list to find the character
    do {
        previousNode = temp;
        temp = temp->next;
        if (temp->character->name == characterRef.name) {
            previousNode->next = temp->next; // Bypass the node to remove
            delete temp; // Free the memory
            std::cout << characterRef.name << " has been removed from the list.\n";
            return;
        }
    } while (temp != start); // Stop if we've looped back to the start

    std::cout << "Character " << characterRef.name << " not found in the list.\n";
}


/**
 * Prints out the list if not empty using a Do while loop.
 */
void TurnOrder::PrintList()
{
    std::cout << "<======================================>\n";
    Node* temp = head;
    if (head == nullptr)
        std::cout << "List is empty, cannot be printed\n";
    else
    {
        int index = 1;
        do
        {
            std::cout << index << ". " << temp->character->name << ".\n";
            // Dereference temp to access character, and dereference to access name.
            temp = temp->next; // Temp becomes the next node in the link
            index++;
        }
        while (temp != head); // if the data isn't the same as the start, keep going
        //std::cout << "\n";
    }
}

void TurnOrder::AdvanceTurn()
{
    // If list isn't empty
    if (head != nullptr)
    {
        head = head->next; // Move the head to the next node
        tail = tail->next; // Keep the circular connection consistent
    }
}

void TurnOrder::GetActiveTurn()
{
    std::cout << "<======================================>\n";
    std::cout << "|| " << head->character->name << "'s turn to act!!! \n";
}
