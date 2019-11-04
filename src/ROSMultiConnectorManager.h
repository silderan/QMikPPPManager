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

#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QObject>
#include <QMap>

#include "ROSPPPoEManager.h"
#include "RadiusManager/QRadiusManager.h"

#include "UnitTests.h"

class ROSMultiConnectManager : public QObject
{
Q_OBJECT

	ROSPPPoEManagerMap m_rosPppoeManagerMap;
#ifdef USE_RADIUS
	QRadiusManager m_radiusManager;
#endif

	void updateRemoteData(ROSPPPoEManager *pppoeManager, const ROSDataBase &rosData, const QString &rosObjectID);

	static void requestAll(ROSPPPoEManager *rosPPPoEManager, DataTypeID dataTypeID);
	static void requestAll(ROSPPPoEManagerPList rosPPPoEManagerPList, DataTypeID dataTypeID);

	void onLogued(const QString &routerName);
	void onRouterConnected(const QString &routerName);
	void onRouterDisconnected(const QString &routerName);

	QStringList rosNameList(DataTypeID dataTypeID, std::function<QString (const ROSDataBase *)> getFnc, const QString &routerName = QString()) const;
	QStringList rosNameList(DataTypeID dataTypeID, std::function<QStringList (const ROSDataBase *)> getFnc, const QString &routerName = QString()) const;

public:
	ROSMultiConnectManager(QObject *papi = Q_NULLPTR);
	~ROSMultiConnectManager();

	const ROSPPPoEManagerMap &rosPPPoEManagerMap() const		{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManagerMap &rosPPPoEManagerMap()					{ return m_rosPppoeManagerMap;	}
	ROSPPPoEManager *rosPppoeManager(const QString &routerName)	{ return m_rosPppoeManagerMap.value(routerName, Q_NULLPTR);	}

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);
#ifdef USE_RADIUS
	void setRadiusConnection(const ConnectInfo &connInfo, const QString &dataBaseName)	{ m_radiusManager.setConnInfo(connInfo, dataBaseName);	}
#endif

	bool areAllDisconnected()const;
	bool areAllConnected()const;
	bool allDone(DataTypeID dataTypeID, const QString &routerName = QString()) const;

	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void requestAll(const QString &routerName, DataTypeID dataTypeID);
	void requestAll(DataTypeID dataTypeID);

	ROSDataBasePList rosDataList(DataTypeID dataTypeID, const QString &routerName = QString()) const;
	QStringList rosAPIUserNameList(const QString &routerName = QString()) const;
	QStringList rosAPIUsersGrupList(const QString &routerName = QString()) const;
	QStringList pppProfileNameList(const QString &routerName = QString()) const;
	QStringList interfaceNameList(const QString &type, const QString &routerName = QString()) const;
	QStringList bridgeNameList(const QString &routerName = QString()) const;
	QStringList etherNameList(const QString &routerName = QString()) const;
	QStringList poolNameList(const QString &routerName = QString()) const;
	QStringList clientCities(const QString &routerName = QString()) const;
	QStringList staticIPv4List(const QString &routerName = QString()) const;

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
	void statusInfo(const QString &routerName, const QString &info);
	void routerDisconnected(const QString &routerName);
	void allRoutersDisconected();

	void routerConnected(const QString &routerName);
	void allRoutersConected();

	void logued(const QString &routerName);
	void comError(const QString &routerName, const QString &errorString);
	void rosError(const QString &routerName, const QString &errorString);
	void rosModReply(const ROSDataBase &rosData);
	void rosDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void rosDone(const QString &routerName, DataTypeID dataTypeID);
};

extern ROSMultiConnectManager multiConnectionManager;

#endif // MULTIROSCONNECTORMANAGER_H
