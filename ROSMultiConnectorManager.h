#ifndef MULTIROSCONNECTORMANAGER_H
#define MULTIROSCONNECTORMANAGER_H

#include <QMetaMethod>
#include <QObject>
#include <QMap>

#include "Comm.h"
#include "ROSAPIUser.h"
#include "ROSAPIUserGroup.h"

namespace ROS
{

class ROSPPPoEManager : public Comm
{
Q_OBJECT

	QROSAPIUserManager		m_rosAPIUser;
	QROSAPIUserGroupManager m_rosAPIUserGroup;

	struct ReceiverInfo
	{
		QObject *ob;
		QString sentenceTag;
		int doneSlot;
		int replySlot;
		int errorSlot;
	};
	struct APIUser : public ReceiverInfo, public ROSAPIUser
	{

	};
	APIUser m_APIUserManager;


public:
	ROSPPPoEManager(QObject *papi) : Comm(papi),
	  m_rosAPIUser(this), m_rosAPIUserGroup(this)
	{
		connect(this, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onDataReceived(ROS::QSentence&)));
	}
	virtual ~ROSPPPoEManager() {	}

public slots:
	void onDataReceived(ROS::QSentence &sentence)
	{
		switch( sentence.getResultType() )
		{
		case ROS::QSentence::None:
			break;
		case ROS::QSentence::Done:
			if( m_APIUserManager.ob && (m_APIUserManager.doneSlot != -1) && (m_APIUserManager.sentenceTag == sentence.tag()) )
			{
				ROSAPIUser *rosUser = dynamic_cast<ROSAPIUser*>(&m_APIUserManager);
				emit done(this);
//				m_APIUserManager.ob->metaObject()->method(m_APIUserManager.doneSlot).invoke(m_APIUserManager.ob, Q_ARG(ROS::ROSPPPoEManager*,this), Q_ARG(ROSAPIUser*,rosUser));
			}
			break;
		case ROS::QSentence::Trap:
			break;
		case ROS::QSentence::Fatal:
			break;
		case ROS::QSentence::Reply:
		  {
			if( m_APIUserManager.ob && m_APIUserManager.sentenceTag == sentence.tag() )
			{
				ROSAPIUser *rosUser = dynamic_cast<ROSAPIUser*>(&m_APIUserManager);
				rosUser->fromSentence(sentence);
				m_APIUserManager.ob->metaObject()->method(m_APIUserManager.doneSlot).invoke(m_APIUserManager.ob, Q_ARG(ROS::ROSPPPoEManager*,this), Q_ARG(ROSAPIUser*,rosUser));
			}
			break;
		  }
		}
	}

public:
	void requestAPIUsers(const QSentence &sentence, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
	{
		requestData(m_APIUserManager, sentence, receiverOb, replySlot, doneSlot, errorSlot);
	}
	void requestData(ReceiverInfo &rInfo, const QSentence &sentence, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
	{
		QByteArray tmp;
		rInfo.ob = receiverOb;

//		receiverOb->metaObject()->invokeMethod(receiverOb, "onAllAPIUsersReceived", Q_ARG(ROS::ROSPPPoEManager*, this) );

		QByteArray _doneSlot = QMetaObject::normalizedSignature("onAllAPIUsersReceived(ROS::ROSPPPoEManager*)");
		int a = receiverOb->metaObject()->indexOfMethod(_doneSlot);
		int b = receiverOb->metaObject()->indexOfMethod(doneSlot);

		Q_ASSERT(rInfo.doneSlot != -1);

		rInfo.replySlot = receiverOb->metaObject()->indexOfMethod(replySlot);
		rInfo.errorSlot = receiverOb->metaObject()->indexOfMethod(errorSlot);
		rInfo.sentenceTag = sentence.tag();

		sendSentence(sentence);
	}

	QROSAPIUserGroupManager &apiUserGroupManager()	{ return m_rosAPIUserGroup;	}
	QROSAPIUserManager &apiUserManager()			{ return m_rosAPIUser;		}
signals:
	void done();
	void done(ROS::ROSPPPoEManager*);
};

typedef QMap<QString, ROSPPPoEManager*> ROSPPPoEManagerMap;
typedef QMapIterator<QString, ROSPPPoEManager*> ROSPPPoEManagerIterator;

class MultiConnectManager : public QObject
{
Q_OBJECT

	ROSPPPoEManagerMap m_rosPppoeManagerMap;

private slots:
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onCommStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

public:
	MultiConnectManager(QObject *papi = Q_NULLPTR);
	~MultiConnectManager();

	ROSPPPoEManager *rosPppoeManager(const QString &routerName)	{ return m_rosPppoeManagerMap[routerName];	}

	void clear();
	void addROSConnection(const QString &routerName, const QString &hostAddr, quint16 hostPort , const QString &uname, const QString &upass);

	bool areAllDisconnected()const;
	bool areAllConnected()const;

public slots:
	void sendCancel(const QString &tag, const QString &routerName = QString());
	void connectHosts(const QString &routerName = QString());
	void disconnectHosts(bool force, const QString &routerName = QString());

	void sendSentence(const QString &routerName, const QSentence &s);
	void sendSentence(const QString &routerName, const QString &s, const QString &tag, const QStringList attrib = QStringList());

signals:
	void statusInfo(QString info, ROS::ROSPPPoEManager *pppoeManager = Q_NULLPTR);
	void routerDisconnected(ROS::ROSPPPoEManager *pppoeManager);
	void routerConnected(ROS::ROSPPPoEManager *pppoeManager);
	void allConected();
	void allDisconnected();
	void logued(ROS::ROSPPPoEManager *pppoeManager);
	void comError(QString errorString, ROS::ROSPPPoEManager *pppoeManager);
};
}
#endif // MULTIROSCONNECTORMANAGER_H
