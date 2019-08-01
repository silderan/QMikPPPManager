/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>

#include "ROSMultiConnectorManager.h"
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
	void setStatusText(const QString routerName, QString errorString);
	void onComError(const QString &routerName, const QString &errorString);

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
	void onShowUserTraffic(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);

	void on_pppLogsButton_clicked();
	void applyUsersRowFilter(QString);

	void on_schedulerButton_clicked();

public slots:
	void updateConfig();

public:
	explicit QMikPPPManager(QWidget *parent = Q_NULLPTR);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
