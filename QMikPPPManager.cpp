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

QConfigData gGlobalConfig;

QMikPPPManager::QMikPPPManager(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QMikPPPManager), estado(Desconectado)
{
	ui->setupUi(this);

	ui->twUsuarios->setEnabled(false);
	// Rellenamos el diálogo con la configuración.
	gGlobalConfig.load();
	updateConfig();

	connect( &mktAPI, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );
	connect( &mktAPI, SIGNAL(loginRequest(QString*,QString*)), this, SLOT(onLoginRequest(QString*,QString*)) );

	connect( &mktAPI, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onStateChanged(ROS::Comm::CommState)) );
	connect( &mktAPI, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );

	connect( &mktAPI, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onReceive(ROS::QSentence&)) );
	connect( ui->twUsuarios, SIGNAL(datoModificado(QSecretDataModel::Columnas,QString,QString)),
			 this, SLOT(onDatoModificado(QSecretDataModel::Columnas,QString,QString)) );
}

QMikPPPManager::~QMikPPPManager()
{
	mktAPI.closeCom();
	// Guardamos los datos del diálogo.
	gGlobalConfig.setRemoteHost(ui->leIP->text());
	gGlobalConfig.setRemotePort(ui->sbPort->value());
	gGlobalConfig.setUserName(ui->leUser->text());
	gGlobalConfig.setUserPass(ui->lePass->text());
	gGlobalConfig.save();
	delete ui;
	ui = 0;
}

void QMikPPPManager::addLogText(const QString &txt)
{
	if( ui )
	{
		ui->statusBar->showMessage(txt);
	}
}

void QMikPPPManager::addSecret(const ROS::QSentence &s)
{
	secretList.append(s);
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
		mktAPI.connectTo(ui->leIP->text(), (unsigned short)ui->sbPort->value());
}


void QMikPPPManager::onStateChanged(ROS::Comm::CommState s)
{
	switch( s )
	{
	case ROS::Comm::Unconnected:
		ui->pbConnect->setText( tr("Conectar") );
		addLogText( tr("Desconectado") );
		break;
	case ROS::Comm::HostLookup:
		ui->pbConnect->setText( tr("Cancelar") ) ;
		addLogText( tr("Resolviendo URL") );
		break;
	case ROS::Comm::Connecting:
		ui->pbConnect->setText( tr("Cancelar") );
		addLogText( tr("Conectando al servidor") );
		break;
	case ROS::Comm::Connected:
		ui->pbConnect->setText( tr("Desconectar") );
		addLogText( tr("Conectado") );
		break;
	case ROS::Comm::Closing:
		ui->pbConnect->setText( tr("Forzar desconexión") );
		addLogText( tr("Cerrando conexión") );
		break;
	}
}

void QMikPPPManager::onLoginChanged(ROS::Comm::LoginState s)
{
	switch( s )
	{
	case ROS::Comm::NoLoged:
		addLogText( tr("No está identificado en el servidor") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::LoginRequested:
		addLogText( tr("Usuario y contraseña pedidos") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::UserPassSended:
		addLogText( tr("Petición de login en curso") );
		ui->twUsuarios->setEnabled(false);
		break;
	case ROS::Comm::LogedIn:
		addLogText( tr("Logado al servidor") );
		ui->pbConnect->setText("Desconectar");
		pidePerfiles();
		ui->twUsuarios->setEnabled(true);
		break;
	}
}

void QMikPPPManager::onLoginRequest(QString *user, QString *pass)
{
	*user = ui->leUser->text();
	*pass = ui->lePass->text();
}

void QMikPPPManager::onComError(ROS::Comm::CommError, QAbstractSocket::SocketError)
{
	addLogText(mktAPI.errorString());
}

void QMikPPPManager::onReceive(ROS::QSentence &s)
{
	if( !s.tag().isEmpty() )
	{
		if( s.tag() == tagUsuarios )
			onUsuarioRecibido(s);
		else
		if( s.tag() == tagPerfiles )
			onPerfilRecibido(s);
		else
		if( s.tag() == tagActivos )
			onActivoRecibido(s);
		else
		if( s.tag() == tagListening )
			actualizaUsuario(s);
		else
		if( s.getResultType() != ROS::QSentence::Done )
			addLogText(s.toString());
		return;
	}
	if( s.getResultType() )
		addLogText(s.toString());
}

void QMikPPPManager::pidePerfiles()
{
	if( !tagPerfiles.isEmpty() )
		mktAPI.sendCancel(tagPerfiles);
	mktAPI.sendSentence( "/ppp/profile/getall", tagPerfiles = "Perfiles" );
}

void QMikPPPManager::pideUsuarios()
{
	if( !tagUsuarios.isEmpty() )
		mktAPI.sendCancel(tagUsuarios);
	ROS::QSentence s("/ppp/secret/getall");
	s.setTag(tagUsuarios = "Usuarios");
	s.queries().addQuery("#|");
	mktAPI.sendSentence( s );
}

void QMikPPPManager::pideActivos()
{
	if( !tagActivos.isEmpty() )
		mktAPI.sendCancel(tagActivos);
	mktAPI.sendSentence( "/ppp/active/print", tagActivos = "Activos" );
}

void QMikPPPManager::pideCambios()
{
	if( !tagListening.isEmpty() )
		mktAPI.sendCancel(tagListening);
	mktAPI.sendSentence( "/ppp/active/listen", tagListening = "Listening" );
}

void QMikPPPManager::onUsuarioRecibido(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage(tr("Usuarios recibidos. Pidiendo activos"));
		tagUsuarios.clear();
		ui->twUsuarios->fillupTable();
		pideActivos();
		break;
	case ROS::QSentence::Reply:
		ui->statusBar->showMessage(QString("Recibido: %1").arg(s.getID()));
		ui->twUsuarios->addSecret(s);
		break;
	case ROS::QSentence::Trap:
		addLogText(s.toString());
		break;
	case ROS::QSentence::Fatal:
		addLogText(s.toString());
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
		tagPerfiles.clear();
		ui->statusBar->showMessage( tr("Perfiles recibidos. Pidiendo usuarios") );
		pideUsuarios();
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
	static int counter;

	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage( tr("Activos recibidos. Comprobando cambios en vivo.") );
		counter = 0;
		pideCambios();
		break;
	case ROS::QSentence::Reply:
		ui->statusBar->showMessage(QString("Activo recibido: %1 (id=%2)").arg(++counter).arg(s.getID()));
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
		addLogText(tr("Conexión %1 (%2) recuperada con IP %3").arg(s.attribute("name"), s.getID(), s.attribute("address")));
	else
	{
		QSecretData *sc = ui->twUsuarios->findDataBySesionID(s.getID());
		if( sc != Q_NULLPTR )
		{
			if( sc->IPActiva() == sc->IPEstatica() )
				addLogText(tr("Conexión %1 (%2) cerrada. IP %3 reservada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
			else
				addLogText(tr("Conexión %1 (%2) cerrada. IP %3 liberada").arg(sc->usuario(), s.getID(), sc->IPActiva()));
		}
		else
			addLogText(tr("Conexión %1 cerrada").arg(s.attribute("name"), s.getID()));
	}
	ui->twUsuarios->actualizaUsuario(s);
}


void QMikPPPManager::on_anyadeUsuario_clicked()
{

}

#include "DlgConfiguracion.h"
void QMikPPPManager::on_btConfig_clicked()
{
	DlgConfiguracion *dlgConfig = new DlgConfiguracion(this);
	if( dlgConfig->exec() )
	{
		updateConfig();
	}
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

void QMikPPPManager::onDatoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &id)
{
	QSecretData *sd = ui->twUsuarios->findDataBySecretID(id);
	if( !sd )
		return;
	switch( col )
	{
	case QSecretDataModel::ColUsuario:
		break;
	case QSecretDataModel::ColPerfil:
		sd->setPerfilOriginal(dato);
		if( sd->activo() )
			sd->setPerfilReal(dato);
		actualizaPerfilRemoto(sd);
		reiniciaConexionRemota(sd);
		break;
	case QSecretDataModel::ColEstado:
		if( (dato == "activo") != sd->activo() )
		{
			// Las notas están vacías cuando aun no tiene los comentarios "formateados"
			if( sd->notas().isEmpty() )
				actualizaComentariosRemoto(sd);

			if( sd->activo() )
				sd->setPerfilReal(gGlobalConfig.perfilInactivo());
			else
				sd->setPerfilReal(sd->perfilOriginal());
			actualizaPerfilRemoto(sd);
		}
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
	case QSecretDataModel::ColConseguidor:
		sd->setConseguidor(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColEMail:
		sd->setEmail(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColVozIP:
		sd->setVozIP(dato != "No");
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::ColNotas:
		sd->setNotas(dato);
		actualizaComentariosRemoto(sd);
		break;
	case QSecretDataModel::NumColumnas:
		break;
	}
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
}
