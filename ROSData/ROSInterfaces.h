#ifndef ROSINTERFACES_H
#define ROSINTERFACES_H

#include "ROSDataBasics.h"

class ROSInterface : public ROSDataBase
{
	QString m_name;
	QString m_type;

public:
	ROSInterface(const QString &routerName) : ROSDataBase(routerName)
	{	}
	~ROSInterface()
	{	}

	inline const QString &interfaceName()const	{ return m_name;	}
	inline const QString &interfaceType()const	{ return m_type;	}

	inline void setInterfaceName(const QString &interfaceName)	{ m_name = interfaceName;	}
	inline void setInterfaceType(const QString &interfaceType)	{ m_type = interfaceType;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosInterface) const;
};
#endif // ROSINTERFACES_H
