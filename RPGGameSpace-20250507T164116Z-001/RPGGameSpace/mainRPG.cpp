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
#include "SaveLoad.hpp" // Make sure SaveLoad.hpp is included

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
    if (!p) return false; 
    if (!e) return p->getCurrHealth() > 0; 

    if (e->getCurrHealth() <= 0 && p->getCurrHealth() > 0) return true; // Player wins
    if (p->getCurrHealth() <= 0 && e->getCurrHealth() > 0) return false; // CPU wins
    return false; 
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
    if (!p || !e) return false; 
    return p->getCurrHealth() > 0 && e->getCurrHealth() > 0;
}

// Corrected createEnemy function
void createEnemy(Enemy*& enemyPtrRef, const string& enemyCharacterType) {
    delete enemyPtrRef; 
    enemyPtrRef = new Enemy("Enemy", enemyCharacterType);
}

// Helper function to pause and wait for Enter
void waitForEnter() {
    UIUtils::displayText(string(CYAN) + "\n--- Press Enter to continue ---" + RESET);
    cin.get(); 
}


// Function to resolve a single turn of battle
void resolveBattleTurn(Character* player, Enemy* enemy, BattleManager& bManager, Menu& menu, int fightFirstInitiative) {
    if (!player || !enemy) {
        UIUtils::displayText("Error: Player or Enemy not initialized for battle turn.");
        return;
    }

    string playerAction;
    UIUtils::displayText("\nSelect action: Attack [Light/Normal/Heavy], Defend [Block/Parry/Evade]");
    cin >> playerAction;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


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
        UIUtils::displayText("Invalid player action '" + playerAction + "'! Your character hesitates.");
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
            waitForEnter(); 
            menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
        } else {
            UIUtils::displayText("Your attack is blocked or evaded!");
            waitForEnter(); 
            menu.BattleMenu4(player->getCharacterType(), false, player, enemy);
        }
    } else if (playerIsAttacking && enemyIsAttacking) {
        UIUtils::displayText("Clash! Player Attack (" + playerAction + "): " + to_string(playerAttackProb) + "% vs. Enemy Attack (" + enemyChosenAction + "): " + to_string(enemyAttackProb) + "%");
        
        bool playerWinsClashRoll = attackVSattack(playerAttackProb, enemyAttackProb);

        if (playerAttackProb == enemyAttackProb) { 
            UIUtils::displayText("Attacks are evenly matched! Initiative decides...");
            if (fightFirstInitiative == 1) { 
                UIUtils::displayText("Your initiative allows your attack to land!");
                bManager.handleAttack(player, enemy, playerAction); 
            } else { 
                UIUtils::displayText("Enemy's initiative allows their attack to land!");
                bManager.handleAttack(enemy, player, enemyChosenAction);
            }
        } else if (playerWinsClashRoll) {
            UIUtils::displayText("Your attack overpowers the enemy's!");
            bManager.handleAttack(player, enemy, playerAction);
        } else { 
            UIUtils::displayText("Enemy's attack overpowers yours!");
            bManager.handleAttack(enemy, player, enemyChosenAction);
        }
        waitForEnter(); 
        if (playerWinsClashRoll || (playerAttackProb == enemyAttackProb && fightFirstInitiative == 1)) {
            menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
        } else {
            menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy);
        }

    } else if (playerIsDefending && enemyIsAttacking) {
        UIUtils::displayText("Player Defend (" + playerAction + "): " + to_string(playerDefendProb) + "% vs. Enemy Attack (" + enemyChosenAction + "): " + to_string(enemyAttackProb) + "%");
        if (userDefendExecuted(playerDefendProb, enemyAttackProb)) {
            UIUtils::displayText("You successfully defend!");
            waitForEnter(); 
            menu.BattleMenu5(player->getCharacterType(), playerAction, true, player, enemy);
        } else {
            UIUtils::displayText("The enemy's attack gets through your defense!");
            bManager.handleAttack(enemy, player, enemyChosenAction); 
            waitForEnter(); 
            menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy);
        }
    } else if (playerIsDefending && enemyIsDefending) {
        UIUtils::displayText("Both combatants chose to defend! Player Defend (" + playerAction + ") vs. Enemy Defend (" + enemyChosenAction + ")");
        UIUtils::displayText("A momentary standoff!");
        waitForEnter(); 
        menu.BattleMenu6(player->getCharacterType(), true, player, enemy); 
    } else if (playerIsAttacking && !enemyIsAttacking && !enemyIsDefending) { 
        UIUtils::displayText("You attack with " + playerAction + " (" + to_string(playerAttackProb) + "%). Enemy is " + enemyChosenAction + ".");
        UIUtils::displayText("Your attack connects as the enemy was not defending!");
        bManager.handleAttack(player, enemy, playerAction);
        waitForEnter(); 
        menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
    } else if (enemyIsAttacking && !playerIsAttacking && !playerIsDefending) { 
         UIUtils::displayText("Enemy attacks with " + enemyChosenAction + " (" + to_string(enemyAttackProb) + "%). Your action was invalid.");
         UIUtils::displayText("Enemy's attack connects as you were unprepared!");
         bManager.handleAttack(enemy, player, enemyChosenAction);
         waitForEnter(); 
         menu.BattleMenu5(player->getCharacterType(), playerAction, false, player, enemy);
    }
     else { 
        UIUtils::displayText("Both combatants pause or chose non-standard actions.");
        waitForEnter(); 
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
            case 1: { 
                string playerCharacterType; 
                string name;                

                menu.NewGameMenu();
                UIUtils::displayText("Enter character type (Warrior, Wizard, Healer, Assassin, or Quit):");
                getline(cin, playerCharacterType); 
                UIUtils::displayText("");
                
                if(playerCharacterType == "Quit" || playerCharacterType == "quit") {
                    menu.QuitMenu();
                    string quitChoice; 
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

                if(playerCharacterType == "Warrior" || playerCharacterType == "warrior") player = new Warrior(name);
                else if(playerCharacterType == "Wizard" || playerCharacterType == "wizard") player = new Wizard(name);
                else if(playerCharacterType == "Healer" || playerCharacterType == "healer") player = new Healer(name);
                else if(playerCharacterType == "Assassin" || playerCharacterType == "assassin") player = new Assassin(name);
                else {
                    UIUtils::displayText("Invalid character type selected: " + playerCharacterType + ". Please try again.");
                    waitForEnter();
                    continue; 
                }

                if(player == nullptr) { 
                    UIUtils::displayText("Error creating player object. Invalid type.");
                    waitForEnter();
                    continue; 
                }
                
                menu.BaseGameMenu(player->getName(), player->getCharacterType(), player);
                cin >> menuInput2; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if(menuInput2 == "Yes" || menuInput2 == "yes") {
                    menu.BattleMenu1(player->getCharacterType(), player);
                    waitForEnter(); 
                    menu.BattleMenu2(player->getCharacterType(), player);
                    waitForEnter(); 

                    UIUtils::displayText("Flip a coin to determine who goes first (Select heads or tails):");
                    string coinToss; 
                    getline(cin, coinToss); 
                    
                    int fightFirst = rand() % 2 + 1; 
                    bool playerCalledCoinCorrectly = false;
                    if ((coinToss == "Heads" || coinToss == "heads") && fightFirst == 1) playerCalledCoinCorrectly = true;
                    if ((coinToss == "Tails" || coinToss == "tails") && fightFirst == 2) playerCalledCoinCorrectly = true;
                    
                    if (playerCalledCoinCorrectly) {
                        UIUtils::displayText("You won the toss and go first!");
                        fightFirst = 1; 
                    } else {
                        UIUtils::displayText("Enemy goes first!");
                        fightFirst = 2;
                    }
                    waitForEnter(); 
                    
                    string enemyTypeForBattle = Enemy::randomizeEnemyTypesStatic(); 
                    createEnemy(enemy, enemyTypeForBattle); 

                    if(!enemy) {
                        UIUtils::displayText("Error creating enemy for battle!");
                        waitForEnter();
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
                    int finalPlayerLevel = player ? player->getLevel() : 0; 
                    int finalPlayerHP = player ? player->getCurrHealth() : 0;
                    int finalEnemyHP = enemy ? enemy->getCurrHealth() : 0;


                    if (playerWon) {
                        UIUtils::displayText("Congratulations! You are victorious!");
                        if(player) player->levelUp(finalPlayerHP, finalEnemyHP); 
                        finalPlayerLevel = player ? player->getLevel() : finalPlayerLevel; 
                        menu.EndBattleMenu(true, finalPlayerLevel);
                    } else if (player && finalPlayerHP <= 0) {
                        UIUtils::displayText("You have been defeated...");
                        if(player) player->levelUp(finalPlayerHP, finalEnemyHP); 
                        finalPlayerLevel = player ? player->getLevel() : finalPlayerLevel;
                        menu.EndBattleMenu(false, finalPlayerLevel);
                    } else {
                        UIUtils::displayText("The battle ended inconclusively or with an error.");
                        if (player && finalPlayerHP > 0 && enemy && finalEnemyHP <=0) {
                             if(player) player->levelUp(finalPlayerHP, finalEnemyHP);
                             finalPlayerLevel = player ? player->getLevel() : finalPlayerLevel;
                             menu.EndBattleMenu(true, finalPlayerLevel);
                        } else if (player) { // If player exists, but didn't win and isn't 0 HP (e.g. enemy fled, or both 0 HP)
                             menu.EndBattleMenu(false, finalPlayerLevel); 
                        }
                    }
                    waitForEnter(); 

                    UIUtils::displayText("Save Game (Yes/No)?");
                    string saveDecision; 
                    cin >> saveDecision;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if ((saveDecision == "Yes" || saveDecision == "yes") && player) {
                        saveGame(player->getName(), player->getCharacterType(), player->getCurrHealth(), player->getCurrArmor(), player->getLevel(), player->getCurrXP(), player->getMaxXP());
                        menu.SavedGameMenu(*player); 
                        waitForEnter();
                    }
                }
                break; 
            } 

            case 2: { 
                UIUtils::displayText("Enter username of the game to load:");
                string usernameToLoad;
                getline(cin, usernameToLoad); 

                string loadedCharacterType;
                int l_hp, l_armor, l_level, l_xp, l_max_xp;

                // Attempt to load the basic data first to determine character type
                ifstream tempLoadFile(usernameToLoad + "_save.txt");
                if (tempLoadFile.is_open()) {
                    if (getline(tempLoadFile, loadedCharacterType)) {
                        // Successfully read character type
                        tempLoadFile.close(); // Close it, we'll reopen with loadGame or read manually

                        delete player; // Delete existing player
                        player = nullptr;

                        if (loadedCharacterType == "Warrior") player = new Warrior(usernameToLoad);
                        else if (loadedCharacterType == "Wizard") player = new Wizard(usernameToLoad);
                        else if (loadedCharacterType == "Healer") player = new Healer(usernameToLoad);
                        else if (loadedCharacterType == "Assassin") player = new Assassin(usernameToLoad);
                        else {
                            UIUtils::displayText("Error: Unknown character type in save file: " + loadedCharacterType);
                            player = nullptr; // Ensure player is null if type is unknown
                        }

                        if (player) {
                            // Now, use your loadGame function to populate the newly created player
                            // This assumes loadGame can correctly populate the already known characterType
                            // or you can modify loadGame to skip reading characterType if it's already known.
                            // For simplicity, let's assume loadGame is called and it re-reads type but we use our new player.
                            
                            // Re-open file to read all stats with your loadGame function
                            // Or, modify loadGame to take an open ifstream& and the Character*
                            // For now, let's use the existing loadGame and then set stats
                            string typeFromFile; // To consume the type read by loadGame
                            if (loadGame(usernameToLoad, typeFromFile, l_hp, l_armor, l_level, l_xp, l_max_xp)) {
                                // Set stats on the correctly typed player object
                                player->setCurrHealth(l_hp);
                                player->setCurrArmor(l_armor);
                                player->setLevel(l_level);
                                player->setCurrXP(l_xp);
                                player->setMaxXP(l_max_xp);
                                // Important: MaxHP and MaxArmor are set by constructors based on type.
                                // If your save file stores MAX values that can change (e.g. items),
                                // you'd need to save/load and setMaxHP/setMaxArmor too.
                                // For now, constructor defaults are used for max values.

                                UIUtils::displayText("Game Loaded for " + player->getName() + " the " + player->getCharacterType());
                                menu.BaseGameMenu(player->getName(), player->getCharacterType(), player);
                            } else {
                                UIUtils::displayText("Error loading full game data for " + usernameToLoad);
                                delete player; // Clean up partially created player
                                player = nullptr;
                            }
                        }
                    } else {
                        UIUtils::displayText("Error reading character type from save file for " + usernameToLoad);
                        tempLoadFile.close();
                    }
                } else {
                    UIUtils::displayText("No saved game found for username: " + usernameToLoad);
                }
                waitForEnter();
                break;
            }

            case 3: { 
                menu.NewGameMenu(); 
                UIUtils::displayText("Enter character type to view details (Warrior, Wizard, Healer, Assassin, or type 'Back'):");
                string typeToView; 
                getline(cin, typeToView); 
                if(typeToView != "Back" && typeToView != "back" && typeToView != "Quit" && typeToView != "quit") {
                    menu.ViewCharactersMenu(typeToView);
                    waitForEnter();
                }
                break;
            }

            case 4: { 
                menu.QuitMenu();
                string quitChoice; 
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
                waitForEnter();
                break;
        } 
    } while (true); 

    delete player;
    delete enemy;
    return 0;
}
