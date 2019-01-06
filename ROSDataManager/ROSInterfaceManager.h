#ifndef ROSINTERFACEMANAGER_H
#define ROSINTERFACEMANAGER_H

#include <QList>

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSInterfaces.h"


class ROSInterfaceManager : public ROSDataManagerBase<ROSInterface>
{
public:
	inline QList<ROSInterface> rosDataList()	{ return ROSDataManagerBase::rosDataList();	}
	QList<ROSInterface> rosDataList(const QString &interfaceType);
};

#endif // ROSINTERFACEMANAGER_H
