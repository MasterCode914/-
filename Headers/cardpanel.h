#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include "card.h"
#include "player.h"

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    // 设置图片获取函数
    // 卡牌的前景图片和背景图片
    void setImage(const QPixmap &front, const QPixmap &back);
    QPixmap getImage();

    // 扑克牌显示哪一面
    void setFrontSide(bool flag);
    bool isFrontSide();

    // 记录窗口是否被选中
    void setSelected(bool flag);
    bool isSelected();

    // 扑克牌的花色以及点数
    void setCard(const Card& card);
    Card getCard();

    // 扑克牌的所有者
    void setOwner(Player* player);
    Player* getOwner();

protected:
    void paintEvent(QPaintEvent *event);     // 这个函数没懂好像是自动触发的
    void mousePressEvent(QMouseEvent* event);       // 鼠标点击就会触发

private:
    QPixmap m_front;
    QPixmap m_back;
    bool m_isfront = true;
    bool m_isSelect = false;
    Card m_card;
    Player* m_player = nullptr;

signals:

};

#endif // CARDPANEL_H
