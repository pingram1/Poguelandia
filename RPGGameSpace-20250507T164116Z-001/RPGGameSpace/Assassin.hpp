//
//  Assassin.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Assassin_hpp
#define Assassin_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Character.hpp"

using namespace std;

class Assassin : public Character {
    private:
        string name;
        string attackType;
        int lightAttackCount, normalAttackCount, heavyAttackCount = 0;
        int attackValue;
        int level;
        int maxArmor;
        unsigned int currArmor;
        int maxHealth;
        int currHealth;
        int currXP;
        int maxXP;
    public:
        Assassin();
        Assassin(string);
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
        int attack(const string &action) override; //returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override;
        int defendProbability(string) override; //returns defend or evade move (abilities vary per character type)
        int decreaseHealth(string, int, string);
        int decreaseArmor(string, int, string); 
        int levelUp(const int &, const int &) override;
};

#endif
