//
//  Wizard.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Wizard.hpp"
#include "Warrior.hpp"
#include "Healer.hpp"
#include "Assassin.hpp"

Wizard::Wizard() {
    name = "";
    level = 1;
    maxArmor = 80;
    currArmor = 80;
    maxHealth = 1000;
    currHealth = 1000;
    maxXP = 0;
    currXP = 200;
}

Wizard::Wizard(string _name) : Character(_name) {
    setCharacterType("Wizard");
    setMaxHealth(1000);
    setCurrHealth(1000);
    setMaxArmor(80);
    setCurrArmor(80);
    setLevel(1);
}

string Wizard::getName() {
    return name;
}

string Wizard::getAttackType() {
    return attackType;
}

int Wizard::getLevel() {
    return level;
}

int Wizard::getMaxArmor() {
    return maxArmor;
}

int Wizard::getCurrArmor() {
    return currArmor;
}

int Wizard::getMaxHealth() {
    return maxHealth;
}

int Wizard::getCurrHealth() {
    return currHealth;
}

int Wizard::getCurrXP() {
    return currXP;
}

int Wizard::getMaxXP() {
    return maxXP;
}
        
void Wizard::setName(string _name) {
    name = _name;
}

void Wizard::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Wizard::setLevel(int _level) {
    level = _level;
}

void Wizard::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Wizard::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Wizard::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
        
void Wizard::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Wizard::setCurrXP(int _currXP) {
    currXP = _currXP;
}
        
void Wizard::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

int Wizard::attack(const string &attackType) {
    
    int baseDamage = 0;
    unsigned int armorCap = maxArmor - 10; //armor should not exceed max amount at any particular level
    int healthCap = maxHealth - 50; //health should not exceed max amount at any particular level
    
    //Special Ability: Mystic Heal
    if(attackType == "Light" || attackType == "light") {
        baseDamage = 65;
        if(currArmor <= armorCap) {
            currArmor = currArmor + 10;
        }
        if(currHealth <= healthCap) {
            currHealth = currHealth + 50;
        }
    }
    else if(attackType == "Normal" || attackType == "normal") {
        baseDamage = 95;
    }
    else if(attackType == "Heavy" || attackType == "heavy") {
        baseDamage = 135;
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

int Wizard::attackProbability(const string &attackType) {
    srand((unsigned int)time(0));
    int attackProbability = 0;
    
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
    srand((unsigned int) time(0));
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

int Wizard::decreaseHealth(string characterType, int attackValue, string attackType) {
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

int Wizard::decreaseArmor(string characterType, int attackValue, string attackType) {
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

int Wizard::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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
