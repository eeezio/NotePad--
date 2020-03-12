#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QPushButton>

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    mybutton(QWidget *parent = 0);
    //重写如下两个方法用于按钮悬停时的缩放特效
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MYBUTTON_H
