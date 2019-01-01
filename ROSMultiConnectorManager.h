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

	const ROSPPPoEManagerMap &rosPPPoEManagerMap() const	{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManagerMap &rosPPPoEManagerMap()				{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManager *rosPppoeManager(const QString &routerName)	{ return m_rosPppoeManagerMap[routerName];	}

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);

	bool areAllDisconnected()const;
	bool areAllConnected()const;

	QStringList rosAPIUsersGrupList()const;

public slots:
	void sendCancel(const QString &tag, const QString &routerName = QString());
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void sendSentence(const QString &routerName, const ROS::QSentence &s);
	void sendSentence(const QString &routerName, const QString &s, const QString &tag, const QStringList attrib = QStringList());

	void setROSAPIUserData(ROSAPIUser rosAPIUser, const QRouterIDMap &routerIDMap);

signals:
	void statusInfo(const QString &info, const QString &routerName);
	void routerDisconnected(const QString &routerName);
	void routerConnected(const QString &routerName);
	void allConected();
	void allDisconnected();
	void logued(const QString &routerName);
	void comError(QString errorString, const QString &routerName);
};

extern ROSMultiConnectManager mktAPI;

#endif // MULTIROSCONNECTORMANAGER_H
/*
Entrants: Compra *Carmeta*
```  embotits
  olives
  papes
  tostadetes
   foie
   formatjes
   salmó```
Crosta (LO QUE SE TROBE!!!): Compra ?  Cuina *Patri*
Primer (Canelons): Compra *Carmeta* Cuina *Carmeta*
Segon (Abadejo): Compra *Lourdes* Cuina *Lourdes*
Postre ???: *Patri sap què vol fer*
Beguda Compra *Carmeta*
```  3-ViBlanc
  1-ViNegre
  2-Cava
  3l-Cerveza (En litrones, quintos o tercios)
  1-Cerveza Light (Radler, Mixta, etc)
  2l-Coca-Cola Zero Zero
  2l-Fanta LLima
  2l-Fanta Taronja
  4l-d'aigua
  1-Licor d'arròs```
*/

