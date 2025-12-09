#include "Player.h"
#include <iostream>
#include <algorithm>

// TODO: Implement Player constructor
// HINTS:
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// TODO: Implement Player destructor
// HINTS:
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // TODO: Delete all inventory items
    for (size_t i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();

}


// TODO: Override displayStats
// HINTS:
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // TODO: Display comprehensive player stats
    std::cout << "====== Player Stats ======" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "HP: " << getCurrentHP() << "/" << getMaxHP() << std::endl;
    int total_attack = getAttack();
    if (equipped_weapon) {
        total_attack += static_cast<Weapon*>(equipped_weapon)->getDamageBonus();
    }
    std::cout << "Attack: " << total_attack << std::endl;
    int total_defense = getDefense();
    if (equipped_armor) {
        total_defense += static_cast<Armor*>(equipped_armor)->getDefenseBonus(); 
    }
    std::cout << "Defense: " << total_defense << std::endl;
    std::cout << "Gold: " << gold << std::endl;
    std::cout << "Experience: " << experience << std::endl;
    if (equipped_weapon) {
        std::cout << "Equipped Weapon: " << equipped_weapon->getName() << std::endl;
    } else {
        std::cout << "Equipped Weapon: None" << std::endl;
    }
    if (equipped_armor) {
        std::cout << "Equipped Armor: " << equipped_armor->getName() << std::endl;
    } else {
        std::cout << "Equipped Armor: None" << std::endl;
    }
    std::cout << "==========================" << std::endl;
}


// TODO: Override calculateDamage to include weapon bonus
// HINTS:
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // TODO: Calculate damage with weapon bonus
    int damage = Character::calculateDamage();
    if (equipped_weapon) {
        damage += static_cast<Weapon*>(equipped_weapon)->getDamageBonus();
    }
    return damage;  // REPLACE THIS
}


// TODO: Implement addItem
// HINTS:
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // TODO: Add item to inventory
    inventory.push_back(item);
    std::cout << "Picked up: " << item->getName() << std::endl;
}


// TODO: Implement removeItem
// HINTS:
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // TODO: Find and remove item from inventory
    std::string lower = item_name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    for (size_t i = 0; i < inventory.size(); i++) {
        std::string name = inventory[i]->getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name == lower) {
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            std::cout << "Removed item: " << item_name << std::endl;
            return;
        }
    }

    std::cout << "Item not found: " << item_name << std::endl;
}



// TODO: Implement displayInventory
// HINTS:
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // TODO: Display all items in inventory
    std::cout << "----- Inventory -----" << std::endl << std::endl;
    if (inventory.empty()) {
        std::cout << "Empty" << std::endl;
    } else {
        for (size_t i = 0; i < inventory.size(); i++) {
            std::cout << "- ";
            inventory[i]->displayBrief();
           // std::cout << std::endl; 
        }
    }
    std::cout << std::endl; 
    std::cout << "--------------------" << std::endl;
}


// TODO: Implement hasItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // TODO: Check if item exists in inventory
    std::string lower = item_name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    for (size_t i = 0; i < inventory.size(); i++) {
        std::string name = inventory[i]->getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name == lower) {
            return true;
        }
    }
    return false;  // REPLACE THIS
}


// TODO: Implement getItem
// HINTS:
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // TODO: Find and return item pointer
    std::string lower = item_name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    for (size_t i = 0; i < inventory.size(); i++) {
        std::string name = inventory[i]->getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name == lower) {
            return inventory[i];
        }
    }
    return NULL;  // REPLACE THIS
}


// TODO: Implement equipWeapon
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // TODO: Equip weapon from inventory
    Item* item = getItem(weapon_name);
    if (item == NULL) {
        std::cout << "Item not found: " << weapon_name << std::endl;
        return;
    }
    if (item->getType() != "Weapon") {
        std::cout << weapon_name << " is not a weapon!" << std::endl;
        return;
    }
    if (equipped_weapon) {
        std::cout << "Unequipped: " << equipped_weapon->getName() << std::endl;
    }
    equipped_weapon = item;
    std::cout << "Equipped: " << equipped_weapon->getName() << std::endl;

}


// TODO: Implement equipArmor
// HINTS:
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // TODO: Equip armor from inventory
    Item* item = getItem(armor_name);
    if (item == NULL) {
        std::cout << "Item not found: " << armor_name << std::endl;
        return;
    }
    if (item->getType() != "Armor") {
        std::cout << armor_name << " is not an armor!" << std::endl;
        return;
    }
    if (equipped_armor) {
        std::cout << "Unequipped: " << equipped_armor->getName() << std::endl;
    }
    equipped_armor = item;
    std::cout << "Equipped: " << equipped_armor->getName() << std::endl;
}


// TODO: Implement unequipWeapon
// HINTS:
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // TODO: Unequip current weapon
    if (equipped_weapon) {
        std::cout << "Unequipped: " << equipped_weapon->getName() << std::endl;
        equipped_weapon = NULL;
    } else {
        std::cout << "No weapon is currently equipped." << std::endl;
    }
}


// TODO: Implement unequipArmor
// HINTS:
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // TODO: Unequip current armor
    if (equipped_armor) {
        std::cout << "Unequipped: " << equipped_armor->getName() << std::endl;
        equipped_armor = NULL;
    } else {
        std::cout << "No armor is currently equipped." << std::endl;
    }
}


// TODO: Implement useItem
// HINTS:
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // TODO: Use consumable item
    Item* item = getItem(item_name);
    if (item == NULL) {
        std::cout << "Item not found: " << item_name << std::endl;
        return;
    }
    if (item->getType() != "Consumable") {
        std::cout << item_name << " is not a consumable!" << std::endl;
        return;
    }
    Consumable* consumable = static_cast<Consumable*>(item);
    if (consumable->isUsed()) {
        std::cout << item_name << " has already been used!" << std::endl;
        return;
    }
    int healing = consumable->getHealingAmount();
    heal(healing);
    consumable->use();
    removeItem(item_name);
}


// TODO: Implement gainExperience
// HINTS:
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // TODO: Add experience and check for level up
    experience += exp;
    std::cout << "Gained " << exp << " experience points!" << std::endl;
    if (experience >= level * 100) {
        levelUp();
    }
}


// TODO: Implement levelUp
// HINTS:
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // TODO: Level up the player
    level++;
    experience = 0;
    setMaxHP(getMaxHP() + 10);
    setCurrentHP(getMaxHP());
    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);
    std::cout << "***** LEVEL UP! You are now level " << level << "! *****" << std::endl;
    displayStats();
}
