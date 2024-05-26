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
    gameControlInit();

    // 4. 玩家得分（更新）
    updatePlayerScore();

    // 5. 切割游戏图片
    initCardMap();

    // 6. 初始化游戏中的按钮组

    // 7. 初始化玩家在窗口中的上下文环境

}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::gameControlInit()
{
    m_gameCtl = new GameControl(this);
    m_gameCtl->playInit();
    // 得到三个玩家的实例对象
    Robot* leftRobot = m_gameCtl->getLeftRobot();
    Robot* rightRobot = m_gameCtl->getRightRobot();
    UserPlayer* user = m_gameCtl->getUserPlayer();
    // 存储的顺序：左侧机器人  右侧机器人   玩家
    m_playerList << leftRobot << rightRobot << user;

}

void GamePanel::updatePlayerScore()
{
    ui->scorePanel->setScores(
                m_playerList[0]->getScore(),
            m_playerList[1]->getScore(),
            m_playerList[2]->getScore());
}

void GamePanel::initCardMap()
{
    // 1. 加载需要剪裁的大图
    QPixmap pixmap(":/images/card.png");
    // 2. 计算每张卡牌的大小
    m_cardSize.setWidth(pixmap.width() / 13);
    m_cardSize.setHeight(pixmap.height() / 5);

    // 3. 背景图（位于大图最后面）
    // pixmap的copy可以实现对图片的剪裁并返回pixmap
    m_cardBackImg = pixmap.copy(2 * m_cardSize.width(), 4 * m_cardSize.height(),
                                m_cardSize.width(), m_cardSize.height());

    // 4. 剪裁正常花色卡牌添加到容器中
    for (int i= 0, suit = Card::Suite_Begin + 1; suit < Card::Suite_End; ++suit, ++i) {
        for (int j = 0, pt = Card::Card_Begin + 1; pt < Card::Card_Begin; ++pt, ++j) {
            Card card((Card::CardPoint)pt, (Card::CardSuit)suit);
            cropImage(pixmap, j * m_cardSize.width(), i * m_cardSize.height(), card);
        }
    }

    // 大小王
    Card c;
    c.setPoint(Card::Card_SJ);
    c.setSuit(Card::Suite_Begin);
    cropImage(pixmap, 0, 4 * m_cardSize.height(), c);

    c.setPoint(Card::Card_BJ);
    cropImage(pixmap, m_cardSize.width(), 4 * m_cardSize.height(), c);

}

void GamePanel::cropImage(QPixmap &pix, int x, int y, Card &c)
{
    QPixmap sub = pix.copy(x, y, m_cardSize.width(), m_cardSize.height());
    CardPanel* panel = new CardPanel(this);
    panel->setCard(c);      // 设置卡牌
    panel->setImage(sub, m_cardBackImg);        // 设置前景图和背景图
    panel->hide();          // 暂时需要隐藏卡牌窗口
    m_cardMap.insert(c, panel);
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    // 窗口被展示show就会调用该函数
    QPainter p(this);
    p.drawPixmap(rect(), m_bkImage);
}

