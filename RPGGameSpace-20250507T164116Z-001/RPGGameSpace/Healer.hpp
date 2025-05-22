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
        int lightAttackCount, normalAttackCount, heavyAttackCount = 0;
    public:
        Healer();
        Healer(string);
        int attack(const string &action) override; // returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override;
        int defendProbability(string) override; // returns defend or evade move (abilities vary per character type)
        int levelUp(const int &, const int &) override;
};

#endif
