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

	void onComError(const QString &errorString, const QString &routerName);
	void onROSError(const QString &routerName, const QString &errorString);
	void onRouterConnected(const QString &routerName);
	void onRouterDisconnected(const QString &routerName);
	void onLogued(const QString &routerName);
	void onConfigChanged();

private slots:
	void addRow(int row = -1, const QString &hostAddr = QString(), quint16 hostPort = 8728, const QString &routerState = QString());
	void removeCurrentRow();
	void on_acceptButton_clicked();
	void on_cancelButton_clicked();
};

#endif // DLGCNFGCONNECT_H
