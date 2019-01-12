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

	inline ROSDataBasePList rosDataList()	{ return ROSDataManager::rosDataList();	}
	ROSDataBasePList rosDataList(const QString &interfaceType);

	QStringList getallQueries() override
	{
		return QStringList() << "type=ether" << "type=bridge" << "type=vlan" << ROSDataManager::getallQueries();
	}
};

#endif // ROSINTERFACEMANAGER_H
