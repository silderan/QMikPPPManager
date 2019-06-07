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

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSIPPool::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	ROSIPPool ipPool(routerName);
	QList<ROS::QSentence> rtn;
	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::IPPool) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	switch( step )
	{
	case 1:
		ipPool.setPoolName( "PoolIPLocal" );
		ipPool.poolRanges().append( IPv4Range(IPv4("192.168.1.1"),IPv4("192.168.1.1")) );
		ipPool.toSentence(sentence).setID("s1");
		rtn.append( sentence );
		break;
	case 2:
		ipPool.setPoolName( "poolClientes" );
		ipPool.poolRanges().append( IPv4Range(IPv4("192.168.1.2"),IPv4("192.168.1.254")) );
		ipPool.toSentence(sentence).setID("s2");
		rtn.append( sentence );
		break;
	case 3:
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
		break;
	}
	return rtn;
}
#endif
