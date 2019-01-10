#include "ROSInterfaceManager.h"


ROSDataBasePList ROSInterfaceManager::rosDataList(const QString &interfaceType)
{
	ROSDataBasePList rtn;
	foreach( ROSDataBase *iface, rosDataList() )
		if( static_cast<ROSInterface*>(iface)->interfaceType() == interfaceType )
			rtn.append(iface);
	return rtn;
}
