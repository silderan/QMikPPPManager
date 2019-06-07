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

#include "DlgNewPPPProfile.h"
#include "ui_DlgNewPPPProfile.h"

#include <QMessageBox>

DlgNewPPPProfile::DlgNewPPPProfile(QWidget *papi)
	: QNewROSDataDialogBase(papi)
	, ui(new Ui::DlgNewPPPProfile)
{
	ui->setupUi(this);
	connect( ui->acceptButton, &QAbstractButton::clicked, this, &QNewROSDataDialogBase::tryAccept<ROSPPPProfile> );
}

DlgNewPPPProfile::~DlgNewPPPProfile()
{
	delete ui;
}

void DlgNewPPPProfile::setROSData(ROSDataBase &rosData)
{
	if( static_cast<ROSPPPProfile&>(rosData).profileName().isEmpty() )
		setWindowTitle( tr("Nuevo perfil PPP") );
	else
		setWindowTitle( tr("Modificando perfil %1").arg(static_cast<ROSPPPProfile&>(rosData).profileName()) );

	ui->pppProfileNameLineEdit->setText( static_cast<ROSPPPProfile&>(rosData).profileName() );
	ui->bridgeComboBox->setCurrentText( static_cast<ROSPPPProfile&>(rosData).bridgeName() );
	ui->localAddressComboBox->setCurrentText( static_cast<ROSPPPProfile&>(rosData).localAddress() );
	ui->remoteAddressComboBox->setCurrentText( static_cast<ROSPPPProfile&>(rosData).remoteAddress() );
	ui->speedRateLimits->setROSRateLimit( static_cast<ROSPPPProfile&>(rosData).rateLimit() );
}

bool DlgNewPPPProfile::getROSData(ROSDataBase &rosData) const
{
	return	setTextMember<ROSPPPProfile>( ui->pppProfileNameLineEdit->text(), rosData, &ROSPPPProfile::setProfileName, tr("nombre del perfil") ) &&
			setTextMember<ROSPPPProfile>( ui->bridgeComboBox->currentText(), rosData, &ROSPPPProfile::setBridgeName, tr("nombre del bridge") ) &&
			setTextMember<ROSPPPProfile>( ui->localAddressComboBox->currentText(), rosData, &ROSPPPProfile::setLocalAddress, tr("local address") ) &&
			setTextMember<ROSPPPProfile>( ui->remoteAddressComboBox->currentText(), rosData, &ROSPPPProfile::setRemoteAddress, tr("remote address") ) &&
			ui->speedRateLimits->getROSRateLimit( static_cast<ROSPPPProfile&>(rosData).rateLimit() );
}
