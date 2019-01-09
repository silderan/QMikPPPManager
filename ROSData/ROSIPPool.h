#ifndef ROSIPPOOL_H
#define ROSIPPOOL_H

#include "ROSDataBasics.h"

#include "../Utils/IPv4Range.h"

class ROSIPPool : public ROSDataBase
{
	QString m_name;
	IPv4RangeList m_pool;

public:
	explicit ROSIPPool(const QString &routerName) : ROSDataBase(DataTypeID::IPPool, routerName)
	{	}

	inline const QString &poolName() const				{ return m_name;	}
	inline void setPoolName(const QString &poolName)	{ m_name = poolName;	}

	inline const IPv4RangeList &poolRanges() const				{ return m_pool;		}
	inline void setPoolRanges(const IPv4RangeList &poolRanges)	{ m_pool = poolRanges;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;
};

#endif // ROSIPPOOL_H
