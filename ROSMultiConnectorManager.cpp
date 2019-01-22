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
	ROSPPPoEManager *rosPPPoEManager = new ROSPPPoEManager(parent());

	rosPPPoEManager->setRouterName( routerName );
	rosPPPoEManager->setUserNamePass( uname, upass );
	rosPPPoEManager->setRemoteHost( hostAddr, hostPort );

	m_rosPppoeManagerMap[routerName] = rosPPPoEManager;

	connect( rosPPPoEManager, SIGNAL(comError(ROS::Comm::CommError,QAbstractSocket::SocketError)),
			 this, SLOT(onComError(ROS::Comm::CommError,QAbstractSocket::SocketError)) );

	connect( rosPPPoEManager, SIGNAL(comStateChanged(ROS::Comm::CommState)),
			 this, SLOT(onCommStateChanged(ROS::Comm::CommState)) );

	connect( rosPPPoEManager, SIGNAL(loginStateChanged(ROS::Comm::LoginState)),
			 this, SLOT(onLoginChanged(ROS::Comm::LoginState)) );

	// Forward signals.
	connect( rosPPPoEManager, SIGNAL(rosError(QString,QString)), this, SIGNAL(rosError(QString,QString)) );
	connect( rosPPPoEManager, SIGNAL(rosModReply(ROSDataBase)), this, SIGNAL(rosModReply(ROSDataBase)) );
	connect( rosPPPoEManager, SIGNAL(rosDelReply(QString,DataTypeID,QString)), this, SIGNAL(rosDelReply(QString,DataTypeID,QString)) );
	connect( rosPPPoEManager, SIGNAL(rosDone(QString,DataTypeID)), this, SIGNAL(rosDone(QString,DataTypeID)) );
}

bool ROSMultiConnectManager::areAllDisconnected() const
{
	ROSPPPoEManagerIterator it(m_rosPppoeManagerMap);
	while( it.hasNext() )
	{
		it.next();
		if( (it.value() != Q_NULLPTR) && !it.value()->isDisconnected() )
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
		if( (it.value() == Q_NULLPTR) || !it.value()->isConnected() )
			return false;
	}
	return true;
}

ROSDataBasePList ROSMultiConnectManager::rosDataList(DataTypeID dataTypeID, const QString &routerName) const
{
	ROSDataBasePList rtn;

	foreach( ROSPPPoEManager *pppoeManager, m_rosPppoeManagerMap)
	{
		if( routerName.isEmpty() || (routerName == pppoeManager->routerName()) )
			rtn.append( pppoeManager->rosDataList(dataTypeID) );
	}
	return rtn;
}

QStringList ROSMultiConnectManager::rosAPIUsersGrupList() const
{
	QStringList rtn;
	QString t;
	foreach( const ROSDataBase *rosData, rosDataList(DataTypeID::APIUsersGroup) )
	{
		t = static_cast<const ROSAPIUsersGroup*>(rosData)->groupName();
		if( !t.isEmpty() && !rtn.contains(t) )
			rtn.append( t );
	}

	return rtn;
}

QStringList ROSMultiConnectManager::pppProfileNameList() const
{
	QStringList rtn;
	QString t;
	foreach( const ROSDataBase *rosData, rosDataList(DataTypeID::PPPProfile) )
	{
		t = static_cast<const ROSPPPProfile*>(rosData)->profileName();
		if( !t.isEmpty() && !rtn.contains(t) )
			rtn.append( t );
	}
	return rtn;
}

QStringList ROSMultiConnectManager::clientCities() const
{
	QStringList rtn;
	QString t;
	foreach( const ROSDataBase *rosData, rosDataList(DataTypeID::PPPSecret) )
	{
		t = static_cast<const ROSPPPSecret*>(rosData)->clientCity();
		if( !t.isEmpty() && !rtn.contains(t) )
			rtn.append( t );
	}
	return rtn;
}

QStringList ROSMultiConnectManager::staticIPv4List() const
{
	QStringList rtn;
	QString t;
	foreach( const ROSDataBase *rosData, rosDataList(DataTypeID::PPPSecret) )
	{
		t = static_cast<const ROSPPPSecret*>(rosData)->staticIP().toString();
		if( !t.isEmpty() && !rtn.contains(t) )
			rtn.append( t );
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

void ROSMultiConnectManager::updateRemoteData(const ROSDataBase &rosData)
{
	Q_ASSERT( m_rosPppoeManagerMap.contains(rosData.routerName()) );
	m_rosPppoeManagerMap[rosData.routerName()]->updateRemoteData(rosData, rosData.rosObjectID());
}

void ROSMultiConnectManager::updateRemoteData(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap)
{
	foreach( ROSPPPoEManager *pppoeManager, m_rosPppoeManagerMap )
	{
		pppoeManager->updateRemoteData( rosData, routerIDMap.dataID(pppoeManager->routerName()) );
	}
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, DataTypeID dataTypeID)
{
	foreach( ROSPPPoEManager *rosPPPoEManager, rosPPPoEManagerPList )
		ROSMultiConnectManager::requestAll(rosPPPoEManager, dataTypeID);
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManager *rosPPPoEManager, DataTypeID dataTypeID)
{
	rosPPPoEManager->requestRemoteData(dataTypeID);
}

void ROSMultiConnectManager::requestAll(DataTypeID dataTypeID)
{
	ROSMultiConnectManager::requestAll(m_rosPppoeManagerMap.values(), dataTypeID);
}

#ifdef SIMULATE_ROS_INPUTS
void ROSMultiConnectManager::simulateROSConnection()
{
	addROSConnection("simulated RouterA", "192.168.88.2", 8729, "", "" );
	emit logued( "simulated RouterA" );
	addROSConnection("simulated RouterB", "192.168.88.3", 8729, "", "" );
	emit logued( "simulated RouterB" );
	addROSConnection("simulated RouterC", "192.168.88.4", 8729, "", "" );
	emit logued( "simulated RouterC" );
}
#endif

void ROSMultiConnectManager::requestAll(const QString &routerName, DataTypeID dataTypeID)
{
	rosPppoeManager(routerName)->requestRemoteData(dataTypeID);
}

ROSMultiConnectManager multiConnectionManager;
