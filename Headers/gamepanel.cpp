#include "gamepanel.h"
#include "ui_gamepanel.h"
#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    ui->btnGroup->initButtons();
    ui->btnGroup->selectPanel(ButtonGroup::Start);

    // 1. 背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString path = QString(":/images/background-%1.png").arg(num + 1);
    m_bkImage.load(path);

    // 2. 窗口的标题大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(2000, 1300);      // 设置窗口大小


    // 3. 实例化控制游戏类的对象

    // 4. 玩家得分（更新）

    // 5. 切割游戏图片

    // 6. 初始化游戏中的按钮组

    // 7. 初始化玩家在窗口中的上下文环境

}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    // 窗口被展示show就会调用该函数
    QPainter p(this);
    p.drawPixmap(rect(), m_bkImage);
}

