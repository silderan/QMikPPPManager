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

#include "QROSAPIUsersGroupTableWidget.h"

#include "QRoutersLineEdit.h"

#include "../ROSData/ROSAPIUserGroup.h"

QROSAPIUsersGroupTableWidget::QROSAPIUsersGroupTableWidget(QWidget *parent) : QROSDataTableWidget(parent)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Permisos" << "Routers" );
	setRouterIDColumn(Routers);
}

QROSAPIUsersGroupTableWidget::~QROSAPIUsersGroupTableWidget()
{

}

QStringList QROSAPIUsersGroupTableWidget::groupNames() const
{
	QStringList ls;
	for( int row = 0; row < rowCount(); ++row )
		ls.append(item(row, GroupName)->text());
	return ls;
}

void QROSAPIUsersGroupTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	QROSDataTableWidget::setupRow(row, rosData);
	const ROSAPIUsersGroup &groupData = static_cast<const ROSAPIUsersGroup &>(rosData);
	setCellText( row, GroupName, groupData.groupName() );
	setCellText( row, Policy, groupData.policy().join(',') );
}

int QROSAPIUsersGroupTableWidget::rowOf(const ROSDataBase &rosData)
{
	const ROSAPIUsersGroup &groupData = static_cast<const ROSAPIUsersGroup &>(rosData);
	return QROSDataTableWidget::rowOf(GroupName, groupData.groupName());
}

ROSDataBase *QROSAPIUsersGroupTableWidget::getRosData(int row)
{
	ROSAPIUsersGroup *groupData = new ROSAPIUsersGroup("");
	groupData->setGroupName( cellText(row, GroupName) );
	groupData->setPolicy( cellText(row, Policy).split(',') );
	return groupData;
}

void QROSAPIUsersGroupTableWidget::updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue)
{
	Q_UNUSED(row);

	switch( static_cast<Columns>(changedColumn) )
	{
	case QROSAPIUsersGroupTableWidget::GroupName:
		static_cast<ROSAPIUsersGroup*>(rosData)->setGroupName(newValue);
		break;
	case QROSAPIUsersGroupTableWidget::Policy:
		static_cast<ROSAPIUsersGroup*>(rosData)->setPolicy(newValue.split(','));
		break;
	case QROSAPIUsersGroupTableWidget::Routers:
		Q_ASSERT(false);
		break;
	case QROSAPIUsersGroupTableWidget::TotalColumns:
		Q_ASSERT(false);
		break;
	}
}
