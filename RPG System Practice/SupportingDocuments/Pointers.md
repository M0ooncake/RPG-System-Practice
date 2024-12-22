# Pointers
## [Back To ReadME](../ReadME.md)
## Notes Taken from internet searches and 'talks' with ChatGPT

Think of pointers like a house address, if you visit your friends house (the variable)
you need to have their address (the pointer)
Thus with the pointer, you know exactly where to go to get to the house (the variable)
but you cannot go in yet.
Referencing, when you use the address, you can access the house now, i.e. using the pointer
allows you to access the house.

# Unique Pointer
*  It's like a key to a house only 1 person can have at a time. Ensuring that the person holding
*  the key, is responsible for what happens to it (like deleting the point after it's used to avoid
*  a memory leak). This method ensures that only 1 person can ever have access at a time.

# Shared Pointer
*  It's like having multiple copies of the same key, to that house. Any number of people can all have
*  keys to the house (a pointer to a value). That house will remain accessible until all keys are
*  returned. i.e, last pointer to be used will delete the reference.

# Weak pointer
*  This is like having a temporary pass to the house. They can see the house, (the variable value)
*  but they cannot own or manage it. (they cannot change it or delete it). Useful to avoid
*  complicated ownership cycles to help avoid memory leaks.

# With different examples, ones pertaining to the system being built.


# Unique Pointer
*  Imagine a character's inventory. You might use a unique pointer to manage a weapon.
*  Only one character can own that weapon at a time. When the character discards or trades it,
*  the ownership is transferred.

# Shared Pointer
*  Think of a shared resource, like a magical artifact that multiple characters
*  can access and benefit from. A shared pointer ensures that the artifact remains until all
*  characters no longer need it.

# Weak Pointer
*  Use this for temporary access, like a reference to a character's current target in combat.
*  It doesn't claim ownership but allows you to check if the target still exists.

With these sorts of examples you can start see how these play together differently.
