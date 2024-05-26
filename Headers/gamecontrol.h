#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "robot.h"
#include "userplayer.h"
#include "cards.h"

#include <QObject>

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = nullptr);

    // 游戏状态
    enum GameStatus {
        DispatchCard,       // 发牌
        CallingLord,        // 叫地主
        PlayingHand         // 出牌
    };

    // 玩家状态
    enum PlayerStatus {
        ThinkingForCallLoad,    // 考虑叫地主
        ThinkingForPlayHand,    // 考虑出牌
        Wining                  // 获胜
    };

    // 初始化玩家
    void playInit();

    // 获得玩家实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 得到出牌玩家和打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    // 初始化扑克牌
    void initAllCards();

    // 取出一张牌（发牌）
    Card takeOneHand();
    // 得到最后三张底牌
    Cards getSuplusCards();

    // 重置卡牌数据
    void resetCardData();

    // 准备叫地主
    void startLordCard();

    // 成为地主
    void becomeLord(Player* player);

    // 清空玩家的所有得分
    void clearPlayerScore();



signals:

private:
    Robot* m_robotLeft = nullptr;
    Robot* m_robotRight = nullptr;
    UserPlayer* m_user = nullptr;
    Player* m_currPlayer = nullptr;     // 当前玩家
    Player* m_pendPlayer = nullptr;     // 出牌玩家
    Cards m_pendCards;                  // 出牌玩家出的牌
    Cards m_allCards;                   // 所有的扑克牌


};

#endif // GAMECONTROL_H
