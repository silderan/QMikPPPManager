/*
	Copyright 2015 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikAPI.

	QMikAPI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikAPI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikAPI.  If not,
	see <http://www.gnu.org/licenses/>.
 */

#include "QMikPPPManager.h"
#include "ui_QMikPPPManager.h"

#include <QMessageBox>
#include "Utils/QPPPLogger.h"

#include "Dialogs/DlgConfiguracion.h"
#include "Dialogs/DlgLookConfig.h"
#include "Dialogs/DlgPPPLogViewer.h"

#include "Utils/Utils.h"

QMikPPPManager::QMikPPPManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QMikPPPManager), dlgCnfgConnect(Q_NULLPTR)
{
	ui->setupUi(this);

#ifdef UNIT_TESTS_UTILS
	Utils::UTests();
#endif

	gGlobalConfig.loadGlobalData();
	gGlobalConfig.loadLocalUserData();
	gGlobalConfig.loadGlobalProtectedData();

	updateConfig();

	connect( &multiConnectionManager, &ROSMultiConnectManager::comError, this, &QMikPPPManager::onComError );

	connect( &multiConnectionManager, &ROSMultiConnectManager::rosError, this, &QMikPPPManager::onROSError );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosModReply, this, &QMikPPPManager::onROSModReply );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosDelReply, this, &QMikPPPManager::onROSDelReply );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosDone, this, &QMikPPPManager::onROSDone );

	connect( &multiConnectionManager, &ROSMultiConnectManager::statusInfo, this,&QMikPPPManager::setStatusText );

	connect( &multiConnectionManager, &ROSMultiConnectManager::routerConnected, this, &QMikPPPManager::onRouterConnected );
	connect( &multiConnectionManager, &ROSMultiConnectManager::allConected, this, &QMikPPPManager::onAllRoutersConnected );

	connect( &multiConnectionManager, &ROSMultiConnectManager::routerDisconnected, this, &QMikPPPManager::onRouterDisconnected );
	connect( &multiConnectionManager, &ROSMultiConnectManager::allDisconnected, this, &QMikPPPManager::onAllRoutersDisconnected );

	connect( &multiConnectionManager, &ROSMultiConnectManager::logued, this, &QMikPPPManager::onLogued );

	connect( ui->usersTable, &QROSSecretTableWidget::editPPPUser,this, &QMikPPPManager::onPPPEditRequest );

	ui->fieldFilterComboBox->addItem( "Cualquiera", 0 );
	ui->fieldFilterComboBox->addItem( "Nombre", FILTRO_NOMBRE );
	ui->fieldFilterComboBox->addItem( "Usuario", FILTRO_USUARIO );
	ui->fieldFilterComboBox->addItem( "Perfil", FILTRO_PERFIL );
	ui->fieldFilterComboBox->addItem( "Dirección", FILTRO_DIRECCION );
	ui->fieldFilterComboBox->addItem( "Población", FILTRO_POBLACION );
	ui->fieldFilterComboBox->addItem( "EMail", FILTRO_EMAIL );
	ui->fieldFilterComboBox->addItem( "Teléfonos", FILTRO_TELEFONOS );
	ui->fieldFilterComboBox->addItem( "IP", FILTRO_IP );
	ui->fieldFilterComboBox->addItem( "CCliente", FILTRO_CCLIENTE );

	ui->serciveStateFilterComboBox->blockSignals(true);
	ui->serciveStateFilterComboBox->addItems( QStringList()
											  << tr("Cualquier estado")
											  << tr("Activos")
											  << tr("Inactivos")
											  << ServiceState::serviceStateNameList() );
	ui->serciveStateFilterComboBox->setCurrentIndex( 0 ); // This sets the index to "any"
	ui->serciveStateFilterComboBox->blockSignals(false);

	onAllRoutersDisconnected();
	ui->usersTable->horizontalHeader()->setFixedHeight(20);

	setUserLevel(ROSAPIUser::Level::NoRights);
	if( gGlobalConfig.connectInfoList().isEmpty() )
	{
		Utils::raiseInfo( this, tr("Parece que es la primera vez que se inicia el programa en este entorno.\nConfigura el acceso a los routers.") );
		on_connectionConfigButton_clicked();
	}
	ui->connectButton->setDisabled(gGlobalConfig.connectInfoList().isEmpty());
}

QMikPPPManager::~QMikPPPManager()
{
	multiConnectionManager.disconnectHosts(true);

	if( isMaximized() )
		gGlobalConfig.setWindowMaximized();
	else
	{
		gGlobalConfig.setAnchoPantalla(width());
		gGlobalConfig.setAltoPantalla(height());
	}
	gGlobalConfig.saveLocalUserData();
	logService.shutdown();
	delete ui;
	ui = Q_NULLPTR;
}

void QMikPPPManager::updateConfig()
{
	if( gGlobalConfig.isWindowMaximized() )
		showMaximized();
	else
		resize(gGlobalConfig.anchoPantalla(), gGlobalConfig.altoPantalla());
	ui->usersTable->onConfigChanged();

	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onConfigChanged();

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onConfigChanged();
}

void QMikPPPManager::setStatusText(QString errorString, const QString routerName)
{
	if( ui )
	{
		if( routerName.isEmpty() )
			ui->statusBar->showMessage( errorString );
		else
			ui->statusBar->showMessage( QString("%1: %2").arg(routerName, errorString) );
	}
}

void QMikPPPManager::onRouterConnected(const QString &routerName)
{
	Q_UNUSED(routerName);
	ui->disconnectButton->setEnabled(true);
	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onRouterConnected(routerName);
}
void QMikPPPManager::onAllRoutersConnected()
{
	ui->connectButton->setDisabled(true);
}

void QMikPPPManager::onRouterDisconnected(const QString &routerName)
{
	Q_UNUSED(routerName);
	ui->connectButton->setEnabled(true);

	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onRouterDisconnected(routerName);

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onDisconnected(routerName);
}
void QMikPPPManager::onAllRoutersDisconnected()
{
	ui->disconnectButton->setDisabled(true);

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->clear();

	multiConnectionManager.clear();
	ui->usersTable->clear();
}

void QMikPPPManager::onLogued(const QString &routerName)
{
	logService.setUserName( gGlobalConfig.userName() );
//	ui->twUsuarios->clear();
//	ui->twUsuarios->setEnabled(true);

	// request api users to know the level privileges.
	multiConnectionManager.requestAll( routerName, DataTypeID::APIUser );
	// And all ppp users data.
	multiConnectionManager.requestAll( routerName, DataTypeID::PPPSecret );
	multiConnectionManager.requestAll( routerName, DataTypeID::PPPActive );


	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onLogued(routerName);

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onLogued(routerName);
}

void QMikPPPManager::onComError(const QString &errorString, const QString &routerName)
{
	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onComError(errorString, routerName);

	setStatusText(errorString, routerName);
	QMessageBox::warning(this,
						 objectName(),
						 tr("Error reportado por la red, router o sistema para el router %1\n\n%2").arg(routerName, errorString));
}

void QMikPPPManager::onROSError(const QString &routerName, const QString &errorString)
{
	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onROSError(errorString, routerName);

	setStatusText(errorString, routerName);
	QMessageBox::warning(this,
						 objectName(),
						 tr("Error en el router %1:\n\n%2").arg(routerName, errorString));
}

void QMikPPPManager::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::APIUser )
	{
		if( static_cast<const ROSAPIUser&>(rosData).userName() == gGlobalConfig.userName() )
			setUserLevel(static_cast<const ROSAPIUser&>(rosData).userLevel());
	}
	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onROSModReply(rosData);
	ui->usersTable->onROSModReply(rosData);
}

void QMikPPPManager::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onROSDelReply(routerName, dataTypeID, rosObjectID);
	ui->usersTable->onROSDelReply(routerName, dataTypeID, rosObjectID);
}

void QMikPPPManager::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	switch( dataTypeID )
	{
	case DataTypeID::ErrorTypeID:	break;
	case DataTypeID::APIUser:
		checkAPISupervisor();
		setStatusText( tr("Usuarios API recibidos"), routerName );
		break;
	case DataTypeID::APIUsersGroup:	setStatusText( tr("Grupos de usuarios API recibidos"), routerName );break;
	case DataTypeID::PPPProfile:	setStatusText( tr("Perfiles PPP recibidos"), routerName );			break;
	case DataTypeID::Interface:		setStatusText( tr("Interfices recibidos"), routerName );			break;
	case DataTypeID::BridgePorts:	setStatusText( tr("Puertos de los bridges recibidos"), routerName );break;
	case DataTypeID::IPAddress:		setStatusText( tr("Direccioens IP recibidas"), routerName );		break;
	case DataTypeID::IPPool:		setStatusText( tr("Pools de direcciones recibidas"), routerName );	break;
	case DataTypeID::PPPSecret:		setStatusText( tr("Recibidos los datos de usuarios"), routerName );	break;
	case DataTypeID::PPPActive:		setStatusText( tr("Usuarios activos recibidos"), routerName );		break;
	case DataTypeID::TotalIDs:		break;
	}
	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onROSDone(routerName, dataTypeID);
	ui->usersTable->onROSDone(routerName, dataTypeID);
}

void QMikPPPManager::pideUsuarios(const QString &routerName)
{
	ROS::QSentence s("/ppp/secret/getall");
	s.setTag( gGlobalConfig.tagSecret );
	s.addQuery("#|");
	multiConnectionManager.sendSentence( routerName, s );

	s.setCommand("/ppp/secret/listen");
	s.setTag( gGlobalConfig.tagLSecret );
	multiConnectionManager.sendSentence( routerName, s );
}

void QMikPPPManager::pideActivos(const QString &routerName)
{
	multiConnectionManager.sendSentence( routerName, "/ppp/active/getall", gGlobalConfig.tagActivo );
}

void QMikPPPManager::pideCambios(const QString &routerName)
{
	multiConnectionManager.sendSentence( routerName, "/ppp/active/listen", gGlobalConfig.tagLActivo );
}

void QMikPPPManager::reiniciaConexionRemota(QSecretData *sd)
{
	// TODO: To do so, need to know the router where the pppoe user is loged.
//	if( !sd->sesionID().isEmpty() )
//	{
//		ROS::QSentence s("/ppp/active/remove");
//		s.setID(sd->sesionID());
//		s.setTag("ReconnectClient");
//		mktAPI.sendSentence(s);
//	}
}


void QMikPPPManager::filtraFilas()
{
	QROSSecretTableWidget::FilterStates fs;
	fs.m_bits = ui->fieldFilterComboBox->currentData().toInt();
	ServiceState::Type st = static_cast<ServiceState::Type>(ui->serciveStateFilterComboBox->currentIndex() - ServiceState::serviceStateNameList().count());

	ui->usersTable->filter( ui->textFilterLineEdit->text(), fs, st );
}

// Comprueba si el código cliente es válido con los siguiente criterios.
// Es un valor positivo.
// El código de cliente no corresponde a otro cliente (se pregunta qué hacer en este caso)
bool QMikPPPManager::codigoClienteValido(const QString &code, const QSecretData *sdOri)
{
//	QSecretData *sd;
//	if( code.toInt() <= 0 )
//	{
//		QMessageBox::warning(this, tr("Código de cliente"), tr("El código de cliente debe ser un número mayor que 0") );
//		return false;
//	}
//	if( code.toInt() > 99999 )
//	{
//		QMessageBox::warning(this, tr("Código de cliente"), tr("El código de cliente debe ser un número positivo menor que 99999") );
//		return false;
//	}

//	if( ((sd = ui->twUsuarios->secrets().findDataByClientCode(code, sdOri)) != Q_NULLPTR) &&
//		(QMessageBox::question(this, tr("Código de cliente"), tr("El código de cliente %1 corresponde a %2 y quieres asociarlo a %3.\n¿Es correcto?")
//							  .arg(code)
//							  .arg(sd->usuario())
//							  .arg(sdOri->nombre()), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) )
//			return false;
	return true;
}

bool QMikPPPManager::checkRouterUsersIntegrity() const
{
	// TODO Comprobar que todos los usuarios que pueden logarse al router están en todos los routers por igual.
	return true;
}

void QMikPPPManager::onAllROSAPIUsersReceived()
{
//	if( (grupo.compare("full") == 0) || (grupo.compare("Supervisores") == 0) )
//		setNivelUsuario(QConfigData::Supervisor);
//	else
//	if( grupo.compare("Instaladores", Qt::CaseInsensitive) == 0 )
//		setNivelUsuario(QConfigData::Instalador);
//	else
//	if( grupo.compare("Administradores", Qt::CaseInsensitive) == 0 )
//		setNivelUsuario(QConfigData::Administrador);
//	else
//	if( grupo.compare("Comerciales", Qt::CaseInsensitive) == 0 )
//	{
//		setNivelUsuario(QConfigData::Comercial);
//	}
//	else
//	{
//		QString info = tr("Usuario %1 pertenece al grupo %2 y no tiene permisos para hacer nada.").arg(nombre, grupo);
//		setNivelUsuario(QConfigData::SinPermisos);
//		setStatusText(routerName, info);
//		QMessageBox::warning(Q_NULLPTR, tr("Información de usuario"), info);
//	}
	//	this->setWindowTitle(QString("%1 - %2 [%4]").arg("Mikrotik PPP Manager", nombre, grupo));
}

void QMikPPPManager::updateGUIAccess()
{
	switch( gGlobalConfig.userLevel() )
	{
	case ROSAPIUser::Level::NoRights:
		ui->usersTable->setEnabled(false);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(true);
		ui->pppLogsButton->setHidden(true);
		break;
	case ROSAPIUser::Level::Comercial:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(true);
		return;
	case ROSAPIUser::Level::Instalator:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(true);
		break;
	case ROSAPIUser::Level::Administrator:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(false);
		break;
	case ROSAPIUser::Level::Supervisor:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(false);
		ui->advancedConfigButton->setHidden(false);
		ui->pppProfilesButton->setHidden(false);
		ui->apiUsersButton->setHidden(false);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(false);
		break;
	}
}

void QMikPPPManager::setUserLevel(ROSAPIUser::Level userLevel)
{
	gGlobalConfig.setUserLevel(userLevel);
	updateGUIAccess();
	updateConfig();
}

void QMikPPPManager::checkAPISupervisor()
{
	if( multiConnectionManager.allDone(DataTypeID::APIUser) )
	{
		foreach( ROSDataBase *rosData, multiConnectionManager.rosDataList(DataTypeID::APIUser) )
		{
			if( static_cast<ROSAPIUser*>(rosData)->userLevel() == ROSAPIUser::Supervisor )
				return;
		}
		ui->apiUsersButton->setHidden(false);
		ui->apiUsersButton->setEnabled(true);
		// There is no supervisor.
		// Let's inform user and elevate it.
		Utils::raiseInfo( this, tr( "No hay ningún usuario supervisor configurado.\n"
									"Configura tu usuario para convertirte en supervisor o crea otro nuevo y conéctate con él para empezar configurar el sistema.\n"
									"Asegúrate antes de continuar de tener los permisos necesarios en los routers para poder modificar los usarios.") );
	}
}

void QMikPPPManager::on_leFiltro_textChanged(const QString &)
{
	filtraFilas();
}

void QMikPPPManager::on_cbFiltro_currentIndexChanged(int )
{
	filtraFilas();
}

void QMikPPPManager::on_connectButton_clicked()
{
#ifdef SIMULATE_ROS_INPUTS
	multiConnectionManager.simulateROSConnection();
#else
	if( gGlobalConfig.connectInfoList().isEmpty() )
	{
		Utils::raiseInfo( this, tr("No hay ninguna conexión configurada. Configúrala para poderte conectar.") );
		return;
	}
	// If all router are disconnected, copy data from config. Otherwise, just reconect.
	// That means that router config can be changed only when no connections is active.
	if( multiConnectionManager.areAllDisconnected() )
	{
		multiConnectionManager.clear();
		foreach( const ConnectInfo &c, gGlobalConfig.connectInfoList() )
		{
			multiConnectionManager.addROSConnection( c.routerName(),
									 c.hostIPv4().toString(),
									 c.hostPort(),
									 gGlobalConfig.userName(),
									 gGlobalConfig.userPass() );
		}
	}
	multiConnectionManager.connectHosts();
#endif
}

void QMikPPPManager::on_disconnectButton_clicked()
{
	multiConnectionManager.disconnectHosts(false);
}

void QMikPPPManager::on_localConfigButton_clicked()
{
	DlgLookConfig dlg(this);
	dlg.show();

	if( dlg.exec() )
	{
		updateConfig();
		gGlobalConfig.saveLocalUserData();
	}

	dlg.deleteLater();
}

void QMikPPPManager::on_connectionConfigButton_clicked()
{
	if( dlgCnfgConnect == Q_NULLPTR )
		dlgCnfgConnect = new DlgCnfgConnect(this, multiConnectionManager);

	dlgCnfgConnect->exec();
	ui->connectButton->setDisabled(gGlobalConfig.connectInfoList().isEmpty());
}

void QMikPPPManager::on_advancedConfigButton_clicked()
{
	DlgConfiguracion *dlgConfig = new DlgConfiguracion( gGlobalConfig.instaladores(),
														gGlobalConfig.comerciales(),
														gGlobalConfig.staticIPv4RangeListMap(),
														gGlobalConfig.clientProfileMap(),
														multiConnectionManager, this );

	if( dlgConfig->exec() == QDialog::Accepted )
	{
		gGlobalConfig.setInstaladores( dlgConfig->installerList() );
		gGlobalConfig.setComerciales( dlgConfig->comercialList() );
		gGlobalConfig.staticIPv4RangeListMap() = dlgConfig->staticIPv4RangeListMap();
		gGlobalConfig.clientProfileMap() = dlgConfig->clientProfileList();
		gGlobalConfig.saveGlobalProtectedData();
		foreach( QDlgMultiDataBase *dlg, m_dialogList )
			dlg->onConfigDataChanged();
		ui->usersTable->onConfigDataChanged();
	}

	dlgConfig->deleteLater();
}

void QMikPPPManager::on_apiUsersButton_clicked()
{
	static DlgROSAPIUsers *dlgROSAPIUsers;

	if( dlgROSAPIUsers == Q_NULLPTR )
	{
		dlgROSAPIUsers = new DlgROSAPIUsers( gGlobalConfig, multiConnectionManager, this );

		connect( dlgROSAPIUsers, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), &multiConnectionManager, SLOT(updateRemoteData(ROSDataBase,QRouterIDMap)) );

		m_dialogList.append(dlgROSAPIUsers);
	}

	dlgROSAPIUsers->show();
}

void QMikPPPManager::on_pppProfilesButton_clicked()
{
	static DlgPPPProfiles *dlgPPPProfiles;
	if( !dlgPPPProfiles )
	{
		dlgPPPProfiles = new DlgPPPProfiles( gGlobalConfig, multiConnectionManager, this );

		connect( dlgPPPProfiles, SIGNAL(dataModified(ROSDataBase,QRouterIDMap)), &multiConnectionManager, SLOT(updateRemoteData(ROSDataBase,QRouterIDMap)) );

		m_dialogList.append(dlgPPPProfiles);
	}

	dlgPPPProfiles->show();
}


void QMikPPPManager::onPPPEditRequest(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive)
{
	static DlgPPPUser *dlgPPPUser;

	if( !dlgPPPUser )
	{
		dlgPPPUser = new DlgPPPUser(gGlobalConfig, multiConnectionManager, this);
		m_dialogList.append(dlgPPPUser);
	}
	dlgPPPUser->onEditUserRequest(pppSecretMap, pppActive);
}

void QMikPPPManager::on_addUserButton_clicked()
{
	onPPPEditRequest( QPPPSecretMap(), ROSPPPActive("") );
}

void QMikPPPManager::on_pppLogsButton_clicked()
{
	DlgPPPLogViewer dlgPPPLogViewer( "", this );
	dlgPPPLogViewer.exec();
}
