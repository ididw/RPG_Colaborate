#include <iostream>
#include <vector>
#include "Player.h"
#include "Skill.h"
#include "Item.h"
#include "Monster.h"
using namespace std;
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

    //戰鬥流程:
    //1.選擇施放普攻/技能，可選擇使用道具
    //2.輪流攻擊，敵人最後攻擊
    //3.擊敗該層所有敵人，進入脫戰
    //4.進入下一層，選擇一個增益
    return 0;
}