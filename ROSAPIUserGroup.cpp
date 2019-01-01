#include "ROSAPIUserGroup.h"

#define ROS_API_USER_GROUP	("ROSAPIUserGroup_Tag")

void ROSAPIUsersGroup::fromSentence(const QString &routerName, const ROS::QSentence &sentence)
{
	ROSDataBase::fromSentence(routerName, sentence);
	m_name = sentence.attribute("name");
	m_policy = sentence.attribute("policy").split(',');
}

