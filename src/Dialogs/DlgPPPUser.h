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

#ifndef DLGPPPUSER_H
#define DLGPPPUSER_H

#include "DlgDataBase.h"
#include <QGroupBox>

#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"
#include "../ConfigData/SchedulerData.h"

namespace Ui
{
	class DlgPPPUser;
}

class DlgPPPUser : public QDlgMultiDataBase
{
	Q_OBJECT
	Ui::DlgPPPUser *ui;

	QPPPSecretMap m_pppSecretMap;

	ROSPPPSecret m_pppSecret;
	ROSPPPActive m_pppActive;

	void updatePPPProfilesComboBox();
	void updateInstallersComboBox();
	void updateCitiesComboBox();
	void updateStaticIPComboBox();
	void updateDialog();
	void updateUserData();
	void updateDialogInfo();

	bool currentEditing(const ROSPPPSecret &pppSecret);

	bool checkStringData(const QString &fieldName, const QString &originalText, const QString &text, std::function<bool(ROSPPPSecret &, const QString &)> setFnc);
	bool checkGroupedData( const QGroupBox *group,
						   QString newText,
						   std::function<const QString &(ROSPPPSecret &)> getFnc,
						   std::function<bool(ROSPPPSecret &, const QString &)> setFnc,
						   const QString &fieldName );
	bool checkIPv4(const QString &fieldName, QString &ipString, bool obligated = false);

	bool getPPPUserName();
	bool getPPPUserPass();
	bool getPPPProfile();
	bool getStaticIP();
	bool getClientName();
	bool getClientAddress();
	bool getClientInstaller();
	bool getClientCity();
	bool getClientPhones();
	bool getClientEMail();
	bool getClientNotes();
	bool getInstallNotes();
	bool getServiceInfo();
	bool getVoIPPhone();
	bool getVoIPSIPServer();
	bool getVoIPUserName();
	bool getVoIPUserPass();
	bool checkWiFiSSID(const QString &fieldName, const QString &originalText, QString &ssid);
	bool checkWiFiWPA(const QString &fieldName, const QString &originalText, QString &wpa);
	bool getWiFi2SSID();
	bool getWiFi2WPA();
	bool getWiFi5SSID();
	bool getWiFi5WPA();
	bool getLocalIP();
	bool getLocalDMZ();
	bool getLocalPorts();
	bool getSchedulerData();

	void updateGUI();

	void addServiceSchedulerRow(const ServiceScheduler::Data &schedulerData = ServiceScheduler::Data());
public:
	DlgPPPUser(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi);
	~DlgPPPUser() override;

	void onROSModReply(const ROSDataBase &rosData) override;
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID) override;
	void onROSDone(const QString &routerName, DataTypeID dataTypeID) override;
	void clear() override;
	void onLogued(const QString &routerName) override;
	void onDisconnected(const QString &routerName) override;
	void onConfigDataChanged() override;

private slots:
	void on_pppProfileComboBox_currentIndexChanged(int index);
	void on_applyDataButton_clicked();
	void on_addPortButton_clicked();
	void on_delPortButton_clicked();
	void on_clientLogsButton_clicked();
	void on_pppUserNameCopyButton_clicked();
	void on_pppUserPassCopyButton_clicked();
	void on_pppUserPassCreateButton_clicked();
	void on_copyInfoButton_clicked();
	void on_delChedulerButton_clicked();
	void on_addSchedulerButton_clicked();
	void on_serviceTypeComboBox_currentIndexChanged(int index);

public slots:
	void onEditUserRequest(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);

	// QWidget interface
protected:
	void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

	// QDialogBase interface
public:
	void onConfigChanged() Q_DECL_OVERRIDE;
};

#endif // DLGPPPUSER_H