#include "AttackAction.h"
#include "../../Characters/Character.h"
#include "../../Supportive/CombatRelated/CombatLoop.h"

void AttackAction::CalculateAndDealDamage()
{
    if (!attacker || !weaponUsed || !target) return; // null check essentially
    // Divide strength by 10, hoping that if below 10, it applies a small penalty to damage. %'s are hard
    baseDamage = weaponUsed->attackPower * attacker->stats.strength / 10;
    isCritical = (rand() % 100 < 10); // 10% chance to crit :D
    // using integer based math for type safety, 
    totalDamage = baseDamage * (isCritical ? 3 : 2) / 2;

    //  Print attack details
    //std::cout << "<======================================>\n";
    //  example "Alvaro has struct Yrsa for 34 points of damage!"
    std::cout << attacker->name << " has struck " << target->name << " for " << totalDamage << " points of damage!!\n";
    ApplyDamageToCharacter(*target, totalDamage, *activeCombat );
        
}
