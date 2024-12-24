#pragma once
#include "../Item.h"

struct Weapon : public Item
{
    ~Weapon() override
    = default;

    int attackPower;
    int range;

    // Enum for weapon types
    enum class WeaponType
    {
        Sword,
        GreatSword,
        Dagger,
        Bow,
        Crossbow,
        Spear,
        Axe,
        GreatAxe
    };

    WeaponType weaponType;

    Weapon(int id, const std::string& name, int value, int weight, int attackPower, int range, WeaponType weaponType)
    {
        this->id = id;
        this->name = name;
        this->value = value;
        this->weight = weight;
        this->itemType = ItemType::Weapon; // Mark this as a Weapon
        this->attackPower = attackPower;
        this->range = range;
        this->weaponType = weaponType;
    }

    // Overridden printDetails function for Weapon-specific details
    void printDetails() const override;

    // Static function to create a weapon based on its type
    static Weapon CreateWeapon(const std::string& name, int value, int weight, WeaponType weaponType);
};

