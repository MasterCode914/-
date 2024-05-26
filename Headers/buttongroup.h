#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    // 页面序号
    enum Panel {
        Start,
        PlayCard,
        PassOrPlay,
        CallLord,
        Empty
    };

    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    // 初始化各种按钮
    void initButtons();

    // 处理page页面的切换
    void selectPanel(Panel panel, int bet = 0);

signals:        // 信号不需要定义，信号也可以绑定信号
    // 开始游戏
    void startGame();

    // 出牌
    void playHand();

    // 不出牌
    void pass();

    // 抢地主
    void betPoint(int bet);     // 指定抢地主的分数

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H
