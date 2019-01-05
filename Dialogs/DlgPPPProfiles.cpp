#include "DlgPPPProfiles.h"
#include "ui_DlgPPPProfiles.h"

DlgPPPProfiles::DlgPPPProfiles(ROSMultiConnectManager *mktAPI, QWidget *parent) :
	QDialog(parent), ui(new Ui::DlgPPPProfiles),
	m_mktAPI(mktAPI)
{
	ui->setupUi(this);
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

}
