#ifndef ROSSECRETMANAGER_H
#define ROSSECRETMANAGER_H

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSSecret.h"

class ROSSecretManager : public ROSDataManager<ROSSecretData>
{
public:
	ROSSecretManager(const QString &path) : ROSDataManager(path)
	{	}

//	virtual ROSDataBase *onROSModReply(const ROS::QSentence &sentence) override;
};

#endif // ROSSECRETMANAGER_H
