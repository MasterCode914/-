#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    void setImage(QString normal, QString hover, QString pressed);

    // 鼠标按下（QAbstraceButton的虚函数）
    void mousePressEvent(QMouseEvent* ev);

    // 鼠标释放
    void mouseReleaseEvent(QMouseEvent* ev);

    // 鼠标进入
    void enterEvent(QEvent* ev);

    // 鼠标离开
    void leaveEvent(QEvent* ev);

    // 绘图
    void paintEvent(QPaintEvent *);

signals:

private:
    QString m_norma;    // 正常状态下图片
    QString m_horver;   // 鼠标悬停图片
    QString m_pressed;  // 按下之后图片
    QPixmap m_pixmap;       // 保存图片数据

};

#endif // MYBUTTON_H
