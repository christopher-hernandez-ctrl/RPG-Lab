#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if (player) {
        delete player;
        player = NULL;
    }
    for (std::map<std::string, Room*>::iterator it = world.begin(); it != world.end(); ++it) {
        delete it->second;
    }
    world.clear();
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                          [Throne Room]  [Chamber]
//                               |              |
//     [Armory] - [Hallway] - [Treasury] - [Passage] - [Library]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // TODO: Create rooms 
    Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* hallway = new Room("Hallway", "A narrow dimly lit hallway...");
    Room* armory = new Room("Armory", "An armory filled with weapons...");
    Room* treasury = new Room("Treasury", "A room glittering with gold...");
    Room* throne_room = new Room("Throne Room", "An imposing throne room...");
    Room* chamber = new Room("Chamber", "A small quiet chamber...");
    Room* passage = new Room("Passage", "A long winding passage...");
    Room* library = new Room("Library", "A dusty old library...");

    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne_room);
    addRoom(chamber);
    addRoom(passage);
    addRoom(library);
    
    // TODO: Connect rooms bidirectionally
    connectRooms("Dungeon Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Treasury", "north", "Throne Room");
    connectRooms("Treasury", "east", "Passage");
    connectRooms("Passage", "north", "Chamber");
    connectRooms("Passage", "east", "Library");
    
    // TODO: Add monsters
    /*
    hallway->setMonster(new Monster("Goblin", 20, 5, 2, 10, 5));
    armory->setMonster(new Monster("Skeleton", 30, 7, 3, 15, 10));
    treasury->setMonster(new Monster("Skeleton", 30, 7, 3, 15, 10));
    throne_room->setMonster(new Monster("Dragon", 100, 15, 5, 50, 100));
    passage->setMonster(new Monster("Troll", 50, 10, 4, 25, 20));
    chamber->setMonster(new Monster("Ghost", 40, 8, 2, 20, 15));
    library->setMonster(new Monster("Ghost", 40, 8, 2, 20, 15));
    */
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne_room->setMonster(new Dragon());
    passage->setMonster(new Troll());
    chamber->setMonster(new Ghost());
    library->setMonster(new Wizard());

    // TODO: Add items
    armory->addItem(new Weapon("Iron Sword", "A sturdy iron sword", 6));
    armory->addItem(new Armor("Chain Mail", "Protective chain mail armor", 4));
    entrance->addItem(new Consumable("Small Potion", "Restores 20 HP", 20));
    treasury->addItem(new Consumable("Health Potion", "Restores 50 HP", 50));


    // TODO: Set starting room
    current_room = entrance;
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    player->addItem(new Weapon("Rusty Dagger", "A worn, old dagger", 2));
    player->addItem(new Consumable("Bread", "A loaf of bread to heal", 5));
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if (room) {
        world[room->getName()] = room;
    }
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    Room* room1 = world[room1_name];
    Room* room2 = world[room2_name];
    if (room1 && room2) {
        room1->addExit(direction, room2);
        std::string reverse;
        if (direction == "north") reverse = "south";
        else if (direction == "south") reverse = "north";
        else if (direction == "east") reverse = "west";
        else if (direction == "west") reverse = "east";
        room2->addExit(reverse, room1);
    }
}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
    std::cout << "Welcome to Dungeon Crawlers RPG!" << std::endl;
    std::cout << "Enter your character's name: ";
    std::string name;
    std::getline(std::cin, name);
    player = new Player(name);
    initializeWorld();
    createStartingInventory();
    current_room->display();
    current_room->markVisited();
    while (!game_over) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        processCommand(command);
        if (victory) {
            std::cout << "Congratulations! You have defeated the Dragon and won the game!" << std::endl;
            game_over = true;
        }
        if (!player->isAlive()) {
            std::cout << "You have been defeated. Game Over." << std::endl;
            game_over = true;
        }
    }
}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
    std::istringstream iss(command);
    std::string verb;;
    iss >> verb;
    std::string object;
    std::getline(iss, object);
    object.erase(0, object.find_first_not_of(" ")); // Trim leading spaces
    if (verb == "go" || verb == "move") {
        move(object);
    } else if (verb == "look" || verb == "l") {
        look();
    } else if (verb == "attack" || verb == "fight") {
        attack();
    } else if (verb == "pickup" || verb == "get" || verb == "take") {
        pickupItem(object);
    } else if (verb == "inventory" || verb == "i") {
        inventory();
    } else if (verb == "use") {
        useItem(object);
    } else if (verb == "equip" || verb == "e") {
        equip(object);
    } else if (verb == "stats") {
        player->displayStats();
    } else if (verb == "help" || verb == "h" || verb == "?") {
        help();
    } else if (verb == "quit" || verb == "exit") {
        game_over = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
    }
}


// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
    if (current_room->hasMonster()) {
        std::cout << "A monster blocks your path! You must defeat it first." << std::endl;
        return;
    }
    Room* next_room = current_room->getExit(direction);
    if (next_room) {
        current_room = next_room;
        current_room->display();
        current_room->markVisited();
    } else {
        std::cout << "You can't go that way!" << std::endl;
    }
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    Monster* monster = current_room->getMonster();
    if (!monster) {
        std::cout << "There is no monster here to attack." << std::endl;
        return;
    }
    combat(monster);
}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // TODO: Implement turn-based combat
    std::cout << "=== COMBAT BEGINS ===" << std::endl;
    while (player->isAlive() && monster->isAlive()) {
        std::cout << monster->getName() << " HP: " << monster->getCurrentHP() << std::endl;
        std::cout << player->getName() << " HP: " << player->getCurrentHP() << std::endl;

        std::cout << "Choose action (attack/use/flee): ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "attack") {
            int dmg = player->calculateDamage();
            std::cout << "You hit for " << dmg << "!" << std::endl;
            monster->takeDamage(dmg);

            if (monster->getCurrentHP() <= 0) {
                std::cout << "You defeated the " << monster->getName() << "!" << std::endl;
                
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());
                std::cout << "You gained " << monster->getExperienceReward() 
                          << " EXP and " << monster->getGoldReward() << " gold!" << std::endl;
                std::vector<Item*> loot = monster->dropLoot();
                if(!loot.empty()) {
                    std::cout << "The " << monster->getName() << " dropped:" << std::endl;
                    for (size_t i = 0; i < loot.size(); i++) {
                        std::cout << "  - " << loot[i]->getName() << std::endl;
                        current_room->addItem(loot[i]);
                    }
                } else {
                    std::cout << "The " << monster->getName() << " dropped no loot." << std::endl;
                }
                if (monster->getName() == "Dragon") {
                    victory = true;
                }

                current_room->clearMonster();
                break;
            }
        }
        else if (cmd == "flee") {
            std::cout << "You flee!" << std::endl;
            break;
        }
        else if (cmd.substr(0, 3) == "use") {
            std::string item = cmd.substr(4);
            player->useItem(item);
        }
        else {
            std::cout << "Invalid action." << std::endl;
            continue;
        }

        if (monster->isAlive()) {
            std::cout << monster->getAttackMessage() << std::endl;
            int dmg = monster->calculateDamage();
            std::cout << monster->getName() << " hits you for " << dmg << "!" << std::endl;
            player->takeDamage(dmg);
        }
    }

    std::cout << "COMBAT ENDS." << std::endl;

}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // TODO: Pick up item from room
    Item* item = current_room->getItem(item_name);
    if (item) {
        player->addItem(item);
        current_room->removeItem(item_name);
        std::cout << "You picked up: " << item->getName() << std::endl;
    } else {
        std::cout << "There is no item named '" << item_name << "' here." << std::endl;
    }
}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
    player->displayInventory();
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
    player->useItem(item_name);
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // TODO: Equip weapon or armor
    Item* item = player->getItem(item_name);
    if (!item) {
        std::cout << "You don't have an item named '" << item_name << "'." << std::endl;
        return; 
    }
    if (item->getType() == "Weapon") {
        player->equipWeapon(item->getName());
    } else if (item->getType() == "Armor") {
        player->equipArmor(item->getName());
    } else {
        std::cout << "You can't equip that item." << std::endl;
    }
}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // TODO: Display help message
    std::cout << "=== Available Commands ===" << std::endl;
    std::cout << "go <direction>  - Move to adjacent room" << std::endl;
    std::cout << "look           - Look around the room" << std::endl;
    std::cout << "attack         - Attack the monster in the room" << std::endl;
    std::cout << "pickup <item>  - Pick up an item from the room" << std::endl;
    std::cout << "inventory      - Show your inventory" << std::endl;
    std::cout << "use <item>     - Use a consumable item" << std::endl;
    std::cout << "equip <item>   - Equip a weapon or armor" << std::endl;
    std::cout << "stats          - Show your character stats" << std::endl;
    std::cout << "help          - Show this help message" << std::endl;
    std::cout << "quit          - Exit the game" << std::endl;
}
