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
	ui->leIP->setText(gGlobalConfig.getHost());
	ui->sbPort->setValue(gGlobalConfig.getPort());
	ui->leUser->setText(gGlobalConfig.getUserName());
	ui->lePass->setText(gGlobalConfig.getUserPass());

	connect( &mktAPI, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );
	connect( &mktAPI, SIGNAL(loginRequest(QString*,QString*)), this, SLOT(onLoginRequest(QString*,QString*)) );

	connect( &mktAPI, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onStateChanged(ROS::Comm::CommState)) );
	connect( &mktAPI, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );

	connect( &mktAPI, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onReceive(ROS::QSentence&)) );

	ui->twUsuarios->setColumnCount(NumColumnas);
	nombresColumnas.reserve(NumColumnas);
	nombresColumnas.append("Usuario");
	nombresColumnas.append("Perfil");
	nombresColumnas.append("Estado");
	nombresColumnas.append("Nombre");
	nombresColumnas.append("Dirección");
	nombresColumnas.append("Población");
	nombresColumnas.append("Teléfonos");
	nombresColumnas.append("Instalador");
	nombresColumnas.append("Notas");
	Q_ASSERT(nombresColumnas.count() == NumColumnas);
	ui->twUsuarios->setHorizontalHeaderLabels(nombresColumnas);
}

QMikPPPManager::~QMikPPPManager()
{
	mktAPI.closeCom();
	// Guardamos los datos del diálogo.
	gGlobalConfig.setHost(ui->leIP->text());
	gGlobalConfig.setPort(ui->sbPort->value());
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

void QMikPPPManager::onNewProfileSelected(const QString &profileName)
{
	// Uso esta variable para saber cuando ya se han recibido los datos
	// de los usuarios, que será cuando el cambio se ha producido
	// a través del GUI y no por la llegada de datos.
	if( tagUsuarios.isEmpty() )
	{
		QComboBox *cb = static_cast<QComboBox*>(sender());
		ROS::QSentence s("/ppp/secret/set");
		s.setID(cb->property("ID").toString());
		s.addAttribute("profile", profileName);
		mktAPI.sendSentence(s);
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
	if( s.tag() == tagUsuarios )
		onUsuarioRecibido(s);
	else
	if( s.tag() == tagPerfiles )
		onPerfilRecibido(s);
	else
	if( s.tag() == tagListening )
		actualizaUsuario(s);
	else
	if( s.getResultType() != ROS::QSentence::Done )
		addLogText(s.toString());
/*	switch( estado )
	{
	case Desconectado:
		throw "No posible!!!";
	case ReciviendoUsuarios:
		switch( s.getResultType() )
		{
		case ROS::QSentence::None:
			break;
		case ROS::QSentence::Done:
			estado = UsuariosRecividos;
			ui->twUsuarios->setEnabled(true);
			break;
		case ROS::QSentence::Trap:
			break;
		case ROS::QSentence::Fatal:
			mktAPI.closeCom(false);
			break;
		case ROS::QSentence::Reply:
			addUser(s);
			break;
		}
	case UsuariosRecividos:
		break;
	}
*/
}

QTableWidgetItem *QMikPPPManager::newTextItem(const QSecretData &s, const QString &txt)
{
	QTableWidgetItem *it = new QTableWidgetItem( txt );
	it->setData(Qt::UserRole, s.ID());
	return it;
}

QComboBox *QMikPPPManager::newListaPerfiles(const QSecretData &s)
{
	QString perfil = s.perfilOriginal();
	QString id = s.ID();
	QComboBox *cb = new QComboBox();
	cb->addItems(perfiles);
	cb->setCurrentText(perfil);
	cb->setProperty("ID", id);
	connect(cb, SIGNAL(currentIndexChanged(QString)), this, SLOT(onNewProfileSelected(QString)));
	return cb;
}

QCheckBox *QMikPPPManager::newEstado(const QSecretData &s)
{
	QCheckBox *cb = new QCheckBox("Activo");
	cb->setChecked(s.activo());
	cb->setProperty("ID", s.ID());
	return cb;
}

void QMikPPPManager::setCellData(int row, int col, const QSecretData &s, const QString &txt, QWidget *w)
{
	ui->twUsuarios->setItem(row, col, newTextItem(s, txt));
	if( w )
		ui->twUsuarios->setCellWidget(row, col, w);
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

void QMikPPPManager::pideCambios()
{
	if( !tagListening.isEmpty() )
		mktAPI.sendCancel(tagListening);
	mktAPI.sendSentence( "/ppp/active/listen", tagListening = "Listening" );
}

void QMikPPPManager::addSecretToTable(const QSecretData &s, int row)
{
	setCellData(row, ColUsuario, s, s.usuario(), 0);
	setCellData(row, ColPerfil, s, s.perfilOriginal(), newListaPerfiles(s));
	setCellData(row, ColEstado, s, s.activo() ? "1" : "0", newEstado(s));
	setCellData(row, ColNombre, s, s.nombre(), 0);
	setCellData(row, ColDireccion, s, s.direccion(), 0);
	setCellData(row, ColPoblacion, s, s.poblacion(), 0);
	setCellData(row, ColTelefonos, s, s.telefonos(), 0);
	setCellData(row, ColNotas, s, s.notas(), 0);
}

void QMikPPPManager::onUsuarioRecibido(const ROS::QSentence &s)
{
	switch( s.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		ui->statusBar->showMessage(tr("Usuarios recibidos"));
		tagUsuarios.clear();
		llenaTabla();
		pideCambios();
		break;
	case ROS::QSentence::Reply:
		ui->statusBar->showMessage(QString("Recibido: %1").arg(s.getID()));
		addSecret(s);
		break;
	case ROS::QSentence::Trap:
		addLogText(s.toString());
		break;
	case ROS::QSentence::Fatal:
		addLogText(s.toString());
		break;
	}
}

void QMikPPPManager::llenaTabla()
{
	ui->twUsuarios->clear();
	ui->twUsuarios->setHorizontalHeaderLabels(nombresColumnas);
	ui->twUsuarios->setRowCount(secretList.count());
	ui->twUsuarios->blockSignals(true);
	for( int i = 0; i < secretList.count(); i++ )
		addSecretToTable(secretList[i], i);
	ui->twUsuarios->blockSignals(false);
}

void QMikPPPManager::addPerfil(const ROS::QSentence &s)
{
	QString nombre = s.attribute("name");
	if( (nombre != gGlobalConfig.getPerfilInactivo()) && !perfiles.contains(nombre) )
		perfiles.append(nombre);
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
		addPerfil(s);
		break;
	case ROS::QSentence::Trap:
		break;
	case ROS::QSentence::Fatal:
		break;
	}
}

void QMikPPPManager::actualizaUsuario(const ROS::QSentence &s)
{
	s.getID();
}
