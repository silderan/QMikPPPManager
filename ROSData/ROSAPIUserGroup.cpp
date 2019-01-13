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
