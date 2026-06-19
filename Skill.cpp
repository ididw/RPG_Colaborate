#include "BattleManager.h"
#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

namespace RPG_Colaborate
{
    //constructors
    Skill::Skill(string theName, string theType, int theDamage, int theMpCost)
    : name(theName), type(theType), damage(theDamage), mpCost(theMpCost) {}

    Skill::~Skill(){}

    //getters
    string Skill::getName() const { return name; }
    string Skill::getType() const { return type; }
    int Skill::getDamage() const { return damage; }
    int Skill::getMpCost() const { return mpCost; }

    //setters
    void Skill::setName(string newName) { name = newName; }
    void Skill::setType(string newType) { name = newType; }
    void Skill::setDamage(int newDamage) { damage = newDamage; }
    void Skill::setMpCost(int newMpCost) { mpCost = newMpCost; }

    //function
    // 使用技能(已調整)
    // 讓技能主導施法程序
    void Skill::use(Player& user, int targetIndex, vector<Player*> players, vector<Monster*> monsters)
    {
        // cout<<"Use \""<<name<<"\" cost "<<mpCost<<" MP"<<endl;
        
        cout << user.getName() << " casts a skill: [" << name << "]!" << endl;
        damage = multiplier * user.getAttackPower();

        // 技能有傷害:依照類型進行索敵
        if (isDamage == DAMAGE) {
            switch (targetType)
            {
            case SINGLE:
                monsters[targetIndex]->takeDamage(damage);
                break;
            case SPREAD:
                monsters[targetIndex]->takeDamage(damage);
                int leftTargetIndex = targetIndex - 1;
                while (leftTargetIndex >= 0 &&
                    (monsters[leftTargetIndex] == nullptr || !monsters[leftTargetIndex]->isAlive())) {
                    leftTargetIndex--;
                }
                if (leftTargetIndex > 0) {
                    monsters[leftTargetIndex]->takeDamage(0.5 * damage);
                }
                break;

                int rightTargetIndex = targetIndex + 1;
                while (leftTargetIndex < monsters.size() &&
                    (monsters[rightTargetIndex] == nullptr || !monsters[rightTargetIndex]->isAlive())) {
                    rightTargetIndex++;
                }
                if (rightTargetIndex > 0) {
                    monsters[rightTargetIndex]->takeDamage(0.5 * damage);
                }
                break;
            case AOE:
                for (int i = 0; i < monsters.size(); i++) {
                    if (monsters[i] != nullptr && monsters[i]->isAlive()) {
                        monsters[i]->takeDamage(damage);
                    }
                }
                break;
            default:
                break;
            }
        }

        if (isStatic == STATIC) {
            if (targetType == OWN) {
                user.takeEffect(effectType);
            }
        }

        // 技能有對隊友增益
        if (isBuff == BUFF) {
            switch (targetType)
            {
            case OWN:
                user.takeEffect(effectType);
                break;
            case TEAM:
                for (int i = 0; i < players.size(); i++) {
                    if (players[i]->isAlive()) {
                        players[i]->takeEffect(effectType);
                    }
                }
            default:
                break;
            }
        }

        // 技能有減益敵人
        if (isDebuff == DEBUFF) {
            switch (targetType)
            {
            case SINGLE:
                monsters[targetIndex]->takeEffect(effectType);
                break;
            case SPREAD:
                monsters[targetIndex]->takeEffect(effectType);
                int leftTargetIndex = targetIndex - 1;
                while (leftTargetIndex >= 0 &&
                    (monsters[leftTargetIndex] == nullptr || !monsters[leftTargetIndex]->isAlive())) {
                    leftTargetIndex--;
                }
                if (leftTargetIndex > 0) {
                    monsters[leftTargetIndex]->takeEffect(effectType);
                }
                break;

                int rightTargetIndex = targetIndex + 1;
                while (leftTargetIndex < monsters.size() &&
                    (monsters[rightTargetIndex] == nullptr || !monsters[rightTargetIndex]->isAlive())) {
                    rightTargetIndex++;
                }
                if (rightTargetIndex > 0) {
                    monsters[rightTargetIndex]->takeEffect(effectType);
                }
                break;
            case AOE:
                for (int i = 0; i < monsters.size(); i++) {
                    if (monsters[i] != nullptr && monsters[i]->isAlive()) {
                        monsters[i]->takeEffect(effectType);
                    }
                }
                break;
            default:
                break;
            }
        }

        // 技能有治療
        if (isHeal == HEAL) {
            switch (targetType)
            {
            case OWN:
                user.heal(0.01 * healPercent * user.getMaxHp());
                break;
            case TEAM:
                for (int i = 0; i < players.size(); i++) {
                    if (players[i]->isAlive()) {
                        players[i]->heal(0.01 * healPercent * user.getMaxHp());
                    }
                }
            default:
                break;
            }
        }

        // 技能有召喚
        if (isSpawn == SPAWN) {
            // 增加召喚物
        }

        // 技能有復活
        if (isRevive == REVIVE) {
            int reviveTarget = 0;
            do
            {
                reviveTarget = rand() % players.size();
            } while (players[reviveTarget]->isAlive());
            players[reviveTarget]->setHp(players[reviveTarget]->getMaxHp());
            players[reviveTarget]->setMp(players[reviveTarget]->getMaxMp());
        }
    }

    void Skill::showInfo() const
    {
        cout << "Skill name:" << name << endl;
        cout << "Mp Cost:" << mpCost << endl;
        cout << "Skill damage:" << damage << endl;
    }
}