#pragma once
#include "AttackAction.h"
#include "../../ItemRelated/Weapons/Weapon.h"

#include "../Turns/TurnOrder.h"
#include <iostream>
#include <thread>
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
    std::vector<Character*> players;
    bool isCombatActive;        // Responsible for keeping combat going
    int playerSelection;
    Character* selectedEnemy;
    
    // Constructor takes references to character lists and initializes the combat loop.
    CombatLoop(const std::vector<Character*>& allCharacters, 
               const std::vector<Character*>& enemies, 
               const std::vector<Character*>& players)
        : players(players), isCombatActive(true)
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
            if (combatTurnOrder.head == nullptr)
                std::cout << "Their dead, handle this outcome \n"; 
            //Firstly show active enemies
            PrintEnemyCharacters(); 

            // Print out the active player's turn
            combatTurnOrder.GetActiveTurn();

            Node* currentCharacter = combatTurnOrder.head;
            if (currentCharacter->character->isNPC == true)
            {
                
                SelectRandomPlayer();
                
                
            }
            else
            {
                PresentPlayerOptions();
                
            }

            std::cout << "Advancing to the next turn...\n";
            
            combatTurnOrder.AdvanceTurn();
        }
        while (isCombatActive == true);
    }

    
    /**
     * Simply prints out the enemyList with some visual formatting.
     */
    void PrintEnemyCharacters()
    {
        //std::cout << "<======================================>\n";
        std::cout << "<====> Active enemies on the field! <====>\n";
        //std::cout << "|| Active enemies on the field!\n";
        enemyList.PrintList();
        
    }

    /**
     * Present the player with options to take and receive input.
     */
    void PresentPlayerOptions()
    {
        /*Node* currentCharacter = combatTurnOrder.head;
        if (currentCharacter->character->isNPC == true)
        {
            SelectRandomPlayer();
            GameDelay(2);
            return;
        }*/
        
        playerSelection = 0; // Reset the players selection upon call
        std::cout << "<======================================>\n";
        std::cout << "|| Select Desired Action\n"
                    << "|| 1. Attack \n";
        std::cout << "---> ";
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

        std::cout << "---> ";
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

        if (character.isNPC == true)
        {
            return dynamic_cast<Weapon*>(character.inventory[0]); // Attack with the first item in the inventory
        }
        
        DisplayCharacterWeapons(character);
        std::cout << "<======================================>\n";
        // Check if the inventory is empty
        if (character.inventory.empty())
        {
            std::cout << "No weapons available to select.\n";
            SelectWeaponFromInventory(character);
            return nullptr;
        }

        // Get player input
        unsigned int selectedIndex; // cant be negative
        std::cout << "Select a weapon to attack with (enter the number): ";
        std::cout << "---> ";
        std::cin >> selectedIndex;

        // Validate input
        if (selectedIndex == 0 || selectedIndex > character.inventory.size())
        {
            std::cout << "Invalid selection. Please try again.\n";
            return nullptr;
        }

        // Check if selected item is a weapon
        Item* selectedItem = character.inventory[selectedIndex - 1];   
        
        //std::cout << "You selected item: " << selectedItem->name << "\n";  
        
       
        //selectedItem->printDetails();
        
        if (selectedItem->itemType != Item::ItemType::Weapon)
        {
            std::cout << "Selected item is not a weapon. Please select a valid weapon.\n";
            return nullptr;
        }

        Weapon* chosenWeapon = dynamic_cast<Weapon*>(selectedItem);

        
        
        return dynamic_cast<Weapon*>(selectedItem); // adding breakpoint
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
        
        //std::cout << characterActive->name << " selected " << selectedWeapon->name << " to attack with.\n";

        
        AttackAction attackAction(characterActive, selectedWeapon, selectedEnemy);  // Initialize attack
        attackAction.CalculateAndDealDamage();  // Perform the attack!
        
    }

    
    void SelectRandomPlayer()
    {
        // going to try and quickly add some logic for an enemy turn player turn switcher
        if(players.empty()) return;
        Character* NPC = combatTurnOrder.head->character;
        // Check if the current turn character is in the enemy list
        
        int enemySelection = rand() % players.size();
        Weapon* NPCWeapon = SelectWeaponFromInventory(*NPC);
        Character* NPCTarget = players[enemySelection];
        
        
        std::cout << NPC->name << " is about to strike " << NPCTarget->name << " with a " << NPCWeapon->name << "!!!\n";
        
        
        AttackAction attackAction(NPC, NPCWeapon, NPCTarget); // mayhaps work??? UwU?
       
        attackAction.CalculateAndDealDamage();
        
    }

    void GameDelay(int seconds)
    {
        //std::this_thread::sleep_for(std::chrono::seconds(seconds)); // pause for X seconds to allow player to read
    }

    
};
