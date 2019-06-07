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

#include "QROSAPIUserTableWidget.h"
#include "../ROSMultiConnectorManager.h"

QROSAPIUserTableWidget::QROSAPIUserTableWidget(QWidget *papi) : QROSDataTableWidget(papi)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Usuario" << "Grupo" << "Nivel/Tipo" << "Routers" );
	setRouterIDColumn(Routers);

	setFancyItemDelegateForColumn( Columns::GroupName, new QComboBoxItemDelegated( this, "", "", false,
													/*add list*/				[] (int) { return multiConnectionManager.rosAPIUsersGrupList();	},
													/*skip list*/				[] (int) { return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::UserLevel, new QComboBoxItemDelegated( this, "", "", false,
													/*add list*/				[] (int) { return ROSAPIUser::levelNames();	},
													/*skip list*/				[] (int) { return QStringList(); } ) );
}

QROSAPIUserTableWidget::~QROSAPIUserTableWidget()
{

}

ROSDataBase *QROSAPIUserTableWidget::getRosData(int row)
{
	ROSAPIUser *rosAPIUserData = new ROSAPIUser("");
	rosAPIUserData->setUserName( userName(row) );
	rosAPIUserData->setUserLevel( userLevel(row) );
	rosAPIUserData->setGroupName( userGroup(row) );
	return rosAPIUserData;
}

void QROSAPIUserTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	const ROSAPIUser &userData = static_cast<const ROSAPIUser&>(rosData);

	Q_ASSERT( !userData.userName().isEmpty() );

	QROSDataTableWidget::setupRow(row, rosData);
	setCellText( row, UserName, userData.userName(), userData.rosObjectID().isEmpty() ? Qt::ItemIsEditable : Qt::NoItemFlags );
	setCellText( row, GroupName, userData.groupName(), Qt::ItemIsEditable );
	setCellText( row, UserLevel, userData.levelName(), Qt::ItemIsEditable );
}


int QROSAPIUserTableWidget::rowOf(const ROSDataBase &rosData)
{
	const ROSAPIUser &userData = static_cast<const ROSAPIUser&>(rosData);
	return QROSDataTableWidget::rowOf(UserName, userData.userName());
}

void QROSAPIUserTableWidget::updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue)
{
	Q_UNUSED(row);

	ROSAPIUser *apiUser = static_cast<ROSAPIUser*>(rosData);
	switch( static_cast<Columns>(changedColumn) )
	{
	case QROSAPIUserTableWidget::UserName:
		// API User Name is not allowed by ROS.
		Q_ASSERT(false);
		break;
	case QROSAPIUserTableWidget::GroupName:
		apiUser->setGroupName(newValue);
		break;
	case QROSAPIUserTableWidget::UserLevel:
		apiUser->setUserLevel(newValue);
		break;
	case QROSAPIUserTableWidget::Routers:
		Q_ASSERT(false);
		break;
	case QROSAPIUserTableWidget::TotalColumns:
		Q_ASSERT(false);
		break;
	}
}
