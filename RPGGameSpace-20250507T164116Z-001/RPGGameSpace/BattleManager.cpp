#include "BattleManager.hpp"
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include "Character.hpp"
#include "Enemy.hpp"

// Process damage by reducing armor first then health
void BattleManager::processDamage(Character &target, int damage) {
    int currentArmor = target.getCurrArmor();
    if (currentArmor >= damage) {
        target.setCurrArmor(currentArmor - damage);
    } else {
        int remainingDamage = damage - currentArmor;
        target.setCurrArmor(0);
        int currentHealth = target.getCurrHealth();
        int newHealth = currentHealth - remainingDamage;
        // Clamp health to zero so it never goes negative:
        if(newHealth < 0) {
            newHealth = 0;
        }
        target.setCurrHealth(newHealth);
    }
}

// Handle an attack from attacker to defender using the provided action.
// It calculates the damage by calling the attack method on the attacker and then applies it.
void BattleManager::handleAttack(Character &attacker, Character &defender, const string &action) {
    int damage = attacker.attack(action);
    processDamage(defender, damage);
}

// Process a battle round: player attacks enemy using a given action,
// then if the enemy is still alive, the enemy performs an attack using a randomized action.
// Returns true if both are still alive after the round; otherwise false.
bool BattleManager::processRound(Character &player, Character &enemy, const string &playerAction) {
    // Player's turn: attack the enemy.
    handleAttack(player, enemy, playerAction);

    // Check if the enemy was defeated.
    if (enemy.getCurrHealth() <= 0) {
        return false;
    }

    // Enemy's turn: pick a random action and counterattack.
    string enemyAction = enemy.randomizeEnemyActions();
    handleAttack(enemy, player, enemyAction);

    // Return true if both are still alive; false if either is defeated.
    return (player.getCurrHealth() > 0 && enemy.getCurrHealth() > 0);
}
