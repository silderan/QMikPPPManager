#include "ROSAPIUser.h"

#define TAG_ROS_API_USER		("ROSAPIUser")

QStringList ROSAPIUser::levelNames(bool plural)
{
	static QStringList plurales = QStringList()
									<< "sin permisos"
									<< "comerciales"
									<< "instaladores"
									<< "administradores"
									<< "supervisores";
	static QStringList singulares = QStringList()
									<< "sin permiso"
									<< "comercial"
									<< "instalador"
									<< "administrador"
									<< "supervisor";
	return plural ? plurales : singulares;
}

void ROSAPIUser::fromSentence(const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(s);
	m_uname = s.attribute("name");
	m_level = static_cast<Level>(ROSAPIUser::levelNames().indexOf(s.attribute("comment").toLower()));
	if( m_level < NoRights )
		m_level = NoRights;
}
QROSAPIUserManager::QROSAPIUserManager(ROS::Comm *papi) : QROSDataManager(papi, TAG_ROS_API_USER)
{

}
ROSDataBase *QROSAPIUserManager::fromSentence(ROS::QSentence &sentence) const
{
	return new ROSAPIUser(sentence);
}
ROS::QSentence QROSAPIUserManager::getallSentence() const
{
	ROS::QSentence s("/user/getall");
	s.setTag(TAG_ROS_API_USER);
	s.addQuery("#|");
	return s;
}
