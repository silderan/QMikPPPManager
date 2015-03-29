#include "QMikPPPManager.h"
#include "ui_QMikPPPManager.h"

QMikPPPManager::QMikPPPManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QMikPPPManager)
{
	ui->setupUi(this);
}

QMikPPPManager::~QMikPPPManager()
{
	delete ui;
}
