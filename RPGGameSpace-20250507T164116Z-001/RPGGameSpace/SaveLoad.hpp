#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

#include <string>
using std::string;

void saveGame(const string& username, const string& characterType, int currHealth, int currArmor, int level, int currXP, int maxXP);
bool loadGame(const string& username, string& characterType, int& currHealth, int& currArmor, int& level, int& currXP, int& maxXP);

#endif // SAVELOAD_HPP
