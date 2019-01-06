#include "ROSPPPoEManager.h"

ROSPPPoEManager::ROSPPPoEManager(QObject *papi) : Comm(papi)
{
	connect(this, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onDataReceived(ROS::QSentence&)));
}

void ROSPPPoEManager::onDataReceived(ROS::QSentence &sentence)
{
	switch( sentence.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		m_rosAPIUserManager.onDone( sentence );
		m_rosAPIUsersGroupManager.onDone( sentence );
		m_rosPPPProfileManager.onDone( sentence );
		break;
	case ROS::QSentence::Trap:
		emit rosError(routerName(), sentence.attribute("message"));
		break;
	case ROS::QSentence::Fatal:
		break;
	case ROS::QSentence::Reply:
		m_rosAPIUserManager.onReply( sentence );
		m_rosAPIUsersGroupManager.onReply( sentence );
		m_rosPPPProfileManager.onReply( sentence );
		break;
	}
}

void ROSPPPoEManager::updateRemoteData(const char *path, const ROSDataBase &newROSData, const ROSDataBase &oldROSData)
{
	Q_ASSERT( strlen(path) > 2 );
	Q_ASSERT( path[0] == '/' );
	Q_ASSERT( path[strlen(path)-1] == '/' );

	ROS::QSentence sentence;

	sentence.setTag( QString("%1-mod" ).arg(this->metaObject()->className()) );

	if( newROSData.dataID().isEmpty() )
	{
		sentence.setCommand( QString("%1add").arg(path) );
		sendSentence(newROSData.toSentence(sentence));
	}
	else
	if( newROSData.deleting() )
	{
		sentence.setCommand( QString("%1remove").arg(path) );
		sentence.setID(newROSData.dataID());
		sendSentence(sentence);
	}
	else
	if( !newROSData.hasSameData(oldROSData) )
	{
		sentence.setCommand( QString("%1set").arg(path) );
		sendSentence(newROSData.toSentence(sentence));
	}
}

void ROSPPPoEManager::requestRemoteData(const char *path, const QString &sentenceTag)
{
	Q_ASSERT( strlen(path) > 2 );
	Q_ASSERT( path[0] == '/' );
	Q_ASSERT( path[strlen(path)-1] == '/' );

	ROS::QSentence sentence;
	sentence.addQuery( "#|" );
	sentence.setTag( sentenceTag );

	sentence.setCommand( QString("%1getall").arg(path) );
	sendSentence(sentence);

	sentence.setCommand( QString("%1listen").arg(path) );
	sendSentence(sentence);
}

void ROSPPPoEManager::requestAllAPIUsers(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	Q_ASSERT( !routerName().isEmpty() );

	QString sentenceTag = "ROSAPIUser-all";
	requestRemoteData( "/user/", sentenceTag );

	m_rosAPIUserManager.setup(receiverOb, routerName(), sentenceTag, replySlot, doneSlot, errorSlot, false);
}
void ROSPPPoEManager::updateROSAPIUser(const ROSAPIUser &newROSAPIUser)
{
	updateRemoteData("/user/", newROSAPIUser, m_rosAPIUserManager.rosData(newROSAPIUser.dataID()));
}

void ROSPPPoEManager::requestAllPPPProfiles(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	Q_ASSERT( !routerName().isEmpty() );

	QString sentenceTag = "ROSPPPProfile-all";
	requestRemoteData( "/ppp/profile/", sentenceTag );

	m_rosPPPProfileManager.setup(receiverOb, routerName(), sentenceTag, replySlot, doneSlot, errorSlot, false);
}
void ROSPPPoEManager::updatePPPProfile(const ROSPPPProfile &newROSPPPProfile)
{
	updateRemoteData("/ppp/profile/", newROSPPPProfile, m_rosAPIUserManager.rosData(newROSPPPProfile.dataID()));
}

void ROSPPPoEManager::requestAllAPIUsersGroup(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	Q_ASSERT( !routerName().isEmpty() );

	QString sentenceTag = "ROSAPIUsersGroup-all";
	requestRemoteData( "/user/group/", sentenceTag );

	m_rosAPIUsersGroupManager.setup(receiverOb, routerName(), sentenceTag, replySlot, doneSlot, errorSlot, false);
}
