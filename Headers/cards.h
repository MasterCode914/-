#ifndef CARDS_H
#define CARDS_H
#include "card.h"
#include <QSet>

class Cards
{
public:
    Cards();

    // 排序规则
    enum SortType {
        Asc,
        Desc,
        NoSort
    };

    // 添加扑克牌
    void add(const Card& card);
    void add(const Cards& cards);

    // 一次性插入多张扑克牌（重载<<运算符)
    Cards& operator << (const Card& card);
    Cards& operator << (const Cards& cards);

    // 删除扑克牌
    void remove(const Card& card);
    void remove(const Cards& cards);

    // 扑克牌的数量
    int cardCount();
    // 是否为空
    bool isEmpty();
    bool isEmpty() const;
    void clear();

    // 最大点数
    Card::CardPoint maxPoint();
    // 最小点数
    Card::CardPoint minPoint();
    // 指定点数牌的数量
    int pointCount(Card::CardPoint point);
    // 某张牌是否在集合中
    bool contains(const Card& card);
    bool contains(const Cards& cards);

    // 随机取出一张扑克牌（随即发牌）
    Card takeRandomCard();


    // QVector<Card>
    // Qset->QVector：使用QVector保存排序好的扑克牌
    CardList toCardList(SortType type = Desc);

private:
    QSet<Card> m_cards;
};

#endif // CARDS_H
