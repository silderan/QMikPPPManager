#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>

#include "ROSMultiConnectorManager.h"
#include "QSecretData.h"
#include "ConfigData/QConfigData.h"
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QCheckBox>
#include <QDesktopServices>
#include <QUrl>
#include <QInputEvent>

#include "UnitTests.h"

#include "ROSData/ROSAPIUser.h"
#include "ROSData/ROSAPIUserGroup.h"
#include "ROSData/ROSPPPProfile.h"


#include "DlgNuevoUsuario.h"

#include "Dialogs/DlgCnfgConnect.h"
#include "Dialogs/DlgDataBase.h"
#include "Dialogs/DlgROSAPIUsers.h"
#include "Dialogs/DlgPPPProfiles.h"
#include "Dialogs/DlgPPPUser.h"

namespace Ui
{
	class QMikPPPManager;
}

class QMikPPPManager : public QMainWindow
{
	Q_OBJECT
	Ui::QMikPPPManager *ui;
	DlgCnfgConnect *dlgCnfgConnect;
	QDlgMultiDataBasePList m_dialogList;

	void updateGUIAccess();
	void setUserLevel(ROSAPIUser::Level userLevel);
	void checkAPISupervisor();

private slots:
	void setStatusText(QString errorString, const QString routerName = QString());
	void onComError(const QString &errorString, const QString &routerName);

	void onROSError(const QString &routerName, const QString &errorString);
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void onROSDone(const QString &routerName, DataTypeID dataTypeID);

	void onRouterConnected(const QString &routerName);
	void onAllRoutersConnected();

	void onRouterDisconnected(const QString &routerName);
	void onAllRoutersDisconnected();

	void onLogued(const QString &routerName);

	// GUI Interface.
	void on_connectButton_clicked();
	void on_localConfigButton_clicked();
	void on_connectionConfigButton_clicked();
	void on_advancedConfigButton_clicked();
	void on_addUserButton_clicked();
	void on_disconnectButton_clicked();
	void on_apiUsersButton_clicked();
	void on_pppProfilesButton_clicked();

	void onPPPEditRequest(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);
	void on_pppLogsButton_clicked();
	void applyUsersRowFilter(QString);

public slots:
	void updateConfig();

public:
	explicit QMikPPPManager(QWidget *parent = Q_NULLPTR);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
