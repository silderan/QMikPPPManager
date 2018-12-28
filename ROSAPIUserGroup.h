#ifndef ROSAPIUSERGROUP_H
#define ROSAPIUSERGROUP_H

#include <QList>

#include "ROSDataBasics.h"

class ROSAPIUserGroup : public ROSDataBase
{
public:
	QString m_name;
	QStringList m_policies;

	ROSAPIUserGroup()
	{	}
	ROSAPIUserGroup(const QString &name, const QString &policies) :
		m_name(name), m_policies(policies.split(','))
	{	}
	ROSAPIUserGroup(const QString &name, const QStringList &policies) :
		m_name(name), m_policies(policies)
	{	}
	ROSAPIUserGroup(const ROS::QSentence &s)
	{
		fromSentence(s);
	}
	virtual void fromSentence(const ROS::QSentence &s);
};
typedef QList<ROSAPIUserGroup> QROSAPIUserGroupList;

class QROSAPIUserGroupManager : public QROSDataManager
{
	QROSAPIUserGroupList m_grouplist;

public:
	QROSAPIUserGroupManager(ROS::Comm *papi);

	QROSAPIUserGroupList &list()	{ return m_grouplist;	}

	virtual ROSDataBase *fromSentence(ROS::QSentence &sentence)const;
	virtual ROS::QSentence getallSentence()const;
};

#endif // ROSAPIUSERGROUP_H
