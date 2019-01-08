#include "ROSPPPoEManager.h"

ROSPPPoEManager::ROSPPPoEManager(QObject *papi) : Comm(papi),
	m_rosAPIUserManager			("rosAPIUserManager",		"/user/"),
	m_rosAPIUsersGroupManager	("rosAPIUsersGroupManager",	"/user/group/"),
	m_rosPPPProfileManager		("rosPPPProfileManager",	"/ppp/profile/"),
	m_rosInterfaceManager		("rosInterfaceManager",		"/interface/"),
	m_rosBridgePortsManager		("rosBridgePortsManager",	"/interface/bridge/port/"),
	m_rosIPAddressManager		("rosIPAddressManager",		"/ip/address/"),
	m_rosIPPoolManager			("rosIPPoolManager",		"/ip/pool/")
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

ROSDataManagerBase &ROSPPPoEManager::rosDataManager(ROSPPPoEManager::ManagerID &managerID)
{
	Q_ASSERT( (managerID >= 0) && (managerID < TotalIDs) );

	switch( managerID )
	{
	case ROSPPPoEManager::APIUser:			return m_rosAPIUserManager;
	case ROSPPPoEManager::APIUsersGroup:	return m_rosAPIUsersGroupManager;
	case ROSPPPoEManager::PPPProfile:		return m_rosPPPProfileManager;
	case ROSPPPoEManager::Interface:		return m_rosInterfaceManager;
	case ROSPPPoEManager::BridgePorts:		return m_rosBridgePortsManager;
	case ROSPPPoEManager::IPAddress:		return m_rosIPAddressManager;
	case ROSPPPoEManager::IPPool:			return m_rosIPPoolManager;
	default:
		break;
	}
	// Will NEVER come here!. But, coding that, avoids warnings.
	return m_rosAPIUserManager;
}

QList<ROSDataBase *> ROSPPPoEManager::rosDataList(ROSPPPoEManager::ManagerID managerID)
{
	return rosDataManager(managerID).rosDataList();
}

void ROSPPPoEManager::updateRemoteData(ROSDataManagerBase &rosDataManager, const ROSDataBase &newROSData, const QString &rosDataID)
{
	// Sentence Tag is not necessary as this program keeps "listening" for ROS changes.
	ROS::QSentence sentence;

	if( rosDataID.isEmpty() )	// Adding new one.
	{
		sentence.setCommand( rosDataManager.addCommand() );
		sendSentence( newROSData.toSentence(sentence) );
	}
	else
	if( newROSData.deleting() )
	{
		sentence.setCommand( rosDataManager.removeCommand() );
		sentence.setID( rosDataID );
		sendSentence(sentence);
	}
	else
	if( !newROSData.hasSameData( *rosDataManager.rosData(rosDataID)) )	// Updating remote data.
	{
		sentence.setCommand( rosDataManager.setCommand() );
		newROSData.toSentence(sentence);
		sentence.setID( rosDataID );
		sendSentence( sentence );
	}
}
void ROSPPPoEManager::updateRemoteData(ROSPPPoEManager::ManagerID managerID, const ROSDataBase &newROSData, const QString &rosDataID)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(managerID);
	updateRemoteData( rosDataManagerBase, newROSData, rosDataID );
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

void ROSPPPoEManager::requestRemoteData(ROSPPPoEManager::ManagerID managerID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	requestRemoteData( rosDataManager(managerID), receiverOb, replySlot, doneSlot, errorSlot );
}
