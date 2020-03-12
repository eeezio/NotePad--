#include "mybutton.h"
#include <QDebug>
#include <QSize>
mybutton::mybutton(QWidget *parent) : QPushButton(parent)
{
    setMouseTracking(true);
    this->setFlat(true);
}
//如下两个函数是设置鼠标悬停时按钮的放大和缩小
void mybutton::enterEvent(QEvent *event)
{
    this->setIconSize(QSize(40, 40));
}
void mybutton::leaveEvent(QEvent *event)
{
    this->setIconSize(QSize(32, 32));
}
