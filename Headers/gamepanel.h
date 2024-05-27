#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "cardpanel.h"
#include "gamecontrol.h"
#include <QMap>

#include <QLabel>
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

    // 初始化游戏中的按钮组
    void initButtonGroup();

    // 初始化游戏中的上下文环境
    void initPlayerContext();

    // 初始化游戏场景：发牌，底牌
    void initGameScene();


protected:
    void paintEvent(QPaintEvent* ev);           // 重写父类函数绘制图像
private:
    enum CardAlign {
        Horizontal,
        Vertical
    };
    // 保存上下文环境信息
    struct PlayerContext
    {
        // 1. 玩家扑克牌的显示区域
        QRect cardRect;
        // 2. 出牌的区域
        QRect playHandRect;
        // 3. 扑克牌的对齐方式（水平/垂直）
        CardAlign align;
        // 4. 扑克牌显示正面还是背面
        bool isFrontSide;
        // 5. 游戏过程中的提示信息，例如：不出
        QLabel* info;
        // 6. 玩家的头像
        QLabel* roleImg;
        // 7. 玩家刚打出的牌
        Cards lastCards;
    };


    Ui::GamePanel *ui;
    QPixmap m_bkImage;      // 背景图片
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;
    QMap<Card, CardPanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImg;
    QMap<Player*, PlayerContext> m_contextMap;
    CardPanel* m_baseCard;      // 发牌区
    CardPanel* m_moveCard;      // 移动发牌
    QVector<CardPanel*> m_last3Card;
    QPoint m_baseCardPos;       // 发牌的位置

};
#endif // GAMEPANEL_H


