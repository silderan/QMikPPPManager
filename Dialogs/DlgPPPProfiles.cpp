#include "DlgPPPProfiles.h"
#include "ui_DlgPPPProfiles.h"

#include "DlgNewPPPProfile.h"

DlgPPPProfiles::DlgPPPProfiles(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi)
	: DlgDataBase(configData, rosMultiConnectManager, papi)
	, ui(new Ui::DlgPPPProfiles)
{
	ui->setupUi(this);

	updateMultipleData( DataTypeIDList() << DataTypeID::PPPProfile );

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
	DlgNewPPPProfile dlg(ROSPPPProfile(""), this);

	if( dlg.exec() == QDialog::Accepted )
		emit dataModified( dlg.rosPPPProfile(), QRouterIDMap() );
}
