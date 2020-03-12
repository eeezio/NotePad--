#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include "helpdialog.h"
#include <QIcon>
#include <QString>
#include <QDialog>
#include <QFont>
#include <QDebug>
#include <QByteArray>
#include <QCoreApplication>
#include "math.h"
#include <Python.h>
#include <QLineEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextDocument>
#include <QTextCodec>
#include <QTimer>
#include <QSoundEffect>
#include <thread>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    //最基本的主窗口UI初始化
    ui->setupUi(this);
    this->setWindowTitle("NotePad--");
    this->setWindowIcon(QIcon(":/image/9.ico"));
    QPixmap marisa = QPixmap("./debug/fin.png");
    int wide = ui->label->width();
    int high = ui->label->height();
    QPixmap fin_marisa = marisa.scaled(wide, high, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(fin_marisa);
    ui->label->move(670, 350);
    QIcon SaveIcon(":/image/save.png");
    QIcon OpenIcon(":/image/open.png");
    QIcon animalIcon(":/image/animal.png");
    QIcon helpIcon(":/image/help.png");
    QIcon searchIcon(":/image/search.png");
    QIcon webIcon(":/image/web.png");
    QIcon dingIcon(":/image/ding.png");
    QIcon newIcon(":/image/new.png");
    ui->saveButton->setIcon(SaveIcon);
    ui->openButton->setIcon(OpenIcon);
    ui->dingButton->setIcon(dingIcon);
    ui->tohoButton->setIcon(animalIcon);
    ui->addButton->setIcon(newIcon);
    ui->helpButton->setIcon(helpIcon);
    ui->netButton->setIcon(webIcon);
    ui->searchButton->setIcon(searchIcon);
    ui->translateButton->setIcon(QIcon(":/image/dic.png"));
    ui->openButton->setToolTip(QString::fromUtf8("打开"));
    ui->saveButton->setToolTip(QString::fromUtf8("保存"));
    ui->translateButton->setToolTip(QString::fromUtf8("翻译"));
    ui->dingButton->setToolTip(QString::fromUtf8("提醒"));
    ui->tohoButton->setToolTip(QString::fromUtf8("看板娘"));
    ui->helpButton->setToolTip(QString::fromUtf8("帮助"));
    ui->netButton->setToolTip(QString::fromUtf8("网络搜索"));
    ui->addButton->setToolTip(QString::fromUtf8("新建文件"));
    ui->searchButton->setToolTip(QString::fromUtf8("查找和替换"));
    //以下是关键的逻辑部分，使用connect链接信号和槽，这里大部分槽函数使用lambda表达式实现。
    connect(ui->dingButton, &QPushButton::clicked, [=]() {
        //新建提醒对话框，以及一些初始化布局工作
        Dlg = new QDialog(this);
        Dlg->setWindowTitle(tr("设置提醒时间"));
        QWidget *text = new QWidget(this);
        QLabel *hourText = new QLabel("小时", text);
        QLabel *minText = new QLabel("分钟后提醒", text);
        LineEdit1 = new QLineEdit(text);
        LineEdit2 = new QLineEdit(text);
        QWidget *buttonArea = new QWidget(this);
        QPushButton *btn = new QPushButton(tr("确定"), buttonArea);
        QPushButton *btn2 = new QPushButton(tr("取消"), buttonArea);
        QHBoxLayout *layout = new QHBoxLayout(text);
        layout->addWidget(LineEdit1);
        layout->addWidget(hourText);
        layout->addWidget(LineEdit2);
        layout->addWidget(minText);
        QHBoxLayout *layout2 = new QHBoxLayout(buttonArea);
        layout2->addWidget(btn);
        layout2->addWidget(btn2);
        QGridLayout *layout3 = new QGridLayout(Dlg);
        layout3->addWidget(text);
        layout3->addWidget(buttonArea);
        Dlg->show();
        //当点击确定或取消时，设置相应的的逻辑
        connect(btn, &QPushButton::clicked, [=]() {
            int hour = LineEdit1->text().toInt();
            int minute = LineEdit2->text().toInt();
            int total = 3600 * hour + 60 * minute;
            Dlg->close();
            this->Bell = QFileDialog::getOpenFileName(this, "请选择提醒文本", "C:\\Users\\saber\\Desktop");
            this->shock1 = new QTimer(this);
            this->shock1->start(total * 1000);
            //到时间后，打开对应的文本
            connect(this->shock1, &QTimer::timeout, [=]() {
                QSoundEffect *player = new QSoundEffect;
                player->setSource(QUrl::fromLocalFile("C:\\Users\\saber\\Desktop\\untitled\\ding.wav"));
                player->play();
                MainWindow *sub = new MainWindow();
                sub->show();
                QTextCodec *codec = QTextCodec::codecForName("gbk");
                QFile file(this->Bell);
                file.open(QIODevice::ReadWrite);
                QByteArray array;
                while (!file.atEnd())
                {
                    array += file.readLine(); //按行读
                }
                sub->ui->widget_2->editor->setText(codec->toUnicode(array));
                file.close();
                this->shock1->stop();
            });
        });
        connect(btn2, &QPushButton::clicked, [=]() {
            Dlg->close();
        });
    });
    //新建功能的实现
    connect(ui->addButton, &QPushButton::clicked, [=]() {
        MainWindow *td = new MainWindow();
        td->show();
    });
    //打开文件功能的实现
    connect(ui->openButton, &QPushButton::clicked, [=]() {
        QTextCodec *codec = QTextCodec::codecForName("gbk");
        this->Path = QFileDialog::getOpenFileName(this, "打开文件", "C:\\Users\\saber\\Desktop");
        if (this->Path == "")
            return;
        QFile file(this->Path);
        file.open(QIODevice::ReadWrite);
        QByteArray array;
        while (!file.atEnd())
        {
            array += file.readLine(); //按行读
        }
        ui->widget_2->editor->setText(codec->toUnicode(array));
        file.close();
    });
    //保存文件功能的实现
    connect(ui->saveButton, &QPushButton::clicked, [=]() {
        if (this->Path == "")
        {
            QString fileName = QFileDialog::getSaveFileName(this,
                                                            tr("保存文件"),
                                                            "C:\\Users\\saber\\Desktop",
                                                            tr("new file(*.txt)"));
            this->Path = fileName;
            QFile file(fileName);
            file.open(QIODevice::ReadWrite | QFile::Truncate);
            QTextStream stream(&file);
            stream << this->ui->widget_2->editor->text().toUtf8();
            stream.flush();
            file.close();
        }
        else
        {
            QFile file(this->Path);
            file.open(QIODevice::ReadWrite | QFile::Truncate);
            QTextStream stream(&file);
            stream << this->ui->widget_2->editor->text().toUtf8();
            stream.flush();
            file.close();
        }
    });
    //网络搜索功能的实现
    connect(ui->netButton, &mybutton::clicked, [=]() {
        //将获取的qstring转为char*供py脚本调用
       if (ui->widget_2->editor->selectedText()=="") return;

       QString scriptPath="sys.path.append('"+ QDir::currentPath()+"/debug/')";
       auto lamThread=[=](){
           Py_Initialize();
           PyRun_SimpleString("import sys");
           char*  ch;
           QByteArray ba = scriptPath.toLatin1();
           ch=ba.data();
           PyRun_SimpleString(ch);
           //导入py模块,注意，脚本名称不能为test。。。
           PyObject *pModule = PyImport_ImportModule("websearch");
           PyObject *pFun_show = PyObject_GetAttrString(pModule, "hello");
           //设置传入参数个数
           PyObject *args = PyTuple_New(1);
           //如果想传入string参数，则在C++中的数据类型应为char*
             char *test = ui->widget_2->editor->selectedText().toUtf8().data();
           PyTuple_SetItem(args, 0, Py_BuildValue("s", test));
           PyEval_CallObject(pFun_show, args);
           Py_Finalize();
       };
       std::thread t(lamThread);
       t.detach();
    });
    //查找与替换功能的实现
    connect(ui->searchButton, &mybutton::clicked, [=]() {
        //UI初始化
        Dlg = new QDialog(this);
        Dlg->setWindowTitle(tr("查找与替换"));
        LineEdit1 = new QLineEdit(tr("查找"), Dlg);
        LineEdit2 = new QLineEdit(tr("替换"), Dlg);
        QPushButton *btnSearchNext = new QPushButton(tr("查找下一个"), Dlg);
        QPushButton *btnSearchLast = new QPushButton(tr("查找上一个"), Dlg);
        QPushButton *btnReaplace = new QPushButton(tr("替换"), Dlg);
        QVBoxLayout *layout = new QVBoxLayout(Dlg);
        layout->addWidget(LineEdit1);
        layout->addWidget(LineEdit2);
        layout->addWidget(btnSearchNext);
        layout->addWidget(btnSearchLast);
        layout->addWidget(btnReaplace);
        Dlg->show();
        //点击按钮时调用对应的槽函数
        connect(btnSearchNext, SIGNAL(clicked()), this, SLOT(showFindText_down()));
        connect(btnReaplace, SIGNAL(clicked()), this, SLOT(ReplaceText()));
        connect(btnSearchLast, SIGNAL(clicked()), this, SLOT(showFindText_up()));
    });
    //翻译功能的实现
    connect(ui->translateButton, &mybutton::clicked, [=]() {
        //如果未选中文本，不调用py脚本
        if (ui->widget_2->editor->selectedText() == "")
            return;
        char *test = ui->widget_2->editor->selectedText().toUtf8().data();
        Py_Initialize();
        PyObject *pModule = PyImport_ImportModule("translator");
        PyObject *pFun_show = PyObject_GetAttrString(pModule, "hello");
        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, Py_BuildValue("s", test));
        PyObject *pReturn = PyEval_CallObject(pFun_show, args);
        Py_Finalize();
        char *szBuffer = NULL;
        PyArg_Parse(pReturn, "s", &szBuffer); //该变量用于接收py脚本返回值
        myDialog Translator(this, szBuffer);
        Translator.exec();
    });
    //看板娘功能实现
    connect(ui->tohoButton, &QPushButton::clicked, [=]() {
        QString tohoName = QFileDialog::getOpenFileName(this, "选择看板娘", "C:\\Users\\saber\\Desktop\\NotePad--\\theme");
        //未选择文件则返回
        if (tohoName == "")
            return;
        //替换原看板娘
        QFile finFile(QDir::currentPath()+"/debug/fin.png");
        finFile.remove();
        QFile tempFile(tohoName);
        tempFile.copy(tohoName,QDir::currentPath()+"/debug/fin.png");
        QPixmap toho = QPixmap(tohoName);
        int wide = this->ui->label->width();
        int high = this->ui->label->height();
        QPixmap fin_toho = toho.scaled(wide, high, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        //刷新看板娘
        this->ui->label->setPixmap(toho);
        this->ui->label->move(670, 350);
        int width = this->frameGeometry().width();
        int tall = this->frameGeometry().height();
        this->resize(width, tall);
    });
    connect(ui->helpButton, &QPushButton::clicked, [=]() {
        helpDialog *help = new helpDialog(this);
        help->show();
    });
}
//以下代码功能见头文件
void MainWindow::resizeEvent(QResizeEvent *sizeEvent)
{
    int width = this->frameGeometry().width();
    int high = this->frameGeometry().height();
    this->ui->label->move(width - 140, high - 270);
}
void MainWindow::showFindText_down()
{
    QString str = LineEdit1->text();
    if (!ui->widget_2->editor->findFirst(str, 1, 1, 1, 1))
    {
        QMessageBox::warning(this, tr("查找"),
                             tr("找不到%1").arg(str));
    }
}
void MainWindow::showFindText_up()
{
    QString str = LineEdit1->text();
    int line, col;
    ui->widget_2->editor->getCursorPosition(&line, &col);
    qDebug() << line << col;
    ui->widget_2->editor->setCursorPosition(line, col - 1);
    qDebug() << line << col;
    if (!ui->widget_2->editor->findFirst(str, 1, 1, 1, 1, 0))
    {
        QMessageBox::warning(this, tr("查找"),
                             tr("找不到%1").arg(str));
    }
}
void MainWindow::ReplaceText()
{
    QString str = LineEdit2->text();
    ui->widget_2->editor->replace(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}
