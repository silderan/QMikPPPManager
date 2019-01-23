#include "ROSPPPoEManager.h"

#include <ROSData/ROSIPPool.h>

ROSPPPoEManager::ROSPPPoEManager(QObject *papi) : Comm(papi),
	m_rosAPIUserManager			("/user/"),
	m_rosAPIUsersGroupManager	("/user/group/"),
	m_rosPPPProfileManager		("/ppp/profile/"),
	m_rosInterfaceManager		("/interface/"),
	m_rosBridgePortsManager		("/interface/bridge/port/"),
	m_rosIPAddressManager		("/ip/address/"),
	m_rosIPPoolManager			("/ip/pool/"),
	m_rosSecretManager			("/ppp/secret/"),
	m_rosActiveManager			("/ppp/active/")
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
		if( !sentence.tag().isEmpty() )
		{
			DataTypeID dataTypeID = static_cast<DataTypeID>(sentence.tag().toInt());
			rosDataManager(dataTypeID).onROSDoneReply();
			emit rosDone( routerName(), dataTypeID );
		}
		break;
	case ROS::QSentence::Trap:
	case ROS::QSentence::Fatal:
		emit rosError( routerName(), sentence.attribute("message") );
		break;
	case ROS::QSentence::Reply:
		if( !sentence.tag().isEmpty() )
		{
			DataTypeID dataTypeID = static_cast<DataTypeID>(sentence.tag().toInt());
			if( sentence.attribute(".dead").isEmpty() )
				emit rosModReply( *rosDataManager(dataTypeID).onROSModReply(sentence) );
			else
			{
				rosDataManager(dataTypeID).onROSDeadReply(sentence);
				emit rosDelReply( routerName(), dataTypeID, sentence.getID() );
			}
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
	case DataTypeID::PPPSecret:		return m_rosSecretManager;
	case DataTypeID::PPPActive:		return m_rosActiveManager;
	default:
		break;
	}
	Q_ASSERT(false);
	// Will NEVER come here!. But, coding that, avoids compiler warnings.
	return m_rosAPIUserManager;
}

const ROSDataManagerBase &ROSPPPoEManager::rosDataManager(DataTypeID dataTypeID) const
{
	return const_cast<ROSPPPoEManager*>(this)->rosDataManager(dataTypeID);
}

ROSDataBasePList ROSPPPoEManager::rosDataList(DataTypeID dataTypeID) const
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
		rosDataManagerBase.logAdding(newROSData);
		sentence.setCommand( rosDataManagerBase.addCommand() );
		newROSData.toSentence(sentence);
		sentence.setID( "" );
		sendSentence( sentence, false );
	}
	else
	if( newROSData.deleting() )
	{
		rosDataManagerBase.logDeleting(newROSData);
		sentence.setCommand( rosDataManagerBase.removeCommand() );
		sentence.setID( rosObjectID );
		sendSentence( sentence, false );
	}
	else
	{
		ROSDataBase *oldData = rosDataManagerBase.rosData(rosObjectID); Q_ASSERT(oldData);
		if( (oldData == Q_NULLPTR) || !newROSData.hasSameData(*oldData) )	// Updating remote data.
		{
			rosDataManagerBase.logChange(*oldData, newROSData);
#ifndef QT_NO_DEBUG
			if( rosDataManagerBase.rosData(rosObjectID) == Q_NULLPTR )
				qWarning("no se ha encontrado el usuario con ID %s del router %s", rosObjectID.toLatin1().data(), routerName().toLatin1().data());
#endif
			sentence.setCommand( rosDataManagerBase.setCommand() );
			newROSData.toSentence(sentence);
			sentence.setID( rosObjectID );
			sendSentence( sentence, false );
		}
	}
}

#ifdef SIMULATE_ROS_INPUTS
#include <QTimer>
#endif

void ROSPPPoEManager::requestRemoteData(DataTypeID dataTypeID)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(dataTypeID);

	Q_ASSERT( !routerName().isEmpty() );

	if( rosDataManagerBase.routerName().isEmpty() )
	{
		rosDataManagerBase.setRouterName( routerName() );

#ifdef SIMULATE_ROS_INPUTS
		QTimer *timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(simulateStep()));
		timer->setProperty( "dataTypeID", static_cast<int>(dataTypeID) );
		timer->setProperty( "step", 1 );
		timer->start(250);
#else
		ROS::QSentence sentence;
		sentence.setTag( QString::number(dataTypeID) );

		sentence.setCommand( rosDataManagerBase.listenCommand() );
		sendSentence(sentence);

		sentence.setCommand( rosDataManagerBase.getallCommand() );
		foreach( const QString &query, rosDataManagerBase.getallQueries() )
			sentence.addQuery(query);
		sendSentence(sentence);
#endif
	}
}

#ifdef SIMULATE_ROS_INPUTS
#include <QRandomGenerator>
void ROSPPPoEManager::simulateStep()
{
	if( sender() == Q_NULLPTR )
		return;
	QList<ROS::QSentence> sList;
	int step = sender()->property("step").toInt();
	DataTypeID dataTypeID = static_cast<DataTypeID>(sender()->property("dataTypeID").toInt());
	quint32 random = QRandomGenerator::global()->generate();
	switch( dataTypeID )
	{
	case DataTypeID::ErrorTypeID:	break;
	case DataTypeID::APIUser:		sList = ROSAPIUser::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::APIUsersGroup:	sList = ROSAPIUsersGroup::simulatedStepSentences(routerName(), random, step );	break;
	case DataTypeID::PPPProfile:	sList = ROSPPPProfile::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::Interface:		sList = ROSInterface::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::BridgePorts:	sList = ROSBridgePort::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::IPAddress:		sList = ROSIPAddress::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::IPPool:		sList = ROSIPPool::simulatedStepSentences(routerName(), random, step );			break;
	case DataTypeID::PPPSecret:		sList = ROSPPPSecret::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::PPPActive:		sList = ROSPPPActive::simulatedStepSentences(routerName(), random, step );		break;
	case DataTypeID::TotalIDs:		break;
	}
	sender()->setProperty("step", step+1);
	foreach( ROS::QSentence sentence, sList )
		onDataReceived( sentence );
}
#endif
