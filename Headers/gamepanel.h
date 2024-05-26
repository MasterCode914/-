#ifndef GAMEPANEL_H
#define GAMEPANEL_H

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

protected:
    void paintEvent(QPaintEvent* ev);           // 重写父类函数绘制图像
private:
    Ui::GamePanel *ui;
    QPixmap m_bkImage;      // 背景图片
};
#endif // GAMEPANEL_H
