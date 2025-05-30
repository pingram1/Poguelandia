//
//  Character.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Character.hpp"

Character::Character() {
    name = "";
    level = 1;
    currArmor = 0;
    maxArmor = 0;
    currHealth = 0;
    maxHealth = 0;
    maxXP = 200;
    currXP = 0;
}

Character::Character(string _name) {
    name = _name;
}

string Character::getName() const {
    return name;
}

string Character::getCharacterType() const {
    return characterType;
}

string Character::getAttackType() const {
    return attackType;
}

int Character::getLevel() const {
    return level;
}

int Character::getMaxArmor() const {
    return maxArmor;
}

int Character::getCurrArmor() const {
    return currArmor;
}

int Character::getMaxHealth() const {
    return maxHealth;
}

int Character::getCurrHealth() const {
    return currHealth;
}

int Character::getCurrXP() const {
    return currXP;
}

int Character::getMaxXP() const {
    return maxXP;
}
        
void Character::setName(string _name) {
    name = _name;
}

void Character::setCharacterType(string& _characterType) {
    characterType = _characterType;
}

void Character::setAttackType(string _attackType) {
    attackType = _attackType;
}

void Character::setLevel(int _level) {
    level = _level;
}

void Character::setMaxArmor(int _maxArmor) {
    maxArmor = _maxArmor;
}

void Character::setCurrArmor(int _currArmor) {
    currArmor = _currArmor;
}

void Character::setMaxHealth(int _maxHealth) {
    maxHealth = _maxHealth;
}
        
void Character::setCurrHealth(int _currHealth) {
    currHealth = _currHealth;
}

void Character::setCurrXP(int _currXP) {
    currXP = _currXP;
}
        
void Character::setMaxXP(int _maxXP) {
    maxXP = _maxXP;
}

int Character::levelUp(const int &currHealth, const int &enemyCurrHealth) {
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

