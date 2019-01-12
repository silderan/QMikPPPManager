#ifndef ROSPPPSECRETMANAGER_H
#define ROSPPPSECRETMANAGER_H

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSSecret.h"

class ROSPPPSecretManager : public ROSDataManager<ROSPPPSecret>
{
public:
	ROSPPPSecretManager(const QString &path) : ROSDataManager(path)
	{	}

//	virtual ROSDataBase *onROSModReply(const ROS::QSentence &sentence) override;
};

#endif // ROSPPPSECRETMANAGER_H
