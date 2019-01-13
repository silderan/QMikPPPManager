#ifndef ROSIPPOOL_H
#define ROSIPPOOL_H

#include "../UnitTests.h"
#include "../Utils/IPv4Range.h"
#include "ROSDataBasics.h"

class ROSIPPool : public ROSDataBase
{
	QString m_name;
	IPv4RangeList m_pool;

public:
	explicit ROSIPPool(const QString &routerName) : ROSDataBase(DataTypeID::IPPool, routerName)
	{	}

	const QString &poolName() const				{ return m_name;	}
	void setPoolName(const QString &poolName)	{ m_name = poolName;	}

	const IPv4RangeList &poolRanges() const				{ return m_pool;		}
	IPv4RangeList &poolRanges()							{ return m_pool;		}
	void setPoolRanges(const IPv4RangeList &poolRanges)	{ m_pool = poolRanges;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSIPPOOL_H
