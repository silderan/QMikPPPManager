#ifndef ROSBRIDGEPORTS_H
#define ROSBRIDGEPORTS_H


#include "ROSDataBasics.h"

class ROSBridgePorts : public ROSDataBase
{
	QString m_bridgeName;
	QString m_ifaceName;

public:
	ROSBridgePorts(const QString &routerName) : ROSDataBase(routerName)
	{	}

	const QString &bridgeName() const				{ return m_bridgeName;		}
	void setBridgeName(const QString &bridgeName)	{ m_bridgeName = bridgeName;}

	const QString &ifaceName() const				{ return m_ifaceName;		}
	void setIfaceName(const QString &ifaceName)		{ m_ifaceName = ifaceName;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosData) const;
};

#endif // ROSBRIDGEPORTS_H
