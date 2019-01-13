#ifndef ROSIPADDRESS_H
#define ROSIPADDRESS_H

#include "../UnitTests.h"
#include "../Utils/IPv4Range.h"
#include "ROSDataBasics.h"

class ROSIPAddress : public ROSDataBase
{
	IPv4 m_address;
	QString m_ifaceName;

public:
	explicit ROSIPAddress(const QString &routerName) : ROSDataBase(DataTypeID::IPAddress, routerName)
	{	}

	void setAddress(const IPv4 &address)		{ m_address = address;	}
	const IPv4 &address() const					{ return m_address;		}

	inline void setIfaceName(const QString &ifaceName)	{ m_ifaceName = ifaceName;	}
	inline const QString &ifaceName() const				{ return m_ifaceName;		}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosData) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSIPADDRESS_H
