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

#include "DlgROSAPIUsers.h"
#include "ui_DlgROSAPIUsers.h"

#include <QTableWidgetItem>

#include "Widgets/QROSAPIUserTableWidget.h"

DlgROSAPIUsers::DlgROSAPIUsers(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi)
	: QDlgMultiDataBase(configData, rosMultiConnectManager, papi)
	, ui(new Ui::DlgROSAPIUsers)
{
	ui->setupUi(this);

	updateMultipleData( DataTypeIDList() << DataTypeID::APIUser << DataTypeID::APIUsersGroup );

	// Forward signals.
	connect( ui->usersTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)) );
	connect( ui->groupsTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)) );

	connect( ui->delUserButton, SIGNAL(clicked()), ui->usersTable, SLOT(removeCurrentData()) );
	connect( ui->delGroupButton, SIGNAL(clicked()), ui->groupsTable, SLOT(removeCurrentData()) );
}

DlgROSAPIUsers::~DlgROSAPIUsers()
{
	delete ui;
}

void DlgROSAPIUsers::clear()
{
	ui->groupsTable->setRowCount(0);
	ui->usersTable->setRowCount(0);
}

#include "Dialogs/DlgNewROSAPIUser.h"
void DlgROSAPIUsers::on_addUserButton_clicked()
{
	ROSAPIUser user("");
	DlgNewROSAPIUser dlg(this);
	if( dlg.exec(user) )
		emit dataModified( user, QRouterIDMap() );
}

void DlgROSAPIUsers::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::APIUser )
		ui->usersTable->onROSModReply(rosData);
	else
	if( rosData.dataTypeID() == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSModReply(rosData);
}

void DlgROSAPIUsers::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	if( dataTypeID == DataTypeID::APIUser )
		ui->usersTable->onROSDelReply(routerName, rosObjectID);
	else
	if( dataTypeID == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSDelReply(routerName, rosObjectID);
}

void DlgROSAPIUsers::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	if( dataTypeID == DataTypeID::APIUser )
		ui->usersTable->onROSDone(routerName);
	else
	if( dataTypeID == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSDone(routerName);
}
