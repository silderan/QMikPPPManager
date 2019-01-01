#ifndef ROSAPIUSERGROUP_H
#define ROSAPIUSERGROUP_H

#include <QList>

#include "ROSDataBasics.h"

class ROSAPIUsersGroup : public ROSDataBase
{
	QString m_name;
	QStringList m_policy;

public:
	ROSAPIUsersGroup(const QString &routerName) : ROSDataBase(routerName)
	{	}
	ROSAPIUsersGroup(const QString &routerName, const QString &name, const QString &policies) : ROSDataBase(routerName),
		m_name(name), m_policy(policies.split(','))
	{	}
	ROSAPIUsersGroup(const QString &routerName, const QString &name, const QStringList &policies) : ROSDataBase(routerName),
		m_name(name), m_policy(policies)
	{	}
	ROSAPIUsersGroup(const QString &routerName, const ROS::QSentence &sentence) : ROSDataBase(routerName)
	{
		fromSentence(routerName, sentence);
	}
	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);

	inline const QString &groupName()const			{ return m_name;	}
	inline void setGroupName(const QString &group)	{ m_name = group;	}

	inline const QStringList &policy() const			{ return m_policy;		}
	inline void setPolicy(const QStringList &policy)	{ m_policy = policy;	}
};
typedef QList<ROSAPIUsersGroup> QROSAPIUsersGroupList;

#endif // ROSAPIUSERGROUP_H
