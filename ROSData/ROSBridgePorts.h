#ifndef ROSBRIDGEPORTS_H
#define ROSBRIDGEPORTS_H

#include "../UnitTests.h"
#include "ROSDataBasics.h"

class ROSBridgePort : public ROSDataBase
{
	QString m_bridgeName;
	QString m_ifaceName;

public:
	explicit ROSBridgePort(const QString &routerName) : ROSDataBase(DataTypeID::BridgePorts, routerName)
	{	}

	const QString &bridgeName() const				{ return m_bridgeName;		}
	void setBridgeName(const QString &bridgeName)	{ m_bridgeName = bridgeName;}

	const QString &ifaceName() const				{ return m_ifaceName;		}
	void setIfaceName(const QString &ifaceName)		{ m_ifaceName = ifaceName;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosData) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSBRIDGEPORTS_H
