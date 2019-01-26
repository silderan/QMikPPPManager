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
	return	fancySetTextToMember( ui->pppProfileNameLineEdit->text(), rosData, ROSPPPProfile, setProfileName, "nombre del perfil" ) &&
			fancySetTextToMember( ui->bridgeComboBox->currentText(), rosData, ROSPPPProfile, setBridgeName, "nombre del bridge" ) &&
			fancySetTextToMember( ui->localAddressComboBox->currentText(), rosData, ROSPPPProfile, setLocalAddress, "local address" ) &&
			fancySetTextToMember( ui->remoteAddressComboBox->currentText(), rosData, ROSPPPProfile, setRemoteAddress, "remote address" ) &&
			ui->speedRateLimits->getROSRateLimit( static_cast<ROSPPPProfile&>(rosData).rateLimit() );
}
