#include "ROSAPIUser.h"


#define TAG_ROS_API_USER		("ROSAPIUser")
#define TAG_ROS_API_USER_GROUP	("ROSAPIGroupUser")

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

void QMultiROSAPIUserManager::onUserReceive(const ROS::QSentence &sentence)
{
	if( sentence.tag() != TAG_ROS_API_USER )
		return;
	switch( sentence.getResultType() )
	{
	case ROS::QSentence::None:
		break;
	case ROS::QSentence::Done:
		disconnect(sender(), SIGNAL(comReceive(ROS::QSentence&)), this, SLOT(onUserReceive(ROS::QSentence)) );

#ifndef QT_NO_DEBUG
		// Clear the property.
		Q_ASSERT( !QVariant().isValid() );	// If this hapens, it is a Qt bug because this is the only way to remove properties
		sender()->setProperty( TAG_ROS_API_USER, QVariant() );
#endif
		emit done();
		break;
	case ROS::QSentence::Trap:
		emit error();
		break;
	case ROS::QSentence::Fatal:
		emit error();
		break;
	case ROS::QSentence::Reply:
		m_userList.append(ROSAPIUser(sentence.attribute("name"), sentence.attribute("group")));
		emit reply(tr("Usuario API %1 del grupo %2 recibido").arg(sentence.attribute("name"), sentence.attribute("group")));
		break;
	}
}

void QMultiROSAPIUserManager::onUserGroupReceive(const ROS::QSentence &sentence)
{
}

void QMultiROSAPIUserManager::requestAPIUsers(ROS::Comm *mktAPI)
{
#ifndef QT_NO_DEBUG
	Q_ASSERT( !mktAPI->property(TAG_ROS_API_USER).isValid() );
	mktAPI->setProperty(TAG_ROS_API_USER, true);
#endif

	connect(mktAPI, SIGNAL(comReceive(ROS::QSentence&,QString)), this, SLOT(onReceive(ROS::QSentence&,QString)) );
	ROS::QSentence s("/user/getall");
	s.setTag(TAG_ROS_API_USER);
	s.addQuery("#|");
	mktAPI->sendSentence( s );

}

void QMultiROSAPIUserManager::requestAPIUserGroups(ROS::Comm *mktAPI)
{
#ifndef QT_NO_DEBUG
	Q_ASSERT( !mktAPI->property(TAG_ROS_API_USER_GROUP).isValid() );
	mktAPI->setProperty(TAG_ROS_API_USER_GROUP, true);
#endif

	connect(mktAPI, SIGNAL(comReceive(ROS::QSentence&,QString)), this, SLOT(onReceive(ROS::QSentence&,QString)) );
	ROS::QSentence s("/user/group/getall");
	s.setTag(TAG_ROS_API_USER_GROUP);
	s.addQuery("#|");
	mktAPI->sendSentence( s );
}

void QMultiROSAPIUserManager::requestData(ROS::Comm *m_mktAPI)
{
	requestAPIUserGroups(m_mktAPI);
	requestAPIUsers(m_mktAPI);
}
