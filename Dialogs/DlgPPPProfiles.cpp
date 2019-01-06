#include "DlgPPPProfiles.h"
#include "ui_DlgPPPProfiles.h"

DlgPPPProfiles::DlgPPPProfiles(QWidget *parent) :
	QDialog(parent), ui(new Ui::DlgPPPProfiles)
{
	ui->setupUi(this);

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

void DlgPPPProfiles::onPPPProfileDataReceived(const ROSPPPProfile &profileData)
{
	ui->profilesTable->onRemoteDataReceived(profileData);
}
