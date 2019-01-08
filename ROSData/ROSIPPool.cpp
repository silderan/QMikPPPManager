#include "ROSIPPool.h"

/*
 * name=pppoePoolA
 * next-pool=pppoePoolA
 * ranges=172.31.249.2-172.31.249.200,192.168.10.0/24
 */

void ROSIPPool::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);

	m_name = s.attribute("name");

	foreach( QString range, s.attribute("ranges").split(',') )
		m_pool.append( IPv4Range().fromNotationString(range) );
}

ROS::QSentence &ROSIPPool::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute("name", m_name);
	QString poolIPs;
	foreach( const IPv4Range &range, m_pool )
	{
		if( !poolIPs.isEmpty() )
			poolIPs.append(",");
		poolIPs.append( QString("%1-%2").arg(range.first().toString(), range.last().toString()) );
	}
	return ROSDataBase::toSentence(sentence);
}

bool ROSIPPool::hasSameData(const ROSDataBase &rosData) const
{
	if( m_name != static_cast<const ROSIPPool &>(rosData).m_name )
		return false;

	if( m_pool.count() != static_cast<const ROSIPPool &>(rosData).m_pool.count() )
		return false;

	for( int i = 0; i < m_pool.count(); ++i )
	{
		if( m_pool[i].first() == static_cast<const ROSIPPool &>(rosData).m_pool[i].first() )
			return false;
		if( m_pool[i].last() == static_cast<const ROSIPPool &>(rosData).m_pool[i].last() )
			return false;
	}
	return true;
}
