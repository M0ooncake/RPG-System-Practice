#pragma once

#include "../../Characters/Character.h"
#include "../../ItemRelated/Weapons/Weapon.h"

struct AttackAction
{
    // Core Attributes
    Character* attacker; // The character initiating the attack
    Weapon* weaponUsed;  // The weapon used for the attack
    Character* target;   // The character receiving the attack

    // Calculated Values
    int baseDamage;  // Base damage from weapon and attacker stats
    int totalDamage; // Final damage after modifiers
    bool isCritical; // Whether the attack was a critical hit


    // Contextual Info that could be useful in the future?
    int turnNumber;       // The turn when the attack occurred
    bool isCounterAttack; // Whether the action was a counterattack


    // Constructor for convenience
    AttackAction(Character* attacker, Weapon* weapon, Character* targetOfAttack)
        : attacker(attacker), weaponUsed(weapon), target(targetOfAttack),
          baseDamage(0), totalDamage(0), isCritical(false),
          turnNumber(0), isCounterAttack(false)
    {}

    void CalculateAndDealDamage()
    {
        if (!attacker || !weaponUsed || !target) return; // null check essentially
        // Divide strength by 10, hoping that if below 10, it applies a small penalty to damage. %'s are hard
        baseDamage = weaponUsed->attackPower * attacker->stats.strength / 10;
        isCritical = (rand() % 100 < 10); // 10% chance to crit :D
        // using integer based math for type safety, 
        totalDamage = baseDamage * (isCritical ? 3 : 2) / 2;
        ApplyDamageToCharacter(*target, totalDamage);

        //  Print attack details
        std::cout << "<======================================>\n";
        //  example "Alvaro has struct Yrsa for 34 points of damage!"
        std::cout << attacker->name << " has struck " << target->name << " for " << totalDamage << " points of damage!!\n";
    }
};
