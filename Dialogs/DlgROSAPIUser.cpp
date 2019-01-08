#include "DlgROSAPIUser.h"
#include "ui_DlgROSAPIUser.h"

DlgROSAPIUser::DlgROSAPIUser(QWidget *papi) :
	QDialog(papi),
	ui(new Ui::DlgROSAPIUser)
{
	ui->setupUi(this);
	ui->acceptButton->setDisabled(true);
	connect( ui->userNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)) );
	connect( ui->userPassLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)) );
}

DlgROSAPIUser::~DlgROSAPIUser()
{
	delete ui;
}

void DlgROSAPIUser::onTextChanged(QString txt)
{
	Q_UNUSED(txt);
	ui->acceptButton->setDisabled(
				ui->userNameLineEdit->text().trimmed().isEmpty() ||
				ui->userPassLineEdit->text().trimmed().isEmpty() );
}

void DlgROSAPIUser::on_acceptButton_clicked()
{
	accept();
}

ROSAPIUser DlgROSAPIUser::rosAPIUser()
{
	ROSAPIUser user( "" );
	user.setGroupName( ui->grupNameComboBox->currentGroupName() );
	user.setUserName( ui->userNameLineEdit->text() );
	user.setUserPass( ui->userPassLineEdit->text() );
	user.setUserLevel( ui->userLevelComboBox->currentLevel() );
	return user;
}

ROSAPIUser DlgROSAPIUser::getRosAPIUser(QWidget *papi)
{
	DlgROSAPIUser *dlg = new DlgROSAPIUser(papi);
	if( dlg->exec() == QDialog::Accepted )
	{
		ROSAPIUser user = dlg->rosAPIUser();
		dlg->deleteLater();
		return user;
	}
	return ROSAPIUser("");
}
