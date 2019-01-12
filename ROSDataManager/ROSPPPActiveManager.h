#ifndef ROSPPPACTIVEMANAGER
#define ROSPPPACTIVEMANAGER

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSSecret.h"

class  ROSPPPActiveManager : public ROSDataManager<ROSPPPActive>
{

public:
	ROSPPPActiveManager(const QString &path) : ROSDataManager(path)
	{	}

	QStringList getallQueries()	override { return QStringList() << "service=pppoe" << ROSDataManager::getallQueries();	}
};

#endif // ROSPPPACTIVEMANAGER
