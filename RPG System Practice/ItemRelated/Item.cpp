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
} // ChatGPT has had a good hand in the pointer arithmetic as I still struggle to understand all that happens
/*
 * I got ChatGPT to explain it in a good way though!.
 * Think of pointers like a house address, if you visit your friends house (the variable)
 * you need to have their address (the pointer)
 * Thus with the pointer, you know exactly where to go to get to the house (the varibale)
 * but you cannot go in yet.
 * Referencing, when you use the address, you can access the house now, i.e using the pointer
 * allows you to access the house.
 *
 * Unique Pointer
 *  Its like a key to a house only 1 person can have at a time. Ensuring that the person holding
 *  the key, is responsible for what happens to it (like deleting the point after its used to avoid
 *  a memory leak). This method ensures that only 1 person can ever have access at a time.
 *  
 * Shared Pointer
 *  Its like having multiple copies of the same key, to that house. Any number of people can all have
 *  keys to the house (a pointer to a value). That house will remain accessible until all keys are
 *  returned. i.e, last pointer to be used will delete the reference.
 *  
 * Weak pointer
 *  This is like having a temporary pass to the house. They can see the house, (the variable value)
 *  but they cannot own or manage it. (they cannot change it or delete it). Useful to adoid
 *  complicated ownership cycles to help avoid memory leaks.
 *
 *
 * With different examples, ones pertaining to the system being built.
 *
 *
 * Unique Pointer
 *  Imagine a character's inventory. You might use a unique pointer to manage a weapon.
 *  Only one character can own that weapon at a time. When the character discards or trades it,
 *  the ownership is transferred.
 *
 * Shared Pointer
 *  Think of a shared resource, like a magical artifact that multiple characters
 *  can access and benefit from. A shared pointer ensures that the artifact remains until all
 *  characters no longer need it.
 *
 * Weak Pointer
 *  Use this for temporary access, like a reference to a character's current target in combat.
 *  It doesn’t claim ownership but allows you to check if the target still exists.
 */
