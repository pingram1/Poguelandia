//
//  Assassin.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"
#include "Assassin.hpp"

Assassin::Assassin() : Character() {
    characterType = "Assassin";
    level = 1;
    maxArmor = 150;
    currArmor = 150;
    maxHealth = 1100;
    currHealth = 1100;
    maxXP = 200;
    currXP = 0;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
}

Assassin::Assassin(string _name) : Character(_name) {
    characterType = "Assassin";
    maxHealth = 1100;
    currHealth = 1100;
    maxArmor = 150;
    currArmor = 150;
    level = 1;
    currXP = 0;
    maxXP = 200;
    lightAttackCount = 0;
    normalAttackCount = 0;
    heavyAttackCount = 0;
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
        defendProbability = rand() % 100;
    }
    
    else if(defendAction == "Parry" || defendAction == "parry") {
        defendProbability = rand() % 100;
    }
    
    //Assassins have 50% chance to evade an attack
    else if(defendAction == "Evade" || defendAction == "evade") {
        defendProbability = rand() % 2 + 1;
        if(defendProbability % 2 == 0) {
            defendProbability = 100;
        }
    }
    
    return defendProbability;
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

