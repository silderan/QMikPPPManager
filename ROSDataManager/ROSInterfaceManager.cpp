#include "ROSInterfaceManager.h"


QList<ROSDataBase *> ROSInterfaceManager::rosDataList(const QString &interfaceType)
{
	QList<ROSDataBase *> rtn;
	foreach( ROSDataBase *iface, rosDataList() )
		if( static_cast<ROSInterface*>(iface)->interfaceType() == interfaceType )
			rtn.append(iface);
	return rtn;
}
