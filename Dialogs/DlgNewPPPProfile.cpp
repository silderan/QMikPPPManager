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
