#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
//用于实现翻译对话框
class myDialog : public QMessageBox
{
public:
    myDialog(QWidget *parent, char *test);
};

#endif // MYDIALOG_H
