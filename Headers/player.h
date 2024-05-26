#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "cards.h"

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);

    // 角色
    enum Role {
        Lord,
        Farmer
    };

    // 性别
    enum Sex {
        Man,
        Woman
    };

    // 头像的显示方位
    enum Direction {
        Left,
        Right
    };

    // 玩家类型
    enum Type {
        Robot,
        User,
        Unknow
    };

    // 名字
    void setName(QString name);
    QString getName();

    // 角色
    void setRole(Role role);
    Role getRole();

    // 性别
    void setSex(Sex sex);
    Sex getSex();

    // 头像方位
    void setDirection(Direction direction);
    Direction getDirection();

    // 玩家类型
    void setType(Type type);
    Type getType();

    // 玩家分数
    void setScore(int score);
    int getScore();

    // 游戏结果
    void setWin(bool flag);
    bool isWin();

    // 当前对象的上家/下家
    void setPrevPlayer(Player* player);
    Player* getPrevPlayer();
    void setNextPlayer(Player* player);
    Player* getNextPlayer();

    // 叫地主/抢地主
    void grabLordBet(int point);

    // 存储扑克牌（通过发牌得到)
    void storeDispatchCard(const Card& card);
    void storeDispatchCard(const Cards& cards);

    // 得到所有的牌
    Cards getCards();
    // 清空玩家手里的牌
    void clearCards();

    // 出牌
    void palyHand(const Cards& cards);

    // 存储出牌玩家和出牌玩家打出的牌
    void setPendingInfo(Player* player, Cards& cards);
    Player* getPendPlayer();
    Cards getPendCards();


    // 虚函数，子类继承定义
    // 不同玩家出牌的逻辑是不一样的
    virtual void prepareCallLord();     // 抢地主
    virtual void preparePlayHand();     // 出牌


protected:
    QString m_name;
    Role m_role;
    Sex m_sex;
    Direction m_direction;
    Type m_type;
    int m_score;
    bool m_isWin = false;
    Player* m_prev = nullptr;
    Player* m_next = nullptr;
    Cards m_cards;      // 玩家手中的牌
    Player* m_pendPlayer = nullptr;     // 记录出牌的玩家
    Cards m_pendCards;                  // 记录出牌玩家打出的牌



signals:

};

#endif // PLAYER_H
