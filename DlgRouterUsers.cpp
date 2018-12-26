#include "DlgRouterUsers.h"
#include "ui_DlgRouterUsers.h"

DlgRouterUsers::DlgRouterUsers(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgRouterUsers)
{
	ui->setupUi(this);
}

DlgRouterUsers::~DlgRouterUsers()
{
	delete ui;
}

void DlgRouterUsers::on_addUserButton_clicked()
{

}

void DlgRouterUsers::on_delUserButton_clicked()
{

}

void DlgRouterUsers::on_acceptButton_clicked()
{

}
