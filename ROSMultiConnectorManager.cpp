#include "ROSMultiConnectorManager.h"

ROSMultiConnectManager::ROSMultiConnectManager(QObject *papi) :
	QObject(papi)
{
}

ROSMultiConnectManager::~ROSMultiConnectManager()
{

}

void ROSMultiConnectManager::clear()
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

void ROSMultiConnectManager::addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort, const QString &uname, const QString &upass)
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

	// Forward error signal.
	connect( mktAPI, SIGNAL(rosError(QString,QString)),
			 this, SIGNAL(rosError(QString,QString)) );
}

bool ROSMultiConnectManager::areAllDisconnected() const
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

bool ROSMultiConnectManager::areAllConnected() const
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

QList<ROSDataBase *> ROSMultiConnectManager::rosDataList(ROSPPPoEManager::ManagerID managerID) const
{
	QList<ROSDataBase*> rtn;
	ROSPPPoEManagerIterator pppoeManagerIterator(m_rosPppoeManagerMap);

	while( pppoeManagerIterator.hasNext() )
	{
		pppoeManagerIterator.next();
		rtn.append( pppoeManagerIterator.value()->rosDataList(managerID) );
	}
	return rtn;
}

QStringList ROSMultiConnectManager::rosAPIUsersGrupList() const
{
	QStringList rtn;
	foreach( const ROSDataBase *rosData, rosDataList(ROSPPPoEManager::APIUsersGroup) )
	{
		if( !rtn.contains( static_cast<const ROSAPIUsersGroup*>(rosData)->groupName()) )
			rtn.append( static_cast<const ROSAPIUsersGroup*>(rosData)->groupName() );
	}

	return rtn;
}

void ROSMultiConnectManager::sendCancel(const QString &tag, const QString &routerName)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->sendCancel(tag);
	}
}

void ROSMultiConnectManager::connectHosts(const QString &routerName)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->connectToROS();
	}
}

void ROSMultiConnectManager::disconnectHosts(bool force, const QString &routerName)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->closeCom(force);
	}
}

void ROSMultiConnectManager::sendSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (it.value()->routerName() == routerName) )
			it.value()->sendSentence(s);
	}
}

void ROSMultiConnectManager::sendSentence(const QString &routerName, const QString &cmd, const QString &tag, const QStringList attrib)
{
	sendSentence( routerName, ROS::QSentence(cmd, tag, attrib) );
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	foreach( ROSPPPoEManager *rosPPPoEManager, rosPPPoEManagerPList)
		ROSMultiConnectManager::requestAll(rosPPPoEManager, managerID, receiverOb, replySlot, doneSlot, errorSlot);
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManager *rosPPPoEManager, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	rosPPPoEManager->requestRemoteData(managerID, receiverOb, replySlot, doneSlot, errorSlot);
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	ROSMultiConnectManager::requestAll(m_rosPppoeManagerMap.values(), managerID, receiverOb, replySlot, doneSlot, errorSlot);
}

void ROSMultiConnectManager::requestAll(const QString &routerName, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	rosPppoeManager(routerName)->requestRemoteData(managerID, receiverOb, replySlot, doneSlot, errorSlot);
}

void ROSMultiConnectManager::onComError(ROS::Comm::CommError /*commError*/, QAbstractSocket::SocketError /*socketError*/)
{
	QString routerName = static_cast<ROSPPPoEManager*>(sender())->routerName();
	QString errorString = static_cast<ROSPPPoEManager*>(sender())->errorString();

	emit statusInfo( errorString, routerName );
	emit comError( errorString, routerName );
}

void ROSMultiConnectManager::onCommStateChanged(ROS::Comm::CommState s)
{
	switch( s )
	{
	case ROS::Comm::Unconnected:
		emit statusInfo( tr("Desconectado"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		emit routerDisconnected( static_cast<ROSPPPoEManager*>(sender())->routerName() );
		if( areAllDisconnected() )
		{
			emit statusInfo( tr("Desconectado de todos los routers"), QString() );
			emit allDisconnected();
		}
		break;
	case ROS::Comm::HostLookup:
		emit statusInfo( tr("resolviendo URL"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	case ROS::Comm::Connecting:
		emit statusInfo( tr("conectando al router"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	case ROS::Comm::Connected:
		emit statusInfo( tr("Conectado al router"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		emit routerConnected( static_cast<ROSPPPoEManager*>(sender())->routerName() );
		if( areAllConnected() )
		{
			emit statusInfo( tr("Conectado a todos los routers"), QString() );
			emit allConected();
		}
		break;
	case ROS::Comm::Closing:
		emit statusInfo( tr("Cerrado conexión"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	}
}

void ROSMultiConnectManager::onLoginChanged(ROS::Comm::LoginState s)
{
	switch( s )
	{
	case ROS::Comm::NoLoged:
		emit statusInfo( tr("No está identificado en el servidor"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	case ROS::Comm::LoginRequested:
		emit statusInfo( tr("Usuario y contraseña pedidos"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	case ROS::Comm::UserPassSended:
		emit statusInfo( tr("Petición de login en curso"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	case ROS::Comm::LogedIn:
		emit statusInfo( tr("Logado al router"), static_cast<ROSPPPoEManager*>(sender())->routerName() );
		emit logued( static_cast<ROSPPPoEManager*>(sender())->routerName() );
		break;
	}
}

void ROSMultiConnectManager::updateRemoteData(ROSPPPoEManager::ManagerID managerID, const ROSDataBase &rosData, const QRouterIDMap &routerIDMap)
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		it.value()->updateRemoteData( managerID, rosData, routerIDMap.dataID(it.key()) );
	}
}

ROSMultiConnectManager mktAPI;
