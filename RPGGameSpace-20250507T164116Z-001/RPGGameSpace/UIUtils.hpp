// UIUtils.hpp
#ifndef UIUTILS_HPP
#define UIUTILS_HPP

#include <string>
#include <vector>
using namespace std;

class Character; // Forward declaration

namespace UIUtils {
    void displayText(const string& text);
    string getUserInput(const string& prompt);
    void displayCharacterStats(const Character* character);
    void displayMenu(const vector<string>& options);
    void clearScreen();
    void typeEffect(const string& text, int delayMs = 50);
}

#endif