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

#ifndef ROSPPPOEMANAGER_H
#define ROSPPPOEMANAGER_H

#include <QMap>
#include <QMapIterator>

#include "ROSAPI/Comm.h"
#include "ROSData/DataTypeID.h"
#include "ROSData/ROSAPIUser.h"
#include "ROSData/ROSAPIUserGroup.h"
#include "ROSData/ROSPPPProfile.h"

#include "UnitTests.h"

#include "ROSDataManager/ROSAPIUserManager.h"
#include "ROSDataManager/ROSAPIUsersGroupManager.h"
#include "ROSDataManager/ROSPPPProfileManager.h"
#include "ROSDataManager/ROSInterfaceManager.h"
#include "ROSDataManager/ROSBridgePortManager.h"
#include "ROSDataManager/ROSIPAddressManager.h"
#include "ROSDataManager/ROSIPPoolManager.h"
#include "ROSDataManager/ROSPPPSecretManager.h"
#include "ROSDataManager/ROSPPPActiveManager.h"

class ROSPPPoEManager : public ROS::Comm
{
Q_OBJECT

private:
	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;
	ROSPPPProfileManager  m_rosPPPProfileManager;
	ROSInterfaceManager m_rosInterfaceManager;
	ROSBridgePortManager m_rosBridgePortsManager;
	ROSIPAddressManager m_rosIPAddressManager;
	ROSIPPoolManager m_rosIPPoolManager;
	ROSPPPSecretManager m_rosSecretManager;
	ROSPPPActiveManager m_rosActiveManager;
	QString mRouterName;

	ROSDataManagerBase &rosDataManager(DataTypeID dataTypeID);
	const ROSDataManagerBase &rosDataManager(DataTypeID dataTypeID) const;

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}
	ROSPPPProfileManager &rosPPPProfileManager()		{ return m_rosPPPProfileManager;	}
	ROSDataBasePList rosDataList(DataTypeID dataTypeID) const;
	bool done(DataTypeID dataTypeID) const;

	void requestRemoteData(DataTypeID dataTypeID);
	void updateRemoteData(const ROSDataBase &newROSData, const QString &rosObjectID);

	void setRouterName(const QString &name)	{ mRouterName = name;	}
	QString routerName() const	{ return mRouterName;	}

#ifdef SIMULATE_ROS_INPUTS
private slots:
	void simulateStep();
#endif

private slots:
	void onDataReceived(ROS::QSentence &sentence);
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onCommStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

signals:
	void statusInfo(const QString &routerName, const QString &info);
	void routerDisconnected(const QString &routerName);
	void routerConnected(const QString &routerName);
	void logued(const QString &routerName);
	void comError(const QString &routerName, const QString &errorString);
	void rosError(const QString &routerName, const QString &errorString);
	void rosModReply(const ROSDataBase &rosData);
	void rosDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void rosDone(const QString &routerName, DataTypeID dataTypeID);
};

typedef QList<ROSPPPoEManager*> ROSPPPoEManagerPList;	// PPPoE Manager pointer list.
typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
