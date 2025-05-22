//
//  Wizard.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Wizard.hpp"
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

Wizard::Wizard() {
    this->attackType = "Wizard";
    this->level = 1;
    this->maxArmor = 80;
    this->currArmor = 80;
    this->maxHealth = 1000;
    this->currHealth = 1000;
    this->maxXP = 0;
    this->currXP = 200;
}

Wizard::Wizard(string _name) : Character(_name) {
    this->characterType = "Wizard";
    this->maxHealth = 1000;
    this->currHealth = 1000;
    this->maxArmor = 80;
    this->currArmor = 80;
    this->level = 1;
    this->maxXP = 200;
    this->currXP = 0;
}

int Wizard::attack(const string &action) { // Parameter name changed for clarity
    int baseDamage = 0;
    bool mysticHealTriggered = false;

    // 1. Apply "Mystic Heal" if applicable and calculate base damage
    if (action == "Light" || action == "light") {
        baseDamage = 65; // Base damage for Light attack

        // Mystic Heal: "you receive 50 HP and 10 armor points with every light attack."
        int currentHP = getCurrHealth();
        int maximumHP = getMaxHealth();
        int currentArm = getCurrArmor();
        int maximumArm = getMaxArmor();

        int healedHP = 0;
        int restoredArmor = 0;

        if (currentHP < maximumHP) {
            int potentialHeal = 50;
            healedHP = min(potentialHeal, maximumHP - currentHP);
            setCurrHealth(currentHP + healedHP);
        }
        if (currentArm < maximumArm) {
            int potentialArmorRestore = 10;
            restoredArmor = min(potentialArmorRestore, maximumArm - currentArm);
            setCurrArmor(currentArm + restoredArmor);
        }

        if (healedHP > 0 || restoredArmor > 0) {
            mysticHealTriggered = true;
            string healMessage = string(BOLD) + getName() + " uses Mystic Heal! ";
            if (healedHP > 0) {
                healMessage += "Recovered " + to_string(healedHP) + " HP. ";
            }
            if (restoredArmor > 0) {
                healMessage += "Restored " + to_string(restoredArmor) + " Armor.";
            }
            UIUtils::displayText(GREEN + healMessage + RESET);
        }

    } else if (action == "Normal" || action == "normal") {
        baseDamage = 95;
    } else if (action == "Heavy" || action == "heavy") {
        baseDamage = 135;
    } else {
        UIUtils::displayText("Wizard cast an unknown spell: " + action);
        baseDamage = 10; // Default small damage for unknown action
    }

    // 2. Apply Critical Hit
    // Ensure srand() is called ONLY ONCE in main()
    const int critChance = 10; // Wizard's critical hit chance (e.g., 10%)
    if (rand() % 100 < critChance) {
        UIUtils::displayText(string(BOLD) + string(RED) + "CRITICAL HIT!" + RESET);
        baseDamage *= 2; // Standard double damage for a critical hit
    }
    
    // 3. Return final damage
    return baseDamage;
}

int Wizard::attackProbability(const string &attackType) {
    unsigned int attackProbability = 0;
    
    if(attackType == "Heavy" || attackType == "heavy") {
        attackProbability = (rand() % 70) + 1;
    }
    
    else if(attackType == "Normal" || attackType == "normal") {
        attackProbability = (rand() % 75) + 1;
    }
    
    else if(attackType == "Light" || attackType == "light") {
        attackProbability = rand() % 100;
    }
    
    return attackProbability;
}

int Wizard::defendProbability(string defendAction) {
    unsigned int defendProbability = 0;
    
    if(defendAction == "Block" || defendAction == "block") {
        defendProbability = (rand() % 70) + 10;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defendProbability = (rand() % 50) + 5;
    }
    
    else if(defendAction == "Evade" || defendAction == "evade") {
        defendProbability = (rand() % 65) + 10;
    }
    
    return defendProbability;
}

int Wizard::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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