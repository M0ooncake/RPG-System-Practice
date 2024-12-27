#include "CombatLoop.h"
#include "../../Characters/Character.h"
#include "AttackAction.h"

void CombatLoop::MainLoop()
{
        
    do
    {
        if (combatTurnOrder.head == nullptr)
            std::cout << "Their dead, handle this outcome \n"; 
        //Firstly show active enemies
        PrintEnemyCharacters(); 

        // Print out the active player's turn
        combatTurnOrder.GetActiveTurn();

        Node* currentCharacter = combatTurnOrder.head;
        if (currentCharacter->character->isNPC == true)
        {
                
            SelectRandomPlayer();
                
                
        }
        else
        {
            PresentPlayerOptions();
                
        }

        std::cout << "Advancing to the next turn...\n";
            
        combatTurnOrder.AdvanceTurn();
    }
    while (isCombatActive == true);
}

void CombatLoop::PrintEnemyCharacters()
{
    //std::cout << "<======================================>\n";
    std::cout << "<====> Active enemies on the field! <====>\n";
    //std::cout << "|| Active enemies on the field!\n";
    enemyList.PrintList();
        
}

void CombatLoop::PresentPlayerOptions()
{
    /*Node* currentCharacter = combatTurnOrder.head;
        if (currentCharacter->character->isNPC == true)
        {
            SelectRandomPlayer();
            GameDelay(2);
            return;
        }*/
        
    playerSelection = 0; // Reset the players selection upon call
    std::cout << "<======================================>\n";
    std::cout << "|| Select Desired Action\n"
            << "|| 1. Attack \n";
    std::cout << "---> ";
    std::cin >> playerSelection;

    switch (playerSelection)
    {
        case 1:
            SelectEnemyTarget();
            break;
        default:
            std::cout << "Invalid entry, ";
            PresentPlayerOptions(); // Recall if they didn't pick a valid target
    }
}

void CombatLoop::SelectEnemyTarget()
{
    playerSelection = 0; // Reset the players selection upon call
    std::cout << "<======================================>\n";
    std::cout << "|| Select Enemy Target! \n";
    enemyList.PrintList(); // Show available targets

    std::cout << "---> ";
    std::cin >> playerSelection;    // take input

    // Validate input and get the target
    Node* temp = enemyList.head;
    int index = 1;
    selectedEnemy = nullptr;    //  Initialize to null

    // Traverse the list to acquire target.
    // While temp isn't null, and our index is less than player selection,
    // That means we need to go deeper to find what we are looking for.
    while (temp != nullptr && index <= playerSelection)
    {
        if (index == playerSelection)
        {
            selectedEnemy = temp->character; // Target acquired
            break;                           // bail out
        }
        temp = temp->next; // Change the temp Node* to be the next to look there.
        index++;           // increase our index to show we've searched one
    }

    if (selectedEnemy)
    {
        std::cout << "You have selected " << selectedEnemy->name << " as the target!\n";
        GetAttackWeapon();
    }
    else
    {
        std::cout << "Invalid selection, enter a choice again. \n";
        SelectEnemyTarget(); // Retry for valid input
    }
        
}

Weapon* CombatLoop::SelectWeaponFromInventory(Character& character)
{

    if (character.isNPC == true)
    {
        return dynamic_cast<Weapon*>(character.inventory[0]); // Attack with the first item in the inventory
    }
        
    DisplayCharacterWeapons(character);
    std::cout << "<======================================>\n";
    // Check if the inventory is empty
    if (character.inventory.empty())
    {
        std::cout << "No weapons available to select.\n";
        SelectWeaponFromInventory(character);
        return nullptr;
    }

    // Get player input
    unsigned int selectedIndex; // cant be negative
    std::cout << "Select a weapon to attack with (enter the number): ";
    std::cout << "---> ";
    std::cin >> selectedIndex;

    // Validate input
    if (selectedIndex == 0 || selectedIndex > character.inventory.size())
    {
        std::cout << "Invalid selection. Please try again.\n";
        return nullptr;
    }

    // Check if selected item is a weapon
    Item* selectedItem = character.inventory[selectedIndex - 1];   
        
    //std::cout << "You selected item: " << selectedItem->name << "\n";  
        
       
    //selectedItem->printDetails();
        
    if (selectedItem->itemType != Item::ItemType::Weapon)
    {
        std::cout << "Selected item is not a weapon. Please select a valid weapon.\n";
        return nullptr;
    }
        
        
    return dynamic_cast<Weapon*>(selectedItem); // adding breakpoint
}

void CombatLoop::GetAttackWeapon()
{
    Node* characterNode = combatTurnOrder.head;
    if (!characterNode) // null check
    {
        std::cout << "No active character in turn order.\n";
        return;
    }

    Character* characterActive = characterNode->character;
    if (!characterActive) // double check null
    {
        std::cout << "Active character is null.\n";
        return;
    }
        
    // Loop until the player selects a valid weapon
    // Dear lord something is FUCKED real good.
    // I have gotten lost in the sauce of pointers real bad. 
    Weapon* selectedWeapon = nullptr;   
    while (!selectedWeapon)
    {
        selectedWeapon = SelectWeaponFromInventory(*characterActive);
        if (selectedWeapon == nullptr)
        {
            std::cout << "selectedWeapon nullptr triggered.\n";
               
        }
        else break;
    }
        
    //std::cout << characterActive->name << " selected " << selectedWeapon->name << " to attack with.\n";

        
    AttackAction attackAction(characterActive, selectedWeapon, selectedEnemy,this); // Initialize attack
    attackAction.CalculateAndDealDamage();                                       // Perform the attack!
        
}

void CombatLoop::SelectRandomPlayer()
{
    // going to try and quickly add some logic for an enemy turn player turn switcher
    if(players.empty()) return;
    Character* NPC = combatTurnOrder.head->character;
    // Check if the current turn character is in the enemy list
        
    int enemySelection = rand() % players.size();
    Weapon* NPCWeapon = SelectWeaponFromInventory(*NPC);
    Character* NPCTarget = players[enemySelection];
        
        
    std::cout << NPC->name << " is about to strike " << NPCTarget->name << " with a " << NPCWeapon->name << "!!!\n";
        
        
    AttackAction attackAction(NPC, NPCWeapon, NPCTarget, this); // mayhaps work??? UwU?
       
    attackAction.CalculateAndDealDamage();
        
}

void CombatLoop::RemoveCharacterFromPlay(Character& characterToRemove)
{
    combatTurnOrder.RemoveNode(characterToRemove);
    enemyList.RemoveNode(characterToRemove);
    playerList.RemoveNode(characterToRemove);
    
    /*searchForCharacterToRemove(combatTurnOrder, characterToRemove);
    searchForCharacterToRemove(enemyList, characterToRemove);
    searchForCharacterToRemove(playerList, characterToRemove);*/
}

void CombatLoop::searchForCharacterToRemove(TurnOrder& list, Character& characterToRemove)
{
    Node* temp = list.head;
    Node* previousNode = nullptr;

    if (temp == nullptr)
    {
        std::cout << "List is empty. Nothing to remove.\n";
        return;
    }

    // Check if the head node matches the character to remove
    if (temp->character && temp->character->name == characterToRemove.name)
    {
        list.head = temp->next;  // Change head to the next node
        delete temp;  // Free memory
        std::cout << characterToRemove.name << " has been removed from the list.\n";
        return;
    }

    // Traverse the list to find the character
    while (temp != nullptr)
    {
        std::cout << "Checking node: " << temp << " with character: " 
          << (temp && temp->character ? temp->character->name : "null") << "\n";
        
        if (temp->character && temp->character->name == characterToRemove.name)
        {
            // Found the character, remove it
            previousNode->next = temp->next;  // Link the previous node to the next node
            delete temp;  // Free memory
            std::cout << characterToRemove.name << " has been removed from the list.\n";
            return;
        }
        previousNode = temp;  // Keep track of the previous node
        temp = temp->next;    // Move to the next node
    }
    
    
    std::cout << "Character " << characterToRemove.name << " not found in the list.\n";
}
