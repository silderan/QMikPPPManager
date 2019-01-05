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

ROSAPIUser::Level ROSAPIUser::level(const QString &levelName)
{
	return static_cast<ROSAPIUser::Level>(levelNames(false).indexOf(levelName.toLower()));
}

void ROSAPIUser::fromSentence(const QString &routerName, const ROS::QSentence &sentence)
{
	ROSDataBase::fromSentence(routerName, sentence);
	m_uname = sentence.attribute("name");
	m_group = sentence.attribute("group");
	m_level = static_cast<Level>(ROSAPIUser::levelNames().indexOf(sentence.attribute("comment").toLower()));
	if( m_level < NoRights )
		m_level = NoRights;
}

ROS::QSentence &ROSAPIUser::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute( "name", m_uname );
	sentence.addAttribute( "group", m_group );
	sentence.addAttribute( "comment", levelName() );
	sentence.addAttribute( "password", m_upass );
	return ROSDataBase::toSentence(sentence);
}

bool ROSAPIUser::hasSameData(const ROSDataBase &rosAPIUser) const
{
	return	(m_uname == static_cast<const ROSAPIUser&>(rosAPIUser).m_uname) &&
			(m_group == static_cast<const ROSAPIUser&>(rosAPIUser).m_group) &&
			(m_level == static_cast<const ROSAPIUser&>(rosAPIUser).m_level);
}

void ROSAPIUser::copyData(const ROSDataBase &rosAPIUser)
{
	m_uname = static_cast<const ROSAPIUser&>(rosAPIUser).m_uname;
	m_group = static_cast<const ROSAPIUser&>(rosAPIUser).m_group;
	m_level = static_cast<const ROSAPIUser&>(rosAPIUser).m_level;
}
