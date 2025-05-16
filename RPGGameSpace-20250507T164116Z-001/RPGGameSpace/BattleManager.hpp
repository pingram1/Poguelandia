#ifndef BATTLE_MANAGER_HPP
#define BATTLE_MANAGER_HPP

#include "Character.hpp"
#include "Enemy.hpp"
#include <string>

class BattleManager {
public:
    // Subtract damage from the target's armor first; any remaining damage is taken from health.
    void processDamage(Character* target, int damage);
    
    // Handles an attack by having the attacker calculate its damage based on the action,
    // then applying that damage to the defender.
    void handleAttack(Character* attacker, Character* defender, const string &action);
    
    // Processes a full battle round. The player executes an attack with a given action,
    // and if the enemy survives, the enemy counterattacks (choosing a random action).
    // Returns true if both combatants remain alive after the round; false otherwise.
    bool processRound(Character* player, Enemy* enemy, const string &playerAction);
};

#endif // BATTLE_MANAGER_HPP

