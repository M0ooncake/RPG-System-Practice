#pragma once
#include "../Character.h"
class PlayerCharacterOne
{
public:
    Character Alvaro =
     {
        "Alvaro",         // name of character
        1,                // Character level
        0,                // Character Experience
        Character::Rogue, // class of character
        {
            8, 14, 12,  // strength, dexterity, wisdom,
            12, 40, 20, 20 // intelligence, speed, health, maxHealth.
        },
        {} // Inventory
     };
};
