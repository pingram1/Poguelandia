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

void Menu::MainMenu() {
    UIUtils::clearScreen();
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                          Welcome to Poguelandia, Traveler.                            |");
    UIUtils::displayText("|                                  DARE to Adventure!                                   |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                     1. New Game                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                     2. Load Game                                      |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                  3. View Characters                                   |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                       4. Quit                                         |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                               by PI   |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("");
}

void Menu::NewGameMenu() {
    UIUtils::clearScreen();
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                              Select your character class:                             |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                           Warrior - Special Ability: War Cry                          |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                          Wizard - Special Ability: Mystic Heal                        |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                   Healer - Special Ability: First Aid, Chronic Abrasion               |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                        Assassin - Special Ability: Sneaky Quick                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                          Quit                                         |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                               by PI   |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("");
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
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

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
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(displayChar->getCurrArmor()) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(displayChar->getCurrHealth()));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                          *                         *                                  |");
        UIUtils::displayText("|    *        *                  *        *                                           * |");
        UIUtils::displayText("|                 *  *   *    *        *        *               *                   *   |");
        UIUtils::displayText("|         *         *           *          *               *                            |");
        UIUtils::displayText("|               *                 *    *           *              *                     |");
        UIUtils::displayText("|                       *                   *                           *               |");
        UIUtils::displayText("|        *                      *                      *                                |");
        UIUtils::displayText("|   _________________________________________________________________________________   |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|   ______|____________|_____________|_____________|_____________|____________|______   |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                  Get ready to fight, your challenger is approaching.                  |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu2.");
    }
    
    UIUtils::displayText("");
}

void Menu::ViewCharactersMenu(string menuCharacterType) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if(menuCharacterType == "Warrior") {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                     Warrior Class                                     |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   These are usually the most powerful character classes in video games. Well esta-    |");
        UIUtils::displayText("|   blished. in attacks and combat, these power characters have the strongest set of    |");
        UIUtils::displayText("|   assets to supoort them. For example, they have the best weapons and armor, high     |");
        UIUtils::displayText("|   health score, attack, and defense. This characters’ class is usually chosen by      |");
        UIUtils::displayText("|   gamers who prefer a hack and slash-style gameplay.                                  |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Health: 1200                                                                        |");
        UIUtils::displayText("|   Armor: 200                                                                          |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Special Ability: Character deals double damage when health is at or below 250.      |");
        UIUtils::displayText("|   Passive Ability: Successful block counter will result in warrior charge that        |");
        UIUtils::displayText("|                    will take enemy health.                                            |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    else if(menuCharacterType == "Wizard") {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                      Wizard Class                                     |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   These characters do not usually have traditional weapons but use spells to fight    |");
        UIUtils::displayText("|   or defend themselves from attacks. They usually have the weakest armor because      |");
        UIUtils::displayText("|   their strong point is fighting from a distance by throwing spells. Wizards can      |");
        UIUtils::displayText("|   cast both attack and defense spells and regeneration.                               |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Health: 1000                                                                        |");
        UIUtils::displayText("|   Armor: 80                                                                           |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Special Ability: Character regains 50HP and 10 armor with every light attack.       |");
        UIUtils::displayText("|   Passive Ability: Heavy attacks do slightly more damage than all other attacks.      |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    else if(menuCharacterType == "Healer") {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                      Healer Class                                     |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   This character class isn't as attack-based as the rest, however, their expert       |");
        UIUtils::displayText("|   medic skills allow to the constantly regeneration health with every move (attack,   |");
        UIUtils::displayText("|   defense, evade). This is the only character with higher defense than a warrior      |");
        UIUtils::displayText("|   and what they lack in power they gain in speed. This character best fits a          |");
        UIUtils::displayText("|   strategic and conservative player that's looking to last in any fight.              |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Health: 1300                                                                        |");
        UIUtils::displayText("|   Armor: 300                                                                          |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Special Abilities: Character regains health 10HP with every move (attack, defend,   |");
        UIUtils::displayText("|                      evade). Character's speed enables them to deal double damage     |");
        UIUtils::displayText("|                      on every other attack.                                           |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    else if(menuCharacterType == "Assassin") {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                     Assassin Class                                    |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   This character class has a more subtle approach, unlike warrior’s brute force.      |");
        UIUtils::displayText("|   They use specific skills, such as stealing, to complete missions. Their abilities   |");
        UIUtils::displayText("|   revolve around smaller and faster weapons. Assassin / Ninja characters slip         |");
        UIUtils::displayText("|   in and out easily and have no problem finding places to hide. Players who choose    |");
        UIUtils::displayText("|   this character class prefer a more cautious but chaotic gameplay style at the       |");
        UIUtils::displayText("|   same time.                                                                          |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Health: 1100                                                                        |");
        UIUtils::displayText("|   Armor: 150                                                                          |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|   Special Ability: Speed kills. Every first type of attack does double damage.        |");
        UIUtils::displayText("|   Passive Ability: Assassin have a 50% chance of executing parries and evades         |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    UIUtils::displayText("");
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
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

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
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(displayChar->getCurrArmor()) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(displayChar->getCurrHealth()));
        UIUtils::displayText("|  Opp. Armor: " + to_string(enemy.getCurrArmor()) + " / " + to_string(enemy.getMaxArmor()) + "   Health: " + to_string(enemy.getCurrHealth()));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                          *                         *                                  |");
        UIUtils::displayText("|    *        *                  *        *                                           * |");
        UIUtils::displayText("|                 *  *   *    *        *        *               *                   *   |");
        UIUtils::displayText("|         *         *           *          *               *                            |");
        UIUtils::displayText("|               *                 *    *           *              *                     |");
        UIUtils::displayText("|                       *                   *                           *               |");
        UIUtils::displayText("|        *                      *                      *                                |");
        UIUtils::displayText("|   _________________________________________________________________________________   |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|   ______|____________|_____________|_____________|_____________|____________|______   |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|         " + battlePhrases);
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu3.");
    }
    
    UIUtils::displayText("");
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
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

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
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(currArmor) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(currHealth));
        UIUtils::displayText("|  Opp. Armor: " + to_string(enemyCurrArmor) + " / " + to_string(enemy.getMaxArmor()) + "   Health: " + to_string(enemyCurrHealth));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                          *                         *                                  |");
        UIUtils::displayText("|    *        *                  *        *                                           * |");
        UIUtils::displayText("|                 *  *   *    *        *        *               *                   *   |");
        UIUtils::displayText("|         *         *           *          *               *                            |");
        UIUtils::displayText("|               *                 *    *           *              *                     |");
        UIUtils::displayText("|                       *                   *                           *               |");
        UIUtils::displayText("|        *                      *                      *                                |");
        UIUtils::displayText("|   _________________________________________________________________________________   |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|   ______|____________|_____________|_____________|_____________|____________|______   |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|         " + battlePhrases);
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu4.");
    }
    
    UIUtils::displayText("");
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
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

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
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(currArmor) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(currHealth));
        UIUtils::displayText("|  Opp. Armor: " + to_string(enemyCurrArmor) + " / " + to_string(enemy.getMaxArmor()) + "   Health: " + to_string(enemyCurrHealth));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                          *                         *                                  |");
        UIUtils::displayText("|    *        *                  *        *                                           * |");
        UIUtils::displayText("|     *            *  *   *    *        *        *               *                   *  |");
        UIUtils::displayText("|         *         *           *          *               *                            |");
        UIUtils::displayText("|      *         *                 *    *           *              *                    |");
        UIUtils::displayText("|                       *                   *                           *               |");
        UIUtils::displayText("|        *                      *                      *                                |");
        UIUtils::displayText("|   _________________________________________________________________________________   |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|   ______|____________|_____________|_____________|_____________|____________|______   |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|         " + battlePhrases);
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu5.");
    }
    
    UIUtils::displayText("");
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
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

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
        UIUtils::displayText("|  Level: " + to_string(displayChar->getLevel()));
        UIUtils::displayText("|  Armor: " + to_string(currArmor) + " / " + to_string(displayChar->getMaxArmor()) + "   Health: " + to_string(currHealth));
        UIUtils::displayText("|  Opp. Armor: " + to_string(enemyCurrArmor) + " / " + to_string(enemy.getMaxArmor()) + "   Health: " + to_string(enemyCurrHealth));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                          *                         *                                  |");
        UIUtils::displayText("|    *        *                  *        *                                           * |");
        UIUtils::displayText("|              *   *    *     *        *        *               *                   *   |");
        UIUtils::displayText("|         *         *           *          *               *                            |");
        UIUtils::displayText("|               *                 *    *           *              *                     |");
        UIUtils::displayText("|                       *                   *                           *               |");
        UIUtils::displayText("|        *                      *                      *                                |");
        UIUtils::displayText("|   _________________________________________________________________________________   |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|         |            |             |             |             |            |         |");
        UIUtils::displayText("|   ______|____________|_____________|_____________|_____________|____________|______   |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|         " + battlePhrases);
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu6.");
    }
    
    UIUtils::displayText("");
}

void Menu::EndBattleMenu(bool result, int level) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if(result) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                           Only winners deserve the prize.                             |");
        UIUtils::displayText("|                                  Level Up! Level " + to_string(level));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                  Save Game (Yes/No)?                                  |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    else {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                        Every great fighter has suffered loss                          |");
        UIUtils::displayText("|                                  Level Up! Level " + to_string(level));
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                  Save Game (Yes/No)?                                  |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    }
    
    UIUtils::displayText("");
}

void Menu::LoadGameMenu(Character &player) {
    string username, characterType;
    int currHealth, currArmor, level, currXP, maxXP;
    int currLevel = 1; 

    UIUtils::displayText("Enter fighter name to load: ");
    username = UIUtils::getUserInput(""); // Get username using UIUtils.

    if (loadGame(username, characterType, currHealth, currArmor, level, currXP, maxXP)) {
        // Update the player's current state based on the loaded data
        player.setCharacterType(characterType);
        player.setCurrHealth(currHealth);
        player.setCurrArmor(currArmor);
        player.setLevel(currLevel);
        UIUtils::displayText("Game loaded successfully!");
        
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");                      
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                            ------ Loaded Game State ------                            |");
        UIUtils::displayText("|                               Character Type: " + characterType);                   
        UIUtils::displayText("|                               Current Health: " + to_string(currHealth));                      
        UIUtils::displayText("|                               Current Armor: " + to_string(currArmor));                        
        UIUtils::displayText("|                               Current Level: " + to_string(currLevel));                        
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                               by PI   |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } 
    
    else {
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
        UIUtils::displayText("|                                  Unable to load game :(                               |");
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
    }

    UIUtils::displayText("");
}

void Menu::SavedGameMenu(Character &player) {
    // Optionally, clear the screen (this is system-dependent)
    // system("clear"); // for Unix-based systems (Linux, macOS)
    UIUtils::clearScreen();
    
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                 Saved Game Details                                    |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|  Type      : " + player.getCharacterType());
    UIUtils::displayText("|  Level     : " + to_string(player.getLevel()));
    UIUtils::displayText("|  Health    : " + to_string(player.getCurrHealth()) + " / " + to_string(player.getMaxHealth()));
    UIUtils::displayText("|  Armor     : " + to_string(player.getCurrArmor()) + " / " + to_string(player.getMaxArmor()));
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("| Options: [R]esume Saved Game    [D]elete Save    [M]ain Menu                          |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("Enter your choice: ");
}





