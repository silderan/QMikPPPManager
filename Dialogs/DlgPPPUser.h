#ifndef DLGPPPUSER_H
#define DLGPPPUSER_H

#include "DlgDataBase.h"
#include <QGroupBox>

#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"

namespace Ui
{
	class DlgPPPUser;
}

class DlgPPPUser : public DlgDataBase
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

	void raiseWarning(const QString &info);

	bool currentEditing(const ROSPPPSecret &pppSecret);

	bool checkStringData(const QString &fieldName, const QString &originalText, const QString &text, std::function<bool(ROSPPPSecret &, const QString &)> setFnc);
	bool checkGroupedData(const QGroupBox *group, const QString &fieldName, const QString &originalText, QString text, std::function<bool(ROSPPPSecret &, const QString &)> setFnc);
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
	bool getONTSN();
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

public slots:
	void onEditUserRequest(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);

	// QWidget interface
protected:
	void hideEvent(QHideEvent *event) override;
};

#endif // DLGPPPUSER_H
