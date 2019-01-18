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

#ifdef SIMULATE_ROS_INPUTS
	void simulateROSConnection();
#endif

public slots:
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
