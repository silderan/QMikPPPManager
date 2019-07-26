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

#include "ROSAPIUserGroup.h"

#define ROS_API_USER_GROUP	("ROSAPIUserGroup_Tag")

void ROSAPIUsersGroup::fromSentence(const QString &routerName, const ROS::QSentence &sentence)
{
	ROSDataBase::fromSentence(routerName, sentence);
	m_name = sentence.attribute("name");
	m_policy = sentence.attribute("policy").split(',');
}

ROS::QSentence &ROSAPIUsersGroup::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute( "name", m_name);
	sentence.addAttribute( "policy", m_policy.join(',') );

	return ROSDataBase::toSentence(sentence);
}

bool ROSAPIUsersGroup::hasSameData(const ROSDataBase &rosAPIUsersGrup) const
{
	return
		(m_name == static_cast<const ROSAPIUsersGroup&>(rosAPIUsersGrup).m_name) &&
			(m_policy == static_cast<const ROSAPIUsersGroup&>(rosAPIUsersGrup).m_policy);
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSAPIUsersGroup::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	ROSAPIUsersGroup userGroup(routerName);
	QList<ROS::QSentence> rtn;

	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::APIUsersGroup) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	switch( step )
	{
	case 1:
		userGroup.setGroupName( "full" );
		userGroup.policy().append( "read" );
		userGroup.policy().append( "write" );
		userGroup.policy().append( "api" );
		userGroup.toSentence( sentence );
		sentence.setID( "s1" );
		rtn.append( sentence );
		break;
	case 2:
		userGroup.setGroupName( "read" );
		userGroup.policy().append( "read" );
		userGroup.toSentence( sentence );
		sentence.setID( "s2" );
		rtn.append( sentence );
		break;
	case 3:
		userGroup.setGroupName( "write" );
		userGroup.policy().append( "write" );
		userGroup.toSentence( sentence );
		sentence.setID( "s3" );
		rtn.append( sentence );
		break;
	case 4:
		userGroup.setGroupName( "API" );
		userGroup.policy().append( "api" );
		userGroup.toSentence( sentence );
		sentence.setID( "s4" );
		rtn.append( sentence );
		break;
	case 5:
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
		break;
	}
	return rtn;
}
#endif
