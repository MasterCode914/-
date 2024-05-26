#include "mybutton.h"

#include <QMouseEvent>
#include <QPainter>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    m_norma = normal;
    m_horver = hover;
    m_pressed = pressed;
    m_pixmap.load(m_norma);

    // 每次都需要更新图片才能自动调用paintEvent绘图显示
    update();
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        // 鼠标左键按下
        m_pixmap.load(m_pressed);
        update();
    }
    // 直接使用父类的函数发出按下clicked信号
    QPushButton::mousePressEvent(ev);
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        // 鼠标左键离开图片恢复正常状态
        m_pixmap.load(m_norma);
        update();
    }
    QPushButton::mousePressEvent(ev);
}

void MyButton::enterEvent(QEvent *ev)
{
    m_pixmap.load(m_horver);
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    m_pixmap.load(m_norma);
    update();
}

// 窗口被刷新时被调用
void MyButton::paintEvent(QPaintEvent *)
{
    // 绘图可以使用QPainter类
    QPainter p(this);
    p.drawPixmap(rect(), m_pixmap);
}


