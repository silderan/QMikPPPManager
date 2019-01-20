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
	m_level = static_cast<Level>(ROSAPIUser::levelNames().indexOf(comment().toLower()));
	if( m_level < NoRights )
		m_level = NoRights;
}

ROS::QSentence &ROSAPIUser::toSentence(ROS::QSentence &sentence) const
{
	sentence.addAttribute( "name", m_uname );
	sentence.addAttribute( "group", m_group );

	// User replies never includes password.
	// So, it's usually empty meaning that you don't want to change password.
	if( !m_upass.isEmpty() )
		sentence.addAttribute( "password", m_upass );

	return ROSDataBase::toSentence(sentence);
}

bool ROSAPIUser::hasSameData(const ROSDataBase &rosAPIUser) const
{
	return	(m_uname == static_cast<const ROSAPIUser&>(rosAPIUser).m_uname) &&
			(m_group == static_cast<const ROSAPIUser&>(rosAPIUser).m_group) &&
			(m_level == static_cast<const ROSAPIUser&>(rosAPIUser).m_level);
}

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSAPIUser::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	ROSAPIUser apiUser(routerName);
	QList<ROS::QSentence> rtn;
	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::APIUser) );
	sentence.setResultType( ROS::QSentence::Result::Reply );

	switch( step )
	{
	case 1:
		apiUser.setUserName( "Rafa" );
		apiUser.setGroupName( "API" );
		apiUser.setUserLevel( Level::Supervisor );
		apiUser.toSentence(sentence).setID("s1");
		rtn.append( sentence );
		break;
	case 2:
		apiUser.setUserName( "Lourdes" );
		apiUser.setGroupName( "API" );
		apiUser.setUserLevel( Level::Administrator );
		apiUser.toSentence(sentence).setID("s2");
		rtn.append( sentence );
		break;
	case 3:
		apiUser.setUserName( "Balma" );
		apiUser.setGroupName( "API" );
		apiUser.setUserLevel( Level::Comercial );
		apiUser.toSentence(sentence).setID("s3");
		rtn.append( sentence );
		break;
	case 4:
		apiUser.setUserName( "Link" );
		apiUser.setGroupName( "API" );
		apiUser.setUserLevel( Level::Instalator );
		apiUser.toSentence(sentence).setID("s4");
		rtn.append( sentence );
		break;
	case 5:
		sentence.setResultType( ROS::QSentence::Result::Done );
		rtn.append( sentence );
		break;
	}

	return rtn;
}
#endif
