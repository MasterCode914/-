#ifndef ROBOT_H
#define ROBOT_H

#include "player.h"

#include <QObject>

class Robot : public Player
{
    Q_OBJECT
public:
    // 1. 父类的构造函数在子类中重写一遍
    // 2. 直接继承父类的构造函数
    using Player::Player;
    explicit Robot(QObject *parent = nullptr);

    void prepareCallLord() override;
    void preparePlayHand() override;
};

#endif // ROBOT_H
