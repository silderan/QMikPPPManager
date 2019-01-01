#include "DlgROSAPIUsers.h"
#include "ui_DlgROSAPIUsers.h"

#include <QTableWidgetItem>

#include "Widgets/QROSAPIUserLevelComboBox.h"
#include "Widgets/QROSAPIUserTableWidget.h"

DlgROSAPIUsers::DlgROSAPIUsers(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgROSAPIUsers)
{
	ui->setupUi(this);
	// Forward signal.
	connect( ui->usersTable, SIGNAL(userModified(ROSAPIUser,QRouterIDMap)), this, SIGNAL(userModified(ROSAPIUser,QRouterIDMap)) );
}

DlgROSAPIUsers::~DlgROSAPIUsers()
{
	delete ui;
}

void DlgROSAPIUsers::onUserDataReceived(const ROSAPIUser &user)
{
	if( user.deleting() )
		ui->usersTable->removeUser(user);
	else
		ui->usersTable->addUser(user);
}

void DlgROSAPIUsers::onUsersGroupDataReceived(const ROSAPIUsersGroup &group)
{
	ui->groupsTable->addGroup(group);
}
