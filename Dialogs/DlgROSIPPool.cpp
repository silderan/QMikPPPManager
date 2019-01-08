#include "DlgROSIPPool.h"
#include "ui_DlgROSIPPool.h"

DlgROSIPPool::DlgROSIPPool(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgROSIPPool)
{
	ui->setupUi(this);
}

DlgROSIPPool::~DlgROSIPPool()
{
	delete ui;
}

void DlgROSIPPool::on_closeButton_clicked()
{

}
