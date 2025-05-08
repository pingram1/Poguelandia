// UIUtils.cpp
#include "UIUtils.hpp"
#include "Character.hpp"
#include <iostream>
#include <iomanip>  // For formatting output
#ifdef _WIN32
    #include <windows.h> // For Sleep() on Windows
#else
    #include <unistd.h>  // For usleep() on non-Windows
#endif

using namespace std;

namespace UIUtils {
    void displayText(const string& text) {
        cout << text << endl;
    }

    string getUserInput(const string& prompt) {
        cout << prompt << endl;
        string input;
        getline(cin, input);
        return input;
    }

    void displayCharacterStats(const Character* character) {
        if (character) {
            cout << "Name: " << character->getName() << endl;
            cout << "Level: " << character->getLevel() << endl;
            cout << "Health: " << character->getCurrHealth() << "/" << character->getMaxHealth() << endl;
            cout << "Armor: " << character->getCurrArmor() << "/" << character->getMaxArmor() << endl;
        } else {
            cout << "No character to display." << endl;
        }
    }

    void displayMenu(const vector<string>& options) {
        for (size_t i = 0; i < options.size(); ++i) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
    }

    void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    void typeEffect(const string& text, int delayMs) {
        for (char c : text) {
            cout << c << flush;
        #ifdef _WIN32
            Sleep(delayMs);
        #else
            usleep(delayMs * 1000); // microseconds
        #endif
        }
        cout << endl;
    }
}
