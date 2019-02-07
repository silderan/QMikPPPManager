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

bool ROSMultiConnectManager::allDone(DataTypeID dataTypeID, const QString &routerName) const
{
	foreach( ROSPPPoEManager *pppoeManager, m_rosPppoeManagerMap)
	{
		if( routerName.isEmpty() || (routerName == pppoeManager->routerName()) )
			if( !pppoeManager->done(dataTypeID) )
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

QStringList ROSMultiConnectManager::rosNameList(DataTypeID dataTypeID, std::function<QString (const ROSDataBase *)> getFnc, const QString &routerName) const
{
	QStringList rtn;
	QString t;
	foreach( const ROSDataBase *rosData, rosDataList(dataTypeID, routerName) )
	{
		Q_ASSERT(rosData);
		t = getFnc(rosData);
		if( !t.isEmpty() && !rtn.contains(t) )
			rtn.append( t );
	}

	return rtn;
}

QStringList ROSMultiConnectManager::rosAPIUserNameList(const QString &routerName) const
{
	return rosNameList(DataTypeID::APIUser, [] (const ROSDataBase *rosData) {
		Q_ASSERT(dynamic_cast<const ROSAPIUser*>(rosData));

		return static_cast<const ROSAPIUser*>(rosData)->userName();
	}, routerName );
}

QStringList ROSMultiConnectManager::rosAPIUsersGrupList(const QString &routerName) const
{
	return rosNameList(DataTypeID::APIUsersGroup, [] (const ROSDataBase *rosData) {
		Q_ASSERT(dynamic_cast<const ROSAPIUsersGroup*>(rosData));

		return static_cast<const ROSAPIUsersGroup*>(rosData)->groupName();
	}, routerName );
}

QStringList ROSMultiConnectManager::pppProfileNameList(const QString &routerName) const
{
	return rosNameList(DataTypeID::PPPProfile, [] (const ROSDataBase *rosData) {
		Q_ASSERT(dynamic_cast<const ROSPPPProfile*>(rosData));

		return static_cast<const ROSPPPProfile*>(rosData)->profileName();
	}, routerName );
}

QStringList ROSMultiConnectManager::interfaceNameList(const QString &type, const QString &routerName) const
{
	return rosNameList(DataTypeID::Interface, [type](const ROSDataBase *rosDataBase) {
		Q_ASSERT(dynamic_cast<const ROSInterface*>(rosDataBase));

		if( type.isEmpty() || (static_cast<const ROSInterface*>(rosDataBase)->interfaceType() == type) )
			return static_cast<const ROSInterface*>(rosDataBase)->interfaceName();
		return QString();
	}, routerName );
}

QStringList ROSMultiConnectManager::bridgeNameList(const QString &routerName) const
{
	return interfaceNameList("bridge", routerName);
}

QStringList ROSMultiConnectManager::etherNameList(const QString &routerName) const
{
	return interfaceNameList("ether", routerName);
}

QStringList ROSMultiConnectManager::poolNameList(const QString &routerName) const
{
	return rosNameList(DataTypeID::IPPool, [](const ROSDataBase *rosDataBase) {
		Q_ASSERT(dynamic_cast<const ROSIPPool*>(rosDataBase));

		return static_cast<const ROSIPPool*>(rosDataBase)->poolName();
	}, routerName );
}

QStringList ROSMultiConnectManager::clientCities(const QString &routerName) const
{
	return rosNameList(DataTypeID::PPPSecret, [] (const ROSDataBase *rosData) {
		Q_ASSERT(dynamic_cast<const ROSPPPSecret*>(rosData));

		return static_cast<const ROSPPPSecret*>(rosData)->clientCity();
	}, routerName );
}

QStringList ROSMultiConnectManager::staticIPv4List(const QString &routerName) const
{
	return rosNameList(DataTypeID::PPPSecret, [] (const ROSDataBase *rosData) {
		Q_ASSERT(dynamic_cast<const ROSPPPSecret*>(rosData));

		return static_cast<const ROSPPPSecret*>(rosData)->staticIP().toString();
	}, routerName );
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
#ifdef USE_RADIUS
	if( !m_radiusManager.open() )
		emit comError( m_radiusManager.lastErrorString(), m_radiusManager.name() );
	else
		m_radiusManager.requestAll(DataTypeID::PPPSecret);
#endif
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
#ifdef USE_RADIUS
	m_radiusManager.close();
#endif
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

void ROSMultiConnectManager::updateRemoteData(ROSPPPoEManager *pppoeManager, const ROSDataBase &rosData, const QString &rosObjectID)
{
	pppoeManager->updateRemoteData(rosData, rosObjectID);
#ifdef USE_RADIUS
	if( !m_radiusManager.updateRemoteData(rosData) )
		emit comError( m_radiusManager.lastErrorString(), m_radiusManager.name() );
#endif
}

void ROSMultiConnectManager::updateRemoteData(const ROSDataBase &rosData)
{
	Q_ASSERT( m_rosPppoeManagerMap.contains(rosData.routerName()) );
	updateRemoteData( m_rosPppoeManagerMap[rosData.routerName()], rosData, rosData.rosObjectID() );
}

void ROSMultiConnectManager::updateRemoteData(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap)
{
	foreach( ROSPPPoEManager *pppoeManager, m_rosPppoeManagerMap )
		updateRemoteData( pppoeManager, rosData, routerIDMap.dataID(pppoeManager->routerName()) );
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManager *rosPPPoEManager, DataTypeID dataTypeID)
{
	rosPPPoEManager->requestRemoteData(dataTypeID);
}

void ROSMultiConnectManager::requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, DataTypeID dataTypeID)
{
	foreach( ROSPPPoEManager *rosPPPoEManager, rosPPPoEManagerPList )
		ROSMultiConnectManager::requestAll(rosPPPoEManager, dataTypeID);
}

void ROSMultiConnectManager::requestAll(DataTypeID dataTypeID)
{
	ROSMultiConnectManager::requestAll(m_rosPppoeManagerMap.values(), dataTypeID);
}

void ROSMultiConnectManager::requestAll(const QString &routerName, DataTypeID dataTypeID)
{
	rosPppoeManager(routerName)->requestRemoteData(dataTypeID);
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

ROSMultiConnectManager multiConnectionManager;
