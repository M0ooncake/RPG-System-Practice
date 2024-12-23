#include <iostream>

#include "Characters/Character.h"
#include "Characters/PlayerCharacterFour/PlayerCharacterFour.h"
#include "Characters/PlayerCharacterOne/PlayerCharacterOne.h"
#include "Characters/PlayerCharacterThree/PlayerCharacterThree.h"
#include "Characters/PlayerCharacterTwo/PlayerCharacterTwo.h"
#include "ItemRelated/Weapons/Weapon.h"
#include "Supportive/CombatRelated/CombatLoop.h"
#include "Supportive/Turns/TurnOrder.h"


int main(int argc, char* argv[])
{
    /*  Well shit. I thought small chance this would work LOL.
     *  And yet it did. Perhaps I'm actually picking up on pointer
     *  arithmetic finally.
     *  I DESPERATELY need a better naming scheme.
     *  Alvaro->Alvaro is crazy shit.
     *  Better name achieved :D
     */
    PlayerCharacterOne* playerOneAlvaro = new PlayerCharacterOne;
    PlayerCharacterTwo* playerTwoStickus = new PlayerCharacterTwo;
    PlayerCharacterThree* playerThreeYrsa = new PlayerCharacterThree;
    PlayerCharacterFour* playerFourAgnar = new PlayerCharacterFour;
    
    Weapon unityGreatSword = Weapon::CreateWeapon("Unity", 100, 20, Weapon::WeaponType::GreatSword);
    Weapon dagger = Weapon::CreateWeapon("Dagger", 10, 5, Weapon::WeaponType::Dagger);
    Item book = CreateItem("Book", 5, 2, Item::ItemType::Misc);
    Weapon TearsOfGodSword = Weapon::CreateWeapon("Tears Of God", 500, 5, Weapon::WeaponType::Sword);
    
    // Add the items to characters inventory
    AddItemToInventory(playerOneAlvaro->Alvaro, unityGreatSword);
    AddItemToInventory(playerOneAlvaro->Alvaro, book);
    AddItemToInventory(playerTwoStickus->Stickus, TearsOfGodSword);
    

    
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
    DisplayCharacter(playerTwoStickus->Stickus);

    //  Now what they're carrying
    DisplayCharacterInventory(playerOneAlvaro->Alvaro);


    // Test item retrieval
    auto seekItem = GetItemById(unityGreatSword.id);
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
    
    auto findItem = GetItemById(book.id);
    {
        if (auto book2 = dynamic_cast<Item*>(findItem.get()))
        {
            book2->printDetails();
        }
    }

    // Attempt to remove a single dagger.
    RemoveItemFromInventory(playerOneAlvaro->Alvaro, dagger.name);

    // Given all 3 daggers share the same name... lets see how this executes
    DisplayCharacterInventory(playerOneAlvaro->Alvaro);
    // amazingly, it worked! it found the first instance of dagger and removed it.
    
    //ApplyDamage(playerOneAlvaro->Alvaro);
    //DisplayCharacter(playerOneAlvaro->Alvaro);

    //  Test list real quick.
    TurnOrder combatTurnOrder;
    
    combatTurnOrder.InsertBasedOffSpeed(playerTwoStickus->Stickus); // second slowest
    combatTurnOrder.InsertBasedOffSpeed(playerOneAlvaro->Alvaro); // fastest hehe~
    combatTurnOrder.InsertBasedOffSpeed(playerFourAgnar->Agnar); // slowest
    combatTurnOrder.InsertBasedOffSpeed(playerThreeYrsa->Yrsa); // second fastest
    combatTurnOrder.PrintList(); // expected output: Alvaro Yrsa Stickus Agnar
    // The above turn order will have no bearing on combat. First attempt of running combat happens now.
    std::vector<Character*> allCharacters = {&playerOneAlvaro->Alvaro, &playerTwoStickus->Stickus, &playerFourAgnar->Agnar,
                                                                &playerThreeYrsa->Yrsa};
    std::vector<Character*> enemies = {&playerTwoStickus->Stickus, &playerThreeYrsa->Yrsa};
    std::vector<Character*> players = {&playerOneAlvaro->Alvaro, &playerFourAgnar->Agnar};
    CombatLoop combatLoop(allCharacters, enemies, players);
    combatLoop.MainLoop();  // It didnt work properly, but it didnt crash!
    return 0; // successful exit
}
