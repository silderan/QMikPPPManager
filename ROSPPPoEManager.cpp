#include "ROSPPPoEManager.h"

ROSPPPoEManager::ROSPPPoEManager(QObject *papi) : Comm(papi),
	m_rosAPIUserManager			("rosAPIUserManager",		"/user/"),
	m_rosAPIUsersGroupManager	("rosAPIUsersGroupManager",	"/user/group/"),
	m_rosPPPProfileManager		("rosPPPProfileManager",	"/ppp/profile/"),
	m_rosInterfaceManager		("rosInterfaceManager",		"/interface/"),
	m_rosBridgeManager			("rosBridgeManager",		"/interface/bridge/"),
	m_rosBridgePortsManager		("rosBridgePortsManager",	"/interface/bridge/port/"),
	m_rosIPAddressManager		("rosIPAddressManager",		"/ip/address/")
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

void ROSPPPoEManager::updateRemoteData(ROSDataManagerBase &rosDataManager, const ROSDataBase &newROSData, const ROSDataBase &oldROSData)
{
	ROS::QSentence sentence;

	// Tag is not necessary as this program keeps "listening" for ROS changes.
	if( newROSData.dataID().isEmpty() )
	{
		sentence.setCommand( rosDataManager.addCommand() );
		sendSentence(newROSData.toSentence(sentence));
	}
	else
	if( newROSData.deleting() )
	{
		sentence.setCommand( rosDataManager.removeCommand() );
		sentence.setID(newROSData.dataID());
		sendSentence(sentence);
	}
	else
	if( !newROSData.hasSameData(oldROSData) )
	{
		sentence.setCommand( rosDataManager.setCommand() );
		sendSentence(newROSData.toSentence(sentence));
	}
}

void ROSPPPoEManager::requestRemoteData(ROSDataManagerBase &rosDataManager, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	Q_ASSERT( receiverOb != Q_NULLPTR );
	Q_ASSERT( !routerName().isEmpty() );

	if( rosDataManager.receiverOb() == Q_NULLPTR )
	{
		rosDataManager.setup( receiverOb, routerName(), replySlot, doneSlot, errorSlot );

		ROS::QSentence sentence;
		sentence.setTag( rosDataManager.sentenceTag() );

		foreach( const QString &query, rosDataManager.getallQueries() )
			sentence.addQuery(query);

		sentence.setCommand( rosDataManager.getallCommand() );
		sendSentence(sentence);

		sentence.setCommand( rosDataManager.listenCommand() );
		sendSentence(sentence);
	}
}

void ROSPPPoEManager::requestAllAPIUsers(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosAPIUserManager, receiverOb, replySlot, doneSlot, errorSlot );
}
void ROSPPPoEManager::updateROSAPIUser(const ROSAPIUser &newROSAPIUser)
{
	updateRemoteData( m_rosAPIUserManager, newROSAPIUser, m_rosAPIUserManager.rosData(newROSAPIUser.dataID()) );
}

void ROSPPPoEManager::requestAllPPPProfiles(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosPPPProfileManager, receiverOb, replySlot, doneSlot, errorSlot );
}
void ROSPPPoEManager::updatePPPProfile(const ROSPPPProfile &newROSPPPProfile)
{
	updateRemoteData( m_rosPPPProfileManager, newROSPPPProfile, m_rosAPIUserManager.rosData(newROSPPPProfile.dataID()) );
}

void ROSPPPoEManager::requestAllAPIUsersGroup(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosAPIUsersGroupManager, receiverOb, replySlot, doneSlot, errorSlot );
}

void ROSPPPoEManager::requestAllIPAddress(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosIPAddressManager, receiverOb, replySlot, doneSlot, errorSlot );
}

void ROSPPPoEManager::updateIPAddress(const ROSIPAddress &newROSIPAddress)
{
	updateRemoteData( m_rosIPAddressManager, newROSIPAddress, m_rosIPAddressManager.rosData(newROSIPAddress.dataID()) );
}

void ROSPPPoEManager::requestAllInterfaces(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosInterfaceManager, receiverOb, replySlot, doneSlot, errorSlot );
}
void ROSPPPoEManager::updateBridgeInterface(const ROSInterface &newBridgeIface)
{
	updateRemoteData( m_rosInterfaceManager, newBridgeIface, m_rosInterfaceManager.rosData(newBridgeIface.dataID()) );
}

void ROSPPPoEManager::requestAllBridgePorts(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( m_rosBridgePortsManager, receiverOb, replySlot, doneSlot, errorSlot );
}
void ROSPPPoEManager::updateBridgePort(const ROSBridgePort &newROSBridgePort)
{
	updateRemoteData( m_rosBridgePortsManager, newROSBridgePort, m_rosBridgePortsManager.rosData(newROSBridgePort.dataID()) );
}
