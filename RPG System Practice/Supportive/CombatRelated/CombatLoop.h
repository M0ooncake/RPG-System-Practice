#pragma once
#include "AttackAction.h"
#include "../../ItemRelated/Weapons/Weapon.h"
#include "../Turns/TurnOrder.h"
#include <iostream>
#include <vector>

/*
 * What does this need. oi oi oi. this will be fking HUGE
 * We need a general do while loop. Doing combat while a bool is true.
 * We need to prompt the player with actions to do, for now it will only be attack.
 * Then, display a list of characters (enemies) that can be attacked.
 * Taking a input and then asking the player what weapon they want to attack with.
 * Then after that is done, we call the various functions necessary to complete
 * those actions.
 */
struct CombatLoop
{
    TurnOrder combatTurnOrder;  // this list will contain every character in play
    TurnOrder enemyList;        // This list will contain any enemy character that can be attacked
    TurnOrder playerList;       // This list will hold all active players to present options like healing allies
    bool isCombatActive;        // Responsible for keeping combat going
    int playerSelection;
    Character* selectedEnemy;
    
    // Constructor takes references to character lists and initializes the combat loop.
    CombatLoop(const std::vector<Character*>& allCharacters, 
               const std::vector<Character*>& enemies, 
               const std::vector<Character*>& players) 
        : isCombatActive(true)
    {
        // Populate combatTurnOrder with all characters.
        for (Character* character : allCharacters)
        {
            combatTurnOrder.InsertBasedOffSpeed(*character);
        }

        // Populate enemyList with enemies.
        for (Character* enemy : enemies)
        {
            enemyList.InsertAtEnd(*enemy);
        }

        // Populate playerList with players.
        for (Character* player : players)
        {
            playerList.InsertAtEnd(*player);
        }
    }

    void MainLoop()
    {
        do
        {
            //Firstly show active enemies
            PrintEnemyCharacters(); 

            // Print out the active player's turn
            combatTurnOrder.GetActiveTurn();

            PresentPlayerOptions();
            
            
        }
        while (isCombatActive == true);
    }

    
    /**
     * Simply prints out the enemyList with some visual formatting.
     */
    void PrintEnemyCharacters()
    {
        std::cout << "<======================================>\n";
        std::cout << "|| Active enemies on the field!\n";
        enemyList.PrintList();
        
    }

    /**
     * Present the player with options to take and receive input.
     */
    void PresentPlayerOptions()
    {
        playerSelection = 0; // Reset the players selection upon call
        std::cout << "<======================================>\n";
        std::cout << "|| Select Desired Action\n"
                    << "|| 1. Attack \n";
        std::cin >> playerSelection;

        switch (playerSelection)
        {
            case 1:
                SelectEnemyTarget();
                break;
            default:
                std::cout << "Invalid entry, ";
                PresentPlayerOptions(); // Recall if they didn't pick a valid target
        }
    }

    
    void SelectEnemyTarget()
    {
        playerSelection = 0; // Reset the players selection upon call
        std::cout << "<======================================>\n";
        std::cout << "|| Select Enemy Target! \n";
        enemyList.PrintList(); // Show available targets
        
        std::cin >> playerSelection;    // take input

        // Validate input and get the target
        Node* temp = enemyList.head;
        int index = 1;
        selectedEnemy = nullptr;    //  Initialize to null

        // Traverse the list to acquire target.
        // While temp isn't null, and our index is less than player selection,
        // That means we need to go deeper to find what we are looking for.
        while (temp != nullptr && index <= playerSelection)
        {
            if (index == playerSelection)
            {
                selectedEnemy = temp->character; // Target acquired
                break;  // bail out
            }
            temp = temp->next;  // Change the temp Node* to be the next to look there.
            index++;    // increase our index to show we've searched one
        }

        if (selectedEnemy)
        {
            std::cout << "You have selected " << selectedEnemy->name << " as the target!\n";
            GetAttackWeapon();
        }
        else
        {
            std::cout << "Invalid selection, enter a choice again. \n";
            SelectEnemyTarget(); // Retry for valid input
        }
        
    }
    Weapon* SelectWeaponFromInventory(Character& character)
    {
        DisplayCharacterWeapons(character);
        std::cout << "<======================================>\n";
        // Check if the inventory is empty
        if (character.inventory.empty())
        {
            std::cout << "No weapons available to select.\n";
            return nullptr;
        }

        // Get player input
        unsigned int selectedIndex; // cant be negative
        std::cout << "Select a weapon to attack with (enter the number): ";
        std::cin >> selectedIndex;

        // Validate input
        if (selectedIndex == 0 || selectedIndex > character.inventory.size())
        {
            std::cout << "Invalid selection. Please try again.\n";
            return nullptr;
        }

        // Check if selected item is a weapon
        auto& selectedItem = character.inventory[selectedIndex - 1];    // changed to auto instead of Item&
        std::cout << "You selected item: " << selectedItem.name << "\n";  // Debugging line, which triggers fine, selection works
        // if you try to select the book in slot 2 this triggers. which makes sense. So selection is a weapon
        if (selectedItem.itemType != Item::ItemType::Weapon)
        {
            std::cout << "Selected item is not a weapon. Please select a valid weapon.\n";
            return nullptr;
        }
        
        /* Cast to Weapon* and return
         * Something has to be wrong with this... it just doesn't work as it should. it seems like its always returning
         * a nullptr. But why? I'm going to try dynamic casting before returning.
         * return dynamic_cast<Weapon*>(&selectedItem); // old code
         * if (auto weapon = dynamic_cast<Weapon*>(seekItem.get())) this code snipped is used in main. im going to adapt it
         */
        std::cout << dynamic_cast<Weapon*>(&selectedItem) << "\n"; // lol see what this does. Probs a memory address?
        // indeed, it yields 00000000000000. So the dynamic cast doesn't work. But why? I dynamic-cast this same thing
        // elsewhere and it works fine.
        return dynamic_cast<Weapon*>(&selectedItem); // adding breakpoint
    }
    /**
     * This function should get the head of the turn order and print options for what weapon
     * to attack with, then attack
     */
    void GetAttackWeapon()
    {
        Node* characterNode = combatTurnOrder.head;
        if (!characterNode) // null check
        {
            std::cout << "No active character in turn order.\n";
            return;
        }

        Character* characterActive = characterNode->character;
        if (!characterActive) // double check null
        {
            std::cout << "Active character is null.\n";
            return;
        }

        // Loop until the player selects a valid weapon
        // Dear lord something is FUCKED real good.
        // I have gotten lost in the sauce of pointers real bad. 
        Weapon* selectedWeapon = nullptr;   
        while (!selectedWeapon)
        {
            selectedWeapon = SelectWeaponFromInventory(*characterActive);
            if (selectedWeapon == nullptr)
            {
                std::cout << "selectedWeapon nullptr triggered.\n";
               
            }
            else break;
        }
        
        std::cout << characterActive->name << " selected " << selectedWeapon->name << " to attack with.\n";

        
        AttackAction attackAction(characterActive, selectedWeapon, selectedEnemy);  // Initialize attack
        attackAction.CalculateAndDealDamage();  // Perform the attack!
           
    }
    
        
    
};
