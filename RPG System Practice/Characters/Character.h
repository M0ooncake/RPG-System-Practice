#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Stats.h"
#include "../ItemRelated/Item.h"
#include "../Supportive/CombatRelated/CombatLoop.h"

//#include "../Supportive/Turns/TurnOrder.h"

/*
 * Various things a character would need to have in order to
 * exist in this.
 */
struct Character
{
    
    std::string name;
    int level;
    float experience;
    enum classType
    {
        Fighter, // Just fighting.
        Templar, // Magic and fighting.
        Rogue,   // Stealth, fighting.
        Shadow,  // Magic, stealth, fighting.
        Adapt    // Just magic
    };

    classType characterClass; // Declare a member variable of this enum type
    
    Stats stats;
    bool isNPC;
    std::vector<Item*> inventory; /* Make it a vector, so it can be expanded or
                                    shrunk without issue
                                 */
    
   
};

std::string CharacterClassToString(Character::classType classType);

void DisplayCharacter(const Character& character);

void AddItemToInventory(Character& character, const Item& item);


void RemoveItemFromInventory(Character& character, const std::string& itemName);

void DisplayCharacterInventory(const Character& character);

void DisplayCharacterWeapons(const Character& character);

void ApplyDamageToCharacter(Character& character, const int Damage, CombatLoop& combatPassToDestroy);

void ApplyHealToCharacter(const Character& character, const int Healing);

void DestroyCharacter(Character& character, CombatLoop& combatToRemoveFrom);