#include "ROSDataBasics.h"

void ROSDataBase::fromSentence(const ROS::QSentence &s)
{
	m_id = s.getID();
}

void QROSDataManager::onDataReceived(ROS::QSentence &sentence)
{
	if( sentence.tag() != sentenceTag() )
		return;

	switch( sentence.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		emit done( rosAPI() );

		disconnect( this, Q_NULLPTR, m_receiverOb, Q_NULLPTR );
		disconnect( rosAPI(), SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onDataReceived(ROS::QSentence&)) );
		break;
	case ROS::QSentence::Trap:
		emit error( rosAPI()->errorString(), rosAPI() );
		break;
	case ROS::QSentence::Fatal:
		emit error( rosAPI()->errorString(), rosAPI() );
		break;
	case ROS::QSentence::Reply:
	  {
		ROSDataBase *data = fromSentence(sentence);
		emit reply( *data, rosAPI() );
		delete data;
		break;
	  }
	}
}

void QROSDataManager::requestData(QObject *receiverOb, const char *receivedOneSlot, const char *receivedAllSlot, const char *errorSlot)
{
	m_receiverOb = receiverOb;

	connect( rosAPI(), SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onDataReceived(ROS::QSentence&)) );
	if( receiverOb )
	{
		if( receivedOneSlot )	connect( this, SIGNAL(reply(ROSDataBase&,ROS::Comm*)), receiverOb, receivedOneSlot );
		if( receivedAllSlot )	connect( this, SIGNAL(done(ROS::Comm*)), receiverOb, receivedAllSlot );
		if( errorSlot )			connect( this, SIGNAL(error(QString,ROS::Comm*)), receiverOb, errorSlot );
	}
	rosAPI()->sendSentence( getallSentence() );
}
