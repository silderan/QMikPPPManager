#include "DlgROSAPIUsers.h"
#include "ui_DlgROSAPIUsers.h"

#include <QTableWidgetItem>

#include "Widgets/QROSAPIUserLevelComboBox.h"
#include "Widgets/QROSAPIUserTableWidget.h"

DlgROSAPIUsers::DlgROSAPIUsers(QWidget *parent, ROSMultiConnectManager &rosMultiConnectManager) :
	DlgDataBase(parent, rosMultiConnectManager), ui(new Ui::DlgROSAPIUsers)
{
	ui->setupUi(this);

	updateMultipleData( DataTypeIDList() << DataTypeID::APIUser << DataTypeID::APIUsersGroup );

	// Forward signals.
	connect( ui->usersTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)) );
	connect( ui->groupsTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)) );

	connect( ui->delUserButton, SIGNAL(clicked()), ui->usersTable, SLOT(removeCurrentData()) );
	connect( ui->delGroupButton, SIGNAL(clicked()), ui->groupsTable, SLOT(removeCurrentData()) );
}

DlgROSAPIUsers::~DlgROSAPIUsers()
{
	delete ui;
}

void DlgROSAPIUsers::clear()
{
	ui->groupsTable->setRowCount(0);
	ui->usersTable->setRowCount(0);
}

#include "Dialogs/DlgROSAPIUser.h"
void DlgROSAPIUsers::on_addUserButton_clicked()
{
	emit dataModified( DlgROSAPIUser::getRosAPIUser(this), QRouterIDMap() );
}

void DlgROSAPIUsers::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::APIUser )
		ui->usersTable->onROSModReply(rosData);
	else
	if( rosData.dataTypeID() == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSModReply(rosData);
}

void DlgROSAPIUsers::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	if( dataTypeID == DataTypeID::APIUser )
		ui->usersTable->onROSDelReply(routerName, rosObjectID);
	else
	if( dataTypeID == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSDelReply(routerName, rosObjectID);
}

void DlgROSAPIUsers::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	if( dataTypeID == DataTypeID::APIUser )
		ui->usersTable->onROSDone(routerName);
	else
	if( dataTypeID == DataTypeID::APIUsersGroup )
		ui->groupsTable->onROSDone(routerName);
}
