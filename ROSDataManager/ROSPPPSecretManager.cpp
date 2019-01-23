#include "ROSPPPSecretManager.h"

#include "Utils/QPPPLogger.h"

void ROSPPPSecretManager::logAdding(const ROSDataBase &newROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&newROSData) != Q_NULLPTR);

	logService.logAddingSecret( static_cast<const ROSPPPSecret &>(newROSData) );
}

void ROSPPPSecretManager::logDeleting(const ROSDataBase &oldROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&oldROSData) != Q_NULLPTR);

	logService.logDeletingSecret( static_cast<const ROSPPPSecret &>(oldROSData) );
}

void ROSPPPSecretManager::logChange(const ROSDataBase &oldROSData, const ROSDataBase &newROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&oldROSData) != Q_NULLPTR);
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&newROSData) != Q_NULLPTR);

	logService.logChangingSecret( static_cast<const ROSPPPSecret &>(oldROSData), static_cast<const ROSPPPSecret &>(newROSData) );
}
