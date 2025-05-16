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

    // ASCII art for "Poguelandia"
    string title = R"(
:::::::::   ::::::::   ::::::::  :::    ::: :::::::::: :::            :::     ::::    ::: ::::::::: :::::::::::     :::     
:+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:        :+:          :+: :+:   :+:+:   :+: :+:    :+:    :+:       :+: :+:   
+:+    +:+ +:+    +:+ +:+        +:+    +:+ +:+        +:+         +:+   +:+  :+:+:+  +:+ +:+    +:+    +:+      +:+   +:+  
+#++:++#+  +#+    +:+ :#:        +#+    +:+ +#++:++#   +#+        +#++:++#++: +#+ +:+ +#+ +#+    +:+    +#+     +#++:++#++: 
+#+        +#+    +#+ +#+   +#+# +#+    +#+ +#+        +#+        +#+     +#+ +#+  +#+#+# +#+    +#+    +#+     +#+     +#+ 
#+#        #+#    #+# #+#    #+# #+#    #+# #+#        #+#        #+#     #+# #+#   #+#+# #+#    #+#    #+#     #+#     #+# 
###         ########   ########   ########  ########## ########## ###     ### ###    #### ######### ########### ###     ###
)";
    // Print the title using a type effect in bold cyan
    typeEffect(string(BOLD) + string(CYAN) + title + string(RESET), 2);

    // Print a subtitle or tagline in yellow
    typeEffect(string(YELLOW) + "Welcome to Poguelandia, Traveler!" + string(RESET), 50);

    // Pause for a couple of seconds to let the player take it in
    this_thread::sleep_for(chrono::seconds(2));
}

/**
 * Checks the result of a battle between the player and an enemy.
 * currHealth: The current health points of the player.
 * enemyCurrHealth: The current health points of the enemy.
 * return True if the player wins, false if the enemy wins or in case of a tie.
 */
bool result(int currHealth, int enemyCurrHealth) {
    // User wins
    if((enemyCurrHealth <= 0) && (currHealth > 0)) {
        return true;
    }
    
    // CPU wins
    else if((currHealth <= 0) && (enemyCurrHealth > 0)) {
        return false;
    }

    // In case of a tie or other situations
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
bool hasHealth(int currHealth, int enemyCurrHealth) {
    return currHealth > 0 && enemyCurrHealth > 0;
}

/**
 * Calculates the attack value based on the character type and action.
 * characterType: The type of character performing the attack.
 * action: The specific action to be executed.
 * return The calculated attack value.
 */
int calculateAttackValue(Character* character, string action) {
    // Instantiate appropriate character class based on characterType and call its attack method
    return character->attack(action);
}

/** 
 * Determines the attack value of the character based on the initiative of the battle.
 * fightFirst: Specifies which character strikes first (1 for player, 2 for enemy). 
 */
int firstHit(int fightFirst, Character* character, string enemyAction, string enemyCharacterType) {
    Enemy enemy;
    int attackValue = 0;
    srand((unsigned int) time(0));
    
    if(fightFirst == 1) {
        attackValue = calculateAttackValue(character, enemyAction);
    }
        
    else if(fightFirst == 2) {
        attackValue = enemy.attack(enemyAction, enemyCharacterType);
    }
    
    return attackValue;
}


// Initiates the battle for the player character.
int UserBattle(Character* character, string action) {
    return calculateAttackValue(character, action);
}

// Initiates the battle for the CPU (enemy) character.
int CPUBattle(string enemyCharacterType, string enemyAction) {
    Enemy enemy;
    
    // Check if enemyAction is one of the expected values
    if((enemyAction != "Light" && enemyAction != "Normal" && enemyAction != "Heavy") || (enemyAction != "light" && enemyAction != "normal" && enemyAction != "heavy")) {
        UIUtils::displayText("Error: Invalid action type '" + enemyAction + "'");
        return -1;  // Return an error value
    }
    
    // If enemyAction is valid, calculate and return the attack value
    int enemyAttackValue = enemy.attack(enemyAction, enemyCharacterType);
    
    return enemyAttackValue;
}

void createEnemy(Enemy* enemy, const string& enemyCharacterType) {
    if (enemyCharacterType == "Warrior") {
        enemy->setCharacterType("Warrior");
        enemy->setMaxHealth(1200);
        enemy->setCurrHealth(1200);
        enemy->setMaxArmor(200);
        enemy->setCurrArmor(200);
        enemy->setLevel(1);
    } else if (enemyCharacterType == "Wizard") {
        enemy->setCharacterType("Wizard");
        enemy->setMaxHealth(1000);
        enemy->setCurrHealth(1000);
        enemy->setMaxArmor(80);
        enemy->setCurrArmor(80);
        enemy->setLevel(1);
    } else if (enemyCharacterType == "Healer") {
        enemy->setCharacterType("Healer");
        enemy->setMaxHealth(1300);
        enemy->setCurrHealth(1300);
        enemy->setMaxArmor(300);
        enemy->setCurrArmor(300);
        enemy->setLevel(1);
    } else if (enemyCharacterType == "Assassin") {
        enemy->setCharacterType("Assassin");
        enemy->setMaxHealth(1100);
        enemy->setCurrHealth(1100);
        enemy->setMaxArmor(150);
        enemy->setCurrArmor(150);
        enemy->setLevel(1);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
     /**
     * This block of code initializes various game objects and variables required for the game loop.
     * It includes initialization of menu, player character, enemy, and other variables such as health, armor, etc.
     * It also determines the order of attack (whether the player or CPU moves first) using a random number generator.
     * After initialization, it displays the main menu of the game.
     */

    showTitle();
    Menu menu;
    BattleManager battleManager;
    Character* player = nullptr;
    Enemy* enemy = new Enemy();
    int menuInput1;
    string menuInput2;
    string coinToss;
    string action;
    bool invalidInput = false;
    
    //Determines whether user or CPU gets to move first
    int fightFirst = rand() % 2 + 1;
    
    string attackType, name, characterType, defendType;
    string enemyAttackType, enemyCharacterType, enemyAction;
    unsigned int attackProbability = 0;
    unsigned int defendProbability = 0;
    unsigned int enemyAttackProbability = 0;
    unsigned int enemyDefendProbability = 0;
    unsigned int currHealth = 1;
    unsigned int currArmor = 1;
    int attackValue = 0;
    int enemyAttackValue = 0;
    int enemyCurrHealth = enemy->getCurrHealth();
    unsigned int enemyCurrArmor = enemy->getCurrArmor();

    // Main game loop
    menu.MainMenu();
    string quitInput;
    
    // Check if the user wants to quit
    do {
        UIUtils::displayText("Enter your choice: ");
        // Clear any previous failed state and leftover characters
        cin.clear();
        while (cin.peek() == '\n') cin.ignore();
        
        // Check if input is actually a number
        if (!(cin >> menuInput1)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            UIUtils::displayText("Invalid input. Please enter a number from the menu.");
            continue;
        }
        
        switch(menuInput1) {
            case 1:
                menu.NewGameMenu();
                UIUtils::displayText("Enter character type:");
                cin >> characterType;
                cin.ignore();
                UIUtils::displayText("");
                
                if(characterType != "Quit") {
                    UIUtils::displayText("Enter Name:");
                    getline(cin, name);
                    UIUtils::displayText("");

                    // Create the concrete player object based on the input.
                    if(characterType == "Warrior")
                        player = new Warrior(name);
                    else if(characterType == "Wizard")
                        player = new Wizard(name);
                    else if(characterType == "Healer")
                        player = new Healer(name);
                    else if(characterType == "Assassin")
                        player = new Assassin(name);

                    if(player == nullptr) {
                        UIUtils::displayText("Error creating player object.");
                        return 1;
                    }

                    player->setCharacterType(characterType);
                    player->setName(name);

                    // Now initialize player-dependent variables.
                    currHealth = player->getCurrHealth();
                    currArmor = player->getCurrArmor();
                }
                
                else {
                    menu.QuitMenu();
                    cin >> quitInput;
                    
                    if(quitInput == "Yes") {
                        menu.QuitMenu2();
                        exit(1);
                    }
                    else if(quitInput == "No") {
                        menu.MainMenu();
                        break;
                    }
                }
                
                menu.BaseGameMenu(name, characterType, player);
                cin >> menuInput2;
                
                if(menuInput2 == "Yes" || menuInput2 == "yes") {
                    menu.BattleMenu1(characterType, player);
                    menu.BattleMenu2(characterType, player);

                    UIUtils::displayText("Health: " + to_string(currHealth) + " Armor: " + to_string(currArmor));
                    UIUtils::displayText("Flip a coin (Select heads or tails)");
                    cin >> coinToss;
                    
                    // Determines who makes the first move (User or CPU)
                    if(coinToss == "Heads" || coinToss == "heads" || coinToss == "Tails" || coinToss == "tails") {
                        menu.BattleMenu3(characterType, fightFirst, player, enemy);
                        
                        //Randomizes enemy type and actions to create realistic opponent
                        enemyCharacterType = enemy->randomizeEnemyTypes();
                        createEnemy(enemy, enemyCharacterType); 
                        enemyAction = enemy->randomizeEnemyActions();
                        enemyCurrArmor = enemy->getCurrArmor();
                        
                        UIUtils::displayText("Select action: Attack [Light  Normal  Heavy], Defend [Block  Parry  Evade]");
                        cin >> action;
                        
                        //Gets probability of performing this attack based on the attack/defend type
                        if(action == "Light" || action == "Normal" || action == "Heavy") {
                            attackType = action;
                            attackProbability = player->attackProbability(attackType);
                        }

                        if(action == "Block" || action == "Parry" || action == "Evade" ||action == "block" || action == "parry" || action == "evade") {
                            defendType = action;
                            defendProbability = player->defendProbability(defendType);
                        }
                            
                        //Declared outside the switch statement (fightFirst)
                        if(fightFirst == 1) {
                            if(action == "Light" || action == "Normal" || action == "Heavy") {
                                attackValue = firstHit(fightFirst, player, enemyAction, enemyCharacterType);
                                enemyDefendProbability = enemy->defendProbability(enemyAction);
                                enemyAttackProbability = enemy->attackProbability(enemyAction);
                            }
                        }
                        
                        else if(fightFirst == 2) {
                            if(enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy") {
                                enemyAttackProbability = enemy->attackProbability(enemyAction);
                                enemyAttackValue = enemy->attack(enemyAction, enemyCharacterType);
                            }
                            
                            if(enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade") {
                                enemyDefendProbability = enemy->defendProbability(enemyAction);
                            }
                        }
                        
                        //Compares every combo of user actions vs. CPU actions
                        bool attackExecuted = userAttackLanded(attackProbability, enemyDefendProbability);
                        bool defendExecuted = userDefendExecuted(defendProbability, enemyAttackProbability);
                        bool attackExecuted2 = attackVSattack(attackProbability, enemyAttackProbability);
                        
                        //Shows percentages in game to see which action will be executed in combat
                        UIUtils::displayText("");
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                            UIUtils::displayText("Attack: " + to_string(attackProbability) + " vs. Enemy Attack: " + to_string(enemyAttackProbability));
                        }
                        
                        else if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                            UIUtils::displayText("Attack: " + to_string(attackProbability) + " vs. Enemy Defend: " + to_string(enemyDefendProbability));
                        }
                        
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                            UIUtils::displayText("Defend: " + to_string(defendProbability) + " vs. Enemy Attack: " + to_string(enemyAttackProbability));
                        }
                        
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                            UIUtils::displayText("Defend: " + to_string(defendProbability) + " vs. Enemy Defend: " + to_string(enemyDefendProbability));
                        }
                        UIUtils::displayText("");
                        
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                            if(attackExecuted == true) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                            }
                            
                            else if(attackExecuted == false) {
                                menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                            }
                        }
                        
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                            if(attackExecuted2 == true) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu4(characterType, attackExecuted2, player, enemy);
                            }
                             
                            else if(attackExecuted2 == false) {
                                battleManager.handleAttack(player, enemy, action); 
                                menu.BattleMenu5(characterType, action, attackExecuted2, player, enemy);
                            }
                        }
                        
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                            if(defendExecuted == true) {
                                menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                            }
                            
                            else if(defendExecuted == false) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                            }
                        }

                        // 
                        while(hasHealth(currHealth, enemyCurrHealth) == true) {
                            enemyAction = enemy->randomizeEnemyActions();
                            
                            UIUtils::displayText("Select action: Attack [Light  Normal  Heavy], Defend [Block  Parry  Evade]");
                            cin >> action; // ... (Get user input)
                            
                            if(action == "Light" || action == "Normal" || action == "Heavy") {
                                attackType = action;
                                attackProbability = player->attackProbability(attackType);
                            }

                            if(action == "Block" || action == "Parry" || action == "Evade") {
                                defendType = action;
                                defendProbability = player->defendProbability(defendType);
                            }
                            
                            attackExecuted = userAttackLanded(attackProbability, enemyDefendProbability);
                            defendExecuted = userDefendExecuted(defendProbability, enemyAttackProbability);
                            attackExecuted2 = attackVSattack(attackProbability, enemyAttackProbability);
                            
                            UIUtils::displayText("");
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                                UIUtils::displayText("Attack chance: " + to_string(attackProbability) + " vs. Enemy Attack chance: " + to_string(enemyAttackProbability));
                            }
                            
                            else if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                                UIUtils::displayText("Attack chance: " + to_string(attackProbability) + " vs. Enemy Defend chance: " + to_string(enemyDefendProbability));
                            }
                            
                            else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                                UIUtils::displayText("Defend chance: " + to_string(defendProbability) + " vs. Enemy Attack chance: " + to_string(enemyAttackProbability));
                            }
                            
                            else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                                UIUtils::displayText("Defend chance: " + to_string(defendProbability) + " vs. Enemy Defend chance: " + to_string(enemyDefendProbability));
                            }
                            UIUtils::displayText("");
                            
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                                //User attack landed on CPU (defense), take health from CPU
                                if(attackExecuted == true) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                                }
                                
                                //User attack failed on CPU
                                else if(attackExecuted == false) {
                                    menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                                }
                            }
                            
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                                //User attack landed on CPU (offense), take health from CPU
                                if(attackExecuted2 == true) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu4(characterType, attackExecuted2, player, enemy);
                                }
                                
                                else if(attackExecuted2 == false) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu5(characterType, action, attackExecuted2, player, enemy);
                                }
                            }
                            
                            
                            if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Light" || enemyAction == "Normal" || enemyAction == "Heavy")) {
                                if(defendExecuted == true) {
                                    menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                                }
                                
                                else if(defendExecuted == false) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                                }
                            }
                            
                            if((action == "Block" || action == "Parry" || action == "Evade") && (enemyAction == "Block" || enemyAction == "Parry" || enemyAction == "Evade")) {
                                bool doubleDefend = true;
                                menu.BattleMenu6(characterType, doubleDefend, player, enemy);
                            }
                        }
                    }
                    
                    bool fightResult = result(currHealth, enemyCurrHealth);
                    
                    if(fightResult) {
                        player->levelUp(currHealth, enemyCurrHealth);
                        menu.EndBattleMenu(fightResult, player->getLevel());
                        string Sdecision; // Save Decision
                        cin >> Sdecision;

                        if (Sdecision == "Yes") {
                            menu.SavedGameMenu(*player);
                        }

                        else if (Sdecision == "No") {
                            menu.MainMenu();
                            break;
                        }
                    }

                    else {
                        UIUtils::displayText("Invalid input");
                    }
                }
                
                else if(menuInput2 == "No" || menuInput2 == "no") {
                    menu.MainMenu();
                    break;
                }
                
                break;
            case 2:
                menu.LoadGameMenu(*player);
                break;
            case 3:
                menu.NewGameMenu();
                
                UIUtils::displayText("Enter character type:");
                cin >> characterType;
                
                if(characterType != "Quit") {
                    menu.ViewCharactersMenu(characterType);
                }
                
                else if(characterType == "Quit") {
                    menu.QuitMenu();
                    cin >> menuInput2;
                    
                    if(menuInput2 == "Yes") {
                        menu.QuitMenu2();
                    }
                    else if(menuInput2 == "No") {
                        menu.MainMenu();
                        break;
                    }
                }
                break;
            case 4:
                menu.QuitMenu();
                cin >> menuInput2;
                
                if(menuInput2 == "Yes") {
                    menu.QuitMenu2();
                }
                else if(menuInput2 == "No") {
                    menu.MainMenu();
                }
                break;
            }
        }
        while(invalidInput == true);

        delete player;
        delete enemy;
        
        return 0;
    }


