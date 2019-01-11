#include "ROSPPPProfile.h"

void ROSPPPProfile::fromSentence(const QString &routerName, const ROS::QSentence &sentence)
{
	ROSDataBase::fromSentence(routerName, sentence);
	/* change-tcp-mss=yes
	 * local-address=192.168.90.1
	 * remote-address=Name-or-IP
	 * bridge=bridgeName
	 * name=profile1
	 * only-one=no
	 * remote-address=pppoePoolA
	 * use-compression=default
	 * use-encryption=default
	 * use-mpls=default
	 * use-upnp=default
	 * rate-limit=1M/2M
	 */
	m_rateLimit.fromString( sentence.attribute("rate-limit") );
	m_name = sentence.attribute("name");
	m_bridgeName = sentence.attribute("bridge");
	m_localAdress = sentence.attribute("local-address");
	m_remoteAdress = sentence.attribute("remote-address");
}

ROS::QSentence &ROSPPPProfile::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute( "name", m_name );
	sentence.addAttribute( "rate-limit", m_rateLimit.isUnlimited() ? "" : m_rateLimit.toString() );
	sentence.addAttribute( m_bridgeName.isEmpty() ? "!bridge" : "bridge", m_bridgeName );
	sentence.addAttribute( "local-address", m_localAdress );
	sentence.addAttribute( "remote-address", m_remoteAdress );

	return ROSDataBase::toSentence(sentence);
}

bool ROSPPPProfile::hasSameData(const ROSDataBase &rosPPPProfile) const
{
	return
		(m_name == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_name) &&
		(m_rateLimit == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_rateLimit) &&
		(m_bridgeName == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_bridgeName) &&
		(m_localAdress == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_localAdress) &&
		(m_remoteAdress == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_remoteAdress) ;
}