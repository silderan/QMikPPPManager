#ifndef ROSINTERFACEMANAGER_H
#define ROSINTERFACEMANAGER_H

#include <QList>

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSInterfaces.h"

class ROSInterfaceManager : public ROSDataManager<ROSInterface>
{
public:
	ROSInterfaceManager(const QString &path) : ROSDataManager(path)
	{	}
	virtual ~ROSInterfaceManager()override
	{	}

	inline ROSDataBasePList rosDataList()	{ return ROSDataManager::rosDataList();	}
	ROSDataBasePList rosDataList(const QString &interfaceType);

	QStringList getallQueries() override
	{
		return QStringList() << "ether" << "bridge" << "vlan";
	}
};

#endif // ROSINTERFACEMANAGER_H
