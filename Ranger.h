#ifndef RANGER_H
#define RANGER_H

#include "Player.h"
#include "Skill.h"
#include "Monster.h"
#include <vector>

namespace RPG_Colaborate {
    class Ranger : public Player {
    private:
        int criticalRate;
        int criticalEffect;
        
        // 遊俠專屬機制變數
        int multiShotTurns; // 連續射擊剩餘回合數
        int decoyHp;        // 假人血量 (大於 0 代表假人存在)

        int currentCD[3];   // 記錄 3 個技能「目前剩餘」的冷卻回合數
        int maxCD[3];       // 記錄 3 個技能的「最大」冷卻回合數

    public:
        // Constructors
        Ranger();
        Ranger(string theName, int theMaxHp, int theMaxMp, int theAttackPower, int theDefense);

        // Getters
        int getCriticalRate() const;
        int getCriticalEffect() const;
        int getMultiShotTurns() const;
        int getDecoyHp() const;

        // Setters
        void setCriticalRate(int newRate);
        void setCriticalEffect(int newEffect);

        // 遊俠機制覆寫 (Overrides)
        // 覆寫普攻：處理對 Boss 增傷 50% 以及 連續射擊 (三連射)
        void attack(int targetIndex, vector<Monster*> monsters) override;

        // 覆寫受傷：處理假人擋刀機制
        void takeDamage(int damage) override;

        // 覆寫使用技能：攔截並實作遊俠特有技能邏輯
        bool useSkill(int skillNumber, int targetIndex, vector<Player*> players, vector<Monster*> monsters) override;
        
        // 處理回合結束的狀態結算 (比如連射回合減少)
        void updateTurnStatus();
    };
}

#endif
