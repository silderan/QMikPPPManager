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
	ROSBridgePortManager m_rosBridgePortsManager;
	ROSIPAddressManager m_rosIPAddressManager;

	void updateRemoteData(const char *path, const ROSDataBase &newROSData, const ROSDataBase &oldROSData);
	void requestRemoteData(const char *path, const QString &sentenceTag);

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

	void requestAllInterfaces(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void requestAllBridges(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);

public slots:
	void onDataReceived(ROS::QSentence &sentence);

signals:
	void rosError(const QString &routerName, const QString &errorString);
};

typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
