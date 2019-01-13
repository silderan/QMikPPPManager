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
	m_address = IPv4(s.attribute("address"));
	m_ifaceName = s.attribute("interface");
}

ROS::QSentence &ROSIPAddress::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute( "address", m_address.toString() );
	sentence.addAttribute( "interface", m_ifaceName );
	return ROSDataBase::toSentence(sentence);
}

bool ROSIPAddress::hasSameData(const ROSDataBase &rosData) const
{
	return
		(m_address == static_cast<const ROSIPAddress &>(rosData).m_address) &&
			(m_ifaceName == static_cast<const ROSIPAddress &>(rosData).m_ifaceName) ;
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSIPAddress::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	static int addr = 0;
	addr++;
	ROSIPAddress ipAddr(routerName);
	QList<ROS::QSentence> rtn;
	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::IPAddress) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	ipAddr.setAddress( IPv4( QString("192.168.%1.1").arg(addr)) );
	ipAddr.setIfaceName( "bridgePPPoE" );
	ipAddr.toSentence(sentence).setID( "s1" );
	rtn.append( sentence );

	ipAddr.setAddress( IPv4( QString("192.168.88.%1").arg(addr+1)) );
	ipAddr.setIfaceName( "ether10" );
	ipAddr.toSentence(sentence).setID( "s2" );
	rtn.append( sentence );

	sentence.setResultType( ROS::QSentence::Result::Done );
	rtn.append( sentence );
	return rtn;
}
#endif
