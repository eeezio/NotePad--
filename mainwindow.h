#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
class QLineEdit;
class QDialog;
#include <QFile>
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //重写这个方法，用于实现看板娘始终保持在编辑器左下角
    void resizeEvent(QResizeEvent *sizeEvent);
    //用于保存通过各种文件对话框获取的文件路径
    QString Path = "";
    //用于保存提醒文本的路径
    QString Bell;
public slots:
    //实现向下查找文本
    void showFindText_down();
    //实现向上查找文本
    void showFindText_up();
    //实现替换文本
    void ReplaceText();

private:
    Ui::MainWindow *ui;
    //各种对话框使用的文本框以及对话框
    QLineEdit *LineEdit1;
    QLineEdit *LineEdit2;
    QDialog *Dlg;
    //提醒功能使用的计时器
    QTimer *shock1;
};

#endif // MAINWINDOW_H
