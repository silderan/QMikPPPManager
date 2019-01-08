#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QObject>
#include <QMap>

#include "ROSPPPoEManager.h"

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
	ROSPPPoEManager *rosPppoeManager(const QString &routerName)	{ return m_rosPppoeManagerMap[routerName];	}

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);

	bool areAllDisconnected()const;
	bool areAllConnected()const;

	void sendCancel(const QString &tag, const QString &routerName = QString());
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void sendSentence(const QString &routerName, const ROS::QSentence &s);
	void sendSentence(const QString &routerName, const QString &s, const QString &tag, const QStringList attrib = QStringList());

	QList<ROSDataBase *>rosDataList(ROSPPPoEManager::ManagerID managerID) const;
	QStringList rosAPIUsersGrupList()const;

	static void requestAll(ROSPPPoEManager *rosPPPoEManager, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	static void requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);

	void requestAll(const QString &routerName, ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void requestAll(ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);

	void updateRemoteData(ROSPPPoEManager::ManagerID managerID, const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);

signals:
	void statusInfo(const QString &info, const QString &routerName);
	void routerDisconnected(const QString &routerName);
	void routerConnected(const QString &routerName);
	void allConected();
	void allDisconnected();
	void logued(const QString &routerName);
	void comError(QString errorString, const QString &routerName);
	void rosError(const QString &routerName, QString errorString);
};

extern ROSMultiConnectManager mktAPI;

#endif // MULTIROSCONNECTORMANAGER_H
