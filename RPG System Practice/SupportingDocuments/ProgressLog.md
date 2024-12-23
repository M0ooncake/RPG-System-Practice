# Date 2024/12/21
* Setup Character files, stat files, Item files, weapon files, turn order files
* Including PlayerCharacterOne, main.

# Date 2024/12/22 
* Setting up documentation in various markdown files.
* Edited turn order to accept a character&, not an int.
* Worked first try surprisingly
* Setup GitHub repository

# Date 2024/12/23
* Attacking function works now.
* to summarize changes, it took a stupid long time to figure
* out. Many google searches, reddit threads, stack overflow threads,
* and back and forth with chatGPT.
* the issue was finally resolved. It required changing how items are store in the inventory.
* rather then pushing the object (which apparently makes a copy) we push a pointer to the inventory.
* that meant that the entire character file had to be adjusted to work with pointers instead of the object, eventually that was resolved.
* then moving to the combatLoop, that took more adjustments to make it compatible with pointers. But it works now.
* Pushing to git immediately.