#pragma once
#include "../Character.h"
class PlayerCharacterThree
{
public:
    Character Yrsa =
     {
        "Yrsa",         // name of character
        1,                // Character level
        0,                // Character Experience
        Character::Rogue, // class of character
        {
            10, 14, 12,  // strength, dexterity, wisdom,
            12, 30, 15, 15 // intelligence, speed, health, maxHealth.
        },
        {} // Inventory
     };
};
