#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QObject>
#include <QMap>

#include "Comm.h"
#include "ROSAPIUser.h"

namespace ROS
{

typedef QMap<QString, Comm*> ROSCommMap;
typedef QMapIterator<QString, Comm*> ROSCommMapIterator;

class MultiConnectManager : public QObject
{
Q_OBJECT

	ROSCommMap m_rosCommMap;
	QMultiROSAPIUserManager m_rosAPIUser;

private slots:
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onReceive(ROS::QSentence &s);
	void onCommStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

public:
	MultiConnectManager(QObject *papi = Q_NULLPTR);
	~MultiConnectManager();

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);

	QMap<QString, QString> errorStrings()const;
	QString errorString(const QString &routerName)const;
	bool areAllDisconnected()const;
	bool areAllConnected()const;

public slots:
	void sendCancel(const QString &tag, const QString &routerName = QString());
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void sendSentence(const QString &routerName, const QSentence &s);
	void sendSentence(const QString &routerName, const QString &s, const QString &tag, const QStringList attrib = QStringList());

public:
	void requestAPIUsers(Comm *mktAPI)				{ m_rosAPIUser.requestAPIUsers(mktAPI);		}
	void requestAPIUsers(const QString &routerName)	{ requestAPIUsers(m_rosCommMap[routerName]);}

	void requestAPIUserGroups(Comm *mktAPI)					{ m_rosAPIUser.requestAPIUserGroups(mktAPI);	}
	void requestAPIUserGroups(const QString &routerName)	{ requestAPIUserGroups(m_rosCommMap[routerName]);}

signals:
	void statusInfo(QString info, QString routerName = QString());
	void disconnected(QString routerName);
	void connected(QString routerName);
	void allConected();
	void allDisconnected();
	void logued(QString routerName);
	void comError(QString errorString, QString routerName);
};
}
#endif // MULTIROSCONNECTORMANAGER_H
