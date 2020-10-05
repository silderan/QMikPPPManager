#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T12:29:14
#
#-------------------------------------------------

QT       += core gui network sql charts printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMikPPPManager
TEMPLATE = app
win32:RC_ICONS += img/main.ico


SOURCES += main.cpp\
    ../../SildeQtUtils/src/IPv4Range.cpp \
    ConfigData/SchedulerData.cpp \
    ConfigData/VoIPData.cpp \
	Dialogs/DlgCreateConfigFile.cpp \
    Dialogs/DlgPortEdit.cpp \
    Dialogs/DlgServiceScheduler.cpp \
    Dialogs/DlgVoIPData.cpp \
	Utils/ROSSpeed.cpp \
	Utils/ROSRateLimit.cpp \
    QMikPPPManager.cpp \
    ROSAPI/QMD5.cpp \
    ROSAPI/QSentences.cpp \
    ROSAPI/Comm.cpp \
    ROSData/ROSAPIUser.cpp \
    ROSData/ROSAPIUserGroup.cpp \
    ROSData/ROSDataBasics.cpp \
	ROSData/ROSPPPProfile.cpp \
	ROSData/ROSInterfaces.cpp \
    ROSDataManager/ROSInterfaceManager.cpp \
    ROSData/ROSBridgePorts.cpp \
    ROSData/ROSIPAddress.cpp \
    ROSData/ROSIPPool.cpp \
	Widgets/QIPv4RangeComboBox.cpp \
    Widgets/QPortForwardListWidget.cpp \
    Widgets/QROSAPIUserTableWidget.cpp \
    Widgets/QROSAPIUsersGroupTableWidget.cpp \
    Widgets/QRoutersLineEdit.cpp \
	Widgets/QPPPProfilesTableWidget.cpp \
    Widgets/QROSIPoolTableWidget.cpp \
    ConfigData/ConnectInfo.cpp \
    ConfigData/TableCellLook.cpp \
    ConfigData/ClientProfile.cpp \
    ConfigData/QConfigData.cpp \
    ROSMultiConnectorManager.cpp \
    ROSPPPoEManager.cpp \
    Dialogs/DlgCnfgConnect.cpp \
    Dialogs/DlgConfiguracion.cpp \
    Dialogs/DlgLookConfig.cpp \
    Dialogs/DlgROSAPIUsers.cpp \
	Dialogs/DlgPPPProfiles.cpp \
    Dialogs/DlgROSIPPool.cpp \
    Dialogs/DlgDataBase.cpp \
    ROSData/ROSSecret.cpp \
    Utils/Utils.cpp \
    Widgets/QROSSecretTableWidget.cpp \
    Dialogs/DlgPPPUser.cpp \
    Utils/PortForward.cpp \
    ROSDataManager/ROSPPPSecretManager.cpp \
    Utils/QPPPLogger.cpp \
    Dialogs/DlgPPPLogViewer.cpp \
    Dialogs/DlgNewPPPProfile.cpp \
    Widgets/QSpeedTableWidget.cpp \
    Widgets/QROSDataTableWidget.cpp \
    Dialogs/DlgNewROSAPIUser.cpp \
    Dialogs/DlgExportUserData.cpp \
    Utils/OpenBrowserInfo.cpp \
    RadiusManager/QRadiusManager.cpp \
    Widgets/QSpeedChart.cpp \
    Dialogs/DlgUserThroughput.cpp \
    Widgets/QUserVoIPDataTableWidget.cpp

HEADERS  += QMikPPPManager.h \
    ../../SildeQtUtils/src/IPv4Range.h \
    ConfigData/SchedulerData.h \
    ConfigData/VoIPData.h \
	Dialogs/DlgCreateConfigFile.h \
    Dialogs/DlgPortEdit.h \
    Dialogs/DlgServiceScheduler.h \
    Dialogs/DlgVoIPData.h \
	Utils/ROSSpeed.h \
	Utils/ROSRateLimit.h \
    ROSAPI/QMD5.h \
    ROSAPI/QSentences.h \
    ROSAPI/Comm.h \
    ROSData/DataTypeID.h \
    ROSData/ROSAPIUser.h \
    ROSData/ROSAPIUserGroup.h \
    ROSData/ROSDataBasics.h \
	ROSData/ROSPPPProfile.h \
	ROSData/ROSInterfaces.h \
    ROSData/ROSBridgePorts.h \
    ROSData/ROSIPAddress.h \
    ROSData/ROSIPPool.h \
	ROSDataManager/ROSDataManagerBase.h \
	ROSDataManager/ROSAPIUserManager.h \
	ROSDataManager/ROSAPIUsersGroupManager.h \
	ROSDataManager/ROSPPPProfileManager.h \
    ROSDataManager/ROSInterfaceManager.h \
    ROSDataManager/ROSBridgePortManager.h \
    ROSDataManager/ROSIPAddressManager.h \
	ConfigData/ConnectInfo.h \
    ConfigData/TableCellLook.h \
    ConfigData/ClientProfile.h \
    ConfigData/QConfigData.h \
    Widgets/QIPv4RangeComboBox.h \
    Widgets/QPortForwardListWidget.h \
    Widgets/QROSAPIUserTableWidget.h \
    Widgets/QROSAPIUsersGroupTableWidget.h \
    Widgets/QRoutersLineEdit.h \
	Widgets/QPPPProfilesTableWidget.h \
    Widgets/QROSIPoolTableWidget.h \
    ROSMultiConnectorManager.h \
    ROSPPPoEManager.h \
    Dialogs/DlgConfiguracion.h \
    Dialogs/DlgLookConfig.h \
    Dialogs/DlgCnfgConnect.h \
    Dialogs/DlgROSAPIUsers.h \
	Dialogs/DlgPPPProfiles.h \
    Dialogs/DlgROSIPPool.h \
    Dialogs/DlgDataBase.h \
    ROSData/ROSSecret.h \
    Utils/Utils.h \
    Widgets/QROSSecretTableWidget.h \
    ROSDataManager/ROSPPPSecretManager.h \
    ROSDataManager/ROSPPPActiveManager.h \
    UnitTests.h \
    Widgets/QComboBoxItemDelegate.h \
    Widgets/QRemoteIPCellItem.h \
    Dialogs/DlgPPPUser.h \
    Utils/PortForward.h \
    Utils/QPPPLogger.h \
    Dialogs/DlgPPPLogViewer.h \
    Dialogs/DlgNewPPPProfile.h \
    Widgets/QSpeedTableWidget.h \
    Widgets/QROSDataTableWidget.h \
    Dialogs/DlgNewROSAPIUser.h \
    Dialogs/DlgExportUserData.h \
    Utils/OpenBrowserInfo.h \
    RadiusManager/QRadiusManager.h \
    ROSDataManager/ROSIPPoolManager.h \
    Widgets/QSpeedChart.h \
    Dialogs/DlgUserThroughput.h \
    Widgets/QUserVoIPDataTableWidget.h

FORMS    += QMikPPPManager.ui \
	Dialogs/DlgCreateConfigFile.ui \
    Dialogs/DlgPortEdit.ui \
    Dialogs/DlgServiceScheduler.ui \
    Dialogs/DlgVoIPData.ui \
    Dialogs/DlgConfiguracion.ui \
    Dialogs/DlgCnfgConnect.ui \
    Dialogs/DlgLookConfig.ui \
    Dialogs/DlgROSAPIUsers.ui \
	Dialogs/DlgNewPPPProfile.ui \
    Dialogs/DlgPPPProfiles.ui \
    Dialogs/DlgROSIPPool.ui \
    Dialogs/DlgPPPUser.ui \
	Dialogs/DlgPPPLogViewer.ui \
    Dialogs/DlgNewROSAPIUser.ui \
    Dialogs/DlgExportUserData.ui \
    Dialogs/DlgUserThroughput.ui

DISTFILES += \
    ToDo.txt

RESOURCES += \
    iconos.qrc
