#include "ROSMultiConnectorManager.h"

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
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		it.value()->deleteLater();
	}
	m_rosPppoeManagerMap.clear();
}

void MultiConnectManager::addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort, const QString &uname, const QString &upass)
{
	ROSPPPoEManager *mktAPI = new ROSPPPoEManager(parent());

	mktAPI->setRouterName( routerName );
	mktAPI->setUserNamePass( uname, upass );
	mktAPI->setRemoteHost( hostAddr, hostPort );

	m_rosPppoeManagerMap[routerName] = mktAPI;

	connect( mktAPI, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );

	connect( mktAPI, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onCommStateChanged(ROS::Comm::CommState)) );

	connect( mktAPI, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );
}

bool MultiConnectManager::areAllDisconnected() const
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
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
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
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
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->sendCancel(tag);
	}
}

void MultiConnectManager::connectHosts(const QString &routerName)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->connectToROS();
	}
}

void MultiConnectManager::disconnectHosts(bool force, const QString &routerName)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->closeCom(force);
	}
}

void MultiConnectManager::sendSentence(const QString &routerName, const QSentence &s)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
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
	ROSPPPoEManager *rosManager = static_cast<ROSPPPoEManager*>(sender());
	QString errorString = rosManager->errorString();

	emit statusInfo( errorString, rosManager );
	emit comError( errorString, rosManager );
}

void MultiConnectManager::onCommStateChanged(Comm::CommState s)
{
	switch( s )
	{
	case ROS::Comm::Unconnected:
		emit statusInfo( tr("Desconectado"), static_cast<ROSPPPoEManager*>(sender()) );
		emit routerDisconnected( static_cast<ROSPPPoEManager*>(sender()) );
		if( areAllDisconnected() )
		{
			emit statusInfo( tr("Desconectado de todos los routers"), Q_NULLPTR );
			emit allDisconnected();
		}
		break;
	case ROS::Comm::HostLookup:
		emit statusInfo( tr("resolviendo URL"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	case ROS::Comm::Connecting:
		emit statusInfo( tr("conectando al router"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	case ROS::Comm::Connected:
		emit statusInfo( tr("Conectado al router"), static_cast<ROSPPPoEManager*>(sender()) );
		emit routerConnected( static_cast<ROSPPPoEManager*>(sender()) );
		if( areAllConnected() )
		{
			emit statusInfo( tr("Conectado a todos los routers"), Q_NULLPTR );
			emit allConected();
		}
		break;
	case ROS::Comm::Closing:
		emit statusInfo( tr("Cerrado conexión"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	}
}

void MultiConnectManager::onLoginChanged(Comm::LoginState s)
{
	switch( s )
	{
	case ROS::Comm::NoLoged:
		emit statusInfo( tr("No está identificado en el servidor"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	case ROS::Comm::LoginRequested:
		emit statusInfo( tr("Usuario y contraseña pedidos"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	case ROS::Comm::UserPassSended:
		emit statusInfo( tr("Petición de login en curso"), static_cast<ROSPPPoEManager*>(sender()) );
		break;
	case ROS::Comm::LogedIn:
		emit statusInfo( tr("Logado al router"), static_cast<ROSPPPoEManager*>(sender()) );
		emit logued( static_cast<ROSPPPoEManager*>(sender()) );
		break;
	}
}

} // End namespace ROS
