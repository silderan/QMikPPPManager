#ifndef ROSPPPOEMANAGER_H
#define ROSPPPOEMANAGER_H

#include <QMap>
#include <QMapIterator>

#include "ROSAPI/Comm.h"
#include "ROSData/ROSAPIUser.h"
#include "ROSData/ROSAPIUserGroup.h"
#include "ROSData/ROSPPPProfile.h"

#include "ROSDataManager/ROSAPIUserManager.h"
#include "ROSDataManager/ROSAPIUsersGroupManager.h"
#include "ROSDataManager/ROSPPPProfileManager.h"
#include "ROSDataManager/ROSInterfaceManager.h"
#include "ROSDataManager/ROSBridgePortManager.h"
#include "ROSDataManager/ROSIPAddressManager.h"
#include "ROSDataManager/ROSIPPoolManager.h"

class ROSPPPoEManager : public ROS::Comm
{
Q_OBJECT

public:
	enum ManagerID
	{
		APIUser,
		APIUsersGroup,
		PPPProfile,
		Interface,
		BridgePorts,
		IPAddress,
		IPPool,
		TotalIDs
	};

private:
	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;
	ROSPPPProfileManager  m_rosPPPProfileManager;
	ROSInterfaceManager m_rosInterfaceManager;
	ROSBridgePortManager m_rosBridgePortsManager;
	ROSIPAddressManager m_rosIPAddressManager;
	ROSIPPoolManager m_rosIPPoolManager;

	ROSDataManagerBase &rosDataManager(ManagerID &managerID);

	void requestRemoteData(ROSDataManagerBase &rosDataManager, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateRemoteData(ROSDataManagerBase &rosDataManager, const ROSDataBase &newROSData, const QString &rosDataID);

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}
	ROSPPPProfileManager &rosPPPProfileManager()		{ return m_rosPPPProfileManager;	}
	QList<ROSDataBase *>rosDataList(ROSPPPoEManager::ManagerID managerID);

	void requestRemoteData(ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateRemoteData(ROSPPPoEManager::ManagerID managerID, const ROSDataBase &newROSData, const QString &rosDataID);

public slots:
	void onDataReceived(ROS::QSentence &sentence);

signals:
	void rosError(const QString &routerName, const QString &errorString);
};

typedef QList<ROSPPPoEManager*> ROSPPPoEManagerPList;	// PPPoE Manager pointer list.
typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
