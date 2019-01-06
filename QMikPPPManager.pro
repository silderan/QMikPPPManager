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
    Utils/IPv4Range.cpp \
	Utils/ROSSpeed.cpp \
	Utils/ROSRateLimit.cpp \
	Utils/QIniFile.cpp \
    Utils/QRegistro.cpp \
    QMikPPPManager.cpp \
    ROSAPI/QMD5.cpp \
    ROSAPI/QSentences.cpp \
    ROSAPI/Comm.cpp \
    ROSData/ROSAPIUser.cpp \
    ROSData/ROSAPIUserGroup.cpp \
    ROSData/ROSDataBasics.cpp \
	ROSData/ROSPPPProfile.cpp \
	ROSData/ROSInterfaces.cpp \
	Widgets/QIPv4RangeComboBox.cpp \
    Widgets/QStaticIPComboBox.cpp \
    Widgets/QROSAPIUserTableWidget.cpp \
    Widgets/QROSAPIUserLevelComboBox.cpp \
    Widgets/QROSAPIUsersGroupTableWidget.cpp \
    Widgets/QRoutersLineEdit.cpp \
    Widgets/QROSAPIUsersGroupComboBox.cpp \
    Widgets/QTableWidgetBase.cpp \
	Widgets/QPPPProfilesTableWidget.cpp \
    ConfigData/ConnectInfo.cpp \
    ConfigData/TableCellLook.cpp \
    ConfigData/ClientProfile.cpp \
    ConfigData/QConfigData.cpp \
    QSecretData.cpp \
    DlgNuevoUsuario.cpp \
	DlgExportar.cpp \
	DlgPortScan.cpp \
    ROSMultiConnectorManager.cpp \
    ROSPPPoEManager.cpp \
    Dialogs/DlgCnfgConnect.cpp \
    Dialogs/DlgConfiguracion.cpp \
    Dialogs/DlgLookConfig.cpp \
    Dialogs/DlgROSAPIUsers.cpp \
	Dialogs/DlgROSAPIUser.cpp \
	Dialogs/DlgPPPProfiles.cpp \
    ROSDataManager/ROSInterfaceManager.cpp \
    ROSData/ROSBridgePorts.cpp \
    ROSData/ROSIPAddress.cpp

HEADERS  += QMikPPPManager.h \
    Utils/IPv4Range.h \
	Utils/ROSSpeed.h \
	Utils/ROSRateLimit.h \
	Utils/QIniFile.h \
    Utils/QRegistro.h \
    ROSAPI/QMD5.h \
    ROSAPI/QSentences.h \
    ROSAPI/Comm.h \
    ROSData/ROSAPIUser.h \
    ROSData/ROSAPIUserGroup.h \
    ROSData/ROSDataBasics.h \
	ROSData/ROSPPPProfile.h \
	ROSData/ROSInterfaces.h \
	ROSDataManager/ROSDataManagerBase.h \
	ROSDataManager/ROSAPIUserManager.h \
	ROSDataManager/ROSAPIUsersGroupManager.h \
	ROSDataManager/ROSPPPProfileManager.h \
	ConfigData/ConnectInfo.h \
    ConfigData/TableCellLook.h \
    ConfigData/ClientProfile.h \
    ConfigData/QConfigData.h \
    Widgets/QIPv4RangeComboBox.h \
    Widgets/QStaticIPComboBox.h \
    Widgets/QROSAPIUserTableWidget.h \
    Widgets/QROSAPIUserLevelComboBox.h \
    Widgets/QROSAPIUsersGroupTableWidget.h \
    Widgets/QRoutersLineEdit.h \
    Widgets/QROSAPIUsersGroupComboBox.h \
    Widgets/QTableWidgetBase.h \
	Widgets/QPPPProfilesTableWidget.h \
    QSecretData.h \
    DlgNuevoUsuario.h \
	DlgExportar.h \
	DlgPortScan.h \
    ROSMultiConnectorManager.h \
    ROSPPPoEManager.h \
    Dialogs/DlgConfiguracion.h \
    Dialogs/DlgLookConfig.h \
    Dialogs/DlgCnfgConnect.h \
    Dialogs/DlgROSAPIUsers.h \
	Dialogs/DlgROSAPIUser.h \
	Dialogs/DlgPPPProfiles.h \
    ROSDataManager/ROSInterfaceManager.h \
    ROSData/ROSBridgePorts.h \
    ROSData/ROSIPAddress.h \
    ROSDataManager/ROSBridgePortManager.h \
    ROSDataManager/ROSIPAddressManager.h

FORMS    += QMikPPPManager.ui \
	DlgNuevoUsuario.ui \
	DlgExportar.ui \
	DlgPortScan.ui \
    Dialogs/DlgConfiguracion.ui \
    Dialogs/DlgCnfgConnect.ui \
    Dialogs/DlgLookConfig.ui \
    Dialogs/DlgROSAPIUsers.ui \
    Dialogs/DlgROSAPIUser.ui \
    Dialogs/DlgPPPProfiles.ui

DISTFILES += \
    ToDo.txt

RESOURCES += \
    iconos.qrc
