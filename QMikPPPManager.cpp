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
#include "QRegistro.h"

QMikPPPManager::QMikPPPManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QMikPPPManager), dlgNuevoUsuario(Q_NULLPTR), estado(Desconectado)
{
	ui->setupUi(this);

	ui->twUsuarios->setEnabled(false);
	// Rellenamos el diálogo con la configuración.
	gGlobalConfig.load();
	updateConfig();

	connect( &mktAPI, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );

	connect( &mktAPI, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onStateChanged(ROS::Comm::CommState)) );
	connect( &mktAPI, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );

	connect( &mktAPI, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onReceive(ROS::QSentence&)) );
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
}

QMikPPPManager::~QMikPPPManager()
{
	mktAPI.closeCom();
	// Guardamos los datos del diálogo.
	gGlobalConfig.setRemoteHost(ui->leIP->text());
	gGlobalConfig.setRemotePort(ui->sbPort->value());
	gGlobalConfig.setUserName(ui->leUser->text());
	gGlobalConfig.setUserPass(ui->lePass->text());
	if( isMaximized() )
		gGlobalConfig.setWindowMaxi();
	else
	{
		gGlobalConfig.setAnchoPantalla(width());
		gGlobalConfig.setAltoPantalla(height());
	}
	gGlobalConfig.save();
	logService.shutdown();
	delete ui;
	ui = Q_NULLPTR;
}

void QMikPPPManager::updateConfig()
{
	ui->leIP->setText(gGlobalConfig.remoteHost());
	ui->sbPort->setValue(gGlobalConfig.remotePort());
	ui->leUser->setText(gGlobalConfig.userName());
	ui->lePass->setText(gGlobalConfig.userPass());

	QFont tableFont = ui->twUsuarios->font();
	tableFont.setPixelSize(gGlobalConfig.tamFuente());
	ui->twUsuarios->setFont(tableFont);
	ui->twUsuarios->verticalHeader()->setDefaultSectionSize(gGlobalConfig.alturaLinea());
	if( gGlobalConfig.windowMaxi() )
		this->showMaximized();
	else
		this->resize(gGlobalConfig.anchoPantalla(), gGlobalConfig.altoPantalla());
}

void QMikPPPManager::setStatusText(const QString &txt)
{
	if( ui )
	{
		ui->statusBar->showMessage(txt);
	}
}

void QMikPPPManager::on_pbConnect_clicked()
{
	if( mktAPI.isClosing() )
		mktAPI.closeCom(true);
	else
	if( mktAPI.isLoged() )
		mktAPI.closeCom();
	else
	if( mktAPI.isConnected() || mktAPI.isConnecting() )
		mktAPI.closeCom();
	else
	{
		gGlobalConfig.setUserName(ui->leUser->text());
		gGlobalConfig.setUserPass(ui->lePass->text());
		gGlobalConfig.setRemoteHost(ui->leIP->text());
		gGlobalConfig.setRemotePort(ui->sbPort->value());
		mktAPI.setRemoteHost(gGlobalConfig.remoteHost(), gGlobalConfig.remotePort());
		mktAPI.setUserNamePass(gGlobalConfig.userName(), gGlobalConfig.userPass());
		mktAPI.connectToROS();
	}
}

void QMikPPPManager::onStateChanged(ROS::Comm::CommState s)
{
	switch( s )
	{
	case ROS::Comm::Unconnected:
		ui->pbConnect->setText( tr("Conectar") );
		setStatusText( tr("Desconectado") );
		break;
	case ROS::Comm::HostLookup:
		ui->pbConnect->setText( tr("Cancelar") ) ;
		setStatusText( tr("Resolviendo URL") );
		break;
	case ROS::Comm::Connecting:
		ui->pbConnect->setText( tr("Cancelar") );
		setStatusText( tr("Conectando al servidor") );
		break;
	case ROS::Comm::Connected:
		ui->pbConnect->setText( tr("Desconectar") );
		setStatusText( tr("Conectado") );
		break;
	case ROS::Comm::Closing:
		ui->pbConnect->setText( tr("Forzar desconexión") );
		setStatusText( tr("Cerrando conexión") );
		break;
	}
}

void QMikPPPManager::onLoginChanged(ROS::Comm::LoginState s)
{
	switch( s )
	{
	case ROS::Comm::NoLoged:
		setStatusText( tr("No está identificado en el servidor") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::LoginRequested:
		setStatusText( tr("Usuario y contraseña pedidos") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::UserPassSended:
		setStatusText( tr("Petición de login en curso") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::LogedIn:
		setStatusText( tr("Logado al servidor") );
		logService.setUserName(ui->leUser->text());
		ui->pbConnect->setText("Desconectar");
		ui->twUsuarios->clear();
		ui->twUsuarios->setEnabled(true);
		pideInfoUsuarioAPI();
		pidePerfiles();
		pideUsuarios();
		break;
	}
}

void QMikPPPManager::onComError(ROS::Comm::CommError, QAbstractSocket::SocketError)
{
	QString s = mktAPI.errorString();
	setStatusText(s);
	QMessageBox::warning(this, objectName(), tr("Error reportado por la red, router o sistema:\n%1").arg(s));
}

void QMikPPPManager::pideInfoUsuarioAPI()
{
	ROS::QSentence s("/user/getall");
	s.setTag(gGlobalConfig.tagAPIUser);
	s.addQuery("name", gGlobalConfig.userName(), ROS::QQuery::EqualProp);
	s.addQuery("#|");
	mktAPI.sendSentence( s );
}

void QMikPPPManager::pidePerfiles()
{
	mktAPI.sendSentence( "/ppp/profile/getall", gGlobalConfig.tagPerfil );
}

void QMikPPPManager::pideUsuarios()
{
	ROS::QSentence s("/ppp/secret/getall");
	s.setTag( gGlobalConfig.tagSecret );
	s.addQuery("#|");
	mktAPI.sendSentence( s );

	s.setCommand("/ppp/secret/listen");
	s.setTag( gGlobalConfig.tagLSecret );
	mktAPI.sendSentence( s );
}

void QMikPPPManager::pideActivos()
{
	mktAPI.sendSentence( "/ppp/active/getall", gGlobalConfig.tagActivo );
}

void QMikPPPManager::pideCambios()
{
	mktAPI.sendSentence( "/ppp/active/listen", gGlobalConfig.tagLActivo );
}

void QMikPPPManager::onReceive(ROS::QSentence &s)
{
	if( !s.tag().isEmpty() )
	{
		if( s.tag() == gGlobalConfig.tagAPIUser )
			onAPIUserInfoRecibida(s);
		else
		if( s.tag() == gGlobalConfig.tagSecret )
			onUsuarioRecibido(s);
		else
		if( s.tag() == gGlobalConfig.tagLSecret )
		{
			if( s.attribute(".dead").isEmpty() )
			{
				ui->twUsuarios->addSecret(s, true);
				if( dlgNuevoUsuario != Q_NULLPTR )
					dlgNuevoUsuario->onSecretAdded(s);
			}
			else
			{
				ui->twUsuarios->delSecret(s);
				if( dlgNuevoUsuario != Q_NULLPTR )
					dlgNuevoUsuario->onSecretDeleted(s);
			}
		}
		else
		if( s.tag() == gGlobalConfig.tagPerfil )
			onPerfilRecibido(s);
		else
		if( s.tag() == gGlobalConfig.tagActivo )
			onActivoRecibido(s);
		else
		if( s.tag() == gGlobalConfig.tagLActivo )
			actualizaUsuario(s);
		else
		if( s.getResultType() != ROS::QSentence::Done )
			setStatusText(s.toString());
		return;
	}
	if( s.getResultType() )
		setStatusText(s.toString());
}

void QMikPPPManager::onAPIUserInfoRecibida(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage(tr("Información del usuario API recibida."));
		break;
	case ROS::QSentence::Reply:
	{
		QString grupo = s.attribute("group");
		QString nombre = s.attribute("name");
		ui->statusBar->showMessage(tr("Recibida info de %1. Grupo %2").arg(nombre, grupo));
		if( (grupo.compare("full") == 0) || (grupo.compare("Supervisores") == 0) )
			setNivelUsuario(QConfigData::Supervisor);
		else
		if( grupo.compare("Instaladores", Qt::CaseInsensitive) == 0 )
			setNivelUsuario(QConfigData::Instalador);
		else
		if( grupo.compare("Administradores", Qt::CaseInsensitive) == 0 )
			setNivelUsuario(QConfigData::Administrador);
		else
		if( grupo.compare("Comerciales", Qt::CaseInsensitive) == 0 )
		{
			setNivelUsuario(QConfigData::Comercial);
		}
		else
		{
			QString info = tr("Usuario %1 pertenece al grupo %2 y no tiene permisos para hacer nada.").arg(nombre, grupo);
			setNivelUsuario(QConfigData::SinPermisos);
			setStatusText(info);
			QMessageBox::warning(Q_NULLPTR, tr("Información de usuario"), info);
		}
		this->setWindowTitle(QString("%1 - %2 [%4]").arg("Mikrotik PPP Manager", nombre, grupo));
		break;
	}
	case ROS::QSentence::Trap:
		setStatusText(s.toString());
		break;
	case ROS::QSentence::Fatal:
		setStatusText(s.toString());
		break;
	}
}

void QMikPPPManager::onUsuarioRecibido(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage(tr("Usuarios recibidos. Pidiendo activos y cambios en vivo"));
		ui->twUsuarios->fillupTable();
		pideActivos();
		pideCambios();
		break;
	case ROS::QSentence::Reply:
		ui->statusBar->showMessage(QString("Recibido: %1").arg(s.getID()));
		ui->twUsuarios->addSecret(s);
		break;
	case ROS::QSentence::Trap:
		setStatusText(s.toString());
		break;
	case ROS::QSentence::Fatal:
		setStatusText(s.toString());
		break;
	}
}

void QMikPPPManager::onPerfilRecibido(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage( tr("Perfiles recibidos.") );
		break;
	case ROS::QSentence::Reply:
		gGlobalConfig.addPerfil(s);
		break;
	case ROS::QSentence::Trap:
		break;
	case ROS::QSentence::Fatal:
		break;
	}
}

void QMikPPPManager::onActivoRecibido(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage( tr("Activos recibidos.") );
		ui->twUsuarios->resizeColumnsToContents();
		break;
	case ROS::QSentence::Reply:
		actualizaUsuario(s);
		break;
	case ROS::QSentence::Trap:
		break;
	case ROS::QSentence::Fatal:
		break;
	}
}

void QMikPPPManager::actualizaUsuario(const ROS::QSentence &s)
{
	if( s.attribute(".dead").isEmpty() )
	{
		setStatusText(tr("Conexión %1 (%2) recuperada con IP %3").arg(s.attribute("name"), s.getID(), s.attribute("address")));
		if( dlgNuevoUsuario != Q_NULLPTR )
			dlgNuevoUsuario->onActivoConectado(s);
	}
	else
	{
		QSecretData *sc = ui->twUsuarios->findDataBySesionID(s.getID());
		if( sc != Q_NULLPTR )
		{
			if( sc->IPActiva() == sc->IPEstatica() )
				setStatusText(tr("Conexión %1 (%2) cerrada. IP %3 reservada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
			else
				setStatusText(tr("Conexión %1 (%2) cerrada. IP %3 liberada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
		}
		else
			setStatusText(tr("Conexión %1 cerrada").arg(s.attribute("name"), s.getID()));
		if( dlgNuevoUsuario != Q_NULLPTR )
			dlgNuevoUsuario->onActivoDesconectado(s);
	}
	ui->twUsuarios->actualizaUsuario(s);
}

void QMikPPPManager::on_anyadeUsuario_clicked()
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
	dlgNuevoUsuario = new DlgNuevoUsuario(&mktAPI, s, ui->twUsuarios->secrets(), this);
	dlgNuevoUsuario->exec();
	dlgNuevoUsuario->deleteLater();
	dlgNuevoUsuario = Q_NULLPTR;
}

#include "DlgConfiguracion.h"
void QMikPPPManager::on_btConfig_clicked()
{
	DlgConfiguracion *dlgConfig = new DlgConfiguracion(this);

	if( dlgConfig->exec() )
		updateConfig();

	dlgConfig->deleteLater();
}

void QMikPPPManager::reiniciaConexionRemota(QSecretData *sd)
{
	if( !sd->sesionID().isEmpty() )
	{
		ROS::QSentence s("/ppp/active/remove");
		s.setID(sd->sesionID());
		s.setTag("ReconnectClient");
		mktAPI.sendSentence(s);
	}
}

void QMikPPPManager::actualizaComentariosRemoto(QSecretData *sd)
{
	ROS::QSentence s("/ppp/secret/set");
	s.setID(sd->secretID());
	s.addAttribute("comment", sd->comment());
	s.setTag("UpdateComment");
	mktAPI.sendSentence(s);
}

void QMikPPPManager::actualizaPerfilRemoto(QSecretData *sd)
{
	ROS::QSentence s;
	s.setCommand("/ppp/secret/set");
	s.setID(sd->secretID());
	s.addAttribute("profile", sd->perfilReal());
	s.setTag("UpdateProfile");
	mktAPI.sendSentence(s);
}

void QMikPPPManager::actualizaIPRemota(QSecretData *sd)
{
	ROS::QSentence s;
	s.setCommand("/ppp/secret/set");
	s.setID(sd->secretID());
	if( sd->IPEstatica().isEmpty() )
		s.addAttribute("!remote-address", "");
	else
		s.addAttribute("remote-address", sd->IPEstatica());
	s.setTag("UpdateProfile");
	mktAPI.sendSentence(s);
}

void QMikPPPManager::setNivelUsuario(QConfigData::NivelUsuario lvl)
{
	gGlobalConfig.setNivelUsuario(lvl);
	switch( gGlobalConfig.nivelUsuario() )
	{
	case QConfigData::SinPermisos:
		ui->twUsuarios->setEnabled(false);
		ui->anyadeUsuario->setEnabled(false);
		ui->btConfig->setEnabled(false);
		ui->btExportar->setEnabled(false);
		break;
	case QConfigData::Comercial:	// El comercial puede verlo todo, por lo tanto, le dejo entrar en todos los sitios.
		ui->anyadeUsuario->setEnabled(false);
		ui->twUsuarios->setEnabled(true);
		ui->btConfig->setEnabled(false);
		ui->btExportar->setEnabled(false);
		break;
	case QConfigData::Instalador:
		ui->anyadeUsuario->setEnabled(true);
		ui->twUsuarios->setEnabled(true);
		ui->btExportar->setEnabled(false);
		ui->btConfig->setEnabled(false);
		break;
	case QConfigData::Administrador:
		ui->anyadeUsuario->setEnabled(true);
		ui->twUsuarios->setEnabled(true);
		ui->btConfig->setEnabled(false);
		ui->btExportar->setEnabled(true);
		break;
	case QConfigData::Supervisor:
		ui->anyadeUsuario->setEnabled(true);
		ui->twUsuarios->setEnabled(true);
		ui->btConfig->setEnabled(true);
		ui->btExportar->setEnabled(true);
		break;
	}
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
				sd->setPerfilReal(gGlobalConfig.perfilDadoDeBaja());
			else
				sd->setPerfilReal(sd->perfilOriginal());
			actualizaPerfilRemoto(sd);
			reiniciaConexionRemota(sd);
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
	if( dlgNuevoUsuario )
		return;

	dlgNuevoUsuario = new DlgNuevoUsuario(&mktAPI, sd, ui->twUsuarios->secrets(), this);
	dlgNuevoUsuario->exec();
	dlgNuevoUsuario->deleteLater();
	dlgNuevoUsuario = Q_NULLPTR;
}

void QMikPPPManager::onClicUsuario(const QSecretData &sd)
{
	if( !sd.IPActiva().isEmpty() )
	{
		int k = qApp->keyboardModifiers();
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

	if( ((sd = ui->twUsuarios->secrets().findDataByClientCode(code, sdOri)) != NULL) &&
		(QMessageBox::question(this, tr("Código de cliente"), tr("El código de cliente %1 corresponde a %2 y quieres asociarlo a %3.\n¿Es correcto?")
							  .arg(code)
							  .arg(sd->usuario())
							  .arg(sdOri->nombre()), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) )
			return false;
	return true;
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

#include "DlgExportar.h"
void QMikPPPManager::on_btExportar_clicked()
{
	if( !ui->twUsuarios->count() )
		QMessageBox::warning(this, objectName(), tr("Ningún usuario descargado del servidor."));
	else
	{
		DlgExportar dlg(this, ui->twUsuarios);
		dlg.exec();
	}
}

#include "DlgPortScan.h"
void QMikPPPManager::on_btPortScan_clicked()
{
	DlgPortScan dlg(this, ui->twUsuarios);
	dlg.exec();
}
