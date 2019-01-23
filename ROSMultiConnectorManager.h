#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QObject>
#include <QMap>

#include "ROSPPPoEManager.h"

#include "UnitTests.h"

class ROSMultiConnectManager : public QObject
{
Q_OBJECT

	ROSPPPoEManagerMap m_rosPppoeManagerMap;

	void updateRemoteData(ROSPPPoEManager *pppoeManager, const ROSDataBase &rosData, const QString &rosObjectID) const;
private slots:
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onCommStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

public:
	ROSMultiConnectManager(QObject *papi = Q_NULLPTR);
	~ROSMultiConnectManager();

	const ROSPPPoEManagerMap &rosPPPoEManagerMap() const		{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManagerMap &rosPPPoEManagerMap()					{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManager *rosPppoeManager(const QString &routerName)	{ return m_rosPppoeManagerMap.value(routerName, Q_NULLPTR);	}

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);

	bool areAllDisconnected()const;
	bool areAllConnected()const;

	void sendCancel(const QString &tag, const QString &routerName = QString());
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void sendSentence(const QString &routerName, const ROS::QSentence &s);
	void sendSentence(const QString &routerName, const QString &s, const QString &tag, const QStringList attrib = QStringList());

	static void requestAll(ROSPPPoEManager *rosPPPoEManager, DataTypeID dataTypeID);
	static void requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, DataTypeID dataTypeID);

	void requestAll(const QString &routerName, DataTypeID dataTypeID);
	void requestAll(DataTypeID dataTypeID);

	ROSDataBasePList rosDataList(DataTypeID dataTypeID, const QString &routerName = QString()) const;
	QStringList rosAPIUsersGrupList() const;
	QStringList pppProfileNameList() const;
	QStringList clientCities() const;
	QStringList staticIPv4List() const;

#ifdef SIMULATE_ROS_INPUTS
	void simulateROSConnection();
#endif

	// Use this just for send data to ONE router. Intended for removing active connection.
	// All the rest of remote updates must be done with the other funcion.
	void updateRemoteData( const ROSDataBase &rosData );

public slots:
	// Use this when you need to update remote data on ALL routers.
	// This should be the mainly used.
	void updateRemoteData(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);

signals:
	void statusInfo(const QString &info, const QString &routerName);
	void routerDisconnected(const QString &routerName);
	void routerConnected(const QString &routerName);
	void allConected();
	void allDisconnected();
	void logued(const QString &routerName);
	void comError(QString errorString, const QString &routerName);

	void rosError(const QString &routerName, QString errorString);
	void rosModReply(const ROSDataBase &rosData);
	void rosDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void rosDone(const QString &routerName, DataTypeID dataTypeID);
};

extern ROSMultiConnectManager multiConnectionManager;

#endif // MULTIROSCONNECTORMANAGER_H
