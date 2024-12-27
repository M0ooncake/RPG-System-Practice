#pragma once
#include <iostream>

struct Character; // forward delcoration

/**
 * As this file currently stands, the data entered into a Node is an int. I am going to
 * try and change that to a character reference and see how that goes.
 */
struct Node
{
    Character* character;   // Not sure how I'll use this yet. Likely a place in the list corresponding to a characters position.
    Node* next; // Next item in the list, i.e. Next characters turn
};


/**
 * Single linked Circular list to handle turn based combat.
 * Being Single linked ensures the turn order can never be reversed.
 */
class TurnOrder
{
public:
    Node* head; //  Start of the list
    Node* tail; // End of the list

    
    TurnOrder();

    // Insert a node at the start
    void InsertAtBeginning(Character& characterRef);

    // Insert a node at the end
    void InsertAtEnd(Character& characterRef);

    // Logic to insert a character either ahead, or in front of another character
    void InsertBasedOffSpeed(Character& characterRef);

    // remove a node, like a character dying
    void RemoveNode(Character& characterRef);
    // Print the existing Circular list
    void PrintList();

    // Logic to point to the next entry in the list
    void AdvanceTurn();

    void GetActiveTurn();
};