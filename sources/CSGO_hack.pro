QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseEntity.cpp \
    Hacks.cpp \
    Vec3.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BaseEntity.h \
    Hacks.h \
    MemManager.h \
    MemOffsets.h \
    Vec3.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RC_ICONS = and1ss.ico
VERSION = 0.1.0.0
QMAKE_PROJECT_NAME = Suck my dick
QMAKE_TARGET_COMPANY = Retard And1sS :D
QMAKE_TARGET_PRODUCT = ne Shrek GNG
QMAKE_TARGET_DESCRIPTION = Just poroflit, nothing more :D
QMAKE_TARGET_COPYRIGHT = And1sS, da - da ya :D

QMAKE_LFLAGS += -static
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
