//
//  Healer.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Healer.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Assassin.hpp"

Healer::Healer() {
    name = "";
    level = 1;
    maxArmor = 300;
    currArmor = 300;
    maxHealth = 1300;
    currHealth = 1300;
    maxXP = 0;
    currXP = 200;
}

Healer::Healer(string _name) : Character(_name) {
}

string Healer::getName() {
    return name;
}

string Healer::getAttackType() {
    return attackType;
}

int Healer::getLevel() {
    return level;
}

int Healer::getMaxArmor() {
    return maxArmor;
}

int Healer::getCurrArmor() {
    return currArmor;
}

int Healer::getMaxHealth() {
    return maxHealth;
}

int Healer::getCurrHealth() {
    return currHealth;
}

int Healer::getCurrXP() {
    return currXP;
}

int Healer::getMaxXP() {
    return maxXP;
}
        
void Healer::setName(string _name) {
    name = _name;
}

void Healer::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Healer::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Healer::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Healer::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
        
void Healer::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Healer::setCurrXP(int _currXP) {
    currXP = _currXP;
}
        
void Healer::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

int Healer::attack(const string &attackType) {

    int baseDamage = 0;
    int healthCap = maxHealth - 10; // health should not exceed max amount at any particular level

    //Special Ability: First Aid, Chronic Abrasion
    if(attackType == "Light" || attackType == "light") {
        if(lightAttackCount % 2 == 1) {
            baseDamage = 90;
        }
        else {
            baseDamage = 45;
        }
        lightAttackCount++;
        
        if(currHealth < healthCap) {
            currHealth = currHealth + 10;
        }
    }
    else if(attackType == "Normal" || attackType == "normal") {
        if(normalAttackCount % 2 == 1) {
            baseDamage = 150;
        }
        else {
            baseDamage = 75;
        }
        normalAttackCount++;
    }
    else if(attackType == "Heavy" || attackType == "Heavy") {
        if(heavyAttackCount % 2 == 1) {
            baseDamage = 210;
        }
        else {
            baseDamage = 105;
        }
        heavyAttackCount++;
    }

    // Critical hit: 10% chance to double the damage.
    const int critChance = 10; // 10 percent chance
    if(rand() % 100 < critChance) {
        cout << "CRITICAL HIT!" << endl;
        baseDamage *= 2;
    }
    
    attackValue = baseDamage;
    return attackValue;
}

int Healer::attackProbability(string attackType) {
    srand((unsigned int)time(0));
    int attackProbability = 0;
    
    if(attackType == "Heavy" || attackType == "heavy") {
        attackProbability = (rand() % 50) + 1;
    }
    
    else if(attackType == "Normal" || attackType == "normal") {
        attackProbability = (rand() % 90) + 1;
    }
    
    else if(attackType == "Light" || attackType == "light") {
        attackProbability = rand() % 100;
    }
    
    return attackProbability;
}

int Healer::defend(string defendAction) {
    int defenseAttack = 0;
    srand((unsigned int) time(0));
    
    if(defendAction == "Block" || defendAction == "block") {
        defenseAttack = rand() % 100;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defenseAttack = rand() % 100;
    }
    
    else if(defendAction == "Evade" || defendAction == "evade") {
        defenseAttack = rand() % 100;
    }
    
    return defenseAttack;
}

int Healer::decreaseHealth(string characterType, int attackValue, string attackType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    if(characterType == "Warrior" || characterType == "warrior") {
        attackValue = warrior.attack(attackType);
    }
    
    else if(characterType == "Wizard" || characterType == "wizard") {
        attackValue = wizard.attack(attackType);
    }
    
    else if(characterType == "Healer" || characterType == "healer") {
        attackValue = healer.attack(attackType);
    }
    
    else if(characterType == "Assassin" || characterType == "assassin") {
        attackValue = assassin.attack(attackType);
    }
    
    int newArmor = currArmor - attackValue;
    if (newArmor < 0) {
        int overflowDamage = -newArmor; // Damage exceeding current armor
        currArmor = 0;
        // Apply leftover damage to health
        currHealth = currHealth - overflowDamage;
    } else {
        currArmor = newArmor;
    }

    return currArmor;
}

int Healer::decreaseArmor(string characterType, int attackValue, string attackType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    if(characterType == "Warrior" || characterType == "warrior") {
        attackValue = warrior.attack(attackType);
    }
    
    else if(characterType == "Wizard" || characterType == "wizard") {
        attackValue = wizard.attack(attackType);
    }
    
    else if(characterType == "Healer" || characterType == "healer") {
        attackValue = healer.attack(attackType);
    }
    
    else if(characterType == "Assassin" || characterType == "assassin") {
        attackValue = assassin.attack(attackType);
    }
    
    currArmor = currArmor - attackValue;
    
    return currArmor;
}

int Healer::levelUp(const int &currHealth, const int &enemyCurrHealth) {
    //User wins
    if((enemyCurrHealth <= 0) && (currHealth > enemyCurrHealth)) {
        currXP += 500;
    }
    
    //CPU wins
    else if((currHealth <= 0) && (enemyCurrHealth > currHealth)) {
        currXP += 250;
    }

    if(currXP > maxXP) {
        currXP = currXP - maxXP;
        maxXP = maxXP * 2;
        level++;
    }
    
    return level;
}

