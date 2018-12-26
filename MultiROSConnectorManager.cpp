#include "MultiROSConnectorManager.h"

namespace ROS
{

MultiConnectManager::MultiConnectManager(QObject *papi) :
	QObject(papi)
{

}

MultiConnectManager::~MultiConnectManager()
{

}

void MultiConnectManager::clear()
{
	Q_ASSERT(areAllDisconnected());
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		it.value()->deleteLater();
	}
	m_rosCommMap.clear();
}

void MultiConnectManager::addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort, const QString &uname, const QString &upass)
{
	Comm *mktAPI = new Comm(parent());

	mktAPI->setRouterName( routerName );
	mktAPI->setUserNamePass( uname, upass );
	mktAPI->setRemoteHost( hostAddr, hostPort );

	m_rosCommMap[routerName] = mktAPI;

	connect( mktAPI, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );

	connect( mktAPI, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onCommStateChanged(ROS::Comm::CommState)) );

	connect( mktAPI, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );

	connect( mktAPI, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onReceive(ROS::QSentence&)) );
}

QMap<QString, QString> MultiConnectManager::errorStrings() const
{
	ROSCommMapIterator it(m_rosCommMap);
	QMap<QString, QString> rtn;
	while( it.hasNext() )
	{
		it.next();
		rtn[it.key()] = it.value()->errorString();
	}
	return rtn;
}

QString MultiConnectManager::errorString(const QString &routerName) const
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (static_cast<ROS::Comm*>(sender())->routerName() == routerName) )
			return it.value()->errorString();
	}
	return QString();
}

bool MultiConnectManager::areAllDisconnected() const
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( !it.value()->isDisconnected() )
			return false;
	}
	return true;
}

bool MultiConnectManager::areAllConnected() const
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( !it.value()->isConnected() )
			return false;
	}
	return true;
}

void MultiConnectManager::sendCancel(const QString &tag, const QString &routerName)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (static_cast<ROS::Comm*>(sender())->routerName() == routerName) )
			it.value()->sendCancel(tag);
	}
}

void MultiConnectManager::connectHosts(const QString &routerName)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->connectToROS();
	}
}

void MultiConnectManager::disconnectHosts(bool force, const QString &routerName)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->closeCom(force);
	}
}

void MultiConnectManager::sendSentence(const QString &routerName, const QSentence &s)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->sendSentence(s);
	}
}

void MultiConnectManager::sendSentence(const QString &routerName, const QString &cmd, const QString &tag, const QStringList attrib)
{
	sendSentence( routerName, QSentence(cmd, tag, attrib) );
}

void MultiConnectManager::onComError(Comm::CommError /*commError*/, QAbstractSocket::SocketError /*socketError*/)
{
	QString routerName = static_cast<Comm*>(sender())->routerName();
	QString errorString = this->errorString( routerName );

	emit statusInfo( errorString, routerName );
	emit comError( errorString, routerName );
}

void MultiConnectManager::onReceive(QSentence &s)
{
	QString routerName = static_cast<Comm*>(sender())->routerName();
}

void MultiConnectManager::onCommStateChanged(Comm::CommState s)
{
	QString routerName = static_cast<Comm*>(sender())->routerName();

	switch( s )
	{
	case ROS::Comm::Unconnected:
		emit statusInfo( tr("Desconectado"), routerName );
		emit disconnected( routerName );
		if( areAllDisconnected() )
			emit allDisconnected();
		break;
	case ROS::Comm::HostLookup:
		emit statusInfo( tr("resolviendo URL"), routerName );
		break;
	case ROS::Comm::Connecting:
		emit statusInfo( tr("conectando al router"), routerName );
		break;
	case ROS::Comm::Connected:
		emit statusInfo( tr("Conectado al router"), routerName );
		if( areAllConnected() )
			emit allConected();
		break;
	case ROS::Comm::Closing:
		emit statusInfo( tr("Cerrado conexión"), routerName );
		break;
	}
}

void MultiConnectManager::onLoginChanged(Comm::LoginState s)
{
	QString routerName = static_cast<Comm*>(sender())->routerName();

	switch( s )
	{
	case ROS::Comm::NoLoged:
		emit statusInfo( tr("No está identificado en el servidor"), routerName );
		break;
	case ROS::Comm::LoginRequested:
		emit statusInfo( tr("Usuario y contraseña pedidos"), routerName );
		break;
	case ROS::Comm::UserPassSended:
		emit statusInfo( tr("Petición de login en curso"), routerName );
		break;
	case ROS::Comm::LogedIn:
		emit statusInfo( tr("Logado al router"), routerName );
		emit logued(routerName);
		break;
	}
}

} // End namespace ROS
