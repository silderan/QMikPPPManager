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

class ROSPPPoEManager : public ROS::Comm
{
Q_OBJECT

	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;
	ROSPPPProfileManager  m_rosPPPProfileManager;
	ROSInterfaceManager m_rosInterfaceManager;
	ROSInterfaceManager m_rosBridgeManager;
	ROSBridgePortManager m_rosBridgePortsManager;
	ROSIPAddressManager m_rosIPAddressManager;

	void updateRemoteData(ROSDataManagerBase &rosDataManager, const ROSDataBase &newROSData, const ROSDataBase &oldROSData);
	void requestRemoteData(ROSDataManagerBase &rosDataManager, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}
	ROSPPPProfileManager &rosPPPProfileManager()		{ return m_rosPPPProfileManager;	}

	void requestAllAPIUsers(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateROSAPIUser(const ROSAPIUser &newROSAPIUser);

	void requestAllPPPProfiles(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updatePPPProfile(const ROSPPPProfile &newROSAPIUser);

	void requestAllAPIUsersGroup(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);

	void requestAllIPAddress(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateIPAddress(const ROSIPAddress &newROSIPAddress);

	void requestAllInterfaces(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateBridgeInterface(const ROSInterface &newBridgeIface);

	void requestAllBridgePorts(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateBridgePort(const ROSBridgePort &newROSBridgePort);

public slots:
	void onDataReceived(ROS::QSentence &sentence);

signals:
	void rosError(const QString &routerName, const QString &errorString);
};

typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
