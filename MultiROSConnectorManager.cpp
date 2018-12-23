#include "MultiROSConnectorManager.h"

#define ROUTER_NAME_PROPERTY	("RouterName")
#define GET_ROUTER_NAME			(sender() ? sender()->property(ROUTER_NAME_PROPERTY).toString() : "")

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

	mktAPI->setProperty( ROUTER_NAME_PROPERTY, routerName );
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
		if( routerName.isEmpty() || (GET_ROUTER_NAME == routerName) )
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

void MultiConnectManager::disconnectHosts(bool force, const QString &routerName)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (GET_ROUTER_NAME == routerName) )
			it.value()->closeCom(force);
	}
}

QString MultiConnectManager::sendSentence(const QString &routerName, const QSentence &s)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( GET_ROUTER_NAME == routerName )
			return it.value()->sendSentence(s);
	}
	return "";
}

QString MultiConnectManager::sendSentence(const QString &routerName, const QString &cmd, const QString &tag, const QStringList attrib)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( GET_ROUTER_NAME == routerName )
			return it.value()->sendSentence(cmd, tag, attrib);
	}
	return "";
}

void MultiConnectManager::connectHosts(const QString &routerName)
{
	ROSCommMapIterator it(m_rosCommMap);
	while( it.hasNext() )
	{
		it.next();
		if( routerName.isEmpty() || (GET_ROUTER_NAME == routerName) )
			it.value()->connectToROS();
	}
}

void MultiConnectManager::onComError(Comm::CommError commError, QAbstractSocket::SocketError socketError)
{
	emit comError(commError, socketError, GET_ROUTER_NAME);
}

void MultiConnectManager::onReceive(QSentence &s)
{
	emit comReceive(s, GET_ROUTER_NAME);
}

void MultiConnectManager::onCommStateChanged(Comm::CommState s)
{
	emit comStateChanged(s, GET_ROUTER_NAME);
}

void MultiConnectManager::onLoginChanged(Comm::LoginState s)
{
	emit loginStateChanged(s, GET_ROUTER_NAME);
}

} // End namespace ROS
