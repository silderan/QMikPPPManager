#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QObject>

#include "Comm.h"

#include <QMap>

namespace ROS
{

typedef QMap<QString, Comm*> ROSCommMap;
typedef QMapIterator<QString, Comm*> ROSCommMapIterator;

class MultiConnectManager : public QObject
{
Q_OBJECT

	ROSCommMap m_rosCommMap;

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
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	QString sendSentence(const QString &routerName , const QSentence &s);
	QString sendSentence(const QString &routerName , const QString &s, const QString &tag, const QStringList attrib = QStringList());

signals:
	void comError(ROS::Comm::CommError ce, QAbstractSocket::SocketError se, const QString &routerName);
	void comReceive(ROS::QSentence &s, const QString &routerName);
	void comStateChanged(ROS::Comm::CommState s, const QString &routerName);
	void loginStateChanged(ROS::Comm::LoginState s, const QString &routerName);
};
}
#endif // MULTIROSCONNECTORMANAGER_H
