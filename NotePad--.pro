#-------------------------------------------------
#
# Project created by QtCreator 2020-03-07T15:34:48
#
#-------------------------------------------------

QT       += core gui\
            multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NotePad--
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mybutton.cpp \
    mydialog.cpp \
    mywidget.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    mybutton.h \
    mydialog.h \
    mywidget.h \
    helpdialog.h

FORMS    += mainwindow.ui \
    helpdialog.ui

RESOURCES += \
    src.qrc

INCLUDEPATH +=-I C:\Users\saber\AppData\Local\Programs\Python\Python37\include
LIBS += -LC:\Users\saber\AppData\Local\Programs\Python\Python37\libs -lpython37 \
-LC:\Users\saber\Desktop\QScintilla-2.11.4\build-qscintilla-Desktop_Qt_5_12_0_MinGW_64_bit-Debug\debug -lqscintilla2_qt5d

DISTFILES += \
    test.py
