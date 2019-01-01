#include "ROSDataBasics.h"

void ROSDataBase::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
    m_dataID = s.getID();
    m_delete = !s.attribute(".dead").isEmpty();
	m_routerName = routerName;
}

ROS::QSentence &ROSDataBase::toSentence(ROS::QSentence &sentence) const
{
	if( !m_dataID.isEmpty() )
		sentence.setID(m_dataID);
	return sentence;
}
