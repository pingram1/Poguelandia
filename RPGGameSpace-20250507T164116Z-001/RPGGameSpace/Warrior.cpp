//
//  Warrior.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Warrior.hpp"
#include "UIUtils.hpp"
#include <string>
#include <cstdlib>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

Warrior::Warrior() : Character() {
    this->characterType = "Warrior"; // Assuming characterType is a protected member of Character
    this->name = ""; // Default name, or let Character() handle it
    this->level = 1;
    this->maxArmor = 200;
    this->currArmor = 200;
    this->maxHealth = 1200;
    this->currHealth = 1200;
    this->currXP = 0;
    this->maxXP = 200; // Default XP for next level
}

Warrior::Warrior(string _name) : Character(_name) {
    this->characterType = "Warrior";
    this->maxHealth = 1200;   
    this->currHealth = 1200;  
    this->maxArmor = 200;    
    this->currArmor = 200;   
    this->level = 1;
    this->currXP = 0;
    this->maxXP = 200;       
}

int Warrior::attack(const string &action) {
    int baseDamage = 0;

    // 1. Calculate base damage based on action and special abilities
    // Using getCurrHealth() which should be a public const method in Character
    if(getCurrHealth() > 250) {
        if(action == "Light" || action == "light") {
            baseDamage = 80;
        }
        else if(action == "Normal" || action == "normal") {
            baseDamage = 110;
        }
        else if(action == "Heavy" || action == "heavy") {
            baseDamage = 130;
        }
    }
    else { // Special Ability: War Cry (currHealth <= 250)
        UIUtils::displayText(std::string(BOLD) + getName() + " unleashes a War Cry!" + RESET); // Feedback for ability
        if(action == "Light" || action == "light") {
            baseDamage = 160; // Example: War Cry doubles light damage
        }
        else if(action == "Normal" || action == "normal") {
            baseDamage = 220; // Example: War Cry doubles normal damage
        }
        else if(action == "Heavy" || action == "heavy") {
            baseDamage = 260; // Example: War Cry doubles heavy damage
        }
    }

    // 2. Apply Critical Hit
    // Ensure srand() is called ONLY ONCE in main()
    const int critChance = 20; // Warrior's critical hit chance (e.g., 20%)
    if (rand() % 100 < critChance) { // Generates a number between 0 and 99
        // Use UIUtils for consistent display, possibly with color
        UIUtils::displayText(string(BOLD) + string(RED) + "CRITICAL HIT!" + RESET);
        baseDamage *= 2; // Standard double damage for a critical hit
    }
    
    // 3. Return final damage
    return baseDamage;
}

int Warrior::attackProbability(const string &attackType) {
    unsigned int attackProbability = 0;
    
    if(attackType == "Heavy" || attackType == "heavy") {
        attackProbability = (rand() % 50) + 1;
    }
    
    else if(attackType == "Normal" || attackType == "normal") {
        attackProbability = (rand() % 75) + 1;
    }
    
    else if(attackType == "Light" || attackType == "light") {
        attackProbability = rand() % 100;
    }
    
    return attackProbability;
}

int Warrior::defendProbability(string defendAction) {
    unsigned int defendProbability = 0;
    
    if(defendAction == "Block" || defendAction == "block") {
        defendProbability = rand() % 100;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defendProbability = rand() % 100;
    }
    
    else if(defendAction == "Evade" || defendAction == "evade") {
        defendProbability = rand() % 100;
    }
    
    return defendProbability;
}

int Warrior::levelUp(const int &currHealth, const int &enemyCurrHealth) {
    // Assuming currXP, maxXP, level are protected members of Character or accessed via setters
    if((enemyCurrHealth <= 0) && (currHealth > 0)) { // Player won
        this->currXP += 500;
    }
    // Optional: XP for losing
    else if((currHealth <= 0) && (enemyCurrHealth > 0)) { // Player lost
        this->currXP += 100; // Example: less XP for losing
    }

    if(this->currXP >= this->maxXP) { // Use >= for level up condition
        this->level++;
        this->currXP -= this->maxXP; // Carry over excess XP
        this->maxXP = static_cast<int>(this->maxXP * 1.5); // Increase XP needed for next level (e.g., by 50%)
        UIUtils::displayText(std::string(BOLD) + getName() + " leveled up to Level " + std::to_string(this->level) + "!" + RESET);
        // Potentially increase stats on level up here or in a separate Character::performLevelUpStats() method
    }
    return this->level;
}



