#include "ROSInterfaceManager.h"


QList<ROSInterface> ROSInterfaceManager::rosDataList(const QString &interfaceType)
{
	QList<ROSInterface> rtn;
	foreach( const ROSInterface &iface, rosDataList() )
		if( iface.interfaceType() == interfaceType )
			rtn.append(iface);
	return rtn;
}
