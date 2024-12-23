#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

/*
 *  Common things that any item would need to have
 *  Like Identifiers.
 *  I don't think it makes sense to have attributes like healing,
 *  damage, that sort of thing in the base struct. That to me
 *  makes more sense to have in a child.
 */

struct Item
{
    enum class ItemType
    {
        Weapon,
        Consumable,
        Armor,
        Misc
    };
    
    std::string name;
    int value;
    int weight;
    int id;

    ItemType itemType;  // Tag to differentiate item types

    virtual void printDetails() const;

    virtual ~Item();  // Virtual destructor for polymorphic deletion
};

// A Global registry for all items
extern std::unordered_map<int, std::unique_ptr<Item>> itemRegistry;

extern int itemIdCounter; // Counter for Unique ID's

std::string ItemTypeToString(Item::ItemType itemType);
// Create an item and register its contents
Item CreateItem(const std::string& name, int value, int weight, Item::ItemType itemType);

// Get an item by its ID and print its details
std::unique_ptr<Item> GetItemById(int id);