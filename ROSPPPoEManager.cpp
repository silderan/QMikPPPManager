#include "ROSPPPoEManager.h"

ROSPPPoEManager::ROSPPPoEManager(QObject *papi) : Comm(papi),
	m_rosAPIUserManager			("/user/"),
	m_rosAPIUsersGroupManager	("/user/group/"),
	m_rosPPPProfileManager		("/ppp/profile/"),
	m_rosInterfaceManager		("/interface/"),
	m_rosBridgePortsManager		("/interface/bridge/port/"),
	m_rosIPAddressManager		("/ip/address/"),
	m_rosIPPoolManager			("/ip/pool/")
{
	connect(this, SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onDataReceived(ROS::QSentence&)));
}

void ROSPPPoEManager::onDataReceived(ROS::QSentence &sentence)
{
	// Empty tags are from updates that won't be usefull as we are
	// listeing for changes everywhere.
	if( sentence.tag().isEmpty() )
		return;

	switch( sentence.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		emit rosDone( routerName(), static_cast<DataTypeID>(sentence.tag().toInt()) );
		break;
	case ROS::QSentence::Trap:
		emit rosError( routerName(), sentence.attribute("message") );
		break;
	case ROS::QSentence::Fatal:
		break;
	case ROS::QSentence::Reply:
		if( sentence.attribute(".dead").isEmpty() )
			emit rosModReply( *rosDataManager( static_cast<DataTypeID>(sentence.tag().toInt()) ).onROSModReply(sentence) );
		else
		{
			DataTypeID dataTypeID = static_cast<DataTypeID>(sentence.tag().toInt());
			rosDataManager( dataTypeID ).onROSDeadReply(sentence);
			emit rosDelReply( routerName(), dataTypeID, sentence.getID() );
		}
		break;
	}
}

ROSDataManagerBase &ROSPPPoEManager::rosDataManager(DataTypeID dataTypeID)
{
	Q_ASSERT( (dataTypeID > DataTypeID::ErrorTypeID) && (dataTypeID < TotalIDs) );

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
	// Will NEVER come here!. But, coding that, avoids compiler warnings.
	return m_rosAPIUserManager;
}

ROSDataBasePList ROSPPPoEManager::rosDataList(DataTypeID dataTypeID)
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
	{
		if( (rosDataManagerBase.rosData(rosObjectID) == Q_NULLPTR) ||
			!newROSData.hasSameData(*rosDataManagerBase.rosData(rosObjectID)) )	// Updating remote data.
		{
#ifndef QT_NO_DEBUG
		if( rosDataManagerBase.rosData(rosObjectID) == Q_NULLPTR )
			qWarning("no se ha encontrado el usuario con ID %s del router %s", rosObjectID.toLatin1().data(), routerName().toLatin1().data());
#endif
			sentence.setCommand( rosDataManagerBase.setCommand() );
			newROSData.toSentence(sentence);
			sentence.setID( rosObjectID );
			sendSentence( sentence );
		}
	}
}

void ROSPPPoEManager::requestRemoteData(DataTypeID dataTypeID)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(dataTypeID);

	Q_ASSERT( !routerName().isEmpty() );

	if( rosDataManagerBase.routerName().isEmpty() )
	{
		rosDataManagerBase.setRouterName( routerName() );

		ROS::QSentence sentence;
		sentence.setTag( QString::number(dataTypeID) );

		foreach( const QString &query, rosDataManagerBase.getallQueries() )
			sentence.addQuery(query);

		sentence.setCommand( rosDataManagerBase.getallCommand() );
		sendSentence(sentence);

		sentence.setCommand( rosDataManagerBase.listenCommand() );
		sendSentence(sentence);
	}
}
