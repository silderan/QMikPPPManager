#include "DlgNewROSAPIUser.h"
#include "ui_DlgROSAPIUser.h"

DlgNewROSAPIUser::DlgNewROSAPIUser(QWidget *papi)
	: QNewROSDataDialogBase(papi)
	, ui(new Ui::DlgROSAPIUser)
{
	ui->setupUi(this);
	connect( ui->acceptButton, &QAbstractButton::clicked, this, &QNewROSDataDialogBase::tryAccept<ROSAPIUser> );
}

DlgNewROSAPIUser::~DlgNewROSAPIUser()
{
	delete ui;
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
	return	fancySetTextToMember( ui->grupNameComboBox->currentGroupName(), rosData, ROSAPIUser, setGroupName, tr("Nombre del grupo de usuarios") ) &&
			fancySetTextToMember( ui->userNameLineEdit->text(), rosData, ROSAPIUser, setUserName, tr("Nombre de usuario") ) &&
			fancySetTextToMember( ui->userPassLineEdit->text(), rosData, ROSAPIUser, setUserPass, tr("Contraseña de usuario") ) &&
			static_cast<ROSAPIUser&>(rosData).setUserLevel( ui->userLevelComboBox->currentLevel() );
}
