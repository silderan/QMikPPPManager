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

ROSDataManagerBase &ROSPPPoEManager::rosDataManager(DataTypeID dataTypeID)
{
	Q_ASSERT( (dataTypeID >= 0) && (dataTypeID < TotalIDs) );

	switch( dataTypeID )
	{
	case DataTypeID::APIUser:		return m_rosAPIUserManager;
	case DataTypeID::APIUsersGroup:	return m_rosAPIUsersGroupManager;
	case DataTypeID::PPPProfile:	return m_rosPPPProfileManager;
	case DataTypeID::Interface:		return m_rosInterfaceManager;
	case DataTypeID::BridgePorts:	return m_rosBridgePortsManager;
	case DataTypeID::IPAddress:		return m_rosIPAddressManager;
	case DataTypeID::IPPool:		return m_rosIPPoolManager;
	default:
		break;
	}
	// Will NEVER come here!. But, coding that, avoids warnings.
	return m_rosAPIUserManager;
}

QList<ROSDataBase *> ROSPPPoEManager::rosDataList(DataTypeID dataTypeID)
{
	return rosDataManager(dataTypeID).rosDataList();
}

void ROSPPPoEManager::updateRemoteData(const ROSDataBase &newROSData, const QString &rosObjectID)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(newROSData.dataTypeID());
	// Sentence Tag is not necessary as this program keeps "listening" for ROS changes.
	ROS::QSentence sentence;

	if( rosObjectID.isEmpty() )	// Adding new one.
	{
		sentence.setCommand( rosDataManagerBase.addCommand() );
		sendSentence( newROSData.toSentence(sentence) );
	}
	else
	if( newROSData.deleting() )
	{
		sentence.setCommand( rosDataManagerBase.removeCommand() );
		sentence.setID( rosObjectID );
		sendSentence(sentence);
	}
	else
	if( !newROSData.hasSameData( *rosDataManagerBase.rosData(rosObjectID)) )	// Updating remote data.
	{
		sentence.setCommand( rosDataManagerBase.setCommand() );
		newROSData.toSentence(sentence);
		sentence.setID( rosObjectID );
		sendSentence( sentence );
	}
}

void ROSPPPoEManager::requestRemoteData(DataTypeID dataTypeID, QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(dataTypeID);

	Q_ASSERT( receiverOb != Q_NULLPTR );
	Q_ASSERT( !routerName().isEmpty() );

	if( rosDataManagerBase.receiverOb() == Q_NULLPTR )
	{
		rosDataManagerBase.setup( receiverOb, routerName(), replySlot, doneSlot, errorSlot );

		ROS::QSentence sentence;
		sentence.setTag( rosDataManagerBase.sentenceTag() );

		foreach( const QString &query, rosDataManagerBase.getallQueries() )
			sentence.addQuery(query);

		sentence.setCommand( rosDataManagerBase.getallCommand() );
		sendSentence(sentence);

		sentence.setCommand( rosDataManagerBase.listenCommand() );
		sendSentence(sentence);
	}
}
