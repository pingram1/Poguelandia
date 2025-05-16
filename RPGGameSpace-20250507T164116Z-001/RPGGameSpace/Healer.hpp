//
//  Healer.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Healer_hpp
#define Healer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Character.hpp"

using namespace std;

class Healer : public Character {
    private:
        string name;
        string attackType;
        int attackValue;
        int lightAttackCount, normalAttackCount, heavyAttackCount = 0;
        int level;
        int maxArmor;
        unsigned int currArmor;
        int maxHealth;
        int currHealth;
        int currXP;
        int maxXP;
    public:
        Healer();
        Healer(string);
        string getName();
        string getAttackType();
        int getLevel();
        int getMaxArmor();
        int getCurrArmor();
        int getMaxHealth();
        int getCurrHealth();
        int getCurrXP();
        int getMaxXP();
        void setName(string);
        void setAttackType(string);
        void setLevel(int);
        void setMaxArmor(int);
        void setCurrArmor(int);
        void setMaxHealth(int);
        void setCurrHealth(int);
        void setCurrXP(int);
        void setMaxXP(int);
        int attack(const string &action) override; // returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override;
        int defendProbability(string) override; // returns defend or evade move (abilities vary per character type)
        int decreaseHealth(string, int, string); // responsible for taking armor/health from character when successfully attacked
        int decreaseArmor(string, int, string);
        int levelUp(const int &, const int &) override;
};

#endif
