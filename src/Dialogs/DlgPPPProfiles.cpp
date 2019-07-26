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

#include "DlgPPPProfiles.h"
#include "ui_DlgPPPProfiles.h"

#include "DlgNewPPPProfile.h"


DlgPPPProfiles::DlgPPPProfiles(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi)
	: QDlgMultiDataBase(configData, rosMultiConnectManager, papi)
	, ui(new Ui::DlgPPPProfiles)
{
	ui->setupUi(this);

	updateMultipleData( DataTypeIDList() << DataTypeID::PPPProfile << DataTypeID::Interface << DataTypeID::IPPool );

	// Forward signal.
	connect( ui->profilesTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)) );
	connect( ui->delButton, SIGNAL(clicked()), ui->profilesTable, SLOT(removeCurrentData()) );
}

DlgPPPProfiles::~DlgPPPProfiles()
{
	delete ui;
}

void DlgPPPProfiles::on_acceptButton_clicked()
{
	accept();
}

void DlgPPPProfiles::clear()
{
	ui->profilesTable->setRowCount(0);
}

void DlgPPPProfiles::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::PPPProfile )
		ui->profilesTable->onROSModReply(rosData);
}

void DlgPPPProfiles::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	if( dataTypeID == DataTypeID::PPPProfile )
		ui->profilesTable->onROSDelReply(routerName, rosObjectID);
}

void DlgPPPProfiles::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	if( dataTypeID == DataTypeID::PPPProfile )
		ui->profilesTable->onROSDone(routerName);
}

void DlgPPPProfiles::on_addButton_clicked()
{
	ROSPPPProfile newPPPProfile("");
	DlgNewPPPProfile dlg(this);

	if( dlg.exec(newPPPProfile) )
		emit dataModified( newPPPProfile, QRouterIDMap() );
}
