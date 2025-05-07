//
//  Assassin.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Assassin.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Healer.hpp"

Assassin::Assassin() {
    name = "";
    level = 1;
    maxArmor = 150;
    currArmor = 150;
    maxHealth = 1100;
    currHealth = 1100;
    maxXP = 0;
    currXP = 200;
}

Assassin::Assassin(string _name) {
    name = _name;
}

string Assassin::getName() {
    return name;
}

string Assassin::getAttackType() {
    return attackType;
}

int Assassin::getLevel() {
    return level;
}

int Assassin::getMaxArmor() {
    return maxArmor;
}

int Assassin::getCurrArmor() {
    return currArmor;
}

int Assassin::getMaxHealth() {
    return maxHealth;
}

int Assassin::getCurrHealth() {
    return currHealth;
}

int Assassin::getCurrXP() {
    return currXP;
}

int Assassin::getMaxXP() {
    return maxXP;
}
        
void Assassin::setName(string _name) {
    name = _name;
}

void Assassin::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Assassin::setLevel(int _level) {
    level = _level;
}

void Assassin::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Assassin::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Assassin::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
        
void Assassin::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Assassin::setCurrXP(int _currXP) {
    currXP = _currXP;
}
        
void Assassin::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

int Assassin::attack(const string &attackType) {

    int baseDamage = 0;

    //Special Ability: Sneaky Quick
    if((attackType == "Light" || attackType == "light") && (lightAttackCount % 2) == 0) {
        lightAttackCount++;
        baseDamage = 140;
    }
    else if((attackType == "Normal" || attackType == "normal") && (normalAttackCount % 3) == 0) {
        normalAttackCount++;
        baseDamage = 200;
    }
    else if((attackType == "Heavy" || attackType == "heavy") && (heavyAttackCount % 3) == 0) {
        heavyAttackCount++;
        baseDamage = 260;
    }

    
    else if((attackType == "Light" || attackType == "light") && (lightAttackCount % 2) > 0) {
        lightAttackCount++;
        baseDamage = 70;
    }
    else if((attackType == "Normal" || attackType == "normal") && (normalAttackCount % 3) > 0) {
        normalAttackCount++;
        baseDamage = 100;
    }
    else if((attackType == "Heavy" || attackType == "heavy") && (heavyAttackCount % 3) > 0) {
        heavyAttackCount++;
        baseDamage = 130;
    }
    
    // Critical hit: 25% chance to double the damage.
    const int critChance = 25; // 25 percent chance
    if(rand() % 100 < critChance) {
        cout << "CRITICAL HIT!" << endl;
        baseDamage *= 2;
    }
    
    attackValue = baseDamage;
    return attackValue;
}

int Assassin::attackProbability(string attackType) {
    srand((unsigned int)time(0));
    int attackProbability = 0;
    
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

int Assassin::defend(string defendAction) {
    int defenseAttack = 0;
    srand((unsigned int) time(0));
    
    if(defendAction == "Block" || defendAction == "block") {
        defenseAttack = rand() % 100;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defenseAttack = rand() % 100;
    }
    
    //Assassins have 50% chance to evade an attack
    else if(defendAction == "Evade" || defendAction == "evade") {
        defenseAttack = rand() % 2 + 1;
        if(defenseAttack % 2 == 0) {
            defenseAttack = 100;
        }
    }
    
    return defenseAttack;
}

int Assassin::decreaseHealth(string characterType, int attackValue, string attackType) {
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
    
    currHealth = currHealth - attackValue;
    
    return currHealth;
}

int Assassin::decreaseArmor(string characterType, int attackValue, string attackType) {
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

int Assassin::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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

