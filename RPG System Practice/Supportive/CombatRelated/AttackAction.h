#pragma once
struct Character; // Forward declaration ?
struct CombatLoop;

#include "../../ItemRelated/Weapons/Weapon.h"


struct AttackAction
{
    // Core Attributes
    Character* attacker; // The character initiating the attack
    Weapon* weaponUsed;  // The weapon used for the attack
    Character* target;   // The character receiving the attack
    CombatLoop* activeCombat;
    // Calculated Values
    int baseDamage;  // Base damage from weapon and attacker stats
    int totalDamage; // Final damage after modifiers
    bool isCritical; // Whether the attack was a critical hit


    // Contextual Info that could be useful in the future?
    int turnNumber;       // The turn when the attack occurred
    bool isCounterAttack; // Whether the action was a counterattack
    

    // Constructor for convenience
    AttackAction(Character* attacker, Weapon* weapon, Character* targetOfAttack, CombatLoop* activeCombat)
        : attacker(attacker), weaponUsed(weapon), target(targetOfAttack),
          activeCombat(), baseDamage(0), totalDamage(0),
          isCritical(false), turnNumber(0), isCounterAttack(false)
    {
         this->activeCombat = activeCombat;
    }

    void CalculateAndDealDamage();
};
