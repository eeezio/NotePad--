#include "mydialog.h"
//在构造函数中设置显示的翻译文本
myDialog::myDialog(QWidget *parent, char *text) : QMessageBox(parent)
{
    this->setText(text);
}
