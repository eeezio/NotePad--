#include "mywidget.h"
#include <QVBoxLayout>
//QsciScintilla作为QWidget的控件，需要添加该控件的头文件
#include <Qsci/qsciscintilla.h>
//以python语法作为例子，该语法分析器的头文件
#include <Qsci/qscilexercpp.h>
//设置代码提示功能，依靠QsciAPIs类实现
#include <Qsci/qsciapis.h>
mywidget::mywidget(QWidget *parent) : QWidget(parent)
{
  editor = new QsciScintilla(this);

  //设置语法
  QsciLexerCPP *textLexer = new QsciLexerCPP(this);
  editor->setLexer(textLexer); //给QsciScintilla设置词法分析器
  //行号提示
  editor->setMarginType(0, QsciScintilla::NumberMargin); //设置编号为0的页边显示行号。
  editor->setMarginLineNumbers(0, true);                 //对该页边启用行号
  editor->setMarginWidth(0, 20);                         //边宽度
  editor->setAutoIndent(true);
  //代码提示
  apis = new QsciAPIs(textLexer);
  apis->add(QString("int"));
  apis->add(QString("using"));
  apis->add(QString("string"));
  apis->add(QString("namespace"));
  apis->add(QString("return"));
  apis->add(QString("long"));
  apis->add(QString("char"));
  apis->add(QString("double"));
  apis->add(QString("float"));
  apis->add(QString("struct"));
  apis->add(QString("class"));
  apis->add(QString("publiv"));
  apis->add(QString("private"));
  apis->add(QString("iostream"));
  apis->add(QString("include"));
  apis->prepare();

  editor->setAutoCompletionSource(QsciScintilla::AcsAll); //设置源，自动补全所有地方出现的
  editor->setAutoCompletionCaseSensitivity(true);         //设置自动补全大小写敏感
  editor->setAutoCompletionThreshold(1);                  //设置每输入一个字符就会出现自动补全的提示
  pLayout = new QVBoxLayout(this);
  pLayout->addWidget(editor);
  pLayout->setContentsMargins(0, 0, 0, 0);
  textLexer->setFont(tr("Sarasa Term Slab SC"), -1);
  textLexer->setPaper(QColor(255, 246, 201));
}
