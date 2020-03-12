#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
//QsciScintilla作为QWidget的控件，需要添加该控件的头文件
#include <Qsci/qsciscintilla.h>
//以python语法作为例子，该语法分析器的头文件
#include <Qsci/qscilexercpp.h>
//设置代码提示功能，依靠QsciAPIs类实现
#include <Qsci/qsciapis.h>
class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = nullptr);
    QsciScintilla *editor;
    QsciAPIs *apis;
    QVBoxLayout *pLayout;

signals:

public slots:
};

#endif // MYWIDGET_H
