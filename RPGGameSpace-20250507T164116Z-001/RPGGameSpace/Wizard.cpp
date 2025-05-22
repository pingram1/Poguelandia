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
    characterType = "Wizard";
    level = 1;
    maxArmor = 80;
    currArmor = 80;
    maxHealth = 1000;
    currHealth = 1000;
    maxXP = 0;
    currXP = 200;
}

Wizard::Wizard(string _name) : Character(_name) {
    characterType = "Wizard";
    maxHealth = 1000;
    currHealth = 1000;
    maxArmor = 80;
    currArmor = 80;
    level = 1;
    maxXP = 200;
    currXP = 0;
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
