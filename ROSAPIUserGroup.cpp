#include "ROSAPIUserGroup.h"

#define ROS_API_USER_GROUP	("ROSAPIUserGroup_Tag")

void ROSAPIUserGroup::fromSentence(const ROS::QSentence &sentence)
{
	ROSDataBase::fromSentence(sentence);
	m_name = sentence.attribute("name");
	m_policies = sentence.attribute("policy").split(',');
}

QROSAPIUserGroupManager::QROSAPIUserGroupManager(ROS::Comm *papi) : QROSDataManager(papi, ROS_API_USER_GROUP)
{

}

ROSDataBase *QROSAPIUserGroupManager::fromSentence(ROS::QSentence &sentence) const
{
	return new ROSAPIUserGroup(sentence);
}

ROS::QSentence QROSAPIUserGroupManager::getallSentence() const
{
	ROS::QSentence s("/user/group/getall");
	s.setTag(ROS_API_USER_GROUP);
	s.addQuery("#|");
	return s;
}
