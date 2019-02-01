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

#include "DlgNewROSAPIUser.h"
#include "ui_DlgNewROSAPIUser.h"


DlgNewROSAPIUser::DlgNewROSAPIUser(QWidget *papi)
	: QNewROSDataDialogBase(papi)
	, ui(new Ui::DlgNewROSAPIUser)
{
	ui->setupUi(this);
	ui->grupNameComboBox->addItems( multiConnectionManager.rosAPIUsersGrupList() );
	ui->userLevelComboBox->addItems( ROSAPIUser::levelNames() );
	connect( ui->acceptButton, &QAbstractButton::clicked, this, &QNewROSDataDialogBase::tryAccept<ROSAPIUser> );
	updateGUI();
}

DlgNewROSAPIUser::~DlgNewROSAPIUser()
{
	delete ui;
}

void DlgNewROSAPIUser::updateGUI()
{
	switch( gGlobalConfig.userLevel() )
	{
	case ROSAPIUser::NoRights:
		Q_ASSERT(false);
		this->setDisabled(true);
		ui->acceptButton->setVisible(false);
		break;
	case ROSAPIUser::Comercial:
		setReadOnly(true);
		ui->acceptButton->setVisible(false);
		break;
	case ROSAPIUser::Instalator:
		setReadOnly(true);
		ui->acceptButton->setVisible(false);
		break;
	case ROSAPIUser::Administrator:
		setReadOnly(true);
		ui->acceptButton->setVisible(false);
		break;
	case ROSAPIUser::Supervisor:
		setReadOnly(false);
		ui->acceptButton->setVisible(true);
		break;
	}
}

void DlgNewROSAPIUser::setROSData(ROSDataBase &rosData)
{
	if( static_cast<ROSAPIUser&>(rosData).userName().isEmpty() )
	{
		setWindowTitle( tr("Nuevo usuario API") );
		ui->userNameLineEdit->setEnabled(true);
	}
	else
	{
		setWindowTitle( tr("Modificando usuario API %1").arg(static_cast<ROSPPPProfile&>(rosData).profileName()) );
		ui->userNameLineEdit->setDisabled(true);
	}
	ui->userNameLineEdit->setText( static_cast<ROSAPIUser&>(rosData).userName() );
	ui->userPassLineEdit->setText( static_cast<ROSAPIUser&>(rosData).userPass() );
	ui->userNameLineEdit->setText( static_cast<ROSAPIUser&>(rosData).userName() );
}

bool DlgNewROSAPIUser::getROSData(ROSDataBase &rosData) const
{
	return	setTextMember<ROSAPIUser>( ui->grupNameComboBox->currentText(), rosData, &ROSAPIUser::setGroupName, tr("Nombre del grupo de usuarios") ) &&
			setTextMember<ROSAPIUser>( ui->userNameLineEdit->text(), rosData, &ROSAPIUser::setUserName, tr("Nombre de usuario") ) &&
			setTextMember<ROSAPIUser>( ui->userPassLineEdit->text(), rosData, &ROSAPIUser::setUserPass, tr("Contraseña de usuario") ) &&
			static_cast<ROSAPIUser&>(rosData).setUserLevel( ui->userLevelComboBox->currentText() );
}

void DlgNewROSAPIUser::onConfigChanged()
{
	updateGUI();
}
