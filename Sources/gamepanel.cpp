#include "gamepanel.h"
#include "ui_gamepanel.h"
#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    // 1. 背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString path = QString(":/images/background-%1.png").arg(num + 1);
    m_bkImage.load(path);

    // 2. 窗口的标题大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000, 650);      // 设置窗口大小


    // 3. 实例化控制游戏类的对象
    gameControlInit();

    // 4. 玩家得分（更新）
    updatePlayerScore();

    // 5. 切割游戏图片
    initCardMap();

    // 6. 初始化游戏中的按钮组
    initButtonGroup();

    // 7. 初始化玩家在窗口中的上下文环境
    initPlayerContext();

    // 8. 扑克牌初始化场景
    // 发牌时的显示，最后三张底牌的显示
    initGameScene();
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

void GamePanel::initButtonGroup()
{
    ui->btnGroup->initButtons();
    ui->btnGroup->selectPanel(ButtonGroup::Start);

    connect(ui->btnGroup, &ButtonGroup::startGame, this, [=](){
        // 界面的初始化
        // 展示空按钮面
        ui->btnGroup->selectPanel(ButtonGroup::Empty);
        m_gameCtl->clearPlayerScore();      // 清空玩家分数
        updatePlayerScore();    // 更新玩家分数
        // 修改游戏状态->发牌
        gameStatusPrecess(GameControl::DispatchCard);
        // 播放背景音乐

    });
    connect(ui->btnGroup, &ButtonGroup::playHand, this, [=](){});
    connect(ui->btnGroup, &ButtonGroup::pass, this, [=](){});
    connect(ui->btnGroup, &ButtonGroup::betPoint, this, [=](){});
}

void GamePanel::initPlayerContext()
{
    // 1. 放置玩家扑克牌的位置
    const QRect cardsRect[] = {
        // x, y, width, height
        QRect(90, 130, 100, height() - 200),                    // 左侧机器人
        QRect(rect().right() - 190, 130, 100, height() - 200),  // 右侧机器人
        QRect(250, rect().bottom() - 120, width() - 500, 100)   // 当前玩家
    };

    // 2. 玩家出牌的区域
    const QRect playHandRect[] =
    {
        QRect(260, 150, 100, 100),                              // 左侧机器人
        QRect(rect().right() - 360, 150, 100, 100),             // 右侧机器人
        QRect(150, rect().bottom() - 290, width() - 300, 105)   // 当前玩家
    };
    // 3. 玩家头像显示的位置
    const QPoint roleImgPos[] =
    {
        QPoint(cardsRect[0].left()-80, cardsRect[0].height() / 2 + 20),     // 左侧机器人
        QPoint(cardsRect[1].right()+10, cardsRect[1].height() / 2 + 20),    // 右侧机器人
        QPoint(cardsRect[2].right()-10, cardsRect[2].top() - 10)            // 当前玩家
    };

    // 循环保存玩家和玩家上下文信息
    int index = m_playerList.indexOf(m_gameCtl->getUserPlayer());
    for (int i = 0; i < m_playerList.size(); ++i) {
        PlayerContext context;
        context.align = i == index ? Horizontal : Vertical;
        context.isFrontSide = i == index ? true : false;
        context.cardRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        // 提示信息
        context.info = new QLabel(this);
        context.info->resize(160, 98);
        context.info->hide();       // 暂时不需要显示
        // 提示信息显示到出牌区域的中心位置
        QRect rect = playHandRect[i];
        QPoint pt(rect.left() + (rect.width() - context.info->width()) / 2,
                  rect.top() + (rect.height() - context.info->height())/ 2);
        context.info->move(pt);

        // 玩家头像
        context.roleImg = new QLabel(this);
        context.roleImg->resize(84, 120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);
        m_contextMap.insert(m_playerList.at(i), context);
    }

}

void GamePanel::initGameScene()
{
    // 1. 发牌区的显示
    m_baseCard = new CardPanel(this);
    m_baseCard->setImage(m_cardBackImg, m_cardBackImg);

    // 2. 发牌过程中的移动扑克牌
    m_moveCard = new CardPanel(this);
    m_moveCard->setImage(m_cardBackImg, m_cardBackImg);

    // 3. 最后三张底牌用于窗口的显示
    for (int i = 0; i < 3; i++) {
        CardPanel* panel = new CardPanel(this);
        panel->setImage(m_cardBackImg, m_cardBackImg);
        m_last3Card.push_back(panel);
        // 宪隐藏窗口，最后再显示
        panel->hide();
    }

    // 扑克牌的位置
    m_baseCardPos = QPoint((width() - m_cardSize.width()) / 2,
                           height() / 2 - 100);
    m_baseCard->move(m_baseCardPos);
    m_moveCard->move(m_baseCardPos);

    // 底牌位置
    int base = (width() - 3 * m_cardSize.width() - 2 * 10) / 2;
    for (int i = 0; i < 3; i++) {
        m_last3Card[i]->move(base + (m_cardSize.width() + 10) * i, 20);
    }

}

void GamePanel::gameStatusPrecess(GameControl::GameStatus status)
{
    // 记录游戏状态
    m_gameStatus = status;
    // 处理游戏状态
    switch (status) {
    case GameControl::DispatchCard:
        startDispatchCard();
        break;
    case GameControl::CallingLord:
        break;
    case GameControl::PlayingHand:
        break;
    default:
        break;
    }

}

void GamePanel::startDispatchCard()
{
    // 重置每张卡牌的属性
    for (auto it = m_cardMap.begin(); it != m_cardMap.end(); it++) {
        it.value()->setSelected(false);
        it.value()->setFrontSide(true);
        it.value()->hide();
    }

    // 隐藏三张底牌
    for (int i = 0; i < m_last3Card.size(); i++) {
        m_last3Card[i]->hide();
    }

    // 重置玩家的窗口上下文信息
    int index = m_playerList.indexOf(m_gameCtl->getUserPlayer());
    for (int i = 0; i < m_playerList.size(); i++) {
        m_contextMap[m_playerList.at(i)].lastCards.clear();     // 清空最后的出牌
        m_contextMap[m_playerList.at(i)].info->hide();
        m_contextMap[m_playerList.at(i)].roleImg->hide();
        m_contextMap[m_playerList.at(i)].isFrontSide = i == index ? true : false;
    }

    // 重置所有玩家的卡牌数据
    m_gameCtl->resetCardData();

    // 显示底牌
    m_baseCard->show();

    // 隐藏按钮面板
    ui->btnGroup->selectPanel(ButtonGroup::Empty);

    // 启动定时器

    // 播放背景音乐
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    // 窗口被展示show就会调用该函数
    QPainter p(this);
    p.drawPixmap(rect(), m_bkImage);
}

