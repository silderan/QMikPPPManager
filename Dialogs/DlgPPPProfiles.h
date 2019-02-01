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

#ifndef DLGPPPPROFILES_H
#define DLGPPPPROFILES_H

#include "DlgDataBase.h"
#include "../ROSData/ROSPPPProfile.h"

namespace Ui
{
	class DlgPPPProfiles;
}

class DlgPPPProfiles : public QDlgMultiDataBase
{
	Q_OBJECT

	Ui::DlgPPPProfiles *ui;

public:
	explicit DlgPPPProfiles(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi);
	~DlgPPPProfiles()override;

private slots:
	void on_acceptButton_clicked();

	void on_addButton_clicked();

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);

public:
	void clear()override;
	void onROSModReply(const ROSDataBase &rosData) override;
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID) override;
	void onROSDone(const QString &routerName, DataTypeID dataTypeID) override;
};

#endif // DLGPPPPROFILES_H
