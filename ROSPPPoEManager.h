#ifndef ROSPPPOEMANAGER_H
#define ROSPPPOEMANAGER_H

#include "Comm.h"
#include "ROSAPIUser.h"
#include "ROSAPIUserGroup.h"

template <typename T>
class ROSReceiverInfo
{
	QObject *m_ob;
	QString m_routerName;
	QString m_sentenceTag;
	int m_doneSlot;
	int m_replySlot;
	int m_errorSlot;
	QList<T> m_list;
	bool m_saveOnLocalList;
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
	ROSReceiverInfo() : m_saveOnLocalList(false), m_clearOnDone(true)
	{	}

	QString sentenceTag() { return m_sentenceTag;	}

	const QList<T> list() const { return m_list;	}

	void onDone(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !m_routerName.isEmpty() );
		if( m_ob && (m_doneSlot != -1) && sentence.tag() == m_sentenceTag )
		{
			m_ob->metaObject()->method(m_doneSlot).invoke(m_ob, Q_ARG(QString, m_routerName), Q_ARG(QList<T>*, &m_list));
			if( m_clearOnDone )
				m_ob = Q_NULLPTR;
		}
	}
	void onReply(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !m_routerName.isEmpty() );
		if( m_ob && (m_replySlot != -1) && sentence.tag() == m_sentenceTag )
		{
			T t(m_routerName, sentence);
			if( m_saveOnLocalList )
				m_list.append(t);
			m_ob->metaObject()->method(m_replySlot).invoke(m_ob, Q_ARG(QString, m_routerName), Q_ARG(T*, &t));
		}
	}

	void setup(QObject *receiverOb, const QString &routerName, const QString &sentenceTag, const char *replySlot, const char *doneSlot, const char *errorSlot, bool clearOnDone, bool saveOnInternaList)
	{
		Q_ASSERT( (m_ob = receiverOb)!= Q_NULLPTR );
		Q_ASSERT( !(m_routerName = routerName).isEmpty() );

		m_doneSlot			= setupSlot(doneSlot);
		m_replySlot			= setupSlot(replySlot);
		m_errorSlot			= setupSlot(errorSlot);
		m_sentenceTag		= sentenceTag;
		m_saveOnLocalList	= saveOnInternaList;
		m_clearOnDone		= clearOnDone;
	}
};

typedef ROSReceiverInfo<ROSAPIUser> ROSAPIUserManager;
typedef ROSReceiverInfo<ROSAPIUsersGroup> ROSAPIUsersGroupManager;

class ROSPPPoEManager : public ROS::Comm
{
Q_OBJECT

	ROSAPIUserManager m_rosAPIUserManager;
	ROSAPIUsersGroupManager m_rosAPIUsersGroupManager;

public:
	ROSPPPoEManager(QObject *papi);
	virtual ~ROSPPPoEManager() {	}

public slots:
	void onDataReceived(ROS::QSentence &sentence);

public:
	ROSAPIUserManager &rosApiUserManager()				{ return m_rosAPIUserManager;		}
	ROSAPIUsersGroupManager &rosApiUsersGroupManager()	{ return m_rosAPIUsersGroupManager;	}

	void requestAllAPIUsers(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
	void updateROSAPIUser(const ROSAPIUser &newROSAPIUser);
	void requestAllAPIUsersGroup(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot);
};

typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

#endif // ROSPPPOEMANAGER_H
