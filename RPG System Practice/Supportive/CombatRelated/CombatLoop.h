#pragma once
#include "../../ItemRelated/Weapons/Weapon.h"


#include "../Turns/TurnOrder.h"
#include <iostream>
#include <thread>
#include <vector>

struct Character; 

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
            //character = this ; // will this work? gulp
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

    void MainLoop();


    /**
     * Simply prints out the enemyList with some visual formatting.
     */
    void PrintEnemyCharacters();

    /**
     * Present the player with options to take and receive input.
     */
    void PresentPlayerOptions();


    void SelectEnemyTarget();

    Weapon* SelectWeaponFromInventory(Character& character);

    /**
     * This function should get the head of the turn order and print options for what weapon
     * to attack with, then attack
     */
    void GetAttackWeapon();


    void SelectRandomPlayer();

    void GameDelay(int seconds)
    {
        //std::this_thread::sleep_for(std::chrono::seconds(seconds)); // pause for X seconds to allow player to read
    }

    void RemoveCharacterFromPlay(Character& characterToRemove);

    void searchForCharacterToRemove(TurnOrder& list, Character& characterToRemove);
};
