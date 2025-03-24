#-------------------------------------------------
#
# Project created by QtCreator 2025-03-22T22:34:59
#
#-------------------------------------------------

QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 123
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    mywidget.cpp \
    tcpserver.cpp

HEADERS  += MainWindow.h \
    mywidget.h \
    tcpserver.h

FORMS    += MainWindow.ui
INCLUDEPATH += /path/to/qt/include
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler)
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += \
    icon.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
