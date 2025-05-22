//
//  Warrior.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Warrior_hpp
#define Warrior_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include "Character.hpp"

using namespace std;

class Warrior : public Character {
    public:
        Warrior();
        Warrior(string);
        int attack(const string &action) override; //returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override; //returns an int 1-100 to land attack vs. attack or defend
        int defendProbability(string) override; //returns defend or evade move (abilities vary per character type)
        int levelUp(const int &, const int &) override;
};

#endif
