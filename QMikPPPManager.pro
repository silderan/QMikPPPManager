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
    QConfigData.cpp \
    DlgConfiguracion.cpp \
    DlgNuevoUsuario.cpp \
    QRegistro.cpp \
	DlgExportar.cpp \
	DlgPortScan.cpp \
    DlgCnfgConnect.cpp \
    IPv4Range.cpp \
    QIPv4RangeComboBox.cpp \
    QStaticIPComboBox.cpp \
    ConnectInfo.cpp \
    ClientProfile.cpp \
    DlgLookConfig.cpp \
    TableCellLook.cpp \
    DlgRouterUsers.cpp \
    ROSAPIUser.cpp \
    ROSAPIUserGroup.cpp \
    ROSDataBasics.cpp \
    ROSMultiConnectorManager.cpp

HEADERS  += QMikPPPManager.h \
    Comm.h \
    QIniFile.h \
    QMD5.h \
    QSentences.h \
    QSecretData.h \
    QConfigData.h \
    DlgConfiguracion.h \
    DlgNuevoUsuario.h \
    QRegistro.h \
	DlgExportar.h \
	DlgPortScan.h \
    DlgCnfgConnect.h \
    IPv4Range.h \
    QIPv4RangeComboBox.h \
    QStaticIPComboBox.h \
    ConnectInfo.h \
    ClientProfile.h \
    DlgLookConfig.h \
    TableCellLook.h \
    DlgRouterUsers.h \
    ROSAPIUser.h \
    ROSAPIUserGroup.h \
    ROSDataBasics.h \
    ROSMultiConnectorManager.h

FORMS    += QMikPPPManager.ui \
    DlgConfiguracion.ui \
	DlgNuevoUsuario.ui \
	DlgExportar.ui \
	DlgPortScan.ui \
    DlgCnfgConnect.ui \
    DlgLookConfig.ui \
    DlgRouterUsers.ui

DISTFILES += \
    ToDo.txt

RESOURCES += \
    iconos.qrc
