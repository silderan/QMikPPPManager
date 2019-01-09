#ifndef ROSPPPOEMANAGER_H
#define ROSPPPOEMANAGER_H

#include <QMap>
#include <QMapIterator>

#include "ROSAPI/Comm.h"
#include "ROSData/DataTypeID.h"
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

private:
	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;
	ROSPPPProfileManager  m_rosPPPProfileManager;
	ROSInterfaceManager m_rosInterfaceManager;
	ROSBridgePortManager m_rosBridgePortsManager;
	ROSIPAddressManager m_rosIPAddressManager;
	ROSIPPoolManager m_rosIPPoolManager;

	ROSDataManagerBase &rosDataManager(DataTypeID dataTypeID);

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}
	ROSPPPProfileManager &rosPPPProfileManager()		{ return m_rosPPPProfileManager;	}
	QList<ROSDataBase *>rosDataList(DataTypeID dataTypeID);

	void requestRemoteData(DataTypeID dataTypeID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateRemoteData(const ROSDataBase &newROSData, const QString &rosObjectID);

public slots:
	void onDataReceived(ROS::QSentence &sentence);

signals:
	void rosError(const QString &routerName, const QString &errorString);
};

typedef QList<ROSPPPoEManager*> ROSPPPoEManagerPList;	// PPPoE Manager pointer list.
typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
