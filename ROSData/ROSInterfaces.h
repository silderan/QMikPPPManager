#ifndef ROSINTERFACES_H
#define ROSINTERFACES_H

#include "../UnitTests.h"
#include "ROSDataBasics.h"

class ROSInterface : public ROSDataBase
{
	QString m_name;
	QString m_type;

public:
	explicit ROSInterface(const QString &routerName) : ROSDataBase(DataTypeID::Interface, routerName)
	{	}

	const QString &interfaceName()const	{ return m_name;	}
	const QString &interfaceType()const	{ return m_type;	}

	void setInterfaceName(const QString &interfaceName)	{ m_name = interfaceName;	}
	void setInterfaceType(const QString &interfaceType)	{ m_type = interfaceType;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosInterface) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};
#endif // ROSINTERFACES_H
