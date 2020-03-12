#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::helpDialog)
{
    ui->setupUi(this);
    //设置标题与图标
    this->setWindowTitle("help");
    QPixmap help = QPixmap(":/image/helpDialog.png");
    ui->label->setPixmap(help);
    ui->label_2->setOpenExternalLinks(true);
    //设置超链接
    ui->label_2->setText("<a style='color: blue;' href=\"https://github.com/eeezio/NotePad--\">https://github.com/eeezio/NotePad--");
    this->resize(this->minimumSize());
}

helpDialog::~helpDialog()
{
    delete ui;
}
