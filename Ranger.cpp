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
        // 用 new 來配置技能記憶體，避免指標未初始化
        skillbox[0] = new Skill("連續射擊", "Buff", 0, 40);
        skillbox[1] = new Skill("假人操術", "Hide", 0, 50);
        skillbox[2] = new Skill("萬箭齊發", "Damage", attackPower, 80);
    }

    Ranger::Ranger(string theName, int theMaxHp, int theMaxMp, int theAttackPower, int theDefense)
    : Player(theName, theMaxHp, theMaxMp, theAttackPower, theDefense), 
      criticalRate(20), criticalEffect(150), multiShotTurns(0), decoyHp(0)
    {
        job = "Ranger";
        // 同樣使用 new 來初始化
        skillbox[0] = new Skill("連續射擊", "Buff", 0, 40);
        skillbox[1] = new Skill("假人操術", "Hide", 0, 50);
        skillbox[2] = new Skill("萬箭齊發", "Damage", attackPower, 80);
    }

    // Getters
    int Ranger::getCriticalRate() const { return criticalRate; }
    int Ranger::getCriticalEffect() const { return criticalEffect; }
    int Ranger::getMultiShotTurns() const { return multiShotTurns; }
    int Ranger::getDecoyHp() const { return decoyHp; }

    // Setters
    void Ranger::setCriticalRate(int newRate) { criticalRate = newRate; }
    void Ranger::setCriticalEffect(int newEffect) { criticalEffect = newEffect; }

    // 覆寫普攻邏輯
    void Ranger::attack(Monster& target) {
        // 確認是否為 Boss (這邊我用名字包含 "Boss" 為判定基準
        bool isBoss = (target.getName().find("Boss") != string::npos);
        double multiplier = isBoss ? 1.5 : 1.0;

        int finalDamage = round(attackPower * multiplier);
        int shots = (multiShotTurns > 0) ? 3 : 1; // 有 Buff 就射 3 發

        if (isBoss) {
            cout << "[Ranger Passive] Locked onto Boss! Damage increased by 50%!" << endl;
        }

        for (int i = 0; i < shots; ++i) {
            cout << name << " shoots an arrow at " << target.getName() << "!" << endl;
            target.takeDamage(finalDamage);
            
            if (!target.isAlive()) {
                break; // 如果怪物死了就停止射擊
            }
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
            // 沒有假人，玩家自己扛
            Player::takeDamage(damage);
        }
    }

    // 實作遊俠的專屬技能邏輯
    bool Ranger::useSkill(int skillNumber, Monster& target, std::vector<Monster*>& allMonsters) {
        if (skillNumber < 1 || skillNumber > 3) {
            cout << "The skill does not exist." << endl;
            return false;
        }

        Skill* usedSkill = skillbox[skillNumber - 1];
        if (!consumeMp(usedSkill->getMpCost())) {
            return false; // 魔力不足
        }

        cout << name << " casts a skill: [" << usedSkill->getName() << "]!" << endl;

        // 判斷技能效果
        if (skillNumber == 1) { // 連續射擊
            multiShotTurns = 2; // 持續 2 回合
            cout << " [Buff] Basic attacks become Triple Shot for 2 turns!" << endl;
            attack(target); // 施放後立刻進行一次普攻
        } 
        else if (skillNumber == 2) { // 假人操術
            decoyHp = hp; // 假人繼承自身當前生命值 (可視平衡改為 maxHp)
            cout << "🪵 [Hide] Summoned a Decoy with " << decoyHp << " HP to absorb incoming damage!" << endl;
        } 
        else if (skillNumber == 3) { // 萬箭齊發
            cout << "[Arrow Rain] Unleashing a barrage of arrows!" << endl;
            // 找尋還活著的怪物
            std::vector<Monster*> aliveMonsters;
            for (auto m : allMonsters) {
                if (m != nullptr && m->isAlive()) {
                    aliveMonsters.push_back(m);
                }
            }

            if (!aliveMonsters.empty()) {
                // 發射 10 支箭
                for (int i = 0; i < 10; ++i) {
                    // 隨機選一個存活的目標
                    int randomIndex = rand() % aliveMonsters.size();
                    Monster* randomTarget = aliveMonsters[randomIndex];
                    
                    // 暴擊判定
                    bool isCrit = (rand() % 100 < criticalRate);
                    int arrowDamage = attackPower;
                    if (isCrit) {
                        arrowDamage = arrowDamage * criticalEffect / 100;
                        cout << "💥 Critical Hit! ";
                    }
                    cout << "Arrow hits " << randomTarget->getName() << "!" << endl;
                    randomTarget->takeDamage(arrowDamage);
                    
                    //  如果目標死了，直接結束
                }
            } else {
                cout << "But there are no enemies left!" << endl;
            }
        }
        return true;
    }

    // 回合結束結算狀態 
    void Ranger::updateTurnStatus() {
        if (multiShotTurns > 0) {
            multiShotTurns--;
            if (multiShotTurns == 0) {
                cout << " [Buff Faded] Triple Shot effect has worn off." << endl;
            }
        }
    }
}
