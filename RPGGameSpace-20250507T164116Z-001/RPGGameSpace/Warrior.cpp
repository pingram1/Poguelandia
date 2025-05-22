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

Warrior::Warrior() : Character() {
    characterType = "Warrior";
    level = 1;
    maxArmor = 200;
    currArmor = 200;
    maxHealth = 1200;
    currHealth = 1200;
    maxXP = 200;
    currXP = 0;
}

Warrior::Warrior(string _name) : Character(_name) {
    characterType = "Warrior";
    maxHealth = 1200;   
    currHealth = 1200;  
    maxArmor = 200;    
    currArmor = 200;   
    level = 1;   
    maxXP = 200;
    currXP = 0;      
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
    
    return baseDamage;
}

int Warrior::attackProbability(const string &attackType) {
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



