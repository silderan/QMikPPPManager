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
	ROSPPPActiveManager  m_rosActiveManager;

	ROSDataManagerBase &rosDataManager(DataTypeID dataTypeID);
	const ROSDataManagerBase &rosDataManager(DataTypeID dataTypeID) const;

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}
	ROSPPPProfileManager &rosPPPProfileManager()		{ return m_rosPPPProfileManager;	}
	ROSDataBasePList rosDataList(DataTypeID dataTypeID) const;

	void requestRemoteData(DataTypeID dataTypeID);
	void updateRemoteData(const ROSDataBase &newROSData, const QString &rosObjectID);

#ifdef SIMULATE_ROS_INPUTS
private slots:
	void simulateStep();
#endif

public slots:
	void onDataReceived(ROS::QSentence &sentence);

signals:
	void rosError(const QString &routerName, const QString &errorString);
	void rosModReply(const ROSDataBase &rosData);
	void rosDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void rosDone(const QString &routerName, DataTypeID dataTypeID);
};

typedef QList<ROSPPPoEManager*> ROSPPPoEManagerPList;	// PPPoE Manager pointer list.
typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
