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
    public:
        Enemy();
        Enemy(string, string);
        int attack(string, string);
        int attack(const string &action) override;
        int attackProbability(const string &action) override;
        int defendProbability(string) override;
        int decreaseHealth(string, int, string); //takes in a string of the character type and decreases health according to that character's stats
        int decreaseArmor(string, int, string);
        string randomizeEnemyTypes();
        static string randomizeEnemyTypesStatic();
        string randomizeEnemyActions() override;
        int levelUp(const int &, const int &) override; //inheritance for each class (adjusted values will vary per class)
};

#endif // Enemy_hpp