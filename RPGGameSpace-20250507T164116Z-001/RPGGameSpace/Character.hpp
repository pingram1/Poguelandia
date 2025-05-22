//
//  Character.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Character {
    protected:
        string name;
        string characterType;
        string attackType;
        int level;
        int maxArmor;
        int currArmor;
        int maxHealth;
        int currHealth;
        int currXP;
        int maxXP;
    public:
        Character();
        Character(string);
        string getName() const;
        string getCharacterType() const;
        string getAttackType() const;
        int getLevel() const;
        int getMaxArmor() const;
        int getCurrArmor() const;
        int getMaxHealth() const;
        int getCurrHealth() const;
        int getCurrXP() const;
        int getMaxXP() const;
        void setName(string);
        void setCharacterType(string& characterType);
        void setAttackType(string);
        void setLevel(int);
        void setMaxArmor(int);
        void setCurrArmor(int);
        void setMaxHealth(int);
        void setCurrHealth(int);
        void setCurrXP(int);
        void setMaxXP(int);
        //int virtual decreaseHealth(string, int, string) = 0; //takes in a string of the character type and decreases health according to that character's stats
        virtual int attackProbability(const string &action) = 0;
        virtual int defendProbability(string) = 0;
        virtual int levelUp(const int &, const int &) = 0; //inheritance for each class (adjusted values will vary per class)
        virtual int attack(const string &action) = 0;
        virtual string randomizeEnemyActions() { return ""; }
        virtual ~Character() {};
};

#endif