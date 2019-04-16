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

#include "QPPPProfilesTableWidget.h"

#include "../ROSData/ROSPPPProfile.h"
#include "QComboBoxItemDelegate.h"
#include "QSpeedTableWidget.h"
#include "../ROSMultiConnectorManager.h"

QPPPProfilesTableWidget::QPPPProfilesTableWidget(QWidget *papi) :
	QROSDataTableWidget(papi)
{
	setColumnCount(Columns::TotalColumns);
	setRouterIDColumn(Columns::Routers);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Velocidades" << "Direccion Router" << "Pool direcciones cliente" << "Bridge" << "Routers" );

	setFancyItemDelegateForColumn( Columns::Bridge, new QComboBoxItemDelegated( this, tr("Ninguno"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.bridgeNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::LocalAddress, new QComboBoxItemDelegated( this, tr("Ninguna"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::RemoteAddress, new QComboBoxItemDelegated( this, tr("Ninguna"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setItemDelegateForColumn( Columns::RateLimit, new QSpeedTableWidgetItemDelegate() );
}

QPPPProfilesTableWidget::~QPPPProfilesTableWidget()
{

}

void QPPPProfilesTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	QROSDataTableWidget::setupRow(row, rosData);

	const ROSPPPProfile &profileData = static_cast<const ROSPPPProfile &>(rosData);
	setCellText( row, Columns::ProfileName, profileData.profileName(), Qt::ItemIsEditable );
	setCellText( row, Columns::RateLimit, profileData.rateLimit().toString(), Qt::ItemIsEditable );
	setCellText( row, Columns::LocalAddress, profileData.localAddress(), Qt::ItemIsEditable );
	setCellText( row, Columns::RemoteAddress, profileData.remoteAddress(), Qt::ItemIsEditable );
	setCellText( row, Columns::Bridge, profileData.bridgeName(), Qt::ItemIsEditable );
}

int QPPPProfilesTableWidget::rowOf(const ROSDataBase &rosData)
{
	return QROSDataTableWidget::rowOf( Columns::ProfileName, static_cast<const ROSPPPProfile &>(rosData).profileName() );
}

ROSDataBase *QPPPProfilesTableWidget::getRosData(int row)
{
	ROSPPPProfile *profileData = new ROSPPPProfile("");
	profileData->setProfileName( cellText(row, Columns::ProfileName) );
	profileData->rateLimit().fromString( cellText(row, Columns::RateLimit) );
	profileData->setLocalAddress( cellText(row, Columns::LocalAddress) );
	profileData->setRemoteAddress( cellText(row, Columns::RemoteAddress) );
	profileData->setBridgeName( cellText(row, Columns::Bridge) );
	return profileData;
}

void QPPPProfilesTableWidget::updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue)
{
	Q_UNUSED(row);

	ROSPPPProfile *profileData = static_cast<ROSPPPProfile*>(rosData);
	switch( static_cast<Columns>(changedColumn) )
	{
	case Columns::ProfileName:
		profileData->setProfileName(newValue);
		break;
	case Columns::RateLimit:
		profileData->rateLimit().fromString(newValue);
		break;
	case Columns::LocalAddress:
		profileData->setLocalAddress(newValue);
		break;
	case Columns::RemoteAddress:
		profileData->setRemoteAddress(newValue);
		break;
	case Columns::Bridge:
		profileData->setBridgeName(newValue);
		break;
	case Columns::Routers:
		Q_ASSERT(false);
		break;
	case Columns::TotalColumns:
		Q_ASSERT(false);
		break;
	}
}
