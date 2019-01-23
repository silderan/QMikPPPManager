#ifndef ROSPPPSECRETMANAGER_H
#define ROSPPPSECRETMANAGER_H

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSSecret.h"

class ROSPPPSecretManager : public ROSDataManager<ROSPPPSecret>
{
public:
	ROSPPPSecretManager(const QString &path) : ROSDataManager(path)
	{	}

	virtual void logAdding(const ROSDataBase &newROSData) override;
	virtual void logDeleting(const ROSDataBase &oldROSData) override;
	virtual void logChange(const ROSDataBase &oldROSData, const ROSDataBase &newROSData) override;
};

#endif // ROSPPPSECRETMANAGER_H
