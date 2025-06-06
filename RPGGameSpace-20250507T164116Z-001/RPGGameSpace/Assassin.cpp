//
//  Assassin.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Assassin.hpp"
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

Assassin::Assassin() : Character() {
    this->characterType = "Assassin";
    this->level = 1;
    this->maxArmor = 150;
    this->currArmor = 150;
    this->maxHealth = 1100;
    this->currHealth = 1100;
    this->maxXP = 200;
    this->currXP = 0;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

Assassin::Assassin(string _name) : Character(_name) {
    this->characterType = "Assassin";
    this->maxHealth = 1100;
    this->currHealth = 1100;
    this->maxArmor = 150;
    this->currArmor = 150;
    this->level = 1;
    this->currXP = 0;
    this->maxXP = 200;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

int Assassin::attack(const string &action) { // Changed parameter name for clarity
    int baseDamage = 0;
    bool abilityTriggered = false;

    // 1. Calculate base damage based on action and "Sneaky Quick" special ability
    if (action == "Light" || action == "light") {
        if (lightAttackCount == 0) { // First light attack
            baseDamage = 140; // Double damage for Sneaky Quick
            abilityTriggered = true;
        } else {
            baseDamage = 70;
        }
        lightAttackCount++; // Increment after checking, so the *next* one isn't the "first"
    } else if (action == "Normal" || action == "normal") {
        if (normalAttackCount == 0) { // First normal attack
            baseDamage = 200; // Double damage
            abilityTriggered = true;
        } else {
            baseDamage = 100;
        }
        normalAttackCount++;
    } else if (action == "Heavy" || action == "heavy") {
        if (heavyAttackCount == 0) { // First heavy attack
            baseDamage = 260; // Double damage
            abilityTriggered = true;
        } else {
            baseDamage = 130;
        }
        heavyAttackCount++;
    } else {
        // Handle unknown action string if necessary, e.g., return 0 or a default small damage
        UIUtils::displayText("Assassin used an unknown attack action: " + action);
        baseDamage = 10; // Default small damage for unknown action
    }

    if (abilityTriggered) {
        UIUtils::displayText(string(BOLD) + getName() + " uses Sneaky Quick with " + action + " attack!" + RESET);
    }

    // 2. Apply Critical Hit
    // Ensure srand() is called ONLY ONCE in main()
    const int critChance = 25; // Assassin's critical hit chance (e.g., 25%)
    if (rand() % 100 < critChance) {
        UIUtils::displayText(string(BOLD) + string(RED) + "CRITICAL HIT!" + RESET);
        baseDamage *= 2; // Standard double damage for a critical hit (can be class-specific)
    }
    
    // 3. Return final damage
    return baseDamage;
}

int Assassin::attackProbability(const string &attackType) {
    unsigned int attackProbability;
    
    if(attackType == "Heavy" || attackType == "heavy") {
        attackProbability = (rand() % 70) + 1;
    }
    
    else if(attackType == "Normal" || attackType == "normal") {
        attackProbability = (rand() % 85) + 1;
    }
    
    else if(attackType == "Light" || attackType == "light") {
        attackProbability = rand() % 100;
    }
    
    return attackProbability;
}

int Assassin::defendProbability(string defendAction) {
    unsigned int defendProbability;
    
    if(defendAction == "Block" || defendAction == "block") {
        defendProbability = (rand() % 60) + 1;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defendProbability = (rand() % 85) + 1;
    }
    
    // Assassins have 50% chance to evade an attack
    else if(defendAction == "Evade" || defendAction == "evade") {
        if (rand() % 2 == 0) { // 50% chance
             UIUtils::displayText(string(BOLD) + getName() + " deftly evades!" + RESET);
            defendProbability = 100; // Successful full evade
        } else {
            defendProbability = (rand() % 50) + 1; // Failed full evade, but still some chance
        }
    }
    
    return defendProbability;
}

int Assassin::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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
        UIUtils::displayText(string(BOLD) + getName() + " leveled up to Level " + to_string(this->level) + "!" + RESET);
        // Potentially increase stats on level up here or in a separate Character::performLevelUpStats() method
    }
    return this->level;
}

