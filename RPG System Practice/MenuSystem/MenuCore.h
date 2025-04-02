#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <stack>

#include "MenuParent.h"
/*
 * The idea here is to have a struct that allows for stacking menus.
 * Since this is outside an Engine, I cannot exactly have a stack of game objects,
 * and having a stack for a menu system without something like this would be impossible
 * due to the sheer amount of information that needs to be contained inside a menu
 * in the first place.
 * Ideally, this struct would contain anything and everything needed.
 * Text, display formatting. That way, a object, made from this struct,
 * could hopefully be pushed into a stack. So this MenuCore, will not be the stack,
 * nor a individual menu. It'll be a template in a way that should allow it to be
 * customized to each menu purpose. Like a main menu, viewing inventory, character party.
 * Ideally I would revise the projects current menuing once this is complete to
 * have all displaying text pipe through this. That was admittedly a shortsighted
 * mistake I made at the start.
 *
 * I am immediately having a challenging time thinking of how to best set this up.
 * There would be no concise way I can think of to have a simple function as the base.
 * i.e. If I wanted to print a simple menu, like a main menu. There is little data that needs
 * be too passed in all honesty to a function like that.
 * But if I want to have a character party menu, there is a lot more that needs to be passed
 * a print like that.
 * That would rapidly end up having SOO many different functions, that are also very similar.
 */
struct MenuCoreBackend
{
 
    
    
};

class MenuCore
{
public:


private:
 
 
};
// Taking inspiration from the item creation process.
/**
 * Goal of this Variable is to be able to have it hold references to all the menus that have been created.
 * In an attempt to be able to access any menu in an instant. This could introduce
 * to much overhead if all the menus still exist in memory, but I'll find out I guess.
 */
extern std::unordered_map<int, std::unique_ptr<MenuParent>> MenuRegistry;

/**
 * Goal of this is to have a globally accessible stack for the menus.
 */
extern std::stack<MenuParent> MenuStack;


extern int menuID; // Counter for Unique Menu ID's. Though not sure if this will helpful.