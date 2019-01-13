#ifndef ROSAPIUSERGROUP_H
#define ROSAPIUSERGROUP_H

#include "../UnitTests.h"
#include "ROSDataBasics.h"

class ROSAPIUsersGroup : public ROSDataBase
{
	QString m_name;
	QStringList m_policy;

public:
	explicit ROSAPIUsersGroup(const QString &routerName) : ROSDataBase(DataTypeID::APIUsersGroup, routerName)
	{	}

	const QString &groupName()const			{ return m_name;	}
	void setGroupName(const QString &group)	{ m_name = group;	}

	const QStringList &policy() const			{ return m_policy;		}
	QStringList &policy()						{ return m_policy;		}
	void setPolicy(const QStringList &policy)	{ m_policy = policy;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosAPIUsersGrup) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSAPIUSERGROUP_H
