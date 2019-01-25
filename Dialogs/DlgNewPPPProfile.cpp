#include "DlgNewPPPProfile.h"
#include "ui_DlgNewPPPProfile.h"

#include <QMessageBox>

DlgNewPPPProfile::DlgNewPPPProfile(const ROSPPPProfile &rosPPPProfile, QWidget *papi) :
	QDialog(papi),
	ui(new Ui::DlgNewPPPProfile)
{
	ui->setupUi(this);
	if( rosPPPProfile.profileName().isEmpty() )
		setWindowTitle( tr("Nuevo perfil PPP") );
	else
		setWindowTitle( tr("Modificando perfil %1").arg(rosPPPProfile.profileName()) );
	setup(rosPPPProfile);
}

DlgNewPPPProfile::~DlgNewPPPProfile()
{
	delete ui;
}

void DlgNewPPPProfile::raiseWarning(const QString &error, const QString &field) const
{
	if( field.isEmpty() )
		QMessageBox::warning( const_cast<DlgNewPPPProfile*>(this), tr("Perfil PPP"), error );
	else
		QMessageBox::warning( const_cast<DlgNewPPPProfile*>(this), tr("Perfil PPP"), tr("El campo %1, %2").arg(field, error) );
}

void DlgNewPPPProfile::setup(const ROSPPPProfile &rosPPPProfile)
{
	ui->pppProfileNameLineEdit->setText( rosPPPProfile.profileName() );
	ui->bridgeComboBox->setCurrentText( rosPPPProfile.bridgeName() );
	ui->localAddressComboBox->setCurrentText( rosPPPProfile.localAddress() );
	ui->remoteAddressComboBox->setCurrentText( rosPPPProfile.remoteAddress() );
	ui->speedRateLimits->setROSRateLimit( rosPPPProfile.rateLimit() );
}

ROSPPPProfile DlgNewPPPProfile::rosPPPProfile() const
{
	ROSPPPProfile rosPPPProfile("");
	if( !rosPPPProfile.setProfileName( ui->pppProfileNameLineEdit->text()) )
		raiseWarning( rosPPPProfile.lastError(), tr("Nombre del perfil") );
	else
	if( !rosPPPProfile.setBridgeName( ui->bridgeComboBox->currentText()) )
		raiseWarning( rosPPPProfile.lastError(), tr("bridge") );
	else
	if( !rosPPPProfile.setLocalAddress( ui->localAddressComboBox->currentText()) )
		raiseWarning( rosPPPProfile.lastError(), tr("Local Address") );
	else
	if( !rosPPPProfile.setRemoteAddress( ui->remoteAddressComboBox->currentText()) )
		raiseWarning( rosPPPProfile.lastError(), tr("Remote Address") );
	else
	if( !rosPPPProfile.setLocalAddress( ui->localAddressComboBox->currentText()) )
		raiseWarning( rosPPPProfile.lastError(), tr("Local Address") );
	else
	if( ui->speedRateLimits->getROSRateLimit(rosPPPProfile.rateLimit()) )
		return rosPPPProfile;
	return ROSPPPProfile("");
}

void DlgNewPPPProfile::on_acceptButton_clicked()
{
	if( !rosPPPProfile().profileName().isEmpty() )
		accept();
}
