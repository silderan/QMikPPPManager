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
#include "Utils/QRegistro.h"

#include "Dialogs/DlgConfiguracion.h"
#include "Dialogs/DlgLookConfig.h"
#include "DlgExportar.h"
#include "DlgPortScan.h"

QMikPPPManager::QMikPPPManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QMikPPPManager),
	dlgNuevoUsuario(Q_NULLPTR), dlgROSAPIUsers(Q_NULLPTR), dlgPPPProfiles(Q_NULLPTR)
{
	ui->setupUi(this);

	ui->twUsuarios->setEnabled(false);

	gGlobalConfig.loadGlobalData();
	gGlobalConfig.loadLocalUserData();
	gGlobalConfig.loadGlobalProtectedData();

	updateConfig();

	connect( &mktAPI, SIGNAL(comError(QString,QString)), this, SLOT(onComError(QString,QString)) );

	connect( &mktAPI, SIGNAL(statusInfo(QString,QString)),this,SLOT(setStatusText(QString,QString)) );

	connect( &mktAPI, SIGNAL(routerConnected(QString)), this, SLOT(onRouterConnected(QString)) );
	connect( &mktAPI, SIGNAL(allConected()), this, SLOT(onAllRoutersConnected()) );

	connect( &mktAPI, SIGNAL(routerDisconnected(QString)), this, SLOT(onRouterDisconnected(QString)) );
	connect( &mktAPI, SIGNAL(allDisconnected()), this, SLOT(onAllRoutersDisconnected()) );

	connect( &mktAPI, SIGNAL(logued(QString)), this, SLOT(onLogued(QString)));

	connect( ui->twUsuarios, SIGNAL(datoModificado(QSecretDataModel::Columnas,QString,QString,bool*)),
			 this, SLOT(onDatoModificado(QSecretDataModel::Columnas,QString,QString,bool*)) );
	connect( ui->twUsuarios, SIGNAL(dobleClicUsuario(QSecretData)), this, SLOT(onDobleClicUsuario(QSecretData)) );
	connect( ui->twUsuarios, SIGNAL(clicUsuario(QSecretData)), this, SLOT(onClicUsuario(QSecretData)) );

	setNivelUsuario(QConfigData::SinPermisos);
	ui->cbFiltro->addItem( "Cualquiera", 0 );
	ui->cbFiltro->addItem( "Nombre", FILTRO_NOMBRE );
	ui->cbFiltro->addItem( "Usuario", FILTRO_USUARIO );
	ui->cbFiltro->addItem( "Perfil", FILTRO_PERFIL );
	ui->cbFiltro->addItem( "Dirección", FILTRO_DIRECCION );
	ui->cbFiltro->addItem( "Población", FILTRO_POBLACION );
	ui->cbFiltro->addItem( "EMail", FILTRO_EMAIL );
	ui->cbFiltro->addItem( "Teléfonos", FILTRO_TELEFONOS );
	ui->cbFiltro->addItem( "IP", FILTRO_IP );
	ui->cbFiltro->addItem( "CCliente", FILTRO_CCLIENTE );
	ui->cbFiltro->addItem( "Alta", FILTRO_ALTA );
	ui->cbFiltro->addItem( "Baja", FILTRO_BAJA );
	onAllRoutersDisconnected();
}

QMikPPPManager::~QMikPPPManager()
{
	mktAPI.disconnectHosts(true);

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
	QFont tableFont = ui->twUsuarios->font();
	tableFont.setPixelSize( gGlobalConfig.tableCellLook().m_fontSize );
	ui->twUsuarios->setFont( tableFont );
	ui->twUsuarios->verticalHeader()->setDefaultSectionSize( gGlobalConfig.tableCellLook().m_rowHeight );
	if( gGlobalConfig.isWindowMaximized() )
		this->showMaximized();
	else
		this->resize(gGlobalConfig.anchoPantalla(), gGlobalConfig.altoPantalla());
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
}
void QMikPPPManager::onAllRoutersConnected()
{
	ui->connectButton->setDisabled(true);
}

void QMikPPPManager::onRouterDisconnected(const QString &routerName)
{
	Q_UNUSED(routerName);
	ui->connectButton->setEnabled(true);
}
void QMikPPPManager::onAllRoutersDisconnected()
{
	ui->disconnectButton->setDisabled(true);
	if( dlgROSAPIUsers )
		dlgROSAPIUsers->clear();
	if( dlgPPPProfiles );
		dlgPPPProfiles->clear();
	mktAPI.clear();
}

void QMikPPPManager::onLogued(const QString &routerName)
{
	logService.setUserName( gGlobalConfig.userName() );
	ui->twUsuarios->clear();
	ui->twUsuarios->setEnabled(true);
	// request api users, grous and so on.
	requestROSAPIUsers(routerName);
	requestROSAPIUserGroups(routerName);
	requestPPPProfiles(routerName);
}

void QMikPPPManager::onComError(const QString &errorString, const QString &routerName)
{
	QMessageBox::warning(this,
						 objectName(),
						 tr("Error reportado por la red, router o sistema para el router %1\n\n%2").arg(routerName, errorString));
}

QString QMikPPPManager::createRouterName(const ConnectInfo &conInfo) const
{
	// Por ahora, el nombre de los routers será su dirección y puerto.
	return QString("%1:%2").arg(conInfo.m_hostIPv4.toString()).arg(conInfo.m_hostPort);
}

void QMikPPPManager::requestROSAPIUsers(const QString &routerName)
{
	mktAPI.rosPppoeManager(routerName)->requestAllAPIUsers( this,
									  SLOT(onOneAPIUsersReceived(QString,ROSAPIUser*)),
									  SLOT(onAllAPIUsersReceived(QString)),
									  SLOT(onAPIUsersErrorReceived(QString,QString)) );
}
void QMikPPPManager::onOneAPIUsersReceived(const QString &routerName, ROSAPIUser *apiUser)
{
	if( dlgROSAPIUsers )
		dlgROSAPIUsers->onUserDataReceived( *apiUser );
	setStatusText( tr("Recibido usuario %1. Tipo acceso: %2").arg(apiUser->userName(), apiUser->levelName()), routerName );
}
void QMikPPPManager::onAllAPIUsersReceived(const QString &routerName)
{
	setStatusText( tr("%1 usuarios API recibidos"), routerName );
}
void QMikPPPManager::onAPIUsersErrorReceived(const QString &routerName, const QString &errorString)
{
	QMessageBox::warning(this, objectName(), tr("Error al recibir los usuarios API\n%1:\n%2").arg(routerName, errorString) );
	setStatusText( tr("Error al recibir los usuarios API"), routerName );
}

void QMikPPPManager::requestROSAPIUserGroups(const QString &routerName)
{
	mktAPI.rosPppoeManager(routerName)->requestAllAPIUsersGroup( this,
										  SLOT(onOneAPIUsersGroupReceived(QString,ROSAPIUsersGroup*)),
										  SLOT(onAllAPIUsersGroupsReceived(QString)),
										  SLOT(onAPIUsersGroupsErrorReceived(QString,QString)) );
}
void QMikPPPManager::onOneAPIUsersGroupReceived(const QString &routerName, ROSAPIUsersGroup *apiUsersGroup)
{
	if( dlgROSAPIUsers )
		dlgROSAPIUsers->onUsersGroupDataReceived( *apiUsersGroup );
	setStatusText( tr("Recibido grupo %1. Tipo acceso: %2").arg(apiUsersGroup->groupName(), apiUsersGroup->policy().join(',')), routerName );
}
void QMikPPPManager::onAllAPIUsersGroupsReceived(const QString &routerName)
{
	setStatusText( tr("Grupos de usuarios API recibidos"), routerName );
}
void QMikPPPManager::onAPIUsersGroupsErrorReceived(const QString &routerName, const QString &errorString)
{
	QMessageBox::warning(this, objectName(), tr("Error al recibir los grupos de usuario API\n%1:\n%2").arg(routerName, errorString) );
	setStatusText( tr("Error al recibir los grupos de usuario API"), routerName );
}

void QMikPPPManager::requestPPPProfiles(const QString &routerName)
{
	mktAPI.rosPppoeManager(routerName)->requestAllPPPProfiles( this,
										  SLOT(onOnePPPProfileReceived(QString,ROSPPPProfile*)),
										  SLOT(onAllPPPProfilesReceived(QString)),
										  SLOT(onPPPProfilesErrorReceived(QString,QString)) );
}
void QMikPPPManager::onOnePPPProfileReceived(const QString &routerName, ROSPPPProfile *rosPPPProfile)
{
//	dlgPPPProfile.onUsersGroupDataReceived( *rosPPPProfile );
	setStatusText( tr("Recibido perfil %1").arg(rosPPPProfile->profileName()), routerName );
}
void QMikPPPManager::onAllPPPProfilesReceived(const QString &routerName)
{
	setStatusText( tr("Grupos de usuarios API recibidos"), routerName );
}
void QMikPPPManager::onPPPProfilesErrorReceived(const QString &routerName, const QString &errorString)
{
	QMessageBox::warning(this, objectName(), tr("Error al recibir los grupos de usuario API\n%1:\n%2").arg(routerName, errorString) );
	setStatusText( tr("Error al recibir los grupos de usuario API"), routerName );
}

void QMikPPPManager::pideUsuarios(const QString &routerName)
{
	ROS::QSentence s("/ppp/secret/getall");
	s.setTag( gGlobalConfig.tagSecret );
	s.addQuery("#|");
	mktAPI.sendSentence( routerName, s );

	s.setCommand("/ppp/secret/listen");
	s.setTag( gGlobalConfig.tagLSecret );
	mktAPI.sendSentence( routerName, s );
}

void QMikPPPManager::pideActivos(const QString &routerName)
{
	mktAPI.sendSentence( routerName, "/ppp/active/getall", gGlobalConfig.tagActivo );
}

void QMikPPPManager::pideCambios(const QString &routerName)
{
	mktAPI.sendSentence( routerName, "/ppp/active/listen", gGlobalConfig.tagLActivo );
}

//void QMikPPPManager::onReceive(ROS::QSentence &s, const QString &routerName)
//{
//	if( !s.tag().isEmpty() )
//	{
//		if( s.tag() == gGlobalConfig.tagAPIUser )
//			onAPIUserInfoRecibida(routerName, s);
//		else
//		if( s.tag() == gGlobalConfig.tagSecret )
//			onPPPoEUsersReceived(routerName, s);
//		else
//		if( s.tag() == gGlobalConfig.tagLSecret )
//		{
//			if( s.attribute(".dead").isEmpty() )
//			{
//				ui->twUsuarios->addSecret(s, true);
//				if( dlgNuevoUsuario != Q_NULLPTR )
//					dlgNuevoUsuario->onSecretAdded(s);
//			}
//			else
//			{
//				ui->twUsuarios->delSecret(s);
//				if( dlgNuevoUsuario != Q_NULLPTR )
//					dlgNuevoUsuario->onSecretDeleted(s);
//			}
//		}
//		else
//		if( s.tag() == gGlobalConfig.tagPerfil )
//			onPerfilRecibido(routerName, s);
//		else
//		if( s.tag() == gGlobalConfig.tagActivo )
//			onActivoRecibido(routerName, s);
//		else
//		if( s.tag() == gGlobalConfig.tagLActivo )
//			actualizaUsuario(routerName, s);
//		else
//		if( s.getResultType() != ROS::QSentence::Done )
//			setStatusText( routerName, s.toString() );
//		return;
//	}
//	if( s.getResultType() )
//		setStatusText( routerName, s.toString() );
//}

void QMikPPPManager::onAPIUserInfoRecibida(const QString &routerName, const ROS::QSentence &s)
{
//	switch( s.getResultType() )
//	{
//	case ROS::QSentence::None:
//		break;
//	case ROS::QSentence::Done:
//		// It is empty when all routers completed the request.
//		if( routerName.isEmpty() )
//		{
//			setStatusText( "", tr("Información de usuarios API recibida de todos los routers.") );
//			onAllROSAPIUsersReceived();
//		}
//		else
//			setStatusText( routerName, tr("Información de usuarios API recibida.") );
//		break;
//	case ROS::QSentence::Reply:
//	{
//		setStatusText( routerName, tr("Usuario de la API del ROS %1 del Grupo %2 recibido.").arg(s.attribute("name"), s.attribute("group")) );
//		break;
//	}
//	case ROS::QSentence::Trap:
//		setStatusText( routerName, s.toString() );
//		break;
//	case ROS::QSentence::Fatal:
//		setStatusText( routerName, s.toString() );
//		break;
//	}
}

void QMikPPPManager::onPPPoEUsersReceived(const QString &routerName, const ROS::QSentence &s)
{
//	switch( s.getResultType() )
//	{
//	case ROS::QSentence::None:
//		break;
//	case ROS::QSentence::Done:
//		if( routerName.isEmpty() )
//		{
//			setStatusText( "", tr("Todos los usuarios PPPoE recibidos.") );
//			ui->twUsuarios->fillupTable();
//		}
//		else
//		{
//			setStatusText( routerName, tr("Usuarios PPPoE recibidos. Pidiendo activos y cambios en directo") );
//			pideActivos(routerName);
//			pideCambios(routerName);
//			break;
//		}
//	case ROS::QSentence::Reply:
//		ui->statusBar->showMessage(QString("Recibido de %1: %2").arg(routerName, s.getID()));
//		ui->twUsuarios->addSecret(s);
//		break;
//	case ROS::QSentence::Trap:
//		setStatusText(routerName, s.toString());
//		break;
//	case ROS::QSentence::Fatal:
//		setStatusText(routerName, s.toString());
//		break;
//	}
}

void QMikPPPManager::onPerfilRecibido(const QString &routerName, const ROS::QSentence &s)
{
//	switch( s.getResultType() )
//	{
//	case ROS::QSentence::None:
//		break;
//	case ROS::QSentence::Done:
//		setStatusText( routerName, tr("Perfiles recibidos.") );
//		break;
//	case ROS::QSentence::Reply:
//		gGlobalConfig.perfiles().append(s);
//		break;
//	case ROS::QSentence::Trap:
//		break;
//	case ROS::QSentence::Fatal:
//		break;
//	}
}

void QMikPPPManager::onActivoRecibido(const QString &routerName, const ROS::QSentence &s)
{
//	switch( s.getResultType() )
//	{
//	case ROS::QSentence::None:
//		break;
//	case ROS::QSentence::Done:
//		setStatusText( routerName, tr("Activos recibidos.") );
//		ui->twUsuarios->resizeColumnsToContents();
//		break;
//	case ROS::QSentence::Reply:
//		actualizaUsuario(s);
//		break;
//	case ROS::QSentence::Trap:
//		break;
//	case ROS::QSentence::Fatal:
//		break;
//	}
}

void QMikPPPManager::actualizaUsuario(const QString &routerName, const ROS::QSentence &s)
{
//	if( s.attribute(".dead").isEmpty() )
//	{
//		setStatusText( routerName, tr("Conexión %1 (%2) recuperada con IP %3").arg(s.attribute("name"), s.getID(), s.attribute("address")));
//		if( dlgNuevoUsuario != Q_NULLPTR )
//			dlgNuevoUsuario->onActivoConectado(s);
//	}
//	else
//	{
//		QSecretData *sc = ui->twUsuarios->findDataBySesionID(s.getID());
//		if( sc != Q_NULLPTR )
//		{
//			if( sc->IPActiva() == sc->IPEstatica() )
//				setStatusText(routerName, tr("Conexión %1 (%2) cerrada. IP %3 reservada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
//			else
//				setStatusText(routerName, tr("Conexión %1 (%2) cerrada. IP %3 liberada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
//		}
//		else
//			setStatusText(routerName, tr("Conexión %1 cerrada").arg(s.attribute("name"), s.getID()));
//		if( dlgNuevoUsuario != Q_NULLPTR )
//			dlgNuevoUsuario->onActivoDesconectado(s);
//	}
//	ui->twUsuarios->actualizaUsuario(s);
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

void QMikPPPManager::actualizaComentariosRemoto(QSecretData *sd)
{
	// TODO: To do so, need to know the router where the pppoe user is loged.
//	ROS::QSentence s("/ppp/secret/set");
//	s.setID(sd->secretID());
//	s.addAttribute("comment", sd->comment());
//	s.setTag("UpdateComment");
//	mktAPI.sendSentence(s);
}

void QMikPPPManager::actualizaPerfilRemoto(QSecretData *sd)
{
	// TODO: To do so, need to know the router where the pppoe user is loged.
//	ROS::QSentence s;
//	s.setCommand("/ppp/secret/set");
//	s.setID(sd->secretID());
//	s.addAttribute("profile", sd->perfilReal());
//	s.setTag("UpdateProfile");
//	mktAPI.sendSentence(s);
}

void QMikPPPManager::actualizaIPRemota(QSecretData *sd)
{
	// TODO: To do so, need to know the router where the pppoe user is loged.
//	ROS::QSentence s;
//	s.setCommand("/ppp/secret/set");
//	s.setID(sd->secretID());
//	if( sd->IPEstatica().isEmpty() )
//		s.addAttribute("!remote-address", "");
//	else
//		s.addAttribute("remote-address", sd->IPEstatica());
//	s.setTag("UpdateProfile");
//	mktAPI.sendSentence(s);
}

void QMikPPPManager::setNivelUsuario(QConfigData::NivelUsuario lvl)
{
//	gGlobalConfig.setNivelUsuario(lvl);
//	switch( gGlobalConfig.nivelUsuario() )
//	{
//	case QConfigData::SinPermisos:
//		ui->twUsuarios->setEnabled(false);
//		ui->addUserButton->setEnabled(false);
//		ui->advancedConfigButton->setEnabled(false);
//		break;
//	case QConfigData::Comercial:	// El comercial puede verlo todo, por lo tanto, le dejo entrar en todos los sitios.
//		ui->addUserButton->setEnabled(false);
//		ui->twUsuarios->setEnabled(true);
//		ui->advancedConfigButton->setEnabled(false);
//		break;
//	case QConfigData::Instalador:
//		ui->addUserButton->setEnabled(true);
//		ui->twUsuarios->setEnabled(true);
//		ui->advancedConfigButton->setEnabled(false);
//		break;
//	case QConfigData::Administrador:
//		ui->addUserButton->setEnabled(true);
//		ui->twUsuarios->setEnabled(true);
//		ui->advancedConfigButton->setEnabled(false);
//		break;
//	case QConfigData::Supervisor:
//		ui->addUserButton->setEnabled(true);
//		ui->twUsuarios->setEnabled(true);
//		ui->advancedConfigButton->setEnabled(true);
//		break;
//	}
}

void QMikPPPManager::onDatoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &id, bool *isValid)
{
	QSecretData *sd = ui->twUsuarios->findDataBySecretID(id);
	QSecretData oldSecret = *sd;
	if( !sd )
		return;
	switch( col )
	{
	case QSecretDataModel::ColUsuario:	// No es modificable localmente.
	case QSecretDataModel::ColNumber:
		break;
	case QSecretDataModel::ColPerfil:
		sd->setPerfilOriginal(dato);
		if( !sd->dadoDeBaja() )
		{
			sd->setPerfilReal(dato);
			actualizaPerfilRemoto(sd);
		}
		actualizaComentariosRemoto(sd);
		reiniciaConexionRemota(sd);
		break;
	case QSecretDataModel::ColContrato:
		if( (dato == "alta") == sd->dadoDeBaja() )
		{
			// Las notas están vacías cuando aun no tiene los comentarios "formateados"
			if( sd->notas().isEmpty() )
				actualizaComentariosRemoto(sd);

			// TODO: Repasar esto!!!!
			if( !sd->dadoDeBaja() )
				sd->setPerfilReal( gGlobalConfig.perfiles().defaultProfile().profileName() );
			else
				sd->setPerfilReal( sd->perfilOriginal() );
			actualizaPerfilRemoto( sd );
			reiniciaConexionRemota( sd );
		}
		break;
	case QSecretDataModel::ColEstado:	// No es modificable localmente.
		break;
	case QSecretDataModel::ColIP:
		sd->setIPEstatica(dato);
		actualizaIPRemota(sd);
		reiniciaConexionRemota(sd);
		break;
	case QSecretDataModel::ColNombre:
		sd->setNombre(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColDireccion:
		sd->setDireccion(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColPoblacion:
		sd->setPoblacion(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColTelefonos:
		sd->setTelefonos(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColInstalador:
		sd->setInstalador(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColVendedor:
		sd->setComercial(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColEMail:
		sd->setEmail(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColUsaIPPublica:
		sd->setFlagsUsaIPPublica(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColNotas:
		sd->setNotas(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColCCliente:
		if( dato.count() && !(*isValid = codigoClienteValido(dato, sd)) )
			return;
		sd->setCodigoCliente(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::NumColumnas:
		break;
	}
	logService.registraCambios(oldSecret, *sd);
}

void QMikPPPManager::onDobleClicUsuario(const QSecretData &sd)
{
	// TODO: To do so, need to know the router where the pppoe user is loged.
//	if( dlgNuevoUsuario )
//		return;

//	dlgNuevoUsuario = new DlgNuevoUsuario(&mktAPI, sd, ui->twUsuarios->secrets(), this);
//	dlgNuevoUsuario->exec();
//	dlgNuevoUsuario->deleteLater();
//	dlgNuevoUsuario = Q_NULLPTR;
}

void QMikPPPManager::onClicUsuario(const QSecretData &sd)
{
	if( !sd.IPActiva().isEmpty() )
	{
		quint32 k = qApp->keyboardModifiers();
		if( k & Qt::AltModifier )
			QDesktopServices::openUrl(QUrl(QString("http://%1:80").arg(sd.IPActiva())));
//		QMenu menu;
//		menu.addAction(QString("http://%1:80").arg(sd.IPActiva()));
//		menu.move(QPoint(400, 400));
//		menu.exec();
	}
	//TODO: Crear el menú constextual para:
	// 1. Abrir cuadro de edición.
	// 2. Abrir navegador web para el cliente http puerto.
	// 3. Abrir navegador web para el cliente http puerto 8080.
	// 4. Abrir navegador web para el cliente http puerto 8888.
	// 5. Abrir navegador web para el cliente https.
}

void QMikPPPManager::filtraFilas()
{
	ui->twUsuarios->filterRows(ui->leFiltro->text(), ui->cbFiltro->currentData().toInt());
}

// Comprueba si el código cliente es válido con los siguiente criterios.
// Es un valor positivo.
// El código de cliente no corresponde a otro cliente (se pregunta qué hacer en este caso)
bool QMikPPPManager::codigoClienteValido(const QString &code, const QSecretData *sdOri)
{
	QSecretData *sd;
	if( code.toInt() <= 0 )
	{
		QMessageBox::warning(this, tr("Código de cliente"), tr("El código de cliente debe ser un número mayor que 0") );
		return false;
	}
	if( code.toInt() > 99999 )
	{
		QMessageBox::warning(this, tr("Código de cliente"), tr("El código de cliente debe ser un número positivo menor que 99999") );
		return false;
	}

	if( ((sd = ui->twUsuarios->secrets().findDataByClientCode(code, sdOri)) != Q_NULLPTR) &&
		(QMessageBox::question(this, tr("Código de cliente"), tr("El código de cliente %1 corresponde a %2 y quieres asociarlo a %3.\n¿Es correcto?")
							  .arg(code)
							  .arg(sd->usuario())
							  .arg(sdOri->nombre()), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) )
			return false;
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

void QMikPPPManager::on_leFiltro_textChanged(const QString &)
{
	filtraFilas();
}

void QMikPPPManager::on_cbFiltro_currentIndexChanged(int )
{
	switch( ui->cbFiltro->currentData().toInt() )
	{
	case FILTRO_ALTA:
	case FILTRO_BAJA:
		ui->leFiltro->setDisabled(true);
		break;
	default:
		ui->leFiltro->setDisabled(false);
		break;
	}
	filtraFilas();
}

void QMikPPPManager::on_connectButton_clicked()
{
	if( gGlobalConfig.connectInfoList().isEmpty() )
	{
		QMessageBox::information( this, objectName(), tr("No hay ninguna conexión configurada. Configurala para poderte conectar.") );
		dlgCnfgConnect.show();
		if( gGlobalConfig.connectInfoList().isEmpty() )
			return;
	}
	// If all router are disconnected, copy data from config. Otherwise, just reconect.
	// That means that router config can be changed only when no connections is active.
	if( mktAPI.areAllDisconnected() )
	{
		mktAPI.clear();
		foreach( const ConnectInfo &c, gGlobalConfig.connectInfoList() )
		{
			mktAPI.addROSConnection( createRouterName(c),
									 c.m_hostIPv4.toString(),
									 c.m_hostPort,
									 gGlobalConfig.userName(),
									 gGlobalConfig.userPass());
		}
	}
	mktAPI.connectHosts();
}

void QMikPPPManager::on_disconnectButton_clicked()
{
	mktAPI.disconnectHosts(false);
}

void QMikPPPManager::on_exportButton_clicked()
{
	if( !ui->twUsuarios->count() )
		QMessageBox::warning(this, objectName(), tr("Ningún usuario descargado del servidor."));
	else
	{
		DlgExportar dlg(this, ui->twUsuarios);
		dlg.exec();
	}
}

void QMikPPPManager::on_portScanButton_clicked()
{
	DlgPortScan dlg(this, ui->twUsuarios);
	dlg.exec();
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
	dlgCnfgConnect.show();
}

void QMikPPPManager::on_advancedConfigButton_clicked()
{
	DlgConfiguracion *dlgConfig = new DlgConfiguracion(this);

	if( dlgConfig->exec() )
		updateConfig();

	dlgConfig->deleteLater();
}

void QMikPPPManager::on_addUserButton_clicked()
{
	QSecretData s;
#ifdef QT_DEBUG
	s.setUsuario("AAAAAAAAAAAA");
	s.setContra("123456789012");
	s.setNombre("Nombre Cliente");
	s.setDireccion("Dirección del cliente");
	s.setPoblacion("Población");
	s.setEmail("Correo@electr.nico");
	s.setWPass("WPA123456");
	s.setSSID("SSID_WIFI");
	s.setInstalador("Aaron");
	s.setTelefonos("123456789,123456789");
#endif
// TODO!
//	dlgNuevoUsuario = new DlgNuevoUsuario(&mktAPI, s, ui->twUsuarios->secrets(), this);
//	dlgNuevoUsuario->exec();
//	dlgNuevoUsuario->deleteLater();
//	dlgNuevoUsuario = Q_NULLPTR;
}

void QMikPPPManager::on_apiUsersButton_clicked()
{
	if( !dlgROSAPIUsers )
		dlgROSAPIUsers = new DlgROSAPIUsers( &mktAPI, this );

	dlgROSAPIUsers->show();
}

void QMikPPPManager::on_pppProfilesButton_clicked()
{
	if( !dlgPPPProfiles )
		dlgPPPProfiles = new DlgPPPProfiles( &mktAPI, this );

	dlgPPPProfiles->show();
}
