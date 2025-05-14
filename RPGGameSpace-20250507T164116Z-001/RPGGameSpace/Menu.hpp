//
//  Menu.hpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include "Character.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class Menu {
    private:
        string menuName;
        string menuCharacterType;
        void typeEffect(const string&, int);
        void displayHealthBar(const string& name, int hp, int maxHp);
    public:
        void MainMenu();
        void NewGameMenu();
        void LoadGameMenu(Character& character);
        void SavedGameMenu(Character& character); 
        void BaseGameMenu(string, string, Character*);
        void BattleMenu1(string, Character*);
        void BattleMenu2(string, Character*);
        void BattleMenu3(string, int, Character*, Enemy*);
        void BattleMenu4(string, bool, Character*, Enemy*);
        void BattleMenu5(string, string, bool, Character*, Enemy*);
        void BattleMenu6(string, bool, Character*, Enemy*);
        void EndBattleMenu(bool, int);
        void ViewCharactersMenu(string);
        void QuitMenu();
        void QuitMenu2();
};

#endif /* Menu_hpp */
