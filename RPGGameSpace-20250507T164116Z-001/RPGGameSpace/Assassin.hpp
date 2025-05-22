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
        int lightAttackCount, normalAttackCount, heavyAttackCount = 0;
    public:
        Assassin();
        Assassin(string);
        int attack(const string &attackType) override; //returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override;
        int defendProbability(string) override; //returns defend or evade move (abilities vary per character type)
        int levelUp(const int &, const int &) override;
};

#endif
