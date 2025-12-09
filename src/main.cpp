#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * Main entry point for Dungeon Crawler RPG
 * 
 * This program demonstrates:
 * - C++ class hierarchies and inheritance
 * - STL containers (vector, map, string)
 * - Polymorphism with virtual functions
 * - Dynamic memory management with new/delete
 * - Resource management with destructors (RAII)
 * 
 * LEARNING OBJECTIVES:
 * - Complete object-oriented design
 * - Multi-file project organization
 * - Memory management patterns
 */

//===========================================================================
// TEST MAINS //

 /* Temporary main for testing Character class */
 /*int main() {
    Character hero("Hero", 100, 10, 5);
    hero.displayStats();
    hero.takeDamage(20);
    hero.heal(10);
    return 0;
}*/

/* Temporary main for testing Item class */
/*int main() {
    Item sword("Iron Sword", "A sturdy blade", "Weapon", 5);
    sword.displayInfo();
    return 0;
}*/

/* Temporary main for testing weapon class */
/*int main() {
    Weapon sword("Iron Sword", "A sturdy blade", 5);
    sword.displayInfo();
    Item* item_ptr = &sword;
    item_ptr->displayInfo();  // Should call Weapon version
    return 0;
}*/

/* Temporary main for testing armor class */
/*int main() {
    Armor chainmail("Chain Mail", "Protective armor", 3);
    chainmail.displayInfo();
    return 0;
}*/

/* Temporary main for testing consumable class */
/*int main() {
    Consumable potion("Health Potion", "Restores health", 30);
    potion.displayInfo();
    potion.use();  // Should work
    potion.use();  // Should print "already used"
    return 0;
}*/

/* Temporary main for items testing*/
/*
#include <vector>
#include "Item.h"

int main() {
    std::vector<Item*> inventory;
    
    // Add items
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Heals", 20));
    
    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }
    
    // Clean up - VERY IMPORTANT!
    for (int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
    
    return 0;
}
*/


/* Temporary main for testing Player class */
/*
int main() {
    Player hero("Alice");
    hero.displayStats();
    hero.takeDamage(20);  // Inherited method
    hero.displayStats();
    Player hero2("Bob");
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Consumable("Potion", "Heals", 20));
    hero.displayInventory();
    hero.removeItem("potion");  // Case insensitive
    hero.displayInventory();
    hero.removeItem("axe");  // Not found
    hero.displayInventory();
    hero.addItem(new Armor("Shield", "Protects", 3));
    hero.addItem(new Consumable("Elixir", "Restores", 50));
    hero.addItem(new Weapon("Axe", "Chops", 7));
    hero.displayInventory();
    hero.displayStats();
    hero.displayStatus();
    
    return 0;
}*/
/* Temporary main for testing equip/unequip */
/*
int main() {
    Player hero("Charlie");
    hero.addItem(new Weapon("Sword", "Sharp", 5));
    hero.addItem(new Armor("Chainmail", "Strong", 3));
    
    hero.equipWeapon("sword");
    hero.equipArmor("chainmail");
    
    hero.displayStats();
    
    int dmg = hero.calculateDamage();
    std::cout << "Damage: " << dmg << std::endl;  // Should include weapon bonus
    
    return 0;
}*/

/* Temporary main for testing useItem */
/*
int main() {
    Player hero("Dana");
    hero.displayStats();
    hero.gainExperience(100);  // Should trigger level up
    hero.displayStats();
    hero.takeDamage(50);
    hero.displayStats();
    hero.takeDamage(60);  // Should trigger defeat
    hero.displayStats();
    hero.takeDamage(20);  // Should not change HP
    hero.displayStats();
    return 0;
}*/

/* Temporary main for testing Monster class */
/*
int main() {
    std::cout << "=== Monster Test 1 ===" << std::endl;
    Monster orc("Orc", 50, 8, 3, 20, 10);
    orc.addLoot(new Consumable("Potion", "Heals", 15));
    orc.displayStats();
    orc.takeDamage(30);
    
    std::vector<Item*> loot = orc.dropLoot();
    // Clean up loot
    for (int i = 0; i < loot.size(); i++) {
        delete loot[i];
    }
    
    std:: cout << "=== Monster Test 2 ===" << std::endl;
    Monster* monsters[3];
    monsters[0] = new Goblin();
    monsters[1] = new Skeleton();
    monsters[2] = new Dragon();
    
    for (int i = 0; i < 3; i++) {
        monsters[i]->displayStats();
        std::cout << monsters[i]->getAttackMessage() << std::endl;
        int dmg = monsters[i]->calculateDamage();
        std::cout << "Damage: " << dmg << std::endl;
        std::cout << std::endl;
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete monsters[i];
    }
    
    return 0;
}*/

/*Temporary main to test rooms*/
/*
int main() {
    std::cout << "=== Room Test 1 ===" << std::endl;
    Room entrance("Entrance", "A dark corridor");
    entrance.display();

    std::cout << "=== Room Test 2 ===" << std::endl;
    Room room1("Room 1", "First room");
    Room room2("Room 2", "Second room");
    
    room1.addExit("north", &room2);
    room2.addExit("south", &room1);
    
    room1.display();
    
    Room* next = room1.getExit("north");
    if (next) {
        next->display();
    }

    std::cout << "=== Room Test 3 ===" << std::endl;
    Room room("Armory", "Weapons everywhere");
    room.addItem(new Weapon("Sword", "Sharp", 5));
    room.setMonster(new Goblin());
    
    room.display();
    
    if (room.hasMonster()) {
        std::cout << "Monster present!" << std::endl;
    }
    
    return 0;
}
    */

/*Temporary main to test compiling*/ 
/*
int main() {
    Game game;
    // Can't test much yet, but should compile
    return 0;
}
    */
    

//===========================================================================
// FINAL MAIN //


int main() {
    // Seed random number generator for combat calculations
    // This ensures different random numbers each time the game runs
    srand(static_cast<unsigned int>(time(0)));
    
    try {
        // Create game object
        Game game;
        
        // Run main game loop
        // This doesn't return until game is over
        game.run();
    }
    catch (const std::exception& e) {
        // Catch any exceptions and print error message
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    // Normal exit
    return 0;
}


