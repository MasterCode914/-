#include "cardpanel.h"

#include <QPainter>

CardPanel::CardPanel(QWidget *parent) : QWidget(parent)
{

}

void CardPanel::setImage(const QPixmap &front, const QPixmap &back)
{
    m_front = front;
    m_back = back;

    setFixedSize(m_front.size());   // 卡牌窗口显示和图片一样的大小

    update();       // 调用update函数，paintEvent函数就自动被框架调用了
}

QPixmap CardPanel::getImage()
{
    return m_front;     // 背面都是一样的
}

void CardPanel::setFrontSide(bool flag)
{
    m_isfront = flag;
}

bool CardPanel::isFrontSide()
{
    return m_isfront;
}

void CardPanel::setSelected(bool flag)
{
    m_isSelect = flag;
}

bool CardPanel::isSelected()
{
    return m_isSelect;
}

void CardPanel::setCard(const Card &card)
{
    m_card = card;
}

Card CardPanel::getCard()
{
    return m_card;
}

void CardPanel::setOwner(Player *player)
{
    m_player = player;
}

Player *CardPanel::getOwner()
{
    return m_player;
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);   // 绘图需要使用QPainter类
    if (m_isfront) {
        p.drawPixmap(rect(), m_front);      // 绘制正面图
    } else {
        p.drawPixmap(rect(), m_back);
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{

}
