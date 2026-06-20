# RPG_Colaborate
程式設計實習期末專案

重大通知:
部分類別程式碼結構大改，參數結構變動極大，請仔細看完

新增類別:戰場
負責管理整場戰鬥的行動，四個主類別全部引用了這個類別
主要元素:角色陣營、怪物陣營、行動回合
        輸出戰鬥面板、回合管理

.h檔內存放鎖定目標類型、治療目標類型與目前全狀態類型
enum EffectType { NONEE, LOWERDEFENSE, TAUNT, PERSEVERANCE, BURN, COLD, POISON, STRENGTH, WEAKEN, SPACEGOAT, HIDE, GOLDBULLET, COUNTERATTACK };
從左到右:
減防 嘲諷 堅毅(不死+回血) 燃燒 寒冷 毒爆 增傷 虛弱 假人 隱身 金色子彈 反擊

Player元素更新:
函式:
attack(怪物位置、怪物站位表)
useSkill(技能代號、當前索敵、玩家站位表、怪物站位表)
(新增)takeEffect(狀態)，受到狀態

Skill元素更新:
存放所有技能效果類型
變數:
targetType 目標
effectType 狀態
multiplier 傷害倍率
isDamage 有傷害
isStatic 自己進入某狀態/模式
isBuff 有增益
isDebuff 有減益
isHeal 有治療
isSpawn 有召喚
isRevive 有復活
healPercent 治療比率
hpCost 耗血率

函式:
建構子:新增了16參數的建構子，能初始化所有需用到的變數
use(使用者、當前索敵、玩家站位表、怪物站位表)

待調整/新增:
showInfo()

需求:補全其他角色