#include "SaveLoad.hpp"
#include <fstream>
#include <iostream>
using namespace std;

void saveGame(const string& username, const string& characterType, int currHealth, int currArmor, int level, int currXP, int maxXP) {
    ofstream saveFile(username + "_save.txt");
    if (saveFile.is_open()) {
        saveFile << characterType << "\n"
                 << currHealth << "\n"
                 << currArmor << "\n"
                 << level << "\n"
                 << currXP << "\n"
                 << maxXP << "\n";
        cout << "Game saved successfully!" << endl;
        saveFile.close();
    } else {
        cout << "Error saving game!" << endl;
    }
}

bool loadGame(const string& username, string& characterType, int& currHealth, int& currArmor, int& level, int& currXP, int& maxXP) {
    ifstream loadFile(username + "_save.txt");
    if (loadFile.is_open()) {
        getline(loadFile, characterType);
        loadFile >> currHealth >> currArmor >> level >> currXP >> maxXP;
        cout << "Game loaded successfully!" << endl;
        loadFile.close();
        return true;
    } else {
        cout << "No saved game found for username: " << username << endl;
        return false;
    }
}
