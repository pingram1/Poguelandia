//
//  Wizard.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Wizard_hpp
#define Wizard_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Character.hpp"

using namespace std;

class Wizard : public Character {
    private:
        int attackValue;
    public:
        Wizard();
        Wizard(string);
        int attack(const string &action) override; //returns attack (type) value based on user input (light, normal, weak)
        int attackProbability(const string &action) override;
        int defendProbability(string) override; //returns defend or evade move (abilities vary per character type)
        int levelUp(const int &, const int &) override;
};

#endif