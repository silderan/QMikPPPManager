/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

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
	connect( this, &ROS::Comm::comError,			this, &ROSPPPoEManager::onComError );
	connect( this, &ROS::Comm::comStateChanged,		this, &ROSPPPoEManager::onCommStateChanged );
	connect( this, &ROS::Comm::loginStateChanged,	this, &ROSPPPoEManager::onLoginChanged );

	connect( this, &ROS::Comm::comReceive, this, &ROSPPPoEManager::onDataReceived );
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
			if( dataTypeID != ErrorTypeID )
			{
				rosDataManager(dataTypeID).onROSDoneReply();
				emit rosDone( routerName(), dataTypeID );
			}
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
			if( dataTypeID != ErrorTypeID )
			{
				if( sentence.attribute(".dead").isEmpty() )
					emit rosModReply( *rosDataManager(dataTypeID).onROSModReply(sentence) );
				else
				{
					rosDataManager(dataTypeID).onROSDeadReply(sentence);
					emit rosDelReply( routerName(), dataTypeID, sentence.getID() );
				}
			}
		}
		break;
	}
}

void ROSPPPoEManager::onComError(ROS::Comm::CommError, QAbstractSocket::SocketError)
{
	emit comError( routerName(), errorString() );
}

void ROSPPPoEManager::onCommStateChanged(ROS::Comm::CommState s)
{
	switch( s )
	{
	case ROS::Comm::Unconnected:
		emit statusInfo( routerName(), tr("Desconectado") );
		emit routerDisconnected( routerName() );
		break;
	case ROS::Comm::HostLookup:
		emit statusInfo( routerName(), tr("resolviendo URL") );
		break;
	case ROS::Comm::Connecting:
		emit statusInfo( routerName(), tr("conectando al router") );
		break;
	case ROS::Comm::Connected:
		emit statusInfo( routerName(), tr("Conectado al router") );
		emit routerConnected( routerName() );
		break;
	case ROS::Comm::Closing:
		emit statusInfo( routerName(), tr("Cerrado conexión") );
		break;
	}
}

void ROSPPPoEManager::onLoginChanged(ROS::Comm::LoginState s)
{
	switch( s )
	{
	case ROS::Comm::NoLoged:
		emit statusInfo( routerName(), tr("No está identificado en el servidor") );
		break;
	case ROS::Comm::LoginRequested:
		emit statusInfo( routerName(), tr("Usuario y contraseña pedidos") );
		break;
	case ROS::Comm::UserPassSended:
		emit statusInfo( routerName(), tr("Petición de login en curso") );
		break;
	case ROS::Comm::LogedIn:
		emit statusInfo( routerName(), tr("Logado al router") );
		emit logued( routerName() );
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

bool ROSPPPoEManager::done(DataTypeID dataTypeID) const
{
	return rosDataManager(dataTypeID).done();
}

void ROSPPPoEManager::updateRemoteData(const ROSDataBase &newROSData, const QString &rosObjectID)
{
	ROSDataManagerBase &rosDataManagerBase = rosDataManager(newROSData.dataTypeID());
	// Sentence's Tag is not necessary as this program keeps "listening" for ROS changes.
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
