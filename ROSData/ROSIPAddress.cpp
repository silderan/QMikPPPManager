#include "ROSIPAddress.h"

/*
actual-interface=bridgeGestio
address=192.168.88.111/24
network=192.168.88.0
disabled=false
dynamic=false
interface=bridgeGestio
invalid=false
*/

void ROSIPAddress::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_address = s.attribute("address");
	m_ifaceName = s.attribute("interface");
}

ROS::QSentence &ROSIPAddress::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute("address", m_address);
	sentence.addAttribute( "interface", m_ifaceName );
	return ROSDataBase::toSentence(sentence);
}

bool ROSIPAddress::hasSameData(const ROSDataBase &rosData) const
{
	return
		(m_address == static_cast<const ROSIPAddress &>(rosData).m_address) &&
		(m_ifaceName == static_cast<const ROSIPAddress &>(rosData).m_ifaceName) ;
}
