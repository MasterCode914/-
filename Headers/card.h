#ifndef CARD_H
#define CARD_H

#include <QVector>



class Card
{
public:
    // 花色
    enum CardSuit
    {
      Suite_Begin,
      Diamond,
      Clud,
      Heart,
      Spande,
      Suite_End
    };

    // 点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,            // small joker
        Card_BJ,            // big joker
        Card_End
    };

    Card();
    Card(CardPoint point, CardSuit suit);

    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);
    CardPoint point() const;
    CardSuit suit() const;

private:
    CardPoint m_point;
    CardSuit m_suit;
};

using CardList = QVector<Card>;
bool lessSort(const Card& c1, const Card& c2);
bool greaterSort(const Card& c1, const Card& c2);
// 在map中使用Card作为key需要重载自定义类型的比较操作符
bool operator <(const Card& c1, const Card& c2);

// QSet里面使用自定义的类型就需要重载==
// 操作符重载（==）
bool operator == (const Card& left, const Card& right);

// 自定义哈希值的计算，只要不同的对象哈希值不同即可
// 重写全局函数
uint qHash(const Card& card);



#endif // CARD_H
