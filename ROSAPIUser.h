#ifndef ROSAPIUSER_H
#define ROSAPIUSER_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QMap>

#include "Comm.h"

struct ROSAPIUserGroup
{
	QString m_name;
	QStringList m_policies;
	ROSAPIUserGroup()
	{	}
	ROSAPIUserGroup(const QString &name, const QString &policies) :
		m_name(name), m_policies(policies.split(','))
	{
	}
	ROSAPIUserGroup(const QString &name, const QStringList &policies) :
		m_name(name), m_policies(policies)
	{
	}
};

typedef QList<ROSAPIUserGroup> QROSAPIUserGroupList;
//typedef QMap<QString, QROSAPIUserGroupList> QROSAPIUserGroupListMap;
//typedef QMapIterator<QString, QROSAPIUserGroupList> QROSAPIUserGroupListMapIterator;

struct ROSAPIUser
{
	// Position is important becouse in some places there is a value compartion.
	enum Level
	{
		NoRights,		// Can't do anything.
		Comercial,		// Can't change anything, just peep data.
		Instalator,		// Can add new PPPoE users and modify their non sensitive data.
		Administrator,	// Can do everything exept change program/router configuration.
		Supervisor		// Can do everything.
	};

	QString m_uname;
	Level m_level;

	static QStringList levelNames(bool plural = false);
	static QString levelName(Level level, bool plural = false)	{ return levelNames(plural)[level];	}

	QString levelName(bool plural = false) const	{ return levelNames(plural)[m_level];	}

	ROSAPIUser() :
		m_level(NoRights)
	{	}
	ROSAPIUser(const QString &name, Level level = NoRights) :
		m_uname(name), m_level(level)
	{	}
	ROSAPIUser(const QString &name, const QString &levelName) :
		m_uname(name), m_level(static_cast<Level>(ROSAPIUser::levelNames().indexOf(levelName.toLower())))
	{
		if( m_level < NoRights )
			m_level = NoRights;
	}
};

typedef QList<ROSAPIUser> QROSAPIUserList;
//typedef QMap<QString, QROSAPIUserList> QROSAPIUserListMap;
//typedef QMapIterator<QString, QROSAPIUserList> QROSAPIUserListMapIterator;

class QMultiROSAPIUserManager : public QObject
{
	Q_OBJECT

	QROSAPIUserList m_userList;
	QROSAPIUserGroupList m_userGroupList;

private slots:
	void onUserReceive(const ROS::QSentence &sentence);
	void onUserGroupReceive(const ROS::QSentence &sentence);

public:
	QMultiROSAPIUserManager(QObject *papi = Q_NULLPTR) : QObject(papi)
	{	}

	void requestAPIUsers(ROS::Comm *mktAPI);
	void requestAPIUserGroups(ROS::Comm *mktAPI);

	virtual void requestData(ROS::Comm *m_mktAPI);

signals:
	void reply(const QString &info);
	void done();
	void error();
};

#endif // ROSAPIUSER_H
