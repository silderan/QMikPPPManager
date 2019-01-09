#ifndef ROSIPADDRESS_H
#define ROSIPADDRESS_H

#include "../Utils/IPv4Range.h"
#include "ROSDataBasics.h"

class ROSIPAddress : public ROSDataBase
{
	QString m_address;
	QString m_ifaceName;

public:
	explicit ROSIPAddress(const QString &routerName) : ROSDataBase(DataTypeID::IPAddress, routerName)
	{	}

	inline void setAddress(const QString &address)		{ m_address = address;	}
	inline const QString &address() const				{ return m_address;		}

	inline void setIfaceName(const QString &ifaceName)	{ m_ifaceName = ifaceName;	}
	inline const QString &ifaceName() const				{ return m_ifaceName;		}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosData) const;
};

#endif // ROSIPADDRESS_H
