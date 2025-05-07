//
//  Menu.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include "Menu.hpp"
#include "Character.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Healer.hpp"
#include "Assassin.hpp"
#include "Enemy.hpp"
#include "SaveLoad.hpp"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
#include "Utils.hpp"

using namespace std;

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Function to display a health bar
void displayHealthBar(const string& name, int hp, int maxHp) {
    int barWidth = 20;
    int filledBars = (hp * barWidth) / maxHp;
    int emptyBars = barWidth - filledBars;
    cout << BOLD << name << " HP: [" << GREEN;
    for (int i = 0; i < filledBars; i++) cout << "|";
    cout << RED;
    for (int i = 0; i < emptyBars; i++) cout << "|";
    cout << RESET << "] " << hp << "/" << maxHp << endl;
}

void Menu::MainMenu() {
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                          Welcome to Poguelandia, Traveler.                            |" << endl;
    cout << "|                                  DARE to Adventure!                                   |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                     1. New Game                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                     2. Load Game                                      |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                  3. View Characters                                   |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                       4. Quit                                         |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                               by PI   |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << endl;
}

void Menu::NewGameMenu() {
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                              Select your character class:                             |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                           Warrior - Special Ability: War Cry                          |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                          Wizard - Special Ability: Mystic Heal                        |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                   Healer - Special Ability: First Aid, Chronic Abrasion               |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                        Assassin - Special Ability: Sneaky Quick                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                          Quit                                         |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                               by PI   |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << endl;
}

void Menu::BaseGameMenu(string menuName, string menuCharacterType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Character Name: " << menuName << endl;
        cout << "|  Character Type: " << menuCharacterType << endl;
        cout << "|  Level: " << warrior.getLevel() << endl;
        cout << "|  Armor: " << warrior.getCurrArmor() << " / " << warrior.getMaxArmor() << "   Health: " << warrior.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Welcome to Poguelandia, " << menuName << ". This is a land where" << endl;
        cout << "|                 champions are made. Your objective is simple. Best every              |" << endl;
        cout << "|               oppenent put before you and become champion. You can level up           |" << endl;
        cout << "|                 your character and gain new abilities. Fight you way to               |" << endl;
        cout << "|                       the top and enjoy the riches of Poguelandia!                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                    Continue (Yes/No)?                                 |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Character Name: " << menuName << endl;
        cout << "|  Character Type: " << menuCharacterType << endl;
        cout << "|  Level: " << wizard.getLevel() << endl;
        cout << "|  Armor: " << wizard.getCurrArmor() << " / " << wizard.getMaxArmor() << "   Health: " << wizard.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Welcome to Poguelandia, " << menuName << ". This is a land where" << endl;
        cout << "|                 champions are made. Your objective is simple. Best every              |" << endl;
        cout << "|               oppenent put before you and become champion. You can level up           |" << endl;
        cout << "|                 your character and gain new abilities. Fight you way to               |" << endl;
        cout << "|                       the top and enjoy the riches of Poguelandia!                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                    Continue (Yes/No)?                                 |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Character Name: " << menuName << endl;
        cout << "|  Character Type: " << menuCharacterType << endl;
        cout << "|  Level: " << healer.getLevel() << endl;
        cout << "|  Armor: " << healer.getCurrArmor() << " / " << healer.getMaxArmor() << "   Health: " << healer.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Welcome to Poguelandia, " << menuName << ". This is a land where" << endl;
        cout << "|                 champions are made. Your objective is simple. Best every              |" << endl;
        cout << "|               oppenent put before you and become champion. You can level up           |" << endl;
        cout << "|                 your character and gain new abilities. Fight you way to               |" << endl;
        cout << "|                       the top and enjoy the riches of Poguelandia!                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                    Continue (Yes/No)?                                 |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Character Name: " << menuName << endl;
        cout << "|  Character Type: " << menuCharacterType << endl;
        cout << "|  Level: " << assassin.getLevel() << endl;
        cout << "|  Armor: " << assassin.getCurrArmor() << " / " << assassin.getMaxArmor() << "   Health: " << assassin.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Welcome to Poguelandia, " << menuName << ". This is a land where" << endl;
        cout << "|                 champions are made. Your objective is simple. Best every              |" << endl;
        cout << "|               oppenent put before you and become champion. You can level up           |" << endl;
        cout << "|                 your character and gain new abilities. Fight you way to               |" << endl;
        cout << "|                       the top and enjoy the riches of Poguelandia!                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                    Continue (Yes/No)?                                 |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::QuitMenu() {
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                            Are you sure you want to quit?                             |" << endl;
    cout << "|                                       (Yes/No)?                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                               by PI   |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << endl;
}

void Menu::QuitMenu2() {
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                          Thanks for playing, see you soon!                            |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                               by PI   |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << endl;
}

void Menu::BattleMenu1(string menuCharacterType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                        << endl;
        cout << "|  Armor: " << warrior.getCurrArmor() << " / " << warrior.getMaxArmor() << "   Health: " << warrior.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                 Before you go into battle, we thought you should know                 |" << endl;
        cout << "|                your character's stats and abilities. It looks like you                |" << endl;
        cout << "|                                 choose to be a " << menuCharacterType << "                                |" << endl;
        cout << "|                          Great pick, very fast, very powerful.                        |" << endl;
        cout << "|                  If you're wondering if you have any special abilites,                |" << endl;
        cout << "|                      you do! Warriors have a War Cry; when your HP                    |" << endl;
        cout << "|                      becomes 250 or lower, you deal double damage.                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                Now it's time for battle!                              |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                        << endl;
        cout << "|  Armor: " << wizard.getCurrArmor() << " / " << wizard.getMaxArmor() << "   Health: " << wizard.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                 Before you go into battle, we thought you should know                 |" << endl;
        cout << "|                your character's stats and abilities. It looks like you                |" << endl;
        cout << "|                                 choose to be a " << menuCharacterType << "                                 |" << endl;
        cout << "|               Very useful for players that enjoy a strong ranged attack.              |" << endl;
        cout << "|                  If you're wondering if you have any special abilites,                |" << endl;
        cout << "|                      you do! Wizards have Mystic Heal; you receive                    |" << endl;
        cout << "|                    50 HP and 10 armor points with every light attack.                 |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                Now it's time for battle!                              |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                        << endl;
        cout << "|  Armor: " << healer.getCurrArmor() << " / " << healer.getMaxArmor() << "   Health: " << healer.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                 Before you go into battle, we thought you should know                 |" << endl;
        cout << "|                your character's stats and abilities. It looks like you                |" << endl;
        cout << "|                                 choose to be a " << menuCharacterType << "                                 |" << endl;
        cout << "|                          Very quick, extremely high defense.                          |" << endl;
        cout << "|                  If you're wondering if you have any special abilites,                |" << endl;
        cout << "|                 you do! Healers have 2, First Aid and Chronic Abrasion.               |" << endl;
        cout << "|       You regain 10 HP with every move and deal 100% damage every other attack.       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                Now it's time for battle!                              |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                        << endl;
        cout << "|  Armor: " << assassin.getCurrArmor() << " / " << assassin.getMaxArmor() << "   Health: " << assassin.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                 Before you go into battle, we thought you should know                 |" << endl;
        cout << "|                your character's stats and abilities. It looks like you                |" << endl;
        cout << "|                                 choose to be a " << menuCharacterType << "                               |" << endl;
        cout << "|                   Substitutes brute force for raw speed and agility.                  |" << endl;
        cout << "|                  If you're wondering if you have any special abilites,                |" << endl;
        cout << "|                 you do! Assassins have Sneaky Quick; every first attack               |" << endl;
        cout << "|                       deals double (because they strike twice).                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                Now it's time for battle!                              |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::BattleMenu2(string menuCharacterType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                        << endl;
        cout << "|  Armor: " << warrior.getCurrArmor() << " / " << warrior.getMaxArmor() << "   Health: " << warrior.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Get ready to fight, your challenger is approaching.                  |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                        << endl;
        cout << "|  Armor: " << wizard.getCurrArmor() << " / " << wizard.getMaxArmor() << "   Health: " << wizard.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Get ready to fight, your challenger is approaching.                  |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                        << endl;
        cout << "|  Armor: " << healer.getCurrArmor() << " / " << healer.getMaxArmor() << "   Health: " << healer.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Get ready to fight, your challenger is approaching.                  |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                        << endl;
        cout << "|  Armor: " << assassin.getCurrArmor() << " / " << assassin.getMaxArmor() << "   Health: " << assassin.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                  Get ready to fight, your challenger is approaching.                  |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::ViewCharactersMenu(string menuCharacterType) {
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                     Warrior Class                                     |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   These are usually the most powerful character classes in video games. Well esta-    |" << endl;
        cout << "|   blished. in attacks and combat, these power characters have the strongest set of    |" << endl;
        cout << "|   assets to supoort them. For example, they have the best weapons and armor, high     |" << endl;
        cout << "|   health score, attack, and defense. This characters’ class is usually chosen by      |" << endl;
        cout << "|   gamers who prefer a hack and slash-style gameplay.                                  |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Health: 1200                                                                        |" << endl;
        cout << "|   Armor: 200                                                                          |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Special Ability: Character deals double damage when health is at or below 250.      |" << endl;
        cout << "|   Passive Ability: Successful block counter will result in warrior charge that        |" << endl;
        cout << "|                    will take enemy health.                                            |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                      Wizard Class                                     |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   These characters do not usually have traditional weapons but use spells to fight    |" << endl;
        cout << "|   or defend themselves from attacks. They usually have the weakest armor because      |" << endl;
        cout << "|   their strong point is fighting from a distance by throwing spells. Wizards can      |" << endl;
        cout << "|   cast both attack and defense spells and regeneration.                               |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Health: 1000                                                                        |" << endl;
        cout << "|   Armor: 80                                                                           |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Special Ability: Character regains 50HP and 10 armor with every light attack.       |" << endl;
        cout << "|   Passive Ability: Heavy attacks do slightly more damage than all other attacks.      |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                      Healer Class                                     |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   This character class isn't as attack-based as the rest, however, their expert       |" << endl;
        cout << "|   medic skills allow to the constantly regeneration health with every move (attack,   |" << endl;
        cout << "|   defense, evade). This is the only character with higher defense than a warrior      |" << endl;
        cout << "|   and what they lack in power they gain in speed. This character best fits a          |" << endl;
        cout << "|   strategic and conservative player that's looking to last in any fight.              |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Health: 1300                                                                        |" << endl;
        cout << "|   Armor: 300                                                                          |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Special Abilities: Character regains health 10HP with every move (attack, defend,   |" << endl;
        cout << "|                      evade). Character's speed enables them to deal double damage     |" << endl;
        cout << "|                      on every other attack.                                           |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                     Assassin Class                                    |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   This character class has a more subtle approach, unlike warrior’s brute force.      |" << endl;
        cout << "|   They use specific skills, such as stealing, to complete missions. Their abilities   |" << endl;
        cout << "|   revolve around smaller and faster weapons. Assassin / Ninja characters slip         |" << endl;
        cout << "|   in and out easily and have no problem finding places to hide. Players who choose    |" << endl;
        cout << "|   this character class prefer a more cautious but chaotic gameplay style at the       |" << endl;
        cout << "|   same time.                                                                          |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Health: 1100                                                                        |" << endl;
        cout << "|   Armor: 150                                                                          |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|   Special Ability: Speed kills. Every first type of attack does double damage.        |" << endl;
        cout << "|   Passive Ability: Assassin have a 50% chance of executing parries and evades         |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::BattleMenu3(string menuCharacterType, int fightFirst) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    Enemy enemy;
    
    string battlePhrases = "";
    
    if(fightFirst == 1) {
        battlePhrases = "Looks like you're fighting first, make a move";
    }
    
    else if(fightFirst == 2) {
        battlePhrases = "Looks like the enemy gets to make the first move, respond accordingly";
    }
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                          << endl;
        cout << "|  Armor: " << warrior.getCurrArmor() << " / " << warrior.getMaxArmor() << "   Health: " << warrior.getCurrHealth() << endl;
        cout << "|  Opp. Armor: " << enemy.getCurrArmor() << " / " << enemy.getMaxArmor() << "   Health: " << enemy.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                           << endl;
        cout << "|  Armor: " << wizard.getCurrArmor() << " / " << wizard.getMaxArmor() << "   Health: " << wizard.getCurrHealth() << endl;
        cout << "|  Opp. Armor: " << enemy.getCurrArmor() << " / " << enemy.getMaxArmor() << "   Health: " << enemy.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                           << endl;
        cout << "|  Armor: " << healer.getCurrArmor() << " / " << healer.getMaxArmor() << "   Health: " << healer.getCurrHealth() << endl;
        cout << "|  Opp. Armor: " << enemy.getCurrArmor() << " / " << enemy.getMaxArmor() << "   Health: " << enemy.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                         << endl;
        cout << "|  Armor: " << assassin.getCurrArmor() << " / " << assassin.getMaxArmor() << "   Health: " << assassin.getCurrHealth() << endl;
        cout << "|  Opp. Armor: " << enemy.getCurrArmor() << " / " << enemy.getMaxArmor() << "   Health: " << enemy.getCurrHealth() << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::BattleMenu4(string menuCharacterType, bool attackExecuted, int currHealth, int enemyCurrHealth, int currArmor, int enemyCurrArmor) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    Enemy enemy;
    
    string battlePhrases = "";
    
    if(attackExecuted != false) {
        battlePhrases = "Great strike! Keep the pressure on 'em";
    }
    
    else {
        battlePhrases = "Not every strike has to land for you to damage your opponent";
    }

    if(enemyCurrHealth < 0) {
        enemyCurrHealth = 0;
    }
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                          << endl;
        cout << "|  Armor: " << currArmor << " / " << warrior.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << wizard.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << healer.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                         << endl;
        cout << "|  Armor: " << currArmor << " / " << assassin.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::BattleMenu5(string menuCharacterType, string action, bool defendExecuted, int currHealth, int enemyCurrHealth, int currArmor, int enemyCurrArmor) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    Enemy enemy;
    
    string battlePhrases = "";
    
    if(defendExecuted == true && action == "Block") {
        battlePhrases = "Effective block, still hurts a little though";
    }
    
    else if(defendExecuted == true && action == "Parry") {
        battlePhrases = "Great reaction! Now it's time to counter your opponent";
    }
    
    else if(defendExecuted == true && action == "Evade") {
        battlePhrases = "Looks like they missed completely, here's your chance";
    }
    
    //User attack probability is lower than enemy attack/defend probability
    else if((defendExecuted == false) && (action == "Light" || action == "Normal" || action == "Heavy")) {
        battlePhrases = "Maybe try recalibrating your swing ... because you missed";
    }
    
    else if((defendExecuted == false) && (action == "Block" || action == "Parry" || action == "Evade")) {
        battlePhrases = "Ouch. They got you pretty good, maybe you should heal or something";
    }

    /*if(currHealth < 0) {
        currHealth = 0;
    }*/
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                          << endl;
        cout << "|  Armor: " << currArmor << " / " << warrior.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << wizard.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << healer.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                         << endl;
        cout << "|  Armor: " << currArmor << " / " << assassin.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::BattleMenu6(string menuCharacterType, bool doubleDefend, int currHealth, int enemyCurrHealth, int currArmor, int enemyCurrArmor) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    Enemy enemy;
    
    string battlePhrases = "";
    
    if(doubleDefend != false) {
        battlePhrases = "So y'all are just going to stare at each other?";
    }
    
    if(menuCharacterType == "Warrior") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << warrior.getLevel()                                                          << endl;
        cout << "|  Armor: " << currArmor << " / " << warrior.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Wizard") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << wizard.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << wizard.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Healer") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << healer.getLevel()                                                           << endl;
        cout << "|  Armor: " << currArmor << " / " << healer.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else if(menuCharacterType == "Assassin") {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|  Level: " << assassin.getLevel()                                                         << endl;
        cout << "|  Armor: " << currArmor << " / " << assassin.getMaxArmor() << "   Health: " << currHealth << endl;
        cout << "|  Opp. Armor: " << enemyCurrArmor << " / " << enemy.getMaxArmor() << "   Health: " << enemyCurrHealth << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                          *                                                      *     |" << endl;
        cout << "|         *                             *              *            *         *         |" << endl;
        cout << "|                   *          *               *             *                          |" << endl;
        cout << "|       *                   *            *                           *              *   |" << endl;
        cout << "|               *            *                  *        *                   *          |" << endl;
        cout << "|                       *           *                              *                    |" << endl;
        cout << "|        *                                *            *                                |" << endl;
        cout << "|   _________________________________________________________________________________   |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|         |            |             |             |             |            |         |" << endl;
        cout << "|   ______|____________|_____________|_____________|_____________|____________|______   |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|         " << battlePhrases                                                               << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::EndBattleMenu(bool result, int level) {
    if(result) {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                           Only winners deserve the prize.                             |" << endl;
        cout << "|                                  Level Up! Level " << level                              << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                  Save Game (Yes/No)?                                  |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    else {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                        Every great fighter has suffered loss                          |" << endl;
        cout << "|                                  Level Up! Level " << level                              << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                  Save Game (Yes/No)?                                  |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }
    
    cout << endl;
}

void Menu::LoadGameMenu(Character &player) {
    string username, characterType;
    int currHealth, currArmor, level, currXP, maxXP;
    int currLevel = 1; 

    cout << "Enter fighter name to load: ";
    cin >> username;

    if (loadGame(username, characterType, currHealth, currArmor, level, currXP, maxXP)) {
        // Update the player's current state based on the loaded data
        player.setCharacterType(characterType);
        player.setCurrHealth(currHealth);
        player.setCurrArmor(currArmor);
        player.setLevel(currLevel);
        cout << "Game loaded successfully!" << endl;
        
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;                      cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                            ------ Loaded Game State ------                            |" << endl;
        cout << "|                               Character Type: " << characterType;                   
        cout << "|                               Current Health: " << currHealth;                      
        cout << "|                               Current Armor: " << currArmor;                        
        cout << "|                               Current Level: " << currLevel;                        
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    } 
    
    else {
        cout << "*---------------------------------------------------------------------------------------*" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                  Unable to load game :(                               |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                                       |" << endl;
        cout << "|                                                                               by PI   |" << endl;
        cout << "*---------------------------------------------------------------------------------------*" << endl;
    }

    cout << endl;
}

void Menu::SavedGameMenu(Character &player) {
    // Optionally, clear the screen (this is system-dependent)
    // system("clear"); // for Unix-based systems (Linux, macOS)
    
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                Saved Game Details                                     |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|  Type      : " << setw(50) << left << player.getCharacterType() << "|" << endl;
    cout << "|  Level     : " << setw(50) << left << player.getLevel() << "|" << endl;
    cout << "|  Health    : " << setw(25) << left << player.getCurrHealth() 
         << " / " << setw(21) << right << player.getMaxHealth() << "|" << endl;
    cout << "|  Armor     : " << setw(25) << left << player.getCurrArmor() 
         << " / " << setw(21) << right << player.getMaxArmor() << "|" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "|                                                                                       |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "| Options: [R]esume Saved Game    [D]elete Save    [M]ain Menu                          |" << endl;
    cout << "*---------------------------------------------------------------------------------------*" << endl;
    cout << "Enter your choice: ";
}





