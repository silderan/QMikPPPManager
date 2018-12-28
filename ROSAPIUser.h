#ifndef ROSAPIUSER_H
#define ROSAPIUSER_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QMap>

#include "ROSDataBasics.h"

struct ROSAPIUser : public ROSDataBase
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
	QString levelName(bool plural = false) const				{ return levelNames(plural)[m_level];	}

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
	ROSAPIUser(const ROS::QSentence &sentence)
	{
		fromSentence(sentence);
	}

	// ROSDataBase interface
public:
	void fromSentence(const ROS::QSentence &s);
};

typedef QList<ROSAPIUser> QROSAPIUserList;
//typedef QMap<QString, QROSAPIUserList> QROSAPIUserListMap;
//typedef QMapIterator<QString, QROSAPIUserList> QROSAPIUserListMapIterator;

class QROSAPIUserManager : public QROSDataManager
{
	QROSAPIUserList m_list;

public:
	QROSAPIUserManager(ROS::Comm *papi);

	QROSAPIUserList &list() { return m_list;	}
	virtual ROSDataBase *fromSentence(ROS::QSentence &sentence)const;
	virtual ROS::QSentence getallSentence()const;
};

#endif // ROSAPIUSER_H
