//
//  Enemy.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/25/23.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "Character.hpp"

class Enemy : public Character {
    private:
        string name;
        string characterType;
        string attackType;
        int level;
        int maxArmor;
        unsigned int currArmor;
        int maxHealth;
        int currHealth;
        int currXP;
        int maxXP;
    public:
        Enemy();
        Enemy(string);
        string getName();
        string getCharacterType();
        string getAttackType();
        int getLevel();
        int getMaxArmor();
        int getCurrArmor();
        int getMaxHealth();
        int getCurrHealth();
        int getCurrXP();
        int getMaxXP();
        void setName(string);
        void setCharacterType(string);
        void setAttackType(string);
        void setLevel(int);
        void setMaxArmor(int);
        void setCurrArmor(int);
        void setMaxHealth(int);
        void setCurrHealth(int);
        void setCurrXP(int);
        void setMaxXP(int);
        int attack(string, string);
        int attack(const string &action) override;
        int attackProbability(const string &action) override;
        int defendProbability(string) override;
        int decreaseHealth(string, int, string); //takes in a string of the character type and decreases health according to that character's stats
        int decreaseArmor(string, int, string);
        string randomizeEnemyTypes();
        string randomizeEnemyActions() override;
        int levelUp(const int &, const int &) override; //inheritance for each class (adjusted values will vary per class)
};

#endif // Enemy_hpp