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
		break;
	case ROS::QSentence::Trap:
		break;
	case ROS::QSentence::Fatal:
		break;
	case ROS::QSentence::Reply:
		m_rosAPIUserManager.onReply( sentence );
		m_rosAPIUsersGroupManager.onReply( sentence );
		break;
	}
}

void ROSPPPoEManager::requestAllAPIUsers(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	ROS::QSentence sentence;

	Q_ASSERT(!routerName().isEmpty());
	sentence.addQuery("#|");
	sentence.setTag("ROSAPIUserManager");
	m_rosAPIUserManager.setup(receiverOb, routerName(), sentence.tag(), replySlot, doneSlot, errorSlot, false, true);

	sentence.setCommand("/user/getall");
	sendSentence(sentence);

	sentence.setCommand("/user/listen");
	sendSentence(sentence);
}

void ROSPPPoEManager::updateROSAPIUser(const ROSAPIUser &newROSAPIUser)
{
	ROS::QSentence sentence;

	// TODO: Borrando un usuario en windox, no se borra en la tabla.
	// TODO: Cambiar de nombre desde la tabla, no lo cambia en el ROS.
	// TODO: Algo he probado que no funciona, pero no lo recuerdo.

	// No implementado
	Q_ASSERT(!newROSAPIUser.deleting());

	if( !newROSAPIUser.dataID().isEmpty() && newROSAPIUser.deleting() )
	{
		sentence.addAttribute(".dead");
		sentence.setID(newROSAPIUser.dataID());
		sendSentence(sentence);
	}
	else
	if( newROSAPIUser.dataID().isEmpty() )
	{
		sentence.setCommand("/user/add");
		sendSentence(newROSAPIUser.toSentence(sentence));
	}
	else
	foreach( ROSAPIUser currentROSAPIUser, m_rosAPIUserManager.list() )
	{
		// if is new "object" OR is the same "object" AND data has changed.
		if( (newROSAPIUser.dataID() == currentROSAPIUser.dataID()) && !currentROSAPIUser.hasSameData(newROSAPIUser) )
		{
			sentence.setCommand("/user/set");
			sendSentence(newROSAPIUser.toSentence(sentence));
			return;
		}
	}
}

void ROSPPPoEManager::requestAllAPIUsersGroup(QObject *receiverOb, const char *replySlot, const char *doneSlot, const char *errorSlot)
{
	ROS::QSentence sentence;

	Q_ASSERT(!routerName().isEmpty());
	sentence.addQuery("#|");
	sentence.setTag("ROSAPIUsersGroupManager");
	m_rosAPIUsersGroupManager.setup(receiverOb, routerName(), sentence.tag(), replySlot, doneSlot, errorSlot, false, true);

	sentence.setCommand("/user/group/getall");
	sendSentence(sentence);

	sentence.setCommand("/user/group/listen");
	sendSentence(sentence);
}
