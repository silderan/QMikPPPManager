#include "DlgROSAPIUsers.h"
#include "ui_DlgROSAPIUsers.h"

#include <QTableWidgetItem>

#include "Widgets/QROSAPIUserLevelComboBox.h"
#include "Widgets/QROSAPIUserTableWidget.h"

DlgROSAPIUsers::DlgROSAPIUsers(ROSMultiConnectManager *mktAPI, QWidget *parent) :
	QDialog(parent), ui(new Ui::DlgROSAPIUsers),
	m_mktAPI(mktAPI)
{
	ui->setupUi(this);

	ROSPPPoEManagerIterator it(mktAPI->rosPPPoEManagerMap());
	while( it.hasNext() )
	{
		it.next();
		foreach( const ROSAPIUser &user, it.value()->rosApiUserManager().rosDataList() )
		{
			ui->usersTable->onRemoteDataReceived(user);
		}
		foreach( const ROSAPIUsersGroup &group, it.value()->rosApiUsersGroupManager().rosDataList() )
		{
			ui->groupsTable->onRemoteDataReceived(group);
		}
	}

	// Forward signals.
	connect( ui->usersTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(userModified(ROSDataBase,QRouterIDMap)) );
	connect( ui->groupsTable, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), this, SIGNAL(groupModified(ROSDataBase,QRouterIDMap)) );

	connect( ui->delUserButton, SIGNAL(clicked()), ui->usersTable, SLOT(removeCurrentData()) );
	connect( ui->delGroupButton, SIGNAL(clicked()), ui->groupsTable, SLOT(removeCurrentData()) );

	connect( this, SIGNAL(userModified(ROSDataBase,QRouterIDMap)), m_mktAPI, SLOT(setROSAPIUserData(ROSDataBase,QRouterIDMap)) );
}

DlgROSAPIUsers::~DlgROSAPIUsers()
{
	delete ui;
}

void DlgROSAPIUsers::onUserDataReceived(const ROSAPIUser &user)
{
	ui->usersTable->onRemoteDataReceived(user);
}

void DlgROSAPIUsers::clear()
{
	ui->groupsTable->setRowCount(0);
	ui->usersTable->setRowCount(0);
}

void DlgROSAPIUsers::on_addUserButton_clicked()
{
	ui->usersTable->addEmptyData();
}

void DlgROSAPIUsers::onUsersGroupDataReceived(const ROSAPIUsersGroup &group)
{
	ui->groupsTable->onRemoteDataReceived(group);
}
