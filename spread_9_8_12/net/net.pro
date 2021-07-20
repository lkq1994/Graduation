#-------------------------------------------------
#
# Project created by QtCreator 2019-09-30T09:27:15
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = net
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += D:\Qt\Qt5.12.0\5.12.0\mingw73_64\include\Qwt

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    myqthread.cpp \
    analydata.cpp \
    myfft.cpp \
    bispecd.cpp \
    mycorr.cpp \
    despread.cpp

HEADERS += \
        widget.h \
    myqthread.h \
    analydata.h \
    myfft.h \
    bispecd.h \
    mycorr.h \
    despread.h

FORMS += \
        widget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += D:/Qt/Qt5.12.0/5.12.0/mingw73_64/include
DEPENDPATH += D:/Qt/Qt5.12.0/5.12.0/mingw73_64/include

win32:CONFIG(release, debug|release): LIBS += -LD:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/ -lqwtd
else:unix: LIBS += -LD:/Qt/Qt5.12.0/5.12.0/mingw73_64/lib/ -lqwt

INCLUDEPATH += D:/Qt/Qt5.12.0/5.12.0/mingw73_64/include
DEPENDPATH += D:/Qt/Qt5.12.0/5.12.0/mingw73_64/include
