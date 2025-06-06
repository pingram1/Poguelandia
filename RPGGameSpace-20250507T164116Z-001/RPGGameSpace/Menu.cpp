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
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ANSI color codes (These will eventually be replaced by GUI elements, but for now, keep them for console compatibility)
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define DARK_GRAY "\033[90m" // Example: for cave walls or less prominent elements
#define BROWN "\033[33m" // Can be used for ground or tree trunks

const vector<string> ARENA_FLOOR_ART = {
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
    " .       .       .       .       .       .       .       .       .       . ",
    "_______________________________________________________________________________"
};

const vector<string> FOREST_BACKDROP_ART = {
    "          /\\              /\\              /\\          ",
    "         /  \\            /  \\            /  \\         ",
    "        /~~~~\\          /~~~~\\          /~~~~\\        ",
    "       /______\\        /______\\        /______\\       ",
    "          ||               ||               ||           ",
    "        ~~\"\"~~        ~~\"\"~~          ~~\"\"~~         "
};

const vector<string> CAVE_BACKDROP_ART = {
    "   ^^^^    ^^^^    ^^^^    ^^^^    ^^^^    ^^^^   ",
    "  /    \\  /    \\  /    \\  /    \\  /    \\  /    \\  ",
    " (  ()  )(  ()  )(  ()  )(  ()  )(  ()  )(  ()  ) ",
    "  \\____/  \\____/  \\____/  \\____/  \\____/  \\____/  ",
    "                                                  ",
    "    V       V       V       V       V       V     "
};

// Simple Enemy Sprite Placeholders (adjust width to ~20-25 chars)
const vector<string> GENERIC_ENEMY_SPRITE = {
    "       .--''''--.       ",
    "      /   O  O   \\      ",
    "      |    --    |      ",
    "      |  ------  |      ",
    "       '.______.'       "
};

const vector<string> WARRIOR_ENEMY_SPRITE = {
    "       .--\"\"--.       ",
    "      / [#]  [#] \\      ",
    "     |   <==>   |      ",
    "     \\   /\"\"\\   /      ",
    "      '.______.'       "
};

const vector<string> WIZARD_ENEMY_SPRITE = {
    "         _/\\_         ",
    "        (o--o)        ",
    "       /(    )\\       ",
    "      / | \"\" | \\      ",
    "     (_/------\\_)      "
};

string centerPad(const std::string& str, int maxWidth) {
    // Calculate effective length of string without ANSI codes for centering
    string tempStr = str;
    size_t pos = 0;
    while((pos = tempStr.find("\033[", pos)) != std::string::npos) {
        size_t endPos = tempStr.find("m", pos);
        if (endPos != std::string::npos) {
            tempStr.erase(pos, endPos - pos + 1);
        } else { // Malformed ANSI
            break;
        }
    }
    int len = tempStr.length();

    if (len >= maxWidth) {
        // This might truncate in the middle of an ANSI sequence if not careful
        // For simplicity, we'll just return the original string if it's too long
        // A more robust solution would strip ANSI before substr, then re-apply if possible
        return str; 
    }
    int padding = (maxWidth - len) / 2;
    return std::string(padding, ' ') + str; // Original string with ANSI codes is prepended with spaces
}

// Helper function to generate a formatted health and armor bar string
// This function is local to Menu.cpp
string getHealthBarString(const string& characterName, int hp, int maxHp, int currentArmor, int maxArmor, int level) {
    string barOutputStr;
    
    // Max widths for alignment
    const int nameFieldWidth = 15;    // Adjusted for "Player" / "Enemy Name"
    const int levelFieldWidth = 8;   // For "Lvl: X"
    const int hpBarVisualWidth = 20; // Width of the [#---] part
    const int hpTextFieldWidth = 12; // For "XXX/XXX"
    const int armorTextFieldWidth = 15; // For "Armor: XX/XX"

    // Character Name (padded or truncated)
    string displayName = characterName;
    if (displayName.length() > static_cast<size_t>(nameFieldWidth -1)) {
        displayName = displayName.substr(0, nameFieldWidth - 4) + "... ";
    } else {
        displayName.insert(0, nameFieldWidth - displayName.length(), ' '); // Right align name
        // displayName.append(nameFieldWidth - displayName.length(), ' '); // Left align name
    }
    barOutputStr += BOLD + displayName + RESET;

    // Level
    string levelStr = " Lvl:" + to_string(level);
    levelStr.append(levelFieldWidth - levelStr.length(), ' ');
    barOutputStr += levelStr;

    // Health Bar
    int displayHp = (hp < 0) ? 0 : hp;
    if (maxHp <= 0) maxHp = 1; // Avoid division by zero and ensure positive maxHp

    int filledBars = static_cast<int>((static_cast<double>(displayHp) / maxHp) * hpBarVisualWidth);
    if (filledBars < 0) filledBars = 0;
    if (filledBars > hpBarVisualWidth) filledBars = hpBarVisualWidth;
    int emptyBars = hpBarVisualWidth - filledBars;

    barOutputStr += " HP:[";
    barOutputStr += GREEN;
    for (int i = 0; i < filledBars; i++) barOutputStr += "#";
    barOutputStr += RED;
    for (int i = 0; i < emptyBars; i++) barOutputStr += "-";
    barOutputStr += RESET;
    barOutputStr += "]";

    string hpText = " " + to_string(displayHp) + "/" + to_string(maxHp);
    hpText.append(hpTextFieldWidth - hpText.length(), ' ');
    barOutputStr += hpText;
    
    // Armor
    string armorText = " Armor:" + to_string(currentArmor) + "/" + to_string(maxArmor);
    armorText.append(armorTextFieldWidth - armorText.length(), ' '); // Padding for armor text
    barOutputStr += armorText;
    
    return barOutputStr;
}

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

void Menu::BaseGameMenu(string menuName, string menuCharacterType, Character* player) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if (player) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|  Character Name: " + menuName);
        UIUtils::displayText("|  Character Type: " + menuCharacterType);
        string playerBar = getHealthBarString("", player->getCurrHealth(), player->getMaxHealth(), player->getCurrArmor(), player->getMaxArmor(), player->getLevel());
        string playerLine = "| " + playerBar;
        size_t paddingNeeded = 0;
        // Calculate visible length of playerBar for padding
        string tempPlayerBar = playerBar;
        size_t pos_pb = 0;
        while((pos_pb = tempPlayerBar.find("\033[", pos_pb)) != string::npos) {
            size_t endPos_pb = tempPlayerBar.find("m", pos_pb);
            if (endPos_pb != string::npos) { tempPlayerBar.erase(pos_pb, endPos_pb - pos_pb + 1); } 
            else { break; }
        }
        if (75 > tempPlayerBar.length()) { paddingNeeded = 75 - tempPlayerBar.length(); }
        playerLine.append(paddingNeeded, ' '); 
        playerLine += " |";
        UIUtils::displayText(playerLine);
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

void Menu::BattleMenu1(string menuCharacterType, Character* player) {
    UIUtils::clearScreen(); 
    string specialAbilityInfo = "";
    if(menuCharacterType == "Warrior") specialAbilityInfo = R"(Warriors have a War Cry; when HP is low, damage doubles.)";
    else if(menuCharacterType == "Wizard") specialAbilityInfo = R"(Wizards have Mystic Heal; regain HP/Armor on Light Attack.)";
    else if(menuCharacterType == "Healer") specialAbilityInfo = R"(Healers: First Aid (HP/move), Chronic Abrasion (dmg boost).)";
    else if(menuCharacterType == "Assassin") specialAbilityInfo = R"(Assassins have Sneaky Quick; first attacks of type deal extra.)";


    if (player) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                    Know Your Hero!                                    |");
        UIUtils::displayText("|---------------------------------------------------------------------------------------|");
        string playerBar = getHealthBarString(player->getName(), player->getCurrHealth(), player->getMaxHealth(), player->getCurrArmor(), player->getMaxArmor(), player->getLevel());
        string playerLine = "| " + playerBar;
        // Padding for playerLine
        string tempPlayerBar_bm1 = playerBar;
        size_t pos_bm1 = 0;
        while((pos_bm1 = tempPlayerBar_bm1.find("\033[", pos_bm1)) != string::npos) {
            size_t endPos_bm1 = tempPlayerBar_bm1.find("m", pos_bm1);
            if (endPos_bm1 != string::npos) { tempPlayerBar_bm1.erase(pos_bm1, endPos_bm1 - pos_bm1 + 1); } 
            else { break; }
        }
        size_t paddingNeeded_bm1 = 0; if (75 > tempPlayerBar_bm1.length()) paddingNeeded_bm1 = 75 - tempPlayerBar_bm1.length();
        playerLine.append(paddingNeeded_bm1, ' '); playerLine += "       |";
        UIUtils::displayText(playerLine);
        
        string specialLine = "| Special: " + specialAbilityInfo;
        // Padding for specialLine
        std::string tempSpecialInfo = specialAbilityInfo;
        size_t pos_si = 0;
        while((pos_si = tempSpecialInfo.find("\033[", pos_si)) != string::npos) { // Unlikely here but good practice
            size_t endPos_si = tempSpecialInfo.find("m", pos_si);
            if (endPos_si != string::npos) { tempSpecialInfo.erase(pos_si, endPos_si - pos_si + 1); } 
            else { break; }
        }
        size_t specialPadding = 0; if (75 > (tempSpecialInfo.length() + 11) ) specialPadding = 75 - (tempSpecialInfo.length() + 11); // +11 for "| Special: " and " |"
        specialLine.append(specialPadding, ' '); specialLine += "       |";
        UIUtils::displayText(specialLine); 
        UIUtils::displayText("|                                Now it's time for battle!                              |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    } else { UIUtils::displayText("Error: Player data not available for BattleMenu1."); }
    UIUtils::displayText("");
}

void Menu::BattleMenu2(string menuCharacterType, Character* player) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if (player) {
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        string playerBar = getHealthBarString(player->getName(), player->getCurrHealth(), player->getMaxHealth(), player->getCurrArmor(), player->getMaxArmor(), player->getLevel());
        string playerLine = "| " + playerBar;
        size_t paddingNeeded = 0;
        if (75 > playerBar.length()) {
            paddingNeeded = 75 - playerBar.length();
        }
        playerLine.append(paddingNeeded, ' ');
        UIUtils::displayText(playerLine);
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
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
        UIUtils::displayText("Error: Player data not available.");
    }
    
    UIUtils::displayText("");
}

void Menu::ViewCharactersMenu(string menuCharacterType) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if(menuCharacterType == "Warrior" || menuCharacterType == "warrior") {
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
    
    else if(menuCharacterType == "Wizard" || menuCharacterType == "wizard") {
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
    
    else if(menuCharacterType == "Healer" || menuCharacterType == "healer") {
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
    
    else if(menuCharacterType == "Assassin" || menuCharacterType == "assassin") {
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

void Menu::BattleMenuSharedContent(Character* player, Enemy* enemy, const string& battleMessage) {
    const int contentWidth = 75;

    // --- Select and Display Dynamic Background & Enemy Sprite ---
    vector<string> backdropArt;
    vector<string> enemySprite = GENERIC_ENEMY_SPRITE; // Default sprite
    string sceneColor = YELLOW; // Default color for backdrop elements

    if (enemy) {
        string enemyType = enemy->getCharacterType();
        if (enemyType == "Warrior" || enemyType == "Goblin") { // Assuming Goblin is a type of warrior
            backdropArt = FOREST_BACKDROP_ART; // Example
            enemySprite = WARRIOR_ENEMY_SPRITE;
            sceneColor = GREEN;
        } else if (enemyType == "Wizard") {
            backdropArt = CAVE_BACKDROP_ART; // Example
            enemySprite = WIZARD_ENEMY_SPRITE;
            sceneColor = DARK_GRAY;
        } else if (enemyType == "Healer") { // Enemy healer might be in a sacred grove / ruins
            backdropArt = FOREST_BACKDROP_ART; // Reuse for simplicity
            // enemySprite = HEALER_ENEMY_SPRITE; // Define this sprite
            sceneColor = GREEN;
        } else if (enemyType == "Assassin") {
             backdropArt = CAVE_BACKDROP_ART; // Dim, shadowy place
            // enemySprite = ASSASSIN_ENEMY_SPRITE; // Define this sprite
            sceneColor = DARK_GRAY;
        } else { // Default
            backdropArt = FOREST_BACKDROP_ART;
        }
    } else { // No enemy data, use a generic backdrop
        backdropArt = ARENA_FLOOR_ART; // This one is wider, be careful
    }

    /*// Display background art (first few lines)
    for (size_t i = 0; i < backdropArt.size() && i < 3; ++i) { // Display top 3 lines of backdrop
        string line = "| " + centerPad(sceneColor + backdropArt[i] + RESET, contentWidth) + " |";
        UIUtils::displayText(line);
    }
    
    // Display enemy sprite (centered)
    for (const std::string& spriteLine : enemySprite) {
        std::string line = "| " + centerPad(RED + spriteLine + RESET, contentWidth) + " |"; // Enemy sprite in Red
        UIUtils::displayText(line);
    }

    // Display rest of background/floor art
    for (const string& floorLine : ARENA_FLOOR_ART) {
        string line = string("| ") + BOLD + BROWN + floorLine.substr(0, std::min((size_t)contentWidth, floorLine.length())) + RESET;
        // Pad the rest if floorLine is shorter than contentWidth
        if (floorLine.length() < contentWidth) {
            line.append(contentWidth - floorLine.length(), ' ');
        }
        line += string(BOLD) + BROWN + " |" + RESET;
        UIUtils::displayText(line);
    }
    
    /*UIUtils::displayText(string(BOLD) + CYAN + 
        "|                                                                                       |" + RESET);*/ 



    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|                                  Battle Status                                        |");
    UIUtils::displayText("|---------------------------------------------------------------------------------------|");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    string playerBarStr = getHealthBarString(player->getName(), player->getCurrHealth(), player->getMaxHealth(), player->getCurrArmor(), player->getMaxArmor(), player->getLevel());
    string playerLine = "| " + playerBarStr;
    size_t playerPadding = 0;
    if (75 > playerBarStr.length() +1) playerPadding = 75 - (playerBarStr.length() +1) ; // +1 for the initial space in "| "
    playerLine.append(playerPadding , ' '); 
    playerLine += "|";
    UIUtils::displayText(playerLine);

    string enemyBarStr  = getHealthBarString(enemy->getName(), enemy->getCurrHealth(), enemy->getMaxHealth(), enemy->getCurrArmor(), enemy->getMaxArmor(), enemy->getLevel());
    string enemyLine = "| " + enemyBarStr;
    size_t enemyPadding = 0;
     if (75 > enemyBarStr.length() +1) enemyPadding = 75 - (enemyBarStr.length() +1) ;
    enemyLine.append(enemyPadding , ' ');
    UIUtils::displayText(enemyLine);

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
    // Battle Message
    string formattedBattleMessage = "| " + battleMessage;
    size_t messagePadding = 0;
    if (contentWidth > battleMessage.length()) messagePadding = contentWidth - battleMessage.length();
    formattedBattleMessage.append(messagePadding, ' ');
    formattedBattleMessage += " |";
    UIUtils::displayText(string(BOLD) + CYAN + formattedBattleMessage + RESET);
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
}

void Menu::BattleMenu3(string menuCharacterType, int fightFirst, Character* player, Enemy* enemy) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display
    
    string battlePhrases = "";
    if(fightFirst == 1) {
        battlePhrases = "Looks like you're fighting first, make a move";
    }
    else if(fightFirst == 2) {
        battlePhrases = "Looks like the enemy gets to make the first move, respond accordingly";
    }

    if (player && enemy) {
        BattleMenuSharedContent(player, enemy,battlePhrases);
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu3.");
    }
    
    UIUtils::displayText("");
}

void Menu::BattleMenu4(string menuCharacterType, bool attackExecuted, Character* player, Enemy* enemy) {
    UIUtils::clearScreen(); // Clear screen for a fresh menu display
    
    string battlePhrases = "";
    if(attackExecuted != false) {
        battlePhrases = "Great strike! Keep the pressure on 'em";
    }
    else {
        battlePhrases = "Not every strike has to land for you to damage your opponent";
    }

    if (player && enemy) {
        BattleMenuSharedContent(player, enemy,battlePhrases);
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu4.");
    }
    
    UIUtils::displayText("");
}

void Menu::BattleMenu5(string menuCharacterType, string action, bool defendExecuted, Character* player, Enemy* enemy) {
    string battlePhrases = "";
    
    if(defendExecuted == true && (action == "Block" || action == "block")) {
        battlePhrases = "Effective block, still hurts a little though";
    }
    
    else if(defendExecuted == true && (action == "Parry" || action == "parry")) {
        battlePhrases = "Great reaction! Now it's time to counter your opponent";
    }
    
    else if(defendExecuted == true && (action == "Evade" || action == "evade")) {
        battlePhrases = "Looks like they missed completely, here's your chance";
    }
    
    //User attack probability is lower than enemy attack/defend probability
    else if((defendExecuted == false) && (action == "Light" || action == "Normal" || action == "Heavy" || action == "light" || action == "normal" || action == "heavy")) {
        battlePhrases = "Maybe try recalibrating your swing ... because you missed";
    }
    
    else if((defendExecuted == false) && (action == "Block" || action == "Parry" || action == "Evade" || action == "block" || action == "parry" || action == "evade")) {
        battlePhrases = "Ouch. They got you pretty good, maybe you should heal or something";
    } else {
        battlePhrases = "The tide of battle shifts!"; // Generic
    }

    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if (player && enemy) {
        BattleMenuSharedContent(player, enemy,battlePhrases);
    } else {
        UIUtils::displayText("Error: Invalid character type for BattleMenu5.");
    }
    
    UIUtils::displayText("");
}

void Menu::BattleMenu6(string menuCharacterType, bool doubleDefend, Character* player, Enemy* enemy) {
    string battlePhrases = "";
    
    if(doubleDefend != false) {
        battlePhrases = "So y'all are just going to stare at each other?";
    }
    
    UIUtils::clearScreen(); // Clear screen for a fresh menu display

    if (player && enemy) {
        BattleMenuSharedContent(player, enemy,battlePhrases);
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
        UIUtils::displayText("|                        Every great fighter has suffered loss                          |");
        UIUtils::displayText("|                                  Level Up! Level " + to_string(level));
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

void Menu::LoadGameMenu(Character &player) {
    // This function needs careful implementation if player might be null
    // or if it's supposed to create/reinitialize the player.
    // The mainRPG.cpp currently calls this with *player, which could be null if not initialized.
    // For now, assuming player is valid or this function handles it.
    string username, characterType;
    int currHealth, currArmor, levelFromFile, currXP, maxXP; // Renamed level to levelFromFile
    // int currLevel = 1; // This was overriding the loaded level.

    UIUtils::displayText("Enter fighter name to load: ");
    // username = UIUtils::getUserInput(""); // getUserInput reads a whole line, cin >> might be better here
    cin >> username;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (loadGame(username, characterType, currHealth, currArmor, levelFromFile, currXP, maxXP)) {
        // If player object is passed by reference, we can modify it.
        // However, the type of player (Warrior, Wizard etc.) is fixed at its creation.
        // Loading should ideally re-create the player object of the correct type.
        // This is a more complex change. For now, we'll just set stats.
        // This assumes the 'player' object passed is of the correct Character subclass.
        
        player.setCharacterType(characterType); // This might not be ideal if 'player' is already a specific subclass.
                                            // The type should match what's in the save file.
        player.setName(username); // Set the name from the save file/username
        player.setCurrHealth(currHealth);
        player.setCurrArmor(currArmor);
        player.setLevel(levelFromFile); // Use loaded level
        player.setCurrXP(currXP);
        player.setMaxXP(maxXP);
        UIUtils::displayText("Game loaded successfully!");
        
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                            ------ Loaded Game State ------                            |");
        UIUtils::displayText("|                               Character Name: " + player.getName());
        UIUtils::displayText("|                               Character Type: " + player.getCharacterType());                   
        UIUtils::displayText("|                               Current Health: " + to_string(player.getCurrHealth()) + "/" + to_string(player.getMaxHealth()));                      
        UIUtils::displayText("|                               Current Armor: " + to_string(player.getCurrArmor()) + "/" + to_string(player.getMaxArmor()));                        
        UIUtils::displayText("|                               Current Level: " + to_string(player.getLevel()));   
        UIUtils::displayText("|                               Current XP: " + to_string(player.getCurrXP()) + "/" + to_string(player.getMaxXP()));                     
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                                                                                       |");
        UIUtils::displayText("|                               Press Enter to continue...                              |");
        UIUtils::displayText("*---------------------------------------------------------------------------------------*");
        cin.get(); // Wait for enter
    } else {
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
        UIUtils::displayText("Press Enter to continue...");
        cin.get();
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
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|  Type      : " + player.getCharacterType());
    UIUtils::displayText("|  Level     : " + to_string(player.getLevel()));
    UIUtils::displayText("|  Health    : " + to_string(player.getCurrHealth()) + " / " + to_string(player.getMaxHealth()));
    UIUtils::displayText("|  Armor     : " + to_string(player.getCurrArmor()) + " / " + to_string(player.getMaxArmor()));
    UIUtils::displayText("|  XP        : " + to_string(player.getCurrXP()) + " / " + to_string(player.getMaxXP()));                                                                                    
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("|                                                                                       |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    UIUtils::displayText("|  Game progress has been saved. Press Enter to return to the Main Menu.                |");
    UIUtils::displayText("*---------------------------------------------------------------------------------------*");
    cin.get();
}





