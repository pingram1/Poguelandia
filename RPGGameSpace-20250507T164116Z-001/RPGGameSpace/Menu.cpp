//
//  Menu.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

// Menu.cpp (Refactored methods)

#include "Menu.hpp"
#include "UIUtils.hpp" // Include UIUtils header
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

using namespace std;

// ANSI color codes (These will eventually be replaced by GUI elements, but for now, keep them for console compatibility)
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Function to display a health bar (This function should also be refactored to use UIUtils or a separate GUI component later)
void displayHealthBar(const string& name, int hp, int maxHp) {
    int barWidth = 20;
    int filledBars = (hp * barWidth) / maxHp;
    int emptyBars = barWidth - filledBars;
    UIUtils::displayText(string(BOLD) + name + " HP: [" + string(GREEN));
    for (int i = 0; i < filledBars; i++) UIUtils::displayText("|");
    UIUtils::displayText(string(RED));
    for (int i = 0; i < emptyBars; i++) UIUtils::displayText("|");
    UIUtils::displayText(string(RESET) + "] " + to_string(hp) + "/" + to_string(maxHp));
}

void Menu::BaseGameMenu(string menuName, string menuCharacterType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    // Using Character* for polymorphism to avoid repeated code blocks
    Character* displayChar = nullptr;
    if (menuCharacterType == "Warrior") {
        displayChar = &warrior;
    } else if (menuCharacterType == "Wizard") {
        displayChar = &wizard;
    } else if (menuCharacterType == "Healer") {
        displayChar = &healer;
    } else if (menuCharacterType == "Assassin") {
        displayChar = &assassin;
    }

    if (displayChar) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|  Character Name: " + menuName);
        UIUtils::displayText("|  Character Type: " + menuCharacterType);
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(displayChar->getCurrArmor()) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(displayChar->getCurrHealth()));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                  Welcome to Poguelandia, " + menuName + ". This is a land where");
        UIUtils::displayText("|                 champions are made. Your objective is simple. Best every              |");
        UIUtils::displayText("|               oppenent put before you and become champion. You can level up           |");
        UIUtils::displayText("|                 your character and gain new abilities. Fight you way to               |");
        UIUtils::displayText("|                       the top and enjoy the riches of Poguelandia!                    |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                    Continue (Yes/No)?                                 |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BaseGameMenu.");
    }
    
    UIUtils::displayText("");
}

void Menu::QuitMenu() {
    UIUtils::clearScreen();
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                            Are you sure you want to quit?                             |");
    UIUtils::displayText("|                                       (Yes/No)?                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                               by PI   |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("");
}

void Menu::QuitMenu2() {
    UIUtils::clearScreen();
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                          Thanks for playing, see you soon!                            |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                               by PI   |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("");
}

void Menu::BattleMenu1(string menuCharacterType) {
    Warrior warrior;
    Wizard wizard;
    Healer healer;
    Assassin assassin;
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    Character* displayChar = nullptr;
    string specialAbilityInfo = "";

    if(menuCharacterType == "Warrior") {
        displayChar = &warrior;
        specialAbilityInfo = R"(                      you do! Warriors have a War Cry; when your HP                    
                      becomes 250 or lower, you deal double damage.                    )";
    }
    else if(menuCharacterType == "Wizard") {
        displayChar = &wizard;
        specialAbilityInfo = R"(                      you do! Wizards have Mystic Heal; you receive                    
                    50 HP and 10 armor points with every light attack.                 )";
    }
    else if(menuCharacterType == "Healer") {
        displayChar = &healer;
        specialAbilityInfo = R"(                 you do! Healers have 2, First Aid and Chronic Abrasion.               
       You regain 10 HP with every move and deal 100% damage every other attack.       )";
    }
    else if(menuCharacterType == "Assassin") {
        displayChar = &assassin;
        specialAbilityInfo = R"(                 you do! Assassins have Sneaky Quick; every first attack               
                       deals double (because they strike twice).                       )";
    }
    
    if (displayChar) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(displayChar->getCurrArmor()) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(displayChar->getCurrHealth()));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                 Before you go into battle, we thought you should know                 |");
        UIUtils::displayText("|                your character's stats and abilities. It looks like you                |");
        UIUtils::displayText("|                                 choose to be a " + menuCharacterType + "                                |");
        if (menuCharacterType == "Warrior") {
            UIUtils::displayText("|                          Great pick, very fast, very powerful.                        |");
        } else if (menuCharacterType == "Wizard") {
            UIUtils::displayText("|               Very useful for players that enjoy a strong ranged attack.              |");
        } else if (menuCharacterType == "Healer") {
            UIUtils::displayText("|                          Very quick, extremely high defense.                          |");
        } else if (menuCharacterType == "Assassin") {
            UIUtils::displayText("|                   Substitutes brute force for raw speed and agility.                  |");
        }
        UIUtils::displayText("|                  If you're wondering if you have any special abilites,                |");
        UIUtils::displayText(specialAbilityInfo);
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                Now it's time for battle!                              |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu1.");
    }
    
    UIUtils::displayText("");
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





