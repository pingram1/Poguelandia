//
//  Healer.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Healer.hpp"

Healer::Healer() {
    characterType = "Healer";
    level = 1;
    maxArmor = 300;
    currArmor = 300;
    maxHealth = 1300;
    currHealth = 1300;
    maxXP = 0;
    currXP = 200;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

Healer::Healer(string _name) : Character(_name) {
    characterType = "Healer";
    maxHealth = 1300;
    currHealth = 1300;
    maxArmor = 300;
    currArmor = 300;
    level = 1;
    maxXP = 200;
    currXP = 0;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
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

