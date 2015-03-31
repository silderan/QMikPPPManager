#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T12:29:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMikPPPManager
TEMPLATE = app


SOURCES += main.cpp\
        QMikPPPManager.cpp \
    Comm.cpp \
    QIniFile.cpp \
    QMD5.cpp \
    QSentences.cpp \
    QSecretData.cpp \
    QConfigData.cpp

HEADERS  += QMikPPPManager.h \
    Comm.h \
    QIniFile.h \
    QMD5.h \
    QSentences.h \
    QSecretData.h \
    QConfigData.h

FORMS    += QMikPPPManager.ui
