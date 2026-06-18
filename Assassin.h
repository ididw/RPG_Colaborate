#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Player.h"
#include "Skill.h"
#include "Monster.h"
#include <vector>
using std::vector;

namespace RPG_Colaborate {
    class Assassin : public Player {
    private:
        int criticalRate;
        int criticalEffect;
        int turnCounter; // Tracks rounds for the passive skill
    public:
        Assassin();
        Assassin(string theName, int theMaxHp, int theMaxMp, int theAttackPower, int theDefense);

        // getters
        // 待寫
        int getCriticalRate() const;
        int getCriticalEffect() const;
        int getTurnCounter() const;

        // setters
        // 待寫
        void setCriticalRate(int newRate);
        void setCriticalEffect(int newEffect);

        // Call this at the end of every turn
        void executeTurnActions(vector<Monster*>& monsterList);
    };
}

#endif