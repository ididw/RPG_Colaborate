#include <iostream>
#include <vector>
#include "Player.h"
#include "Skill.h"
#include "Item.h"
#include "Monster.h"
using std::vector;
using std::cin;
using std::cout;
using namespace RPG_Colaborate;

int
main()
{
    //創建四個人
    vector<Player> players;
    int role;
    for (int i = 0; i < 4; i++) {
        cout << "Choose job(Player " << i+1 << "): ";
        cin >> role;
        switch (role)
        {
        case 0:
            break;
        default:
            break;
        }
    }
    

    //創建怪物
    //戰鬥準備:
    //1.選擇職業
    //2.每人自帶一個回血與回魔道具
    //3.進入戰場，選擇一個增益

    std::vector<Monster> monsterTable;

    // 參數順序：名字, 血量, 攻擊力, 獎勵金幣, 閃避率, 防禦力, 等級(Rank)
    // 1. 小怪們 (Normal)
    monsterTable.push_back(Monster("Slime", 50, 10, 10, 0, 0, NORMAL));
    monsterTable.push_back(Monster("Goblin", 80, 10, 15, 5, 0, NORMAL));
    monsterTable.push_back(Monster("Goblin Warrior", 80, 10, 20, 5, 5, NORMAL));
    monsterTable.push_back(Monster("Skeleton", 60, 16, 25, 0, 2, NORMAL));

    // 2. 精英怪們 (Elite)
    monsterTable.push_back(Monster("Elite Goblin Warrior", 150, 18, 50, 5, 12, ELITE));
    monsterTable.push_back(Monster("Death Knight", 250, 22, 100, 0, 20, ELITE)); // 高血高防

    //戰鬥流程:
    //1.選擇施放普攻/技能，可選擇使用道具
    //2.輪流攻擊，敵人最後攻擊
    //3.擊敗該層所有敵人，進入脫戰
    //4.進入下一層，選擇一個增益
    return 0;
}