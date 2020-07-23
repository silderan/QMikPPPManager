/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "QMikPPPManager.h"
#include "ui_QMikPPPManager.h"

#include "Utils/QPPPLogger.h"
#include "Utils/Utils.h"

#include "Dialogs/DlgConfiguracion.h"
#include "Dialogs/DlgLookConfig.h"
#include "Dialogs/DlgPPPLogViewer.h"
#include "Dialogs/DlgUserThroughput.h"
#include "Dialogs/DlgServiceScheduler.h"
#include "Dialogs/DlgVoIPData.h"

#include "ConfigData/VoIPData.h"

#include "Utils/Utils.h"


QMikPPPManager::QMikPPPManager(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::QMikPPPManager)
	, dlgCnfgConnect(Q_NULLPTR)
{
	ui->setupUi(this);

#ifdef UNIT_TESTS_UTILS
	Utils::UTests();
#endif

	gGlobalConfig.loadGlobalData();
	gGlobalConfig.loadLocalUserData();
	gGlobalConfig.loadGlobalProtectedData();

	updateConfig();

	connect( &multiConnectionManager, &ROSMultiConnectManager::statusInfo,	this, &QMikPPPManager::setStatusText );

	connect( &multiConnectionManager, &ROSMultiConnectManager::comError,	this, &QMikPPPManager::onComError );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosError,	this, &QMikPPPManager::onROSError );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosModReply, this, &QMikPPPManager::onROSModReply );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosDelReply, this, &QMikPPPManager::onROSDelReply );
	connect( &multiConnectionManager, &ROSMultiConnectManager::rosDone,		this, &QMikPPPManager::onROSDone );


	connect( &multiConnectionManager, &ROSMultiConnectManager::routerConnected,		this, &QMikPPPManager::onRouterConnected );
	connect( &multiConnectionManager, &ROSMultiConnectManager::allRoutersConected,	this, &QMikPPPManager::onAllRoutersConnected );

	connect( &multiConnectionManager, &ROSMultiConnectManager::routerDisconnected,		this, &QMikPPPManager::onRouterDisconnected );
	connect( &multiConnectionManager, &ROSMultiConnectManager::allRoutersDisconected,	this, &QMikPPPManager::onAllRoutersDisconnected );

	connect( &multiConnectionManager, &ROSMultiConnectManager::logued, this, &QMikPPPManager::onLogued );

	connect( ui->usersTable, &QROSSecretTableWidget::editPPPUser, this, &QMikPPPManager::onPPPEditRequest );
	connect( ui->usersTable, &QROSSecretTableWidget::showUserTraffic, this, &QMikPPPManager::onShowUserTraffic );

	ui->fieldFilterComboBox->addItems( QStringList()
									   << tr("Cualquier dato")
									   << tr("Múltiples usuarios")
									   << tr("Múltiples CCliente")
									   << ui->usersTable->columnsNames() );
	ui->fieldFilterComboBox->setCurrentIndex(0);

	ui->serviceStateFilterComboBox->addItems( QStringList()
											  << tr("Cualquier estado del servicio")
											  << tr("Activos")
											  << tr("Cancelados")
											  << ServiceState::serviceStateNameList() );
	ui->serviceStateFilterComboBox->setCurrentIndex(0);

	ui->VoIPFilterComboBox->addItems( QStringList()
									  << tr("Sin VoIP")
									  << tr("Con y sin VoIP")
									  << tr("Con VoIP") );
	ui->VoIPFilterComboBox->setCurrentIndex(1);

	ui->portFilterComboBox->addItems( QStringList()
									  << tr("Sin puertos")
									  << tr("Con y sin puertos")
									  << tr("Con puertos") );
	ui->portFilterComboBox->setCurrentIndex(1);

	ui->staticIpFilterComboBox->addItems( QStringList()
									  << tr("Sin IP fija")
									  << tr("Con y sin IP fija")
									  << tr("Con IP Fija") );
	ui->staticIpFilterComboBox->setCurrentIndex(1);

	ui->serviceTypeComboBox->addItems( QStringList()
									   << tr("Todos los tipos")
									   << ServiceInfo::serviceTypeNameList() );
	ui->serviceTypeComboBox->setCurrentIndex(0);

	connect( ui->fieldFilterComboBox, SIGNAL(currentIndexChanged(QString)),			this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->serviceStateFilterComboBox, SIGNAL(currentIndexChanged(QString)),	this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->textFilterLineEdit, SIGNAL(textChanged(QString)),					this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->VoIPFilterComboBox, SIGNAL(currentIndexChanged(QString)),			this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->portFilterComboBox, SIGNAL(currentIndexChanged(QString)),			this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->staticIpFilterComboBox, SIGNAL(currentIndexChanged(QString)),		this, SLOT(applyUsersRowFilter(QString)) );
	connect( ui->serviceTypeComboBox, SIGNAL(currentIndexChanged(QString)),			this, SLOT(applyUsersRowFilter(QString)) );

	onAllRoutersDisconnected();
	ui->usersTable->horizontalHeader()->setFixedHeight(20);

	setUserLevel(ROSAPIUser::Level::NoRights);
	if( gGlobalConfig.connectInfoList().isEmpty() )
	{
		Utils::raiseInfo( this, tr("Parece que es la primera vez que se inicia el programa en este entorno.\n"
								   "Configura el acceso a los routers.") );
		on_connectionConfigButton_clicked();
	}
	ui->connectButton->setDisabled( gGlobalConfig.connectInfoList().isEmpty() );

	gVoipData.load();
}

void QMikPPPManager::applyUsersRowFilter(QString)
{
	int serviceStateType = ui->serviceStateFilterComboBox->currentIndex() - (ui->serviceStateFilterComboBox->count() - ServiceState::serviceStateNameList().count());
	int columnIndex = ui->fieldFilterComboBox->currentIndex() - (ui->fieldFilterComboBox->count() - QROSSecretTableWidget::Columns::TotalColumns);

	ui->usersTable->filter( ui->textFilterLineEdit->text(),
							static_cast<QROSSecretTableWidget::Columns>(columnIndex),
							static_cast<ServiceState::Type>(serviceStateType),
							static_cast<ServiceInfo::ServiceType>(ui->serviceTypeComboBox->currentIndex() - 1),
							ui->VoIPFilterComboBox->currentIndex()-1,
							ui->portFilterComboBox->currentIndex()-1,
							ui->staticIpFilterComboBox->currentIndex()-1);
}

void QMikPPPManager::on_filterGroupBox_clicked(bool checked)
{
	ui->usersTable->applyFilter(checked);
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

void QMikPPPManager::setStatusText(const QString routerName, QString errorString)
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
	setStatusText( QString(), tr("Conectado a todos los routers.") );
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
	setStatusText( QString(), tr("Desconectado de todos los routers.") );
	ui->disconnectButton->setDisabled(true);

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->clear();

	ui->usersTable->clear();
}

void QMikPPPManager::onLogued(const QString &routerName)
{
	logService.setUserName( gGlobalConfig.userName() );

	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onLogued(routerName);

	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onLogued(routerName);
}

void QMikPPPManager::onComError(const QString &routerName, const QString &errorString)
{
	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onComError( routerName, errorString );

	setStatusText( routerName, errorString );
	Utils::raiseWarning( this, tr("Error reportado por la red, router o sistema para el router %1\n\n%2").arg(routerName, errorString) );
}

void QMikPPPManager::onROSError(const QString &routerName, const QString &errorString)
{
	if( dlgCnfgConnect != Q_NULLPTR )
		dlgCnfgConnect->onROSError( routerName, errorString );

	setStatusText( routerName, errorString );
	Utils::raiseWarning( this, tr("Error en el router %1:\n\n%2").arg(routerName, errorString) );
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
		setStatusText( routerName, tr("Usuarios API recibidos") );
		break;
	case DataTypeID::APIUsersGroup:	setStatusText( routerName, tr("Grupos de usuarios API recibidos") );break;
	case DataTypeID::PPPProfile:	setStatusText( routerName, tr("Perfiles PPP recibidos") );			break;
	case DataTypeID::Interface:		setStatusText( routerName, tr("Interfices recibidos") );			break;
	case DataTypeID::BridgePorts:	setStatusText( routerName, tr("Puertos de los bridges recibidos") );break;
	case DataTypeID::IPAddress:		setStatusText( routerName, tr("Direccioens IP recibidas") );		break;
	case DataTypeID::IPPool:		setStatusText( routerName, tr("Pools de direcciones recibidas") );	break;
	case DataTypeID::PPPSecret:		setStatusText( routerName, tr("Recibidos los datos de usuarios") );	break;
	case DataTypeID::PPPActive:		setStatusText( routerName, tr("Usuarios activos recibidos") );		break;
	case DataTypeID::TotalIDs:		break;
	}
	foreach( QDlgMultiDataBase *dlg, m_dialogList )
		dlg->onROSDone(routerName, dataTypeID);
	ui->usersTable->onROSDone(routerName, dataTypeID);
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
//		ui->schedulerButton->setHidden(true);
		break;
	case ROSAPIUser::Level::Comercial:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(true);
		ui->schedulerButton->setHidden(true);
		return;
	case ROSAPIUser::Level::Instalator:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(true);
		ui->schedulerButton->setHidden(true);
		break;
	case ROSAPIUser::Level::Administrator:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(true);
		ui->advancedConfigButton->setHidden(true);
		ui->pppProfilesButton->setHidden(true);
		ui->apiUsersButton->setHidden(true);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(false);
		ui->schedulerButton->setHidden(false);
		break;
	case ROSAPIUser::Level::Supervisor:
		ui->usersTable->setEnabled(true);
		ui->pppLogsButton->setHidden(false);
		ui->advancedConfigButton->setHidden(false);
		ui->pppProfilesButton->setHidden(false);
		ui->apiUsersButton->setHidden(false);
		ui->addUserButton->setHidden(false);
		ui->pppLogsButton->setHidden(false);
		ui->schedulerButton->setHidden(false);
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
#ifdef USE_RADIUS
		multiConnectionManager.setRadiusConnection(gGlobalConfig.radiusConnInfo(), gGlobalConfig.radiusDataBase());
#endif
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

void QMikPPPManager::onShowUserTraffic(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive)
{
	new DlgUserThroughput(multiConnectionManager, pppActive, this);
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

void QMikPPPManager::on_schedulerButton_clicked()
{
	DlgServiceScheduler dlg(multiConnectionManager, *ui->usersTable, this);
	dlg.exec();
}

void QMikPPPManager::on_voipButton_clicked()
{
	DlgVoIPData dlg(*ui->usersTable, this);
	dlg.exec();
}
