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
