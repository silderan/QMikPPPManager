#include "ROSDataBasics.h"

void ROSDataBase::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	m_rosObjectID = s.getID();
    m_delete = !s.attribute(".dead").isEmpty();
	m_comment = s.attribute("comment");
	m_routerName = routerName;
}

ROS::QSentence &ROSDataBase::toSentence(ROS::QSentence &sentence) const
{
	if( !m_rosObjectID.isEmpty() )
		sentence.setID(m_rosObjectID);

	sentence.addAttribute("comment", m_comment);

	return sentence;
}
