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

#ifndef DLGCONFIGURACION_H
#define DLGCONFIGURACION_H

#include <QDialog>

#include "../Utils/IPv4Range.h"
#include "../ConfigData/QConfigData.h"
#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgConfiguracion;
}

class DlgConfiguracion : public QDialog
{
	Q_OBJECT

	Ui::DlgConfiguracion *ui;

	QStringList m_installerList;
	QStringList m_comercialList;
	IPv4RangeListMap m_staticIPv4RangeListMap;
	QClientProfileMap m_clientProfileMap;
	ROSMultiConnectManager &m_multiConManager;
	QStringList m_groupNames;
	QStringList m_selectedProfiles;

	void addProfileTableRow(const ClientProfileData &clientProfileData = ClientProfileData());
	void addStaticIPRangeRow(const IPv4Range &ipv4Range = IPv4Range(), const QString &profileName = QString());
	void refillDialogUsedData();
	void raisesWarning(const QString &error);
	bool checkValidGroupName(const QString &groupName, int row);


public:
	explicit DlgConfiguracion(const QStringList &installerList,
							  const QStringList &comercialList,
							  const IPv4RangeListMap &ipv4RangeListMap,
							  const QClientProfileMap &clientProfileList,
							  ROSMultiConnectManager &multiConManager,
							  QWidget *papi);
	~DlgConfiguracion();

	QStringList installerList() const					{ return m_installerList;	}
	QStringList comercialList() const					{ return m_comercialList;	}
	IPv4RangeListMap staticIPv4RangeListMap() const		{ return m_staticIPv4RangeListMap;	}
	QClientProfileMap clientProfileList() const			{ return m_clientProfileMap;		}

	QStringList selectableGroupNames(int row) const;

private slots:
	void on_btAceptar_clicked();
	void on_btCancelar_clicked();
	void on_addProfileButton_clicked();
	void on_delProfileButton_clicked();
	void on_addStaticRangeButton_clicked();
	void on_delStaticRangeButton_clicked();
	void on_profilesTable_cellChanged(int row, int column);
	void on_upButton_clicked();
	void on_downButton_clicked();
};

#endif // DLGCONFIGURACION_H
