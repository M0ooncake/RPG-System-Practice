#pragma once
#include "../Character.h"
class PlayerCharacterFour
{
public:
    Character Agnar =
     {
        "Agnar",         // name of character
        4,                // Character level
        49.0,                // Character Experience
        Character::Rogue, // class of character
        {
            10, 8, 10,  // strength, dexterity, wisdom,
            12, 15, 30, 30 // intelligence, speed, health, maxHealth.
        },
        {} // Inventory
     };
};
