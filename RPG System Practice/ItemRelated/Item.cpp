#include "Item.h"

#include "Weapons/Weapon.h"


int itemIdCounter = 0; // Counter for Unique ID's

std::unordered_map<int, std::unique_ptr<Item>> itemRegistry;

void Item::printDetails() const
{
    std::cout << "<======================================>\n";
    std::cout << "|| Item Name: " << name << "\n"
            << "|| ID: " << id << "\n"
            << "|| Value: " << value << "\n"
            << "|| Weight: " << weight << "\n";
    
}



/**
 * Creates a new item based on provided values.
 * Registers newly created item into the itemRegistry.
 * Returns newly made item.
 * @param name Name of the item
 * @param value Value of the item
 * @param weight Weight of the item
 * @param itemType Type of the item
 * @return Newly created item
 */
Item CreateItem(const std::string& name, int value, int weight, Item::ItemType itemType)
{
    int id = itemIdCounter++; // post decrement so it assigns a number before increasing counter
    Item* newItem = new Item;
    newItem->name = name;
    newItem->value = value;
    newItem->weight = weight;
    newItem->id = id;
    newItem->itemType = itemType;
    
    itemRegistry[newItem->id] = std::unique_ptr<Item>(newItem);
                                        /*  register a new item at the corresponding index to
                                         *  the newly made item
                                         */
    return *newItem;                     // Return the newly made item.
    
}


/**
 * Checks the itemRegistry for the given ID and returns a pointer to the found item.
 * @param id ID of the item to find
 * @return Unique pointer to the item, or nullptr if not found
 */
std::unique_ptr<Item> GetItemById(int id)
{
    auto it = itemRegistry.find(id);
    if (it != itemRegistry.end())
    {
        return std::move(it->second);  // Return ownership of the found item (using move)
    }
    return nullptr;  // Return nullptr if no item is found
} 
