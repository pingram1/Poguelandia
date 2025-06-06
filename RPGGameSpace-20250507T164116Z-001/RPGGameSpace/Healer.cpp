//
//  Healer.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Healer.hpp"
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

Healer::Healer() {
    this->characterType = "Healer";
    this->level = 1;
    this->maxArmor = 300;
    this->currArmor = 300;
    this->maxHealth = 1300;
    this->currHealth = 1300;
    this->maxXP = 0;
    this->currXP = 200;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

Healer::Healer(string _name) : Character(_name) {
    this->characterType = "Healer";
    this->maxHealth = 1300;
    this->currHealth = 1300;
    this->maxArmor = 300;
    this->currArmor = 300;
    this->level = 1;
    this->maxXP = 200;
    this->currXP = 0;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

int Healer::attack(const string &action) { // Parameter name changed for clarity
    int baseDamage = 0;
    bool chronicAbrasionTriggered = false;

    // --- Apply "First Aid" passive healing part ---
    // "Character regains 10HP with every move (attack, defend, evade)"
    // This healing should ideally happen regardless of the attack action,
    // potentially even if the attack "misses" or is a defensive move.
    // For simplicity here, we'll apply it if an attack action is chosen.
    // A more robust way would be a separate `onTurnStart()` or `onAction()` method.
    
    int healthBeforeFirstAid = getCurrHealth();
    int maxHp = getMaxHealth();
    if (healthBeforeFirstAid < maxHp) {
        int healAmount = 10;
        int newHealth = healthBeforeFirstAid + healAmount;
        if (newHealth > maxHp) {
            newHealth = maxHp;
        }
        setCurrHealth(newHealth); // Assuming setCurrHealth is a public/protected method in Character
        if (getCurrHealth() > healthBeforeFirstAid) { // Check if actual healing occurred
            UIUtils::displayText(string(BOLD) + getName() + " uses First Aid and recovers " + to_string(getCurrHealth() - healthBeforeFirstAid) + " HP!" + RESET);
        }
    }

    // --- Calculate base damage based on action and "Chronic Abrasion" ---
    // "deal 100% damage every other attack" (meaning double damage on those "other" attacks)
    if(action == "Light" || action == "light") {
        baseDamage = 45; // Base light damage
        if(lightAttackCount % 2 == 1) { // Every other attack (1st, 3rd, 5th... if 0-indexed count)
            baseDamage *= 2; // Chronic Abrasion doubles damage
            chronicAbrasionTriggered = true;
        }
        lightAttackCount++;
    }
    else if(action == "Normal" || action == "normal") {
        baseDamage = 75; // Base normal damage
        if(normalAttackCount % 2 == 1) {
            baseDamage *= 2;
            chronicAbrasionTriggered = true;
        }
        normalAttackCount++;
    }
    else if(action == "Heavy" || action == "heavy") { // Corrected "Heavy" casing
        baseDamage = 105; // Base heavy damage
        if(heavyAttackCount % 2 == 1) {
            baseDamage *= 2;
            chronicAbrasionTriggered = true;
        }
        heavyAttackCount++;
    } else {
        UIUtils::displayText("Healer used an unknown attack action: " + action);
        baseDamage = 5; // Minimal damage for unknown action
    }

    if (chronicAbrasionTriggered) {
        UIUtils::displayText(string(BOLD) + getName() + "'s Chronic Abrasion empowers the " + action + " attack!" + RESET);
    }

    // --- Apply Critical Hit ---
    const int critChance = 10; // Healer's critical hit chance (e.g., 10%)
    if (rand() % 100 < critChance) {
        UIUtils::displayText(string(BOLD) + string(RED) + "CRITICAL HIT!" + RESET);
        baseDamage *= 2; // Standard double damage for a critical hit
    }
    
    return baseDamage;
}

int Healer::attackProbability(const string &attackType) {
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

int Healer::defendProbability(string defendAction) {
    unsigned int defendProbability = 0;
    
    if(defendAction == "Block" || defendAction == "block") {
        defendProbability = (rand() % 80) + 20;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defendProbability = (rand() % 100) + 15;
    }
    
    else if(defendAction == "Evade" || defendAction == "evade") {
        defendProbability = (rand() % 100) + 10;
    }
    
    return defendProbability;
}

int Healer::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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

