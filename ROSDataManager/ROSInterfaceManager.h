#ifndef ROSINTERFACEMANAGER_H
#define ROSINTERFACEMANAGER_H

#include <QList>

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSInterfaces.h"


class ROSInterfaceManager : public ROSDataManager<ROSInterface>
{
public:
	ROSInterfaceManager(const QString &routerName, const QString &path) : ROSDataManager(routerName, path)
	{	}

	inline QList<ROSInterface> rosDataList()	{ return ROSDataManager::rosDataList();	}
	QList<ROSInterface> rosDataList(const QString &interfaceType);
};

#endif // ROSINTERFACEMANAGER_H
