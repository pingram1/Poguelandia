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

Enemy::Enemy(string _name) : Character(_name) {
}

// Getters
string Enemy::getName() {
    return name;
}

string Enemy::getAttackType() {
    return attackType;
}

int Enemy::getLevel() {
    return level;
}

int Enemy::getMaxArmor() {
    return maxArmor;
}

int Enemy::getCurrArmor() {
    return currArmor;
}

int Enemy::getMaxHealth() {
    return maxHealth;
}

int Enemy::getCurrHealth() {
    return currHealth;
}

int Enemy::getCurrXP() {
    return currXP;
}

int Enemy::getMaxXP() {
    return maxXP;
}

// Setters
void Enemy::setName(string _name) {
    name = _name;
}

void Enemy::setCharacterType(string _characterType) {
    characterType = _characterType;
}

void Enemy::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Enemy::setLevel(int _level) {
    level = _level;
}

void Enemy::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Enemy::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Enemy::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}

void Enemy::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Enemy::setCurrXP(int _currXP) {
    currXP = _currXP;
}

void Enemy::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

// Override the pure virtual function attack(const string&) from Character.
// This override simply calls the two-argument version, passing the enemy's character type.
int Enemy::attack(const string &action) {
    return attack(action, getCharacterType());
}

// Two-argument attack function. It chooses a damage value based on the provided character type.
int Enemy::attack(string attackType, string charType) {
    if (charType == "Warrior") {
        Warrior warriorEnemy;
        return warriorEnemy.attack(attackType);
    } else if (charType == "Wizard") {
        Wizard wizardEnemy;
        return wizardEnemy.attack(attackType);
    } else if (charType == "Healer") {
        Healer healerEnemy;
        return healerEnemy.attack(attackType);
    } else if (charType == "Assassin") {
        Assassin assassinEnemy;
        return assassinEnemy.attack(attackType);
    }
    return 0;
}

int Enemy::attackProbability(string attackType) {
    srand((unsigned int)time(0));
    int attackProbability = 0;

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

int Enemy::defend(string enemyAction) {
    unsigned int defenseProbability = 0;
    srand((unsigned int) time(0));

    if(enemyAction == "Block" || enemyAction == "block") {
        defenseProbability = rand() % 100;
    }
    else if(enemyAction == "Parry" || enemyAction == "parry") {
        defenseProbability = rand() % 100;
    }
    else if(enemyAction == "Evade" || enemyAction == "evade") {
        defenseProbability = rand() % 100;
    }

    return defenseProbability;
}

int Enemy::decreaseHealth(string characterType, int attackValue, string attackType) {
    if(characterType == "Warrior" || characterType == "warrior") {
        Warrior warrior;
        attackValue = warrior.attack(attackType);
    }
    else if(characterType == "Wizard" || characterType == "wizard") {
        Wizard wizard;
        attackValue = wizard.attack(attackType);
    }
    else if(characterType == "Healer" || characterType == "healer") {
        Healer healer;
        attackValue = healer.attack(attackType);
    }
    else if(characterType == "Assassin" || characterType == "assassin") {
        Assassin assassin;
        attackValue = assassin.attack(attackType);
    }

    currHealth = currHealth - attackValue;
    return currHealth;
}

string Enemy::randomizeEnemyTypes() {
    string enemyType = "";
    string enemy1 = "Warrior";
    string enemy2 = "Wizard";
    string enemy3 = "Healer";
    string enemy4 = "Assassin";

    srand((unsigned int) time(0));
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

string Enemy::randomizeEnemyActions() {
    string enemyAction = "";
    string action1 = "Light";
    string action2 = "Normal";
    string action3 = "Heavy";
    string action4 = "Block";
    string action5 = "Parry";
    string action6 = "Evade";

    srand((unsigned int) time(0));
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

int Enemy::decreaseArmor(string characterType, int attackValue, string attackType) {
    if(characterType == "Warrior" || characterType == "warrior") {
        Warrior warrior;
        attackValue = warrior.attack(attackType);
    }
    else if(characterType == "Wizard" || characterType == "wizard") {
        Wizard wizard;
        attackValue = wizard.attack(attackType);
    }
    else if(characterType == "Healer" || characterType == "healer") {
        Healer healer;
        attackValue = healer.attack(attackType);
    }
    else if(characterType == "Assassin" || characterType == "assassin") {
        Assassin assassin;
        attackValue = assassin.attack(attackType);
    }

    currArmor = currArmor - attackValue;
    return currArmor;
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

string Enemy::getCharacterType() {
    return characterType;
}