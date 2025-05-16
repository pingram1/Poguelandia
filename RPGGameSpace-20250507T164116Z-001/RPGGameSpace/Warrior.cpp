//
//  Warrior.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Healer.hpp"
#include "Assassin.hpp"

Warrior::Warrior() {
    name = "";
    level = 1;
    maxArmor = 200;
    currArmor = 200;
    maxHealth = 1200;
    currHealth = 1200;
    maxXP = 200;
    currXP = 0;
}

Warrior::Warrior(string _name) : Character(_name) {
    setCharacterType("Warrior");
    setMaxHealth(1200);   
    setCurrHealth(1200);  
    setMaxArmor(200);    
    setCurrArmor(200);   
    setLevel(1);         
}

string Warrior::getName() {
    return name;
}

string Warrior::getAttackType() {
    return attackType;
}

int Warrior::getLevel() {
    return level;
}

int Warrior::getMaxArmor() {
    return maxArmor;
}

int Warrior::getCurrArmor() {
    return currArmor;
}

int Warrior::getMaxHealth() {
    return maxHealth;
}

int Warrior::getCurrHealth() {
    return currHealth;
}

int Warrior::getCurrXP() {
    return currXP;
}

int Warrior::getMaxXP() {
    return maxXP;
}
        
void Warrior::setName(string _name) {
    name = _name;
}

void Warrior::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Warrior::setLevel(int _level) {
    level = _level;
}

void Warrior::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Warrior::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Warrior::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
        
void Warrior::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Warrior::setCurrXP(int _currXP) {
    currXP = _currXP;
}
        
void Warrior::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

int Warrior::attack(const string &attackType) {
    int baseDamage = 0;

    if(currHealth > 250) {
        if(attackType == "Light" || attackType == "light") {
            baseDamage = 80;
        }
        else if(attackType == "Normal" || attackType == "normal") {
            baseDamage = 110;
        }
        else if(attackType == "Heavy" || attackType == "heavy") {
            baseDamage = 130;
        }
    }

    //Special Ability: War Cry
    else if(currHealth <= 250) {
        if(attackType == "Light" || attackType == "light") {
            baseDamage = 160;
        }
        else if(attackType == "Normal" || attackType == "normal") {
            baseDamage = 220;
        }
        else if(attackType == "Heavy" || attackType == "heavy") {
            baseDamage = 260;
        }
    }

    // Critical hit: 20% chance to double the damage.
    const int critChance = 20; // 20 percent chance
    if(rand() % 100 < critChance) {
        cout << "CRITICAL HIT!" << endl;
        baseDamage *= 2;
    }
    
    attackValue = baseDamage;
    return attackValue;
}

int Warrior::attackProbability(const string &attackType) {
    srand((unsigned int)time(0));
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
    srand((unsigned int)time(0));
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

int Warrior::decreaseHealth(string characterType, int attackValue, string attackType) {
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

int Warrior::decreaseArmor(string characterType, int attackValue, string attackType) {
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

int Warrior::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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



