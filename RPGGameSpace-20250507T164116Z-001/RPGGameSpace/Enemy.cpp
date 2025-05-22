//
//  Enemy.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/25/23.
//

#include "Enemy.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Healer.hpp"
#include "Assassin.hpp"
#include <cstdlib>
#include <ctime>

Enemy::Enemy() {
    name = "";
    level = 1;
    maxArmor = 180;
    currArmor = 180;
    maxHealth = 1150;
    currHealth = 1150;
    maxXP = 200;
    currXP = 0;
}

Enemy::Enemy(string _name, string _enemyCharacterType) : Character(_name) {
    characterType = _enemyCharacterType; // Set the character type
    level = 1;
    currXP = 0;
    maxXP = 200; // Standard XP

    if (_enemyCharacterType == "Warrior") {
        maxHealth = 1200; currHealth = 1200;
        maxArmor = 200; currArmor = 200;
    } else if (_enemyCharacterType == "Wizard") {
        maxHealth = 1000; currHealth = 1000;
        maxArmor = 80; currArmor = 80;
    } else if (_enemyCharacterType == "Healer") {
        maxHealth = 1300; currHealth = 1300;
        maxArmor = 300; currArmor = 300;
    } else if (_enemyCharacterType == "Assassin") {
        maxHealth = 1100; currHealth = 1100;
        maxArmor = 150; currArmor = 150;
    } else { // Default/Generic Enemy Stats if type is unknown
        maxHealth = 1150; currHealth = 1150;
        maxArmor = 180; currArmor = 180;
    }
}

// Override the pure virtual function attack(const string&) from Character.
// This override simply calls the two-argument version, passing the enemy's character type.
int Enemy::attack(const string &action) {
    int baseDamage = 0;
    string enemyOwnType = getCharacterType(); // Or this->characterType if protected

    // This should mirror the player classes' base damages, or have unique enemy values.
    if (enemyOwnType == "Warrior") {
        if (action == "Light") baseDamage = 75; // Warrior enemy light attack
        else if (action == "Normal") baseDamage = 100;
        else if (action == "Heavy") baseDamage = 125;
        // Add War Cry logic if enemy warriors can also have it
        // if (getCurrHealth() <= /* some threshold */) baseDamage *= 2;
    } else if (enemyOwnType == "Wizard") {
        if (action == "Light") baseDamage = 60; // Wizard enemy light attack
        else if (action == "Normal") baseDamage = 90;
        else if (action == "Heavy") baseDamage = 130;
        // Add Mystic Heal logic for enemy wizards if they use light attacks
        // if (action == "Light") { /* heal self slightly */ }
    } else if (enemyOwnType == "Healer") {
        // ... Healer enemy logic (Chronic Abrasion, First Aid)
    } else if (enemyOwnType == "Assassin") {
        // ... Assassin enemy logic (Sneaky Quick)
    } else {
        // Default enemy attack if type is unknown or generic
        if (action == "Light") baseDamage = 50;
        else if (action == "Normal") baseDamage = 70;
        else if (action == "Heavy") baseDamage = 90;
    }

    // Generic critical hit chance for all enemies (can be type-specific too)
    const int critChance = 15; // e.g., 15% crit chance for enemies
    if (rand() % 100 < critChance) {
        cout << "ENEMY CRITICAL HIT!" << endl;
        baseDamage *= 2;
    }
    return baseDamage;
}

int Enemy::attackProbability(const string &attackType) {
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

int Enemy::defendProbability(string enemyAction) {
    unsigned int defendProbability = 0;

    if(enemyAction == "Block" || enemyAction == "block") {
        defendProbability = rand() % 100;
    }
    else if(enemyAction == "Parry" || enemyAction == "parry") {
        defendProbability = rand() % 100;
    }
    else if(enemyAction == "Evade" || enemyAction == "evade") {
        defendProbability = rand() % 100;
    }

    return defendProbability;
}

string Enemy::randomizeEnemyTypes() {
    string enemyType = "";
    string enemy1 = "Warrior";
    string enemy2 = "Wizard";
    string enemy3 = "Healer";
    string enemy4 = "Assassin";

    int randNum = rand() % 4 + 1;

    if(randNum == 1) {
        enemyType = enemy1;
    }
    else if(randNum == 2) {
        enemyType = enemy2;
    }
    else if(randNum == 3) {
        enemyType = enemy3;
    }
    else if(randNum == 4) {
        enemyType = enemy4;
    }

    return enemyType;
}

string Enemy::randomizeEnemyTypesStatic() {
    string enemyType = "";
    string types[] = {"Warrior", "Wizard", "Healer", "Assassin"};
    int randNum = rand() % 4;
    enemyType = types[randNum];
    
    return enemyType;
}

string Enemy::randomizeEnemyActions() {
    string enemyAction = "";
    string action1 = "Light";
    string action2 = "Normal";
    string action3 = "Heavy";
    string action4 = "Block";
    string action5 = "Parry";
    string action6 = "Evade";

    int randNum = (rand() % 6) + 1;

    if(randNum == 1) {
        enemyAction = action1;
    }
    else if(randNum == 2) {
        enemyAction = action2;
    }
    else if(randNum == 3) {
        enemyAction = action3;
    }
    else if(randNum == 4) {
        enemyAction = action4;
    }
    else if(randNum == 5) {
        enemyAction = action5;
    }
    else if(randNum == 6) {
        enemyAction = action6;
    }

    return enemyAction;
}

int Enemy::levelUp(const int &currHealth, const int &enemyCurrHealth) {
    if ((enemyCurrHealth <= 0) && (currHealth > enemyCurrHealth)) {
        currXP += 500;
    }
    else if ((currHealth <= 0) && (enemyCurrHealth > currHealth)) {
        currXP += 250;
    }
    if (currXP > maxXP) {
        currXP = currXP - maxXP;
        maxXP *= 2;
        level++;
    }
    return level;
}