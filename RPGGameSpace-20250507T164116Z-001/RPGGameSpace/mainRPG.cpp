//
//  main.cpp
//  Game Battle RPG
//
//  Created by Pierre Ingram on 4/19/23.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
#include <limits>
#include "Character.hpp"
#include "BattleManager.hpp"
#include "Warrior.hpp"
#include "Wizard.hpp"
#include "Healer.hpp"
#include "Assassin.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Utils.hpp"
#include "UIUtils.hpp"

using namespace std;

// ANSI escape codes for colors and styles
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define BOLD "\033[1m"

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to display the title screen for "Poguelandia"
void showTitle() {
    clearScreen();
    string title = R"(
:::::::::   ::::::::   ::::::::  :::    ::: :::::::::: :::            :::     ::::    ::: ::::::::: :::::::::::     :::     
:+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:        :+:          :+: :+:   :+:+:   :+: :+:    :+:    :+:       :+: :+:   
+:+    +:+ +:+    +:+ +:+        +:+    +:+ +:+        +:+         +:+   +:+  :+:+:+  +:+ +:+    +:+    +:+      +:+   +:+  
+#++:++#+  +#+    +:+ :#:        +#+    +:+ +#++:++#   +#+        +#++:++#++: +#+ +:+ +#+ +#+    +:+    +#+     +#++:++#++: 
+#+        +#+    +#+ +#+   +#+# +#+    +#+ +#+        +#+        +#+     +#+ +#+  +#+#+# +#+    +#+    +#+     +#+     +#+ 
#+#        #+#    #+# #+#    #+# #+#    #+# #+#        #+#        #+#     #+# #+#   #+#+# #+#    #+#    #+#     #+#     #+# 
###         ########   ########   ########  ########## ########## ###     ### ###    #### ######### ########### ###     ###
)";
    typeEffect(string(BOLD) + string(CYAN) + title + string(RESET), 2);
    typeEffect(string(YELLOW) + "Welcome to Poguelandia, Traveler!" + string(RESET), 50);
    this_thread::sleep_for(chrono::seconds(2));
}

// Checks the result of a battle
bool result(const Character* p, const Character* e) {
    if (!p) return false; // Player pointer is null
    if (!e) return p->getCurrHealth() > 0; // Enemy pointer is null, player wins if alive

    if (e->getCurrHealth() <= 0 && p->getCurrHealth() > 0) return true; // Player wins
    if (p->getCurrHealth() <= 0 && e->getCurrHealth() > 0) return false; // CPU wins
    return false; // Tie or other situations
}

// Determines if the player's attack is more likely to succeed than the enemy's attack.
bool attackVSattack(int attackProbability, int enemyAttackProbability) {
    return (attackProbability > enemyAttackProbability);
}

// Determines if the player's defense is more likely to succeed than the enemy's attack.
bool userDefendExecuted(int defendProbability, int enemyAttackProbability) {
    return (defendProbability > enemyAttackProbability);
}

// Determines if the player's attack is more likely to land than the enemy's defense.
bool userAttackLanded(int attackProbability, int enemyDefendProbability) {
    return (attackProbability > enemyDefendProbability);
}

// Checks if both the player and the enemy still have health points remaining.
bool hasHealth(const Character* p, const Character* e) {
    if (!p || !e) return false; // Safety check for null pointers
    return p->getCurrHealth() > 0 && e->getCurrHealth() > 0;
}

// Corrected createEnemy function
void createEnemy(Enemy*& enemyPtrRef, const string& enemyCharacterType) {
    delete enemyPtrRef; // Safely delete the old enemy object if it exists
    enemyPtrRef = new Enemy("Mysterious Foe", enemyCharacterType);
    // Ensure Enemy constructor (Enemy(string name, string type)) correctly sets stats based on type.
}

// Function to resolve a single turn of battle
void resolveBattleTurn(Character* player, Enemy* enemy, BattleManager& bManager, Menu& menu, int fightFirstInitiative) {
    if (!player || !enemy) {
        UIUtils::displayText("Error: Player or Enemy not initialized for battle turn.");
        return;
    }

    string playerAction;
    UIUtils::displayText("Select action: Attack [Light/Normal/Heavy], Defend [Block/Parry/Evade]");
    cin >> playerAction;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

    unsigned int playerAttackProb = 0;
    unsigned int playerDefendProb = 0;
    bool playerIsAttacking = (playerAction == "Light" || playerAction == "light" ||
                              playerAction == "Normal" || playerAction == "normal" ||
                              playerAction == "Heavy" || playerAction == "heavy");
    bool playerIsDefending = (playerAction == "Block" || playerAction == "block" ||
                              playerAction == "Parry" || playerAction == "parry" ||
                              playerAction == "Evade" || playerAction == "evade");

    if (playerIsAttacking) {
        playerAttackProb = player->attackProbability(playerAction);
    } else if (playerIsDefending) {
        playerDefendProb = player->defendProbability(playerAction);
    } else {
        UIUtils::displayText("Invalid player action '" + playerAction + "'! Turn may be skipped or default action taken.");
        playerIsAttacking = false; 
        playerIsDefending = false;
    }

    string enemyChosenAction = enemy->randomizeEnemyActions();
    unsigned int enemyAttackProb = 0;
    unsigned int enemyDefendProb = 0;
    bool enemyIsAttacking = (enemyChosenAction == "Light" || enemyChosenAction == "Normal" || enemyChosenAction == "Heavy");
    bool enemyIsDefending = (enemyChosenAction == "Block" || enemyChosenAction == "Parry" || enemyChosenAction == "Evade");

    if (enemyIsAttacking) {
        enemyAttackProb = enemy->attackProbability(enemyChosenAction);
    } else if (enemyIsDefending) { 
        enemyDefendProb = enemy->defendProbability(enemyChosenAction);
    } else {
         UIUtils::displayText("Enemy chose an unknown action: " + enemyChosenAction);
         enemyIsAttacking = false;
         enemyIsDefending = false;
    }

    UIUtils::displayText(""); 

    if (playerIsAttacking && enemyIsDefending) {
        UIUtils::displayText("Player Attack (" + playerAction + "): " + to_string(playerAttackProb) + "% vs. Enemy Defend (" + enemyChosenAction + "): " + to_string(enemyDefendProb) + "%");
        if (userAttackLanded(playerAttackProb, enemyDefendProb)) {
            UIUtils::displayText("Your attack connects!");
            bManager.handleAttack(player, enemy, playerAction);
            menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
        } else {
            UIUtils::displayText("Your attack is blocked or evaded!");
            menu.BattleMenu4(player->getCharacterType(), false, player, enemy);
        }
    } else if (playerIsAttacking && enemyIsAttacking) {
        UIUtils::displayText("Clash! Player Attack (" + playerAction + "): " + to_string(playerAttackProb) + "% vs. Enemy Attack (" + enemyChosenAction + "): " + to_string(enemyAttackProb) + "%");
        
        bool playerWinsClashRoll = attackVSattack(playerAttackProb, enemyAttackProb);
        // bool enemyWinsClashRoll = attackVSattack(enemyAttackProb, playerAttackProb); // Redundant if using else if

        if (playerAttackProb == enemyAttackProb) { 
            UIUtils::displayText("Attacks are evenly matched! Initiative decides...");
            if (fightFirstInitiative == 1) { 
                UIUtils::displayText("Your initiative allows your attack to land!");
                bManager.handleAttack(player, enemy, playerAction);
                menu.BattleMenu4(player->getCharacterType(), true, player, enemy); 
            } else { 
                UIUtils::displayText("Enemy's initiative allows their attack to land!");
                bManager.handleAttack(enemy, player, enemyChosenAction);
                menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy); 
            }
        } else if (playerWinsClashRoll) {
            UIUtils::displayText("Your attack overpowers the enemy's!");
            bManager.handleAttack(player, enemy, playerAction);
            menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
        } else { // Implies enemyAttackProb > playerAttackProb
            UIUtils::displayText("Enemy's attack overpowers yours!");
            bManager.handleAttack(enemy, player, enemyChosenAction);
            menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy); 
        }
    } else if (playerIsDefending && enemyIsAttacking) {
        UIUtils::displayText("Player Defend (" + playerAction + "): " + to_string(playerDefendProb) + "% vs. Enemy Attack (" + enemyChosenAction + "): " + to_string(enemyAttackProb) + "%");
        if (userDefendExecuted(playerDefendProb, enemyAttackProb)) {
            UIUtils::displayText("You successfully defend!");
            menu.BattleMenu5(player->getCharacterType(), playerAction, true, player, enemy);
        } else {
            UIUtils::displayText("The enemy's attack gets through your defense!");
            bManager.handleAttack(enemy, player, enemyChosenAction);
            menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy);
        }
    } else if (playerIsDefending && enemyIsDefending) {
        UIUtils::displayText("Both combatants chose to defend! Player Defend (" + playerAction + ") vs. Enemy Defend (" + enemyChosenAction + ")");
        UIUtils::displayText("A momentary standoff!");
        menu.BattleMenu6(player->getCharacterType(), true, player, enemy); 
    } else if (playerIsAttacking && !enemyIsAttacking && !enemyIsDefending) { 
        UIUtils::displayText("You attack with " + playerAction + " (" + to_string(playerAttackProb) + "%). Enemy is " + enemyChosenAction + ".");
        UIUtils::displayText("Your attack connects as the enemy was not defending!");
        bManager.handleAttack(player, enemy, playerAction);
        menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
    } else if (enemyIsAttacking && !playerIsAttacking && !playerIsDefending) { 
         UIUtils::displayText("Enemy attacks with " + enemyChosenAction + " (" + to_string(enemyAttackProb) + "%). Your action was invalid.");
         UIUtils::displayText("Enemy's attack connects as you were unprepared!");
         bManager.handleAttack(enemy, player, enemyChosenAction);
         menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy);
    }
     else { 
        UIUtils::displayText("Both combatants pause or chose non-standard actions.");
        menu.BattleMenu6(player->getCharacterType(), false, player, enemy); 
    }
    UIUtils::displayText(""); 
}


int main() {
    srand(static_cast<unsigned int>(time(0))); 

    showTitle();
    Menu menu;
    BattleManager battleManager;
    Character* player = nullptr;
    Enemy* enemy = nullptr; 

    int menuInput1;
    string menuInput2;
    // These are now local to case 1 or other relevant scopes
    // string name, playerCharacterType; 
    
    do {
        menu.MainMenu(); 
        UIUtils::displayText("Enter your choice: ");
        
        if (!(cin >> menuInput1)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            UIUtils::displayText("Invalid input. Please enter a number from the menu.");
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch(menuInput1) {
            case 1: { // New Game - Added braces
                string playerCharacterType; // Declared inside case scope
                string name;                // Declared inside case scope

                menu.NewGameMenu();
                UIUtils::displayText("Enter character type (Warrior, Wizard, Healer, Assassin, or Quit):");
                cin >> playerCharacterType;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                UIUtils::displayText("");
                
                if(playerCharacterType == "Quit" || playerCharacterType == "quit") {
                    menu.QuitMenu();
                    string quitChoice; // Declared inside this block's scope
                    cin >> quitChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if(quitChoice == "Yes" || quitChoice == "yes") {
                        menu.QuitMenu2();
                        delete player;
                        delete enemy;
                        return 0; 
                    } else {
                        continue; 
                    }
                }

                UIUtils::displayText("Enter Name:");
                getline(cin, name); 
                UIUtils::displayText("");

                delete player; 
                player = nullptr; 

                if(playerCharacterType == "Warrior") player = new Warrior(name);
                else if(playerCharacterType == "Wizard") player = new Wizard(name);
                else if(playerCharacterType == "Healer") player = new Healer(name);
                else if(playerCharacterType == "Assassin") player = new Assassin(name);
                else {
                    UIUtils::displayText("Invalid character type selected. Please try again.");
                    continue; 
                }

                if(player == nullptr) { 
                    UIUtils::displayText("Error creating player object. Invalid type.");
                    continue; 
                }
                
                menu.BaseGameMenu(player->getName(), player->getCharacterType(), player);
                cin >> menuInput2; // menuInput2 is fine as it was declared outside switch
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(menuInput2 == "Yes" || menuInput2 == "yes") {
                    menu.BattleMenu1(player->getCharacterType(), player);
                    menu.BattleMenu2(player->getCharacterType(), player);

                    UIUtils::displayText("Flip a coin to determine who goes first (Select heads or tails):");
                    string coinToss; // Declared inside this block's scope
                    cin >> coinToss;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    int fightFirst = rand() % 2 + 1; 
                    if (((coinToss == "Heads" || coinToss == "heads") && fightFirst == 1) ||
                        ((coinToss == "Tails" || coinToss == "tails") && fightFirst == 2) ) {
                         UIUtils::displayText("You won the toss and go first!");
                         fightFirst = 1; 
                    } else {
                        UIUtils::displayText("Enemy goes first!");
                        fightFirst = 2;
                    }
                    
                    string enemyTypeForBattle = Enemy::randomizeEnemyTypesStatic(); 
                    createEnemy(enemy, enemyTypeForBattle); 

                    if(!enemy) {
                        UIUtils::displayText("Error creating enemy for battle!");
                        continue;
                    }
                    
                    menu.BattleMenu3(player->getCharacterType(), fightFirst, player, enemy);
                    
                    while(hasHealth(player, enemy)) {
                        resolveBattleTurn(player, enemy, battleManager, menu, fightFirst);
                        
                        if (!hasHealth(player, enemy)) {
                            break;
                        }
                    }
                    
                    bool playerWon = result(player, enemy);
                    
                    if (playerWon) {
                        UIUtils::displayText("Congratulations! You are victorious!");
                        if(player) player->levelUp(player->getCurrHealth(), (enemy ? enemy->getCurrHealth() : 0) ); 
                        menu.EndBattleMenu(true, player ? player->getLevel() : 0);
                    } else if (player && player->getCurrHealth() <= 0) {
                        UIUtils::displayText("You have been defeated...");
                        if(player) player->levelUp(player->getCurrHealth(), (enemy ? enemy->getCurrHealth() : 0) ); 
                        menu.EndBattleMenu(false, player ? player->getLevel() : 0);
                    } else if (enemy && enemy->getCurrHealth() <= 0 && player && player->getCurrHealth() > 0) {
                        // This case should be caught by playerWon = true, but as a fallback
                         UIUtils::displayText("Congratulations! You are victorious! (Fallback check)");
                        if(player) player->levelUp(player->getCurrHealth(), enemy->getCurrHealth() ); 
                        menu.EndBattleMenu(true, player ? player->getLevel() : 0);
                    }
                    else {
                        UIUtils::displayText("The battle ended inconclusively or with an error.");
                    }

                    UIUtils::displayText("Save Game (Yes/No)?");
                    string saveDecision; // Declared inside this block's scope
                    cin >> saveDecision;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (saveDecision == "Yes" || saveDecision == "yes") {
                        if(player) menu.SavedGameMenu(*player); 
                    }
                }
                break; 
            } 

            case 2: { // Load Game - Added braces
                UIUtils::displayText("Load Game functionality to be fully implemented.");
                // string usernameToLoad; // Example of variable that would need this scope
                // UIUtils::displayText("Enter username of the game to load:");
                // cin >> usernameToLoad;
                break;
            }

            case 3: { // View Characters - Added braces
                menu.NewGameMenu(); 
                UIUtils::displayText("Enter character type to view details (or type 'Back'):");
                string typeToView; // Declared inside case scope
                cin >> typeToView;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(typeToView != "Back" && typeToView != "back" && typeToView != "Quit" && typeToView != "quit") {
                    menu.ViewCharactersMenu(typeToView);
                    UIUtils::displayText("Press Enter to return to the main menu...");
                    cin.get(); 
                }
                break;
            }

            case 4: { // Quit - Added braces
                menu.QuitMenu();
                string quitChoice; // Declared inside case scope
                cin >> quitChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(quitChoice == "Yes" || quitChoice == "yes") {
                    menu.QuitMenu2();
                    delete player;
                    delete enemy;
                    return 0; 
                }
                break;
            }
            default:
                UIUtils::displayText("Invalid menu choice. Please try again.");
                break;
        } 
    } while (true); 

    delete player;
    delete enemy;
    return 0;
}
