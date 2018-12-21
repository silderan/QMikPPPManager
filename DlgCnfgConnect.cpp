#include "DlgCnfgConnect.h"
#include "ui_DlgCnfgConnect.h"

#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegExp>

#include "QTableWidgetItem"
#include "QConfigData.h"
#include "IPv4Range.h"

#define WARNING(_t)	(QMessageBox::warning(this, objectName(), _t) )

DlgCnfgConnect::DlgCnfgConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCnfgConnect)
{
    ui->setupUi(this);
	ui->hostsTable->setColumnCount(3);
	ui->hostsTable->setHorizontalHeaderLabels(QStringList() << "IP Servidor" << "Puerto API" << "Estado" );
	connect( ui->addButton, SIGNAL(clicked()), this, SLOT(addRow()) );
	connect( ui->delButton, SIGNAL(clicked()), this, SLOT(removeCurrentRow()) );
}

DlgCnfgConnect::~DlgCnfgConnect()
{
	delete ui;
}

void DlgCnfgConnect::setup()
{
	ui->userLineEdit->setText(gGlobalConfig.userName());
	ui->passLineEdit->setText(gGlobalConfig.userPass());

	while( ui->hostsTable->rowCount() )
		ui->hostsTable->removeRow(0);

	int row;
	for( row = 0; row < gGlobalConfig.connectInfoList().count(); ++row )
	{
		addRow(row,
			   gGlobalConfig.connectInfoList().at(row).m_hostIPv4.toString(),
			   gGlobalConfig.connectInfoList().at(row).m_hostPort );
	}
	// Remove the extra rows.
	while( ui->hostsTable->rowCount() > row )
		ui->hostsTable->removeRow(row);
}

void DlgCnfgConnect::addRow(int row, const QString &hostAddr, quint16 hostPort)
{
	if( row == -1 )	// Add always a new row.
		row = ui->hostsTable->rowCount();
	while( row >= ui->hostsTable->rowCount() )
	{
		ui->hostsTable->insertRow(row);
		QSpinBox *portSpinBox = new QSpinBox();
		portSpinBox->setMinimum(1);
		portSpinBox->setMaximum(0xffff);

		ui->hostsTable->setItem( row, 0, new QTableWidgetItem() );
		ui->hostsTable->setCellWidget( row, 1, portSpinBox );
		ui->hostsTable->setItem( row, 2, new QTableWidgetItem() );
	}
	ui->hostsTable->item(row, 0)->setText( hostAddr );
	static_cast<QSpinBox*>(ui->hostsTable->cellWidget(row, 1))->setValue(hostPort);
}

void DlgCnfgConnect::removeCurrentRow()
{
	ui->hostsTable->removeRow(ui->hostsTable->currentRow());
}

bool DlgCnfgConnect::checkData()
{
	if( ui->userLineEdit->text().isEmpty() )
		WARNING( tr("Falta el nombre de usuario.") );
	else
	if( ui->userLineEdit->text().contains( QRegExp("\\W") ) )
		WARNING( tr("El nombre de usuario no puede contener espacios en blanco ni caracteres especiales ni letras con tildes.") );
	else
	if( ui->passLineEdit->text().isEmpty() )
		WARNING( tr("Falta la contraseña de acceso a los routers.") );
	else
	if( ui->passLineEdit->text().contains( QRegExp("[=\\s]") ) )
		WARNING( tr("La contraseña no puede contener caracteres en blanco ni el caracter '='") );
	else
	{
		for( int row = 0; row < ui->hostsTable->rowCount(); ++row )
		{
			if( !IPv4(ui->hostsTable->item(row, 0)->text()).isValid() )
			{
				WARNING( tr("La IP del router configurado en la linea %1 no es válida").arg(row+1) );
				return false;
			}
		}
		return true;
	}
	return false;
}

void DlgCnfgConnect::copyDataToGlobalConfig()
{
	gGlobalConfig.setUserName( ui->userLineEdit->text() );
	gGlobalConfig.setUserPass( ui->passLineEdit->text() );

	int row;
	for( row = 0; row < ui->hostsTable->rowCount(); ++row )
	{
		if( gGlobalConfig.connectInfoList().count() <= row )
			gGlobalConfig.connectInfoList().append( ConnectInfo() );
		gGlobalConfig.connectInfoList()[row].m_hostIPv4 = ui->hostsTable->item(row, 0)->text();
		gGlobalConfig.connectInfoList()[row].m_hostPort = static_cast<quint16>(static_cast<QSpinBox*>(ui->hostsTable->cellWidget(row, 1))->value());
		// For now, username is taken globally for all routers.
		// This way, a username that can connect to the router is used as name in logging.
		// As connection info is stored globally for all users, this info must not be used. So, clear it.
		gGlobalConfig.connectInfoList()[row].m_uname.clear();
		gGlobalConfig.connectInfoList()[row].m_upass.clear();
	}
	while( gGlobalConfig.connectInfoList().count() > row )
		gGlobalConfig.connectInfoList().removeLast();
}

void DlgCnfgConnect::on_connectButton_clicked()
{
	copyDataToGlobalConfig();
	gGlobalConfig.saveGlobalData();
	gGlobalConfig.saveLocalUserData();
	emit globalConfigChanged();

	if( gGlobalConfig.connectInfoList().count() )
		emit connectToHosts();
	else
		WARNING( tr("No has configurado ningún host para poderte conectar") );
}

void DlgCnfgConnect::on_acceptButton_clicked()
{
	if( checkData() )
	{
		copyDataToGlobalConfig();
		gGlobalConfig.saveGlobalData();
		gGlobalConfig.saveLocalUserData();
		emit globalConfigChanged();
		accept();
	}
}

void DlgCnfgConnect::on_cancelButton_clicked()
{
	reject();
}

void DlgCnfgConnect::show()
{
	setup();
	QDialog::show();
}
