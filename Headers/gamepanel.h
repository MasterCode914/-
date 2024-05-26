#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "cardpanel.h"
#include "gamecontrol.h"
#include <QMap>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    // 初始化游戏控制类信息
    void gameControlInit();

    // 更新分数面板的分数
    void updatePlayerScore();

    // 切割并存储图片
    void initCardMap();
    // 剪裁图片
    void cropImage(QPixmap& pix, int x, int y, Card& c);


protected:
    void paintEvent(QPaintEvent* ev);           // 重写父类函数绘制图像
private:
    Ui::GamePanel *ui;
    QPixmap m_bkImage;      // 背景图片
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;
    QSize m_cardSize;
    QMap<Card, CardPanel*> m_cardMap;
    QPixmap m_cardBackImg;
};
#endif // GAMEPANEL_H
