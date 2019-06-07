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
	if( m_rateLimit.isUnlimited() )
		sentence.addAttribute( "!rate-limit", "" );
	else
		sentence.addAttribute( "rate-limit", m_rateLimit.toString() );
	sentence.addAttribute( m_bridgeName.isEmpty() ? "!bridge" : "bridge", m_bridgeName );
	sentence.addAttribute( m_localAdress.isEmpty() ? "!local-address" : "local-address", m_localAdress );
	sentence.addAttribute( m_remoteAdress.isEmpty() ? "!remote-address" : "remote-address", m_remoteAdress );

	return ROSDataBase::toSentence(sentence);
}

bool ROSPPPProfile::hasSameData(const ROSDataBase &rosPPPProfile) const
{
	return	(m_name == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_name) &&
			(m_rateLimit == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_rateLimit) &&
			(m_bridgeName == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_bridgeName) &&
			(m_localAdress == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_localAdress) &&
			(m_remoteAdress == static_cast<const ROSPPPProfile &>(rosPPPProfile).m_remoteAdress) ;
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSPPPProfile::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	ROSPPPProfile pppProfile(routerName);
	QList<ROS::QSentence> rtn;

	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::PPPProfile) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	switch( step )
	{
	case 1:
		pppProfile.setProfileName( "Basico" );
		pppProfile.setBridgeName( "bridgePPPoE" );
		pppProfile.setLocalAddress( "localGateway" );
		pppProfile.setRemoteAddress( "clientIPPool" );
		pppProfile.rateLimit().fromString( "5M/5M" );
		pppProfile.toSentence(sentence).setID( "s1" );
		rtn.append( sentence );
		pppProfile.setProfileName( "SinServicio" );
		pppProfile.setBridgeName( "bridgePPPoE" );
		pppProfile.setLocalAddress( "localGateway" );
		pppProfile.setRemoteAddress( "clientIPPool" );
		pppProfile.rateLimit().fromString( "0/0" );
		pppProfile.toSentence(sentence).setID( "s0" );
		rtn.append( sentence );
		break;
	case 2:
		pppProfile.setProfileName( "Medio" );
		pppProfile.setBridgeName( "bridgePPPoE" );
		pppProfile.setLocalAddress( "localGateway" );
		pppProfile.setRemoteAddress( "clientIPPool" );
		pppProfile.rateLimit().fromString( "10M/10M" );
		pppProfile.toSentence(sentence).setID( "s2" );
		rtn.append( sentence );
		break;
	case 3:
		pppProfile.setProfileName( "Alto" );
		pppProfile.setBridgeName( "bridgePPPoE" );
		pppProfile.setLocalAddress( "localGateway" );
		pppProfile.setRemoteAddress( "clientIPPool" );
		pppProfile.rateLimit().fromString( "15M/15M" );
		pppProfile.toSentence(sentence).setID( "s3" );
		rtn.append( sentence );
		break;
	case 4:
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
		break;
	}
	return rtn;
}
#endif
