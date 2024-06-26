#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

Player::Player(QString name, QObject *parent)
{
    m_name = name;
}

void Player::setName(QString name)
{
    m_name = name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setRole(Player::Role role)
{
    m_role = role;
}

Player::Role Player::getRole()
{
    return m_role;
}

void Player::setSex(Player::Sex sex)
{
    m_sex = sex;
}

Player::Sex Player::getSex()
{
    return m_sex;
}

void Player::setDirection(Player::Direction direction)
{
    m_direction = direction;
}

Player::Direction Player::getDirection()
{
    return m_direction;
}

void Player::setType(Player::Type type)
{
    m_type = type;
}

Player::Type Player::getType()
{
    return m_type;
}

void Player::setScore(int score)
{
    m_score = score;
}

int Player::getScore()
{
    return m_score;
}

void Player::setWin(bool flag)
{
    m_isWin = flag;
}

bool Player::isWin()
{
    return m_isWin;
}

void Player::setPrevPlayer(Player *player)
{
    m_prev = player;
}

Player *Player::getPrevPlayer()
{
    return m_prev;
}

void Player::setNextPlayer(Player *player)
{
    m_next = player;
}

Player *Player::getNextPlayer()
{
    return m_next;
}

void Player::storeDispatchCard(const Card &card)
{
    m_cards.add(card);
}

void Player::storeDispatchCard(const Cards &cards)
{
    m_cards.add(cards);
}

Cards Player::getCards()
{
    return m_cards;
}

void Player::clearCards()
{
    m_cards.clear();
}

void Player::setPendingInfo(Player *player, Cards &cards)
{
    m_pendCards = cards;
    m_pendPlayer = player;
}

Player *Player::getPendPlayer()
{
    return m_pendPlayer;
}

Cards Player::getPendCards()
{
    return m_pendCards;
}

void Player::prepareCallLord()
{

}

void Player::preparePlayHand()
{

}
