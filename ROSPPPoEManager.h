#ifndef ROSPPPOEMANAGER_H
#define ROSPPPOEMANAGER_H

#include "ROSAPI/Comm.h"
#include "ROSData/ROSAPIUser.h"
#include "ROSData/ROSAPIUserGroup.h"
#include "ROSData/ROSPPPProfile.h"

template <typename T>
class ROSReceiverInfo
{
	QObject *m_ob;
	QString m_routerName;
	QString m_sentenceTag;
	int m_doneSlot;
	int m_replySlot;
	int m_errorSlot;
	QMap<QString, T> m_idDataMap;
	bool m_clearOnDone;

	int setupSlot(const char *slotFunction)
	{
		Q_ASSERT( m_ob != Q_NULLPTR );

		if( slotFunction != Q_NULLPTR )
		{
			while( isdigit(*slotFunction) )
				slotFunction++;
#ifndef QT_NO_DEBUG
			if( m_ob->metaObject()->indexOfMethod(slotFunction) == -1 )
				qWarning("Función %s no localizada en %s", slotFunction, m_ob->metaObject()->className());
			else
#endif
			return m_ob->metaObject()->indexOfMethod(slotFunction);
		}
		return -1;
	}

public:
	ROSReceiverInfo() : m_clearOnDone(true)
	{	}

	QString sentenceTag() { return m_sentenceTag;	}

	inline T rosData(const QString &dataID)			{ return m_idDataMap.value(dataID, T(QString("InvalidROSData")));	}
	inline const QList<T> rosDataList()				{ return m_idDataMap.values();		}
	inline const QMap<QString, T> &rosDataMap()		{ return m_idDataMap;				}

	void onDone(const ROS::QSentence &sentence)
	{
		if( m_ob && (m_doneSlot != -1) && sentence.tag() == m_sentenceTag )
		{
			Q_ASSERT( !m_routerName.isEmpty() );

			m_ob->metaObject()->method(m_doneSlot).invoke(m_ob, Q_ARG(QString, m_routerName) );
			if( m_clearOnDone )
				m_ob = Q_NULLPTR;
		}
	}
	void onReply(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !sentence.getID().isEmpty() );

		if( m_ob && (m_replySlot != -1) && (sentence.tag() == m_sentenceTag) )
		{
			Q_ASSERT( !m_routerName.isEmpty() );

			T t(m_routerName, sentence);

			if( t.deleting() )
				m_idDataMap.remove(t.dataID());
			else
				m_idDataMap.insert(sentence.getID(), t);

			m_ob->metaObject()->method(m_replySlot).invoke(m_ob, Q_ARG(QString, m_routerName), Q_ARG(T*, &t));
		}
	}

	void setup(QObject *receiverOb, const QString &routerName, const QString &sentenceTag, const char *replySlot, const char *doneSlot, const char *errorSlot, bool clearOnDone)
	{
		Q_ASSERT( (m_ob = receiverOb)!= Q_NULLPTR );
		Q_ASSERT( !(m_routerName = routerName).isEmpty() );

		m_doneSlot			= setupSlot(doneSlot);
		m_replySlot			= setupSlot(replySlot);
		m_errorSlot			= setupSlot(errorSlot);
		m_sentenceTag		= sentenceTag;
		m_clearOnDone		= clearOnDone;
	}
};

typedef ROSReceiverInfo<ROSAPIUser> ROSAPIUserManager;
typedef ROSReceiverInfo<ROSAPIUsersGroup> ROSAPIUsersGroupManager;
typedef ROSReceiverInfo<ROSPPPProfile> ROSPPPProfileManager;

class ROSPPPoEManager : public ROS::Comm
{
Q_OBJECT

	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;
	ROSPPPProfileManager  m_rosPPPProfileManager;

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

public slots:
	void onDataReceived(ROS::QSentence &sentence);
};

typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
