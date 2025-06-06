//
//  Enemy.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/25/23.
//

#include "Character.hpp" // Should be included first
#include "Enemy.hpp"
#include "UIUtils.hpp"   // For UIUtils::displayText
#include <string>        // For std::string
#include <vector>        // For std::vector in randomize methods
#include <cstdlib>       // For rand()
#include <ctime>         // For time()
using namespace std;

// ANSI color codes - consider moving these to a central place like UIUtils.hpp
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

// Default Constructor: Creates a generic enemy.
// Its type and specific stats might be overwritten by createEnemy in mainRPG.cpp.
Enemy::Enemy() : Character() {
    this->characterType = "Generic Goblin"; // Default enemy type
    this->name = "Goblin Grunt";
    this->level = 1;
    this->maxArmor = 50;
    this->currArmor = 50;
    this->maxHealth = 300;
    this->currHealth = 300;
    this->currXP = 0;   // Enemies don't typically track XP to level up themselves
    this->maxXP = 0;    // Not relevant for enemy leveling
    // Note: Attack counts for special abilities are not part of the generic enemy by default
    // If specific enemy types (like an "Enemy Assassin") need them, they'd be handled
    // within the attack logic based on characterType.
}

// Parameterized Constructor: Creates an enemy of a specific type with appropriate stats.
Enemy::Enemy(string _name, string _enemyCharacterType) : Character(_name) {
    this->characterType = _enemyCharacterType;
    this->name = _name; // Use the provided name
    this->level = 1;    // Default level, can be adjusted
    this->currXP = 0;
    this->maxXP = 0;

    // Set stats based on the enemy's character type
    // These should mirror player classes or have unique enemy stats
    if (_enemyCharacterType == "Warrior") {
        this->maxHealth = 1200; this->currHealth = 1200;
        this->maxArmor = 200; this->currArmor = 200;
        // Potentially add warrior-like attack patterns or flags here
    } else if (_enemyCharacterType == "Wizard") {
        this->maxHealth = 1000; this->currHealth = 1000;
        this->maxArmor = 80; this->currArmor = 80;
    } else if (_enemyCharacterType == "Healer") {
        // Enemy Healers might be rare or have different abilities (e.g., self-heal more, weak attack)
        this->maxHealth = 1300; this->currHealth = 1300;
        this->maxArmor = 300; this->currArmor = 300;
    } else if (_enemyCharacterType == "Assassin") {
        this->maxHealth = 1100; this->currHealth = 1100;
        this->maxArmor = 150; this->currArmor = 150;
    } else { // Default for unknown or generic types passed to constructor
        this->characterType = "Mysterious Foe"; // Override if type was unknown
        this->maxHealth = 1000; this->currHealth = 1000;
        this->maxArmor = 100; this->currArmor = 100;
    }
}


// Refactored attack method for Enemy
// This single method handles attacks based on the enemy's own characterType.
int Enemy::attack(const string &action) {
    int baseDamage = 0;
    string enemyOwnType = getCharacterType(); // Get the enemy's actual type

    // --- Determine base damage based on enemy's type and action ---
    // These are example values. You should balance them for your game.
    // This section simulates how different enemy types would attack.
    if (enemyOwnType == "Warrior") {
        if (action == "Light") baseDamage = 70;
        else if (action == "Normal") baseDamage = 100;
        else if (action == "Heavy") baseDamage = 140;
        else baseDamage = 30; // Default for unknown action for this type

        // Enemy Warrior "War Cry" equivalent (optional)
        if (getCurrHealth() <= static_cast<int>(getMaxHealth() * 0.25)) { // e.g., below 25% HP
            UIUtils::displayText(string(BOLD) + getName() + " roars with fury (War Cry)!" + RESET);
            baseDamage = static_cast<int>(baseDamage * 1.5); // 50% damage increase
        }

    } else if (enemyOwnType == "Wizard") {
        if (action == "Light") {
            baseDamage = 60;
            // Enemy Wizard "Mystic Heal" equivalent (optional, less potent for enemies)
            if (getCurrHealth() < getMaxHealth()) {
                int healAmount = std::min(20, getMaxHealth() - getCurrHealth());
                setCurrHealth(getCurrHealth() + healAmount);
                if (healAmount > 0) UIUtils::displayText(string(BOLD) + getName() + " siphons some energy, healing for " + to_string(healAmount) + " HP!" + RESET);
            }
        } else if (action == "Normal") baseDamage = 90;
        else if (action == "Heavy") baseDamage = 125;
        else baseDamage = 25;

    } else if (enemyOwnType == "Healer") {
        // Enemy Healers might focus more on debuffs or smaller, consistent damage
        if (action == "Light") baseDamage = 40;
        else if (action == "Normal") baseDamage = 60;
        else if (action == "Heavy") baseDamage = 80;
        else baseDamage = 20;
        // Enemy Healer "First Aid" (self-heal per turn)
        if (getCurrHealth() < getMaxHealth()) {
            int healAmount = min(15, getMaxHealth() - getCurrHealth()); // Heal a bit each turn
            setCurrHealth(getCurrHealth() + healAmount);
             if (healAmount > 0) UIUtils::displayText(string(BOLD) + getName() + " mends its wounds slightly, healing for " + to_string(healAmount) + " HP!" + RESET);
        }

    } else if (enemyOwnType == "Assassin") {
        // Enemy Assassins might not have the "first attack" bonus for simplicity,
        // or you could implement a simplified version (e.g. first attack in combat has bonus)
        if (action == "Light") baseDamage = 70;
        else if (action == "Normal") baseDamage = 100;
        else if (action == "Heavy") baseDamage = 130;
        else baseDamage = 30;
        // Could add a higher base crit chance for enemy assassins later

    } else { // Generic or unknown enemy type
        if (action == "Light") baseDamage = 50;
        else if (action == "Normal") baseDamage = 70;
        else if (action == "Heavy") baseDamage = 90;
        else baseDamage = 20; // Default for unknown action
    }

    // --- Apply Critical Hit ---
    // Ensure srand() is called ONLY ONCE in main()
    int critChance = 15; // Default enemy critical hit chance (e.g., 15%)
    // Optionally, make critChance vary by enemy type:
    // if (enemyOwnType == "Assassin") critChance = 25;

    if (rand() % 100 < critChance) {
        UIUtils::displayText(string(BOLD) + string(RED) + "ENEMY CRITICAL HIT!" + RESET);
        baseDamage *= 2; // Standard double damage for a critical hit
    }
    
    return baseDamage;
}


// attackProbability and defendProbability can be generic for enemies,
// or you can make them vary based on this->characterType as well.
int Enemy::attackProbability(const std::string &action) {
    unsigned int attackProbability = 0;
    string enemyOwnType = getCharacterType();

    // Example: Make probabilities slightly different based on enemy type
    if (enemyOwnType == "Assassin") {
        if(action == "Heavy") attackProbability = (rand() % 65) + 15; // 15-79%
        else if(action == "Normal") attackProbability = (rand() % 75) + 20; // 20-94%
        else if(action == "Light") attackProbability = (rand() % 80) + 20; // 20-99%
        else attackProbability = rand() % 50; // Default for unknown
    } else { // Default for other types
        if(action == "Heavy") attackProbability = (rand() % 50) + 1;  // 1-50%
        else if(action == "Normal") attackProbability = (rand() % 75) + 1; // 1-75%
        else if(action == "Light") attackProbability = rand() % 100;    // 0-99%
        else attackProbability = rand() % 40; // Default for unknown
    }
    return attackProbability;
}

int Enemy::defendProbability(string defendAction) {
    unsigned int defendProbability = 0;
    string enemyOwnType = getCharacterType();

    // Example: Make probabilities slightly different based on enemy type
    if (enemyOwnType == "Warrior" || enemyOwnType == "Healer") { // Tankier types
        if(defendAction == "Block") defendProbability = (rand() % 70) + 25; // 25-94%
        else if(defendAction == "Parry") defendProbability = (rand() % 60) + 15; // 15-74%
        else if(defendAction == "Evade") defendProbability = (rand() % 50) + 5;  // 5-54%
        else defendProbability = rand() % 30;
    } else { // Squishier types like Wizard, Assassin
        if(defendAction == "Block") defendProbability = (rand() % 50) + 10; // 10-59%
        else if(defendAction == "Parry") defendProbability = (rand() % 65) + 10; // 10-74%
        else if(defendAction == "Evade") defendProbability = (rand() % 70) + 15; // 15-84%
        else defendProbability = rand() % 25;
    }
    return defendProbability;
}

// Static method to randomize enemy types - called from mainRPG.cpp
// Ensure srand() is called once in main.
string Enemy::randomizeEnemyTypesStatic() {
    vector<string> types = {"Warrior", "Wizard", "Healer", "Assassin"};
    int randNum = rand() % types.size(); // 0 to size-1
    return types[randNum];
}

// Instance method to randomize actions for this specific enemy
string Enemy::randomizeEnemyActions() {
    vector<string> actions = {"Light", "Normal", "Heavy", "Block", "Parry", "Evade"};
    // Could make actions weighted based on enemy type later
    int randNum = rand() % actions.size();
    return actions[randNum];
}

// Enemies typically don't level up in the same way players do.
// This method is inherited but might not be actively used for enemy progression.
// If it is, ensure it uses this->currXP, this->maxXP, this->level.
int Enemy::levelUp(const int &playerCurrentHealth, const int &thisEnemyCurrentHealth) {
    // This logic is more for player characters.
    // For an enemy, this might represent it getting stronger if it wins,
    // but typically enemies don't "level up" from battle to battle in simple RPGs.
    // If you want enemies to scale, it's usually done by creating higher-level enemies.
    // For now, let's keep it simple or comment out if not used for enemies.
    
    // Example: If an enemy wins, it might get a temporary buff next fight (not implemented here)
    // UIUtils::displayText(getName() + " seems to have learned from the battle!");
    return this->level; // Return current level, no change
}
