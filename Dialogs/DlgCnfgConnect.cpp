#include "DlgCnfgConnect.h"
#include "ui_DlgCnfgConnect.h"

#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegExp>

#include "Utils/IPv4Range.h"
#include "QTableWidgetItem"
#include "ConfigData/QConfigData.h"

#define WARNING(_t)	(QMessageBox::warning(this, objectName(), _t) )

DlgCnfgConnect::DlgCnfgConnect(QWidget *parent, ROSMultiConnectManager &rosMultiConnectManager) :
    QDialog(parent),
	ui(new Ui::DlgCnfgConnect),
	m_rosMultiConnectManager(rosMultiConnectManager)
{
    ui->setupUi(this);

	ui->hostsTable->setColumnCount(3);
	ui->hostsTable->setHorizontalHeaderLabels(QStringList() << "IP Servidor" << "Puerto API" << "Estado" );

	setup();
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
		const ConnectInfo &conInfo = gGlobalConfig.connectInfoList().at(row);
		const QString routerName = conInfo.routerName();
		ROSPPPoEManager *rosPPPoEManager = multiConnectionManager.rosPppoeManager(routerName);
		QString routerState;
		if( rosPPPoEManager != Q_NULLPTR )
		{
			if( rosPPPoEManager->isLoged() )
				routerState = tr("Logado al router");
			else
			if( rosPPPoEManager->isDisconnected() )
				routerState = tr("Desconectado");
			else
				routerState = tr("Desconocido");
		}
		else
			routerState = tr("Desconectado");
		addRow( row, conInfo.hostIPv4().toString(), conInfo.hostPort(), routerState );

	}
	// Remove the extra rows.
	while( ui->hostsTable->rowCount() > row )
		ui->hostsTable->removeRow(row);
}

void DlgCnfgConnect::addRow(int row, const QString &hostAddr, quint16 hostPort, const QString &routerState)
{
	if( row == -1 )	// Add always a new row.
		row = ui->hostsTable->rowCount();
	while( row >= ui->hostsTable->rowCount() )
	{
		ui->hostsTable->insertRow(row);
		QSpinBox *portSpinBox = new QSpinBox();
		portSpinBox->setMinimum(1);
		portSpinBox->setMaximum(0xffff);

		ui->hostsTable->setItem( row, AddressCol, new QTableWidgetItem() );
		ui->hostsTable->setCellWidget( row, PortCol, portSpinBox );
		ui->hostsTable->setItem( row, StatusCol, new QTableWidgetItem( routerState ) );
	}
	ui->hostsTable->item(row, AddressCol)->setText( hostAddr );
	static_cast<QSpinBox*>(ui->hostsTable->cellWidget(row, PortCol))->setValue(hostPort);
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
		gGlobalConfig.connectInfoList()[row].setHostIPv4( IPv4(ui->hostsTable->item(row, 0)->text()) );
		gGlobalConfig.connectInfoList()[row].setHostPort(static_cast<quint16>(static_cast<QSpinBox*>(ui->hostsTable->cellWidget(row, 1))->value()));
		// For now, username is taken globally for all routers.
		// This way, a username that can connect to the router is used as name in logging.
		// As connection info is stored globally for all users, this info must not be used. So, clear it.
		gGlobalConfig.connectInfoList()[row].setUserName("");
		gGlobalConfig.connectInfoList()[row].setUserPass("");
	}
	while( gGlobalConfig.connectInfoList().count() > row )
		gGlobalConfig.connectInfoList().removeLast();
}

void DlgCnfgConnect::setRouterStatus(const QString &routerName, const QString &errorString)
{
	// There is no need to ompitize it because:
	// 1. There are usually few routers configured.
	// 2. Status changes are not quite often.
	for( int i = 0; i < gGlobalConfig.connectInfoList().count(); ++i )
	{
		if( routerName.isEmpty() || (gGlobalConfig.connectInfoList().at(i).routerName() == routerName) )
		{
			for( int row = 0; row < ui->hostsTable->rowCount(); ++row )
				if( ui->hostsTable->item(row, AddressCol)->text() == gGlobalConfig.connectInfoList().at(i).hostIPv4().toString() )
					ui->hostsTable->item(row, StatusCol)->setText(errorString);
		}
	}
}

void DlgCnfgConnect::on_acceptButton_clicked()
{
	if( checkData() )
	{
		copyDataToGlobalConfig();
		gGlobalConfig.saveGlobalData();
		gGlobalConfig.saveLocalUserData();
		accept();
	}
}

void DlgCnfgConnect::on_cancelButton_clicked()
{
	reject();
}

void DlgCnfgConnect::onComError(const QString &errorString, const QString &routerName)
{
	setRouterStatus(routerName, errorString);
}

void DlgCnfgConnect::onROSError(const QString &routerName, const QString &errorString)
{
	setRouterStatus(routerName, errorString);
}

void DlgCnfgConnect::onRouterConnected(const QString &routerName)
{
	setRouterStatus( routerName, tr("Conectado") );
}

void DlgCnfgConnect::onRouterDisconnected(const QString &routerName)
{
	setRouterStatus(routerName, tr("Desconectado") );
}

void DlgCnfgConnect::onLogued(const QString &routerName)
{
	setRouterStatus(routerName, tr("Logado") );
}

void DlgCnfgConnect::onConfigChanged()
{
	// TODO
}
