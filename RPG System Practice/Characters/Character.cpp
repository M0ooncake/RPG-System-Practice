#include "Character.h"

/**
 * Converts a Character::classType enum value to its string representation.
 * @param classType The Character::classType value to convert.
 * @return A string representing the class.
 */
std::string CharacterClassToString(Character::classType classType) {
    switch (classType) {
        case Character::Fighter: return "Fighter";
        case Character::Templar: return "Templar";
        case Character::Rogue: return "Rogue";
        case Character::Shadow: return "Shadow";
        case Character::Adapt: return "Adapt";
        default: return "Unknown";
    }
}


/**
 * Prints out various details about the character given.
 * when called.
 * @param character A reference to the character to print out.
 */
void DisplayCharacter(const Character& character)
{
    // Attempt to have it visually formatted
    std::cout << "<======================================>\n";
    std::cout << "|| Name: " << character.name << "\n"
            << "|| Class: " << CharacterClassToString(character.characterClass) << "\n"
            << "|| Level: " << character.level << "\n"
            << "|| Current Experience: " << character.experience << "\n"
            << "|| Stats:\n"
            << "||   Strength: " << character.stats.strength << "\n"
            << "||   Dexterity: " << character.stats.dexterity << "\n"
            << "||   Wisdom: " << character.stats.wisdom << "\n"
            << "||   Intelligence: " << character.stats.intelligence << "\n"
            << "||   Speed: " << character.stats.speed << "\n"
            << "||   Health: " << character.stats.health << "\n"
            << "||  Max Health: " << character.stats.maxHealth << "\n";
    
} // Hopefully this will print it nicely


/**
 * Pushes an item to the back of the vector for a given character.
 * @param character Reference to the character to assign item.
 * @param item Reference to the item to assign.
 */
void AddItemToInventory(Character& character, const Item& item)
{
    // chatGPT has recommend a change. Store pointers to the object, not just pushing the object
    
    // Get the item from within the registry, this seems like an odd choice
    // as if there are thousands of items would this not be highly inefficient?
    auto itemPointer = itemRegistry[item.id].get();
    
    // Push the pointer into the inventory, so we preserve the original item and its type info
    character.inventory.push_back(itemPointer);
    std::cout << "<======================================>\n";
    std::cout << item.name << " Added to " << character.name << "'s inventory. \n";
    /*character.inventory.push_back(item);
    std::cout << "<======================================>\n";
    std::cout << item.name << " Added to " << character.name << "'s inventory. \n";*/
}

/**
 * Searches the vector for an element (item) that matches the given name.
 * If found it will remove.
 * @param character Reference to the character to remove item from
 * @param itemName String reference to the item to be removed
 */
void RemoveItemFromInventory(Character& character, const std::string& itemName)
{
    std::cout << "<======================================>\n";
    // The lambda function compares the item.name with the provided itemName
    auto it = std::find_if(    // type auto in case that changes over time
        character.inventory.begin(),           // i.e weapon, consumable
        character.inventory.end(),
        [&itemName](const Item* item)
        {
            return item->name == itemName;
        }
    );
    // If the item is found, "Cast it into the fire! Destroy it!"
    if (it != character.inventory.end())
    {
        std::cout << "Removing item: " << (*it)->name << " from inventory.\n";
        character.inventory.erase(it);
    }
    else
    {
        std::cout << "Item: " << itemName << " not found in " << character.name << "'s inventory.\n";
    }
}

/**
 * Checks if the inventory is empty. Then prints out their current
 * inventory.
 * @param character  Reference to the character to display inventory of.
 */
void DisplayCharacterInventory(const Character& character)
{
    std::cout << "<======================================>\n";
    // No sense in printing nothing
    if (character.inventory.empty())
    {
        std::cout << character.name << "'s inventory is empty.\n";
        return;
    }
    std::cout << "|| " << character.name << "'s Inventory:\n";
    // Debug complained about comparing between int and unsigned long long. Which I guess is fair
    for (unsigned long long i = 0; i < character.inventory.size(); ++i)
    {                                                                
        const auto& item = character.inventory[i];
        std::cout << "||   " << (i + 1) << ". " << item->name
                  << "||  (Value: " << item->value
                  << "|| , Weight: " << item->weight << ")\n";
    }
    
}

void DisplayCharacterWeapons(const Character& character)
{
    std::cout << "<======================================>\n";
    if (character.inventory.empty())
    {
        std::cout <<  character.name << "'s inventory is empty!\n";
    }

    std::cout << "|| " << character.name << "'s weapons:\n";

    for (unsigned long long i = 0; i < character.inventory.size(); ++i)
    {
        const auto& weapon = character.inventory[i];
        if(weapon->itemType == Item::ItemType::Weapon)   // only print if the item is a weapon
        {
            std::cout << "||   " << (i + 1) << ". " << weapon->name << "\n"; // print weapons
                
        }
    }
}

void ApplyDamageToCharacter(const Character& character, const int damage)
{
    if (damage < 0) return; // Don't heal off negative numbers
    std::cout << "<======================================>\n";
    character.stats.health -= damage; // Damage the characters health
    std::cout << character.name << " has been dealt " << damage << " damage!!!\n";
    if (character.stats.health <= 0)
    {
        std::cout << character.name << " has reached 0 health!\n";
    }
}

void ApplyHealToCharacter(const Character& character, const int healing)
{
    if (healing < 0) return; // Don't damage off negative numbers
    std::cout << "<======================================>\n";
    character.stats.health += healing; // Heal the characters health
    std::cout << character.name << " has been given " << healing << " healing!!!\n";
    if (character.stats.health > character.stats.maxHealth)
    {
        std::cout << character.name << " has exceeded maxHealth!\n";
        std::cout << "Clamping health to " << character.stats.maxHealth << "\n";
    }
}
