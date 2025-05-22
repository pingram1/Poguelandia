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
bool result(const Character* p, const Character* e) {
    if (e->getCurrHealth() <= 0 && p->getCurrHealth() > 0) return true; // Player wins
    if (p->getCurrHealth() <= 0 && e->getCurrHealth() > 0) return false; // CPU wins
    return false; // Tie or both alive (though loop should handle both alive)
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
    return p->getCurrHealth() > 0 && e->getCurrHealth() > 0;
}

void createEnemy(Enemy*& enemyPtrRef, const string& enemyCharacterType) { // Note: Enemy*&
    delete enemyPtrRef; // Safely delete the old enemy object if it exists
    enemyPtrRef = new Enemy("Mysterious Foe", enemyCharacterType);
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
    string enemyAttackType, enemyCharacterType, enemyCurrentAction;
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
                        enemyCurrentAction = enemy->randomizeEnemyActions();
                        //enemyCurrArmor = enemy->getCurrArmor();
                        
                        UIUtils::displayText("Select action: Attack [Light  Normal  Heavy], Defend [Block  Parry  Evade]");
                        cin >> action;

                        unsigned int playerAttackProb = 0;
                        unsigned int playerDefendProb = 0;
                        bool playerIsAttacking = (action == "Light" || action == "light" || action == "Normal" || action == "normal" || action == "Heavy" || action == "heavy");
                        
                        if (playerIsAttacking) {
                            playerAttackProb = player->attackProbability(action);
                        }
                        else if (action == "Block" || action == "Parry" || action == "Evade" || action == "block" || action == "parry" || action == "evade") { // Player is defending
                            playerDefendProb = player->defendProbability(action);
                        } 
                        else {
                            UIUtils::displayText("Invalid action! Turn skipped."); // Or re-prompt
                            continue;
                        }

                        // Enemy Action and Probabilities
                        unsigned int enemyAttackProb = 0;
                        unsigned int enemyDefendProb = 0;
                        bool enemyIsAttacking = (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy" || enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade");

                        if (enemyIsAttacking) {
                            enemyAttackProb = enemy->attackProbability(enemyCurrentAction);
                        } 
                        else { // Enemy is defending
                            enemyDefendProb = enemy->defendProbability(enemyCurrentAction);
                        }

                        // Display Probabilities (as you do with UIUtils::displayText)
                        if (playerIsAttacking && !enemyIsAttacking) { // Player Attacks, Enemy Defends
                            UIUtils::displayText("Player Attack (" + action + "): " + to_string(playerAttackProb) + "% vs. Enemy Defend (" + enemyCurrentAction + "): " + to_string(enemyDefendProb) + "%");
                            if (playerAttackProb > enemyDefendProb) { // Player's attack lands
                                UIUtils::displayText("Your attack connects!");
                                battleManager.handleAttack(player, enemy, action); // Pass player's action
                                menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
                            } 
                            else {
                                UIUtils::displayText("Your attack is blocked or evaded!");
                                menu.BattleMenu4(player->getCharacterType(), false, player, enemy);
                            }
                        } 
                        else if (playerIsAttacking && enemyIsAttacking) { // Player Attacks, Enemy Attacks (Clash)
                            UIUtils::displayText("Clash! Player Attack (" + action + "): " + to_string(playerAttackProb) + "% vs. Enemy Attack (" + enemyCurrentAction + "): " + to_string(enemyAttackProb) + "%");
                            // Resolve who hits. Example: fightFirst or higher probability.
                            // This part needs to reflect your desired clash mechanics.
                            // Simplified: If player's probability is higher, player hits. Enemy might still hit if they survive.
                            // Or, only one hits.
                            bool playerHitsInClash = (playerAttackProb > enemyAttackProb);
                            bool enemyHitsInClash = (enemyAttackProb > playerAttackProb); 
                            if (playerAttackProb == enemyAttackProb) { // Tie? Maybe both hit or neither.
                                UIUtils::displayText("Attacks are evenly matched!");
                                // Decide outcome: for now, let's say player hits if fightFirst == 1 in tie, else enemy.
                                // Inside Attack vs. Attack
                                if (fightFirst == 1) { // Player has initiative
                                    if (playerAttackProb > enemyAttackProb) { /* Player hits */ 
                                        battleManager.handleAttack(player, enemy, action); 
                                    }
                                    if (enemy->getCurrHealth() > 0 && enemyAttackProb > playerAttackProb) { /* Enemy hits */ 
                                        battleManager.handleAttack(enemy, player, enemyCurrentAction); 
                                    }
                                    // Handle ties: 
                                    if (playerAttackProb == enemyAttackProb) { /* Player hits due to initiative */ 
                                        battleManager.handleAttack(player, enemy, action); 
                                    }
                                } 
                                else { // Enemy has initiative
                                    if (enemyAttackProb > playerAttackProb) { /* Enemy hits */ 
                                        battleManager.handleAttack(enemy, player, enemyCurrentAction); 
                                    }
                                    if (player->getCurrHealth() > 0 && playerAttackProb > enemyAttackProb) { /* Player hits */ 
                                        battleManager.handleAttack(player, enemy, action); 
                                    }
                                    // Handle ties: 
                                    if (playerAttackProb == enemyAttackProb) { /* Enemy hits due to initiative */ 
                                        battleManager.handleAttack(enemy, player, enemyCurrentAction); 
                                    }
                                }
                            }

                            if (playerHitsInClash) {
                                UIUtils::displayText("Your attack lands in the clash!");
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu4(player->getCharacterType(), true, player, enemy);
                            }
                            if (enemy->getCurrHealth() > 0 && enemyHitsInClash) { // Enemy can only hit if alive and won the clash roll for their hit
                                UIUtils::displayText("The enemy's attack lands in the clash!");
                                battleManager.handleAttack(enemy, player, enemyCurrentAction);
                                // Which menu to call if player also hit? Or if only enemy hit?
                                menu.BattleMenu5(player->getCharacterType(), action, false, player, enemy); // If player got hit
                            }
                            if (!playerHitsInClash && !enemyHitsInClash && playerAttackProb != enemyAttackProb) { // One missed, other didn't hit due to lower prob
                                UIUtils::displayText("Both attacks miss in the chaos!");
                            }

                        else if (!playerIsAttacking && enemyIsAttacking) { // Player Defends, Enemy Attacks
                            UIUtils::displayText("Player Defend (" + action + "): " + to_string(playerDefendProb) + "% vs. Enemy Attack (" + enemyCurrentAction + "): " + to_string(enemyAttackProb) + "%");
                            if (playerDefendProb > enemyAttackProb) {
                                UIUtils::displayText("You successfully defend!");
                                menu.BattleMenu5(player->getCharacterType(), action, true, player, enemy);
                            } 
                            else {
                                UIUtils::displayText("The enemy's attack gets through!");
                                battleManager.handleAttack(enemy, player, enemyCurrentAction); // Pass enemy's action
                                menu.BattleMenu5(player->getCharacterType(), action, false, player, enemy);
                            }
                        } 
                        else { // Player Defends, Enemy Defends
                            UIUtils::displayText("Both defend! Player Defend (" + action + "): " + to_string(playerDefendProb) + "% vs. Enemy Defend (" + enemyCurrentAction + "): " + to_string(enemyDefendProb) + "%");
                            UIUtils::displayText("A momentary standoff!");
                            menu.BattleMenu6(player->getCharacterType(), true, player, enemy);
                        }

                        // Check for game over after the round
                        if (player->getCurrHealth() <= 0 || enemy->getCurrHealth() <= 0) {
                            break; // Exit battle loop
                        }
                    }
                        
                        //Gets probability of performing this attack based on the attack/defend type
                        if(action == "Light" || action == "Normal" || action == "Heavy") {
                            attackType = action;
                            attackProbability = player->attackProbability(attackType);
                        }
                        if(action == "Block" || action == "Parry" || action == "Evade" ||action == "block" || action == "parry" || action == "evade") {
                            defendType = action;
                            defendProbability = player->defendProbability(defendType);
                        }
                                                    
                        //Compares every combo of user actions vs. CPU actions
                        bool attackExecuted = userAttackLanded(attackProbability, enemyDefendProbability);
                        bool defendExecuted = userDefendExecuted(defendProbability, enemyAttackProbability);
                        bool attackExecuted2 = attackVSattack(attackProbability, enemyAttackProbability);
                                                
                        //Shows percentages in game to see which action will be executed in combat
                        UIUtils::displayText("");
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                            UIUtils::displayText("Attack: " + to_string(attackProbability) + " vs. Enemy Attack: " + to_string(enemyAttackProbability));
                        }
                                                
                        else if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                            UIUtils::displayText("Attack: " + to_string(attackProbability) + " vs. Enemy Defend: " + to_string(enemyDefendProbability));
                        }
                                                
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                            UIUtils::displayText("Defend: " + to_string(defendProbability) + " vs. Enemy Attack: " + to_string(enemyAttackProbability));
                        }
                                                
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                            UIUtils::displayText("Defend: " + to_string(defendProbability) + " vs. Enemy Defend: " + to_string(enemyDefendProbability));
                        }
                        UIUtils::displayText("");
                                                
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                            if(attackExecuted == true) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                            }
                                                    
                            else if(attackExecuted == false) {
                                menu.BattleMenu4(characterType, attackExecuted, player, enemy);
                            }
                        }
                                                
                        if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                            if(attackExecuted2 == true) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu4(characterType, attackExecuted2, player, enemy);
                            }
                                                    
                            else if(attackExecuted2 == false) {
                                battleManager.handleAttack(player, enemy, action);
                                menu.BattleMenu5(characterType, action, attackExecuted2, player, enemy);
                                }
                        }
                                                
                        else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                            if(defendExecuted == true) {
                                menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                            }
                                                    
                        else if(defendExecuted == false) {
                            battleManager.handleAttack(player, enemy, action);
                            menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                        }

                        // 
                        while(hasHealth(player, enemy) == true) {
                            enemyCurrentAction = enemy->randomizeEnemyActions();
                                                
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
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                                UIUtils::displayText("Attack chance: " + to_string(attackProbability) + " vs. Enemy Attack chance: " + to_string(enemyAttackProbability));
                            }
                            
                            else if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                                UIUtils::displayText("Attack chance: " + to_string(attackProbability) + " vs. Enemy Defend chance: " + to_string(enemyDefendProbability));
                            }
                            
                            else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                                UIUtils::displayText("Defend chance: " + to_string(defendProbability) + " vs. Enemy Attack chance: " + to_string(enemyAttackProbability));
                            }
                            
                            else if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                                UIUtils::displayText("Defend chance: " + to_string(defendProbability) + " vs. Enemy Defend chance: " + to_string(enemyDefendProbability));
                            }
                            UIUtils::displayText("");
                            
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
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
                            
                            if((action == "Light" || action == "Normal" || action == "Heavy") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy"))
                                if(attackExecuted2 == true) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu4(characterType, attackExecuted2, player, enemy);
                                }
                                
                                else if(attackExecuted2 == false) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu5(characterType, action, attackExecuted2, player, enemy);
                                }
                            }
                            
                            
                            if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Light" || enemyCurrentAction == "Normal" || enemyCurrentAction == "Heavy")) {
                                if(defendExecuted == true) {
                                    menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                                }
                                
                                else if(defendExecuted == false) {
                                    battleManager.handleAttack(player, enemy, action);
                                    menu.BattleMenu5(characterType, action, defendExecuted, player, enemy);
                                }
                            }
                            
                            if((action == "Block" || action == "Parry" || action == "Evade") && (enemyCurrentAction == "Block" || enemyCurrentAction == "Parry" || enemyCurrentAction == "Evade")) {
                                bool doubleDefend = true;
                                menu.BattleMenu6(characterType, doubleDefend, player, enemy);
                            }
                        }
                    }
                    
                    bool fightResult = result(player, enemy);
                    
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


