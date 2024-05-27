#include "card.h"

Card::Card()
{

}

Card::Card(Card::CardPoint point, Card::CardSuit suit)
{
    m_point = point;
    m_suit = suit;
}

void Card::setPoint(Card::CardPoint point)
{
    m_point = point;
}

void Card::setSuit(Card::CardSuit suit)
{
    m_suit = suit;
}

Card::CardPoint Card::point() const
{
    return m_point;
}

Card::CardSuit Card::suit() const
{
    return m_suit;
}

bool lessSort(const Card &c1, const Card &c2)
{
    if (c1.point() == c2.point()) {
        return c1.suit() < c2.suit();
    } else {
        return c1.point() < c2.point();
    }
}

bool greaterSort(const Card &c1, const Card &c2)
{
    if (c1.point() == c2.point()) {
        return c1.suit() > c2.suit();
    } else {
        return c1.point() > c2.point();
    }
}

bool operator ==(const Card &left, const Card &right)
{
    return left.suit() == right.suit() && left.point() == right.point();
}

uint qHash(const Card &card)
{
    return card.point() * 10 + card.suit();
}

bool operator <(const Card &c1, const Card &c2)
{
    return lessSort(c1, c2);
}
