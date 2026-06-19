#ifndef SKILL_H
#define SKILL_H

#include "BattleManager.h"
#include <string>
using std::string;

namespace RPG_Colaborate
{
    class Player;
    class Monster;

    enum SkillType { NONE, DAMAGE, STATIC, BUFF, DEBUFF, HEAL, SPAWN, REVIVE };
    
    class Skill
    {
    private:
        string name;
        string type;
        TargetType targetType;
        HealTargetType healTargetType;
        EffectType effectType;
        SkillType isDamage;
        SkillType isStatic;
        SkillType isBuff;
        SkillType isDebuff;
        SkillType isHeal;
        SkillType isSpawn;
        SkillType isRevive;
        int damage;
        double multiplier;
        int healPercent;
        int mpCost;
        int hpCost;
    public:
        // 建構子
        Skill();
        Skill(string theName, string theType, int theDamage, int theMpCost);
        Skill(std::string theName, TargetType TType, HealTargetType HType, EffectType EType,
        SkillType isDmg, SkillType isSt, SkillType isB, SkillType isDb, SkillType isH, SkillType isSp, SkillType isRv,
        int theDamage, double theMultiplier, int theHealPercent, int theMpCost, int theHpCost);
        ~Skill();

        // Getters
        string getName() const;
        string getType() const;
        int getDamage() const;
        int getMpCost() const;

        // Setters
        void setName(string newName);
        void setType(string newType);
        void setDamage(int newDamage);
        void setMpCost(int newMpCost);

        // 用技能 嗯大概這樣
        void use(Player& user, int targetIndex, vector<Player*> players, vector<Monster*> monsters);
        void showInfo() const;
    };
}

#endif