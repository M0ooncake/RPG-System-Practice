#pragma once
// What sort of things will we need?
struct Stats
{
    /* Going to make various stats that make sense for an RPG character to have,
     * Like DnD comes to mind first. But really any RPG.
    */

    int strength;
    int dexterity;
    int wisdom;
    int intelligence;
    int speed;
    mutable int health;
    int maxHealth;
};
