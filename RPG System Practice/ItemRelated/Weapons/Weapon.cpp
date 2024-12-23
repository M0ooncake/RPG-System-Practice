#include "Weapon.h"



void Weapon::printDetails() const
{
    Item::printDetails();  // Call base class method
    std::cout << "|| Attack Power: " << attackPower << "\n"
            << "|| Range: " << range << "\n"
            << "|| Weapon Type: " << static_cast<int>(weaponType) << "\n";
    
}

// Function to create a weapon based on its type
Weapon Weapon::CreateWeapon(const std::string& name, int value, int weight, WeaponType weaponType)
{
    int id = itemIdCounter++;  // Increment the global item ID counter

    // Default values for attackPower and range based on weapon type
    int attackPower = 0;
    int range = 0;

    switch (weaponType)
    {
        case WeaponType::Sword:
            attackPower = 5;
            range = 5;  // Melee range
        break;
        case WeaponType::GreatSword:
            attackPower = 8;
            range = 5;
        break;
        case WeaponType::Dagger:
            attackPower = 4;
            range = 5;
        break;
        case WeaponType::Bow:
            attackPower = 15;
            range = 60;  // Long range like dnd 60ft
        break;
        case WeaponType::Crossbow:
            attackPower = 15;
            range = 40;
        break;
        case WeaponType::Spear:
            attackPower = 8;
            range = 10;
        break;
        default:
            std::cerr << "Invalid WeaponType!" << "\n";
            break;
    }

    // Create and initialize the Weapon object
    Weapon* newWeapon = new Weapon{id, name, value, weight, attackPower, range, weaponType};

    // Register the newly created weapon in the global itemRegistry
    itemRegistry[newWeapon->id] = std::unique_ptr<Item>(newWeapon);

    return *newWeapon;  // Return the newly created and registered weapon
}