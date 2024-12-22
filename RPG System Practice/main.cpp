#include <iostream>

#include "Characters/Character.h"
#include "Characters/Alvaro/PlayerCharacterOne.h"
#include "ItemRelated/Weapons/Weapon.h"
#include "Supportive/Turns/TurnOrder.h"


int main(int argc, char* argv[])
{
    PlayerCharacterOne* playerOneAlvaro = new PlayerCharacterOne;
    /*  Well shit. I thought small chance this would work LOL.
     *  And yet it did. Perhaps I'm actually picking up on pointer
     *  arithmetic finally.
     *  I DESPERATELY need a better naming scheme.
     *  Alvaro->Alvaro is crazy shit.
     *  Better name achieved :D
     */


    Weapon unity = Weapon::CreateWeapon("Unity", 100, 20, Weapon::WeaponType::GreatSword);
    Weapon dagger = Weapon::CreateWeapon("Dagger", 10, 5, Weapon::WeaponType::Dagger);
    Item book = CreateItem("Book", 5, 2, Item::ItemType::Misc);


    // Add the greatsword to characters inventory
    AddItemToInventory(playerOneAlvaro->Alvaro, unity);
    AddItemToInventory(playerOneAlvaro->Alvaro, book);
    /*
     *  Should work? Although this could have very unintended
     *  complications if I try to say, remove a dagger :Thinking_Face:
     */
    for (int i = 0; i < 3; ++i)
    {
        AddItemToInventory(playerOneAlvaro->Alvaro, dagger);
    }

    //  Print out character information
    DisplayCharacter(playerOneAlvaro->Alvaro);

    //  Now what they're carrying
    DisplayCharacterInventory(playerOneAlvaro->Alvaro);


    // Test item retrieval
    auto seekItem = GetItemById(unity.id);
    if (seekItem)
    {
        // Dereference the unique_ptr and then cast the raw pointer
        if (auto weapon = dynamic_cast<Weapon*>(seekItem.get()))
        {
            weapon->printDetails();
        }
        else
        {
            std::cout << "ERROR: The item is not a weapon\n";
        }
    }
    else
    {
        std::cout << "ERROR: Item not found\n";
    }

    // Attempt to remove a single dagger.
    RemoveItemFromInventory(playerOneAlvaro->Alvaro, dagger.name);

    // Given all 3 daggers share the same name... lets see how this executes
    DisplayCharacterInventory(playerOneAlvaro->Alvaro);
    // amazingly, it worked! it found the first instance of dagger and removed it.

    ApplyDamage(playerOneAlvaro->Alvaro, 10);
    DisplayCharacter(playerOneAlvaro->Alvaro);

    //  Test list real quick.
    TurnOrder list;
    list.PrintList(); // Output: 
    list.InsertAtBeginning(playerOneAlvaro->Alvaro);
    // Dereference alvaroCharacter (the child class) to access the data of \
                                                           // the parent class (character)
    list.PrintList(); // Output: 0 1 2 3
    // it worked. Tomorrow I'll turn this into a way to track which character is when in a turn order
    // Signing off at 11:30pm
    return 0; // successful exit
}
