#include "ROSSecretManager.h"

//#include "ConfigData/QConfigData.h"

// // Overrides to take care of some data integrity.
//ROSDataBase *ROSSecretManager::onROSModReply(const ROS::QSentence &sentence)
//{
//	ROSDataBase *rosData = ROSDataManager::onROSModReply(sentence);

//	if( static_cast<ROSSecretData*>(rosData)->originalProfile().isEmpty() )
//		static_cast<ROSSecretData*>(rosData)->setOriginalProfile( static_cast<ROSSecretData*>(rosData)->profile() );

//	return rosData;
//}
