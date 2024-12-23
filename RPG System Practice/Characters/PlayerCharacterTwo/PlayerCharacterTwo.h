#pragma once
#include "../Character.h"
class PlayerCharacterTwo
{
public:
    Character Stickus =
     {
        "Stickus",         // name of character
        13,                // Character level
        132.0,                // Character Experience
        Character::Rogue, // class of character
        {
            12, 10, 8,  // strength, dexterity, wisdom,
            10, 20, 24, 24 // intelligence, speed, health, maxHealth.
        },
        {} // Inventory
     };
};
