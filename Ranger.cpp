#include "Ranger.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using std::cout;
using std::endl;

namespace RPG_Colaborate {
    // Constructors
    Ranger::Ranger()
    : Player(), criticalRate(20), criticalEffect(150), multiShotTurns(0), decoyHp(0)
    {
        job = "Ranger";
        skillbox[0] = new Skill("連續射擊", "Buff", 0, 40);
        skillbox[1] = new Skill("假人操術", "Hide", 0, 50);
        skillbox[2] = new Skill("萬箭齊發", "Damage", attackPower, 80);

        //  初始化技能冷卻狀態
        for(int i = 0; i < 3; ++i) {
            currentCD[i] = 0; // 初始 CD 皆為 0 (可直接使用)
        }
        maxCD[0] = 4; 
        maxCD[1] = 3; 
        maxCD[2] = 6; 
    }

    Ranger::Ranger(string theName, int theMaxHp, int theMaxMp, int theAttackPower, int theDefense)
    : Player(theName, theMaxHp, theMaxMp, theAttackPower, theDefense), 
      criticalRate(20), criticalEffect(150), multiShotTurns(0), decoyHp(0)
    {
        job = "Ranger";
        skillbox[0] = new Skill("連續射擊", "Buff", 0, 40);
        skillbox[1] = new Skill("假人操術", "Hide", 0, 50);
        skillbox[2] = new Skill("萬箭齊發", "Damage", attackPower, 80);

        //  初始化技能冷卻狀態
        for(int i = 0; i < 3; ++i) {
            currentCD[i] = 0; 
        }
        maxCD[0] = 4; 
        maxCD[1] = 3; 
        maxCD[2] = 6; 
    }

    // Getters & Setters 
    int Ranger::getCriticalRate() const { return criticalRate; }
    int Ranger::getCriticalEffect() const { return criticalEffect; }
    int Ranger::getMultiShotTurns() const { return multiShotTurns; }
    int Ranger::getDecoyHp() const { return decoyHp; }
    void Ranger::setCriticalRate(int newRate) { criticalRate = newRate; }
    void Ranger::setCriticalEffect(int newEffect) { criticalEffect = newEffect; }

    // 覆寫普攻邏輯
    void Ranger::attack(Monster& target) {
        bool isBoss = (target.getName().find("Boss") != string::npos);
        double multiplier = isBoss ? 1.5 : 1.0;
        int finalDamage = round(attackPower * multiplier);
        int shots = (multiShotTurns > 0) ? 3 : 1; 

        if (isBoss) {
            cout << " [Ranger Passive] Locked onto Boss! Damage increased by 50%!" << endl;
        }

        for (int i = 0; i < shots; ++i) {
            cout << name << " shoots an arrow at " << target.getName() << "!" << endl;
            target.takeDamage(finalDamage);
            if (!target.isAlive()) break; 
        }
    }

    // 覆寫受傷邏輯 (假人機制)
    void Ranger::takeDamage(int damage) {
        if (decoyHp > 0) {
            cout << "🪵 [Decoy] The decoy takes the hit!" << endl;
            decoyHp -= damage;
            if (decoyHp <= 0) {
                decoyHp = 0;
                cout << "🪵 The decoy has been destroyed!" << endl;
            }
        } else {
            Player::takeDamage(damage);
        }
    }

    // 遊俠的技能邏輯 
    bool Ranger::useSkill(int skillNumber, Monster& target, std::vector<Monster*>& allMonsters) {
        if (skillNumber < 1 || skillNumber > 3) {
            cout << "The skill does not exist." << endl;
            return false;
        }

        int skillIndex = skillNumber - 1;
        Skill* usedSkill = skillbox[skillIndex];

        //  檢查是否在冷卻中
        if (currentCD[skillIndex] > 0) {
            cout << " Skill [" << usedSkill->getName() << "] is on cooldown! (" 
                 << currentCD[skillIndex] << " turns remaining)" << endl;
            return false; // 施放失敗，讓玩家重新選擇
        }

        // 檢查魔力
        if (!consumeMp(usedSkill->getMpCost())) {
            return false; 
        }

        cout << name << " casts a skill: [" << usedSkill->getName() << "]!" << endl;

        // 執行技能效果
        if (skillNumber == 1) { 
            multiShotTurns = 2; 
            cout << " [Buff] Basic attacks become Triple Shot for 2 turns!" << endl;
            attack(target); 
        } 
        else if (skillNumber == 2) { 
            decoyHp = hp; 
            cout << "🪵 [Hide] Summoned a Decoy with " << decoyHp << " HP to absorb incoming damage!" << endl;
        } 
        else if (skillNumber == 3) { 
            cout << " [Arrow Rain] Unleashing a barrage of arrows!" << endl;
            std::vector<Monster*> aliveMonsters;
            for (auto m : allMonsters) {
                if (m != nullptr && m->isAlive()) {
                    aliveMonsters.push_back(m);
                }
            }

            if (!aliveMonsters.empty()) {
                for (int i = 0; i < 10; ++i) {
                    int randomIndex = rand() % aliveMonsters.size();
                    Monster* randomTarget = aliveMonsters[randomIndex];
                    bool isCrit = (rand() % 100 < criticalRate);
                    int arrowDamage = attackPower;
                    if (isCrit) {
                        arrowDamage = arrowDamage * criticalEffect / 100;
                        cout << " Critical Hit! ";
                    }
                    cout << "Arrow hits " << randomTarget->getName() << "!" << endl;
                    randomTarget->takeDamage(arrowDamage);
                }
            } else {
                cout << "But there are no enemies left!" << endl;
            }
        }

        // 技能成功施放後，進入冷卻狀態
        currentCD[skillIndex] = maxCD[skillIndex];
        return true;
    }

    // 回合結束結算狀態 (包含 CD 減少)
    void Ranger::updateTurnStatus() {
        // 1. 減少連續射擊的 Buff 回合
        if (multiShotTurns > 0) {
            multiShotTurns--;
            if (multiShotTurns == 0) {
                cout << " [Buff Faded] Triple Shot effect has worn off." << endl;
            }
        }

        // 2. 減少所有技能的冷卻時間
        for (int i = 0; i < 3; ++i) {
            if (currentCD[i] > 0) {
                currentCD[i]--;
            }
        }
    }
}
