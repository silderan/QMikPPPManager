#ifndef DLGCNFGCONNECT_H
#define DLGCNFGCONNECT_H

#include <QDialog>

#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgCnfgConnect;
}

class DlgCnfgConnect : public QDialog
{
    Q_OBJECT
	Ui::DlgCnfgConnect *ui;
	ROSMultiConnectManager &m_rosMultiConnectManager;

	enum Columns
	{
		AddressCol,
		PortCol,
		StatusCol
	};

	void setup();
	bool checkData();
	void copyDataToGlobalConfig();

	void setRouterStatus(const QString &routerName, const QString &errorString);

public:
	explicit DlgCnfgConnect(QWidget *parent, ROSMultiConnectManager &rosMultiConnectManager);
    ~DlgCnfgConnect();

private slots:
	void addRow(int row = -1, const QString &hostAddr = QString(), quint16 hostPort = 8728, const QString &routerState = QString());
	void removeCurrentRow();
	void on_connectButton_clicked();
	void on_acceptButton_clicked();
	void on_cancelButton_clicked();

public slots:
	void onComError(const QString &errorString, const QString &routerName);
	void onROSError(const QString &routerName, const QString &errorString);
	void onRouterConnected(const QString &routerName);
	void onRouterDisconnected(const QString &routerName);
	void onLogued(const QString &routerName);

signals:
	void connectToHosts();
	void globalConfigChanged();
};

#endif // DLGCNFGCONNECT_H
