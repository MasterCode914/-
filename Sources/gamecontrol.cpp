#include "gamecontrol.h"
#include <QRandomGenerator>
GameControl::GameControl(QObject *parent) : QObject(parent)
{

}

void GameControl::playInit()
{
    // 对象实例化
    m_robotLeft = new Robot("机器人A", this);      // 添加this可以由框架管理析构
    m_robotRight = new Robot("机器人B", this);
    m_user = new UserPlayer("我自己", this);

    // 头像显示方位
    m_robotLeft->setDirection(Player::Left);
    m_robotRight->setDirection(Player::Right);
    m_user->setDirection(Player::Right);

    // 性别
    Player::Sex sex;
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLeft->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_user->setSex(sex);

    // 出牌顺序
    // 上下家
    m_robotLeft->setPrevPlayer(m_robotRight);
    m_robotLeft->setNextPlayer(m_user);

    m_robotRight->setPrevPlayer(m_user);
    m_robotRight->setPrevPlayer(m_robotLeft);

    m_user->setPrevPlayer(m_robotLeft);
    m_user->setPrevPlayer(m_robotRight);

    // 指定当前玩家
    m_currPlayer = m_user;

}

Robot *GameControl::getLeftRobot()
{
    return m_robotLeft;
}

Robot *GameControl::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameControl::getUserPlayer()
{
    return m_user;
}

void GameControl::setCurrentPlayer(Player *player)
{
    m_currPlayer = player;
}

Player *GameControl::getCurrentPlayer()
{
    return m_currPlayer;
}

Player *GameControl::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameControl::getPendCards()
{
    return m_pendCards;
}

//void GameControl::initAllCards()
//{
//    m_allCards.clear();         // 清空扑克牌
//    // 创建卡牌对象
//    for (int p = Card::Card_Begin + 1; p < Card::Card_SJ; ++p) {
//        for (int s = Card::Suite_Begin + 1; s < Card::Suite_End; ++s) {
//            Card t((Card::CardPoint)p, (Card::CardSuit)s);
//            m_allCards.add(t);
//        }
//    }
//    m_allCards.add(Card(Card::Card_SJ, Card::Suite_Begin));
//    m_allCards.add(Card(Card::Card_BJ, Card::Suite_Begin));
//}

void GameControl::initAllCards()
{
    m_allCards.clear();
    for(int p = Card::Card_Begin+1; p<Card::Card_SJ; ++p)
    {
        for(int s = Card::Suite_Begin+1; s<Card::Suite_End; ++s)
        {
            Card c((Card::CardPoint)p, (Card::CardSuit)s);
            m_allCards.add(c);
        }
    }
    m_allCards.add(Card(Card::Card_SJ, Card::Suite_Begin));
    m_allCards.add(Card(Card::Card_BJ, Card::Suite_Begin));
}

Card GameControl::takeOneHand()
{
    return m_allCards.takeRandomCard();
}

Cards GameControl::getSuplusCards()
{
    // 直接返回最后三张即可，已经发完牌了
    return m_allCards;
}

void GameControl::resetCardData()
{
    // 洗牌
    initAllCards();
    // 清空玩家所有的牌
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_user->clearCards();
    // 初始化出牌玩家和出牌玩家的牌
    m_pendCards.clear();
    m_pendPlayer = nullptr;
}

void GameControl::startLordCard()
{
    m_currPlayer->prepareCallLord();
}

void GameControl::becomeLord(Player *player)
{
    player->setRole(Player::Lord);
    player->getPrevPlayer()->setRole(Player::Farmer);
    player->getNextPlayer()->setRole(Player::Farmer);

    m_currPlayer = player;
    // 地主玩家得到最后三张底牌
    player->storeDispatchCard(getSuplusCards());
}

void GameControl::clearPlayerScore()
{
    m_user->setScore(0);
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
}
