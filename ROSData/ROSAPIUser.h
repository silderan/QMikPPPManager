#ifndef ROSAPIUSER_H
#define ROSAPIUSER_H

#include "DataTypeID.h"
#include "ROSDataBasics.h"

class ROSAPIUser : public ROSDataBase
{
public:
	// Position is important becouse in some places there is a value compartion.
	enum Level
	{
		NoRights,		// Can't do anything.
		Comercial,		// Can't change anything, just peep data.
		Instalator,		// Can add new PPPoE users and modify their non sensitive data.
		Administrator,	// Can do everything exept change program/router configuration.
		Supervisor		// Can do everything.
	};

private:
	QString m_uname;
	QString m_upass;
	QString m_group;
	Level m_level;

public:
	static QStringList levelNames(bool plural = false);
	static QString levelName(Level level, bool plural = false)	{ return levelNames(plural)[level];		}
	QString levelName(bool plural = false) const				{ return levelNames(plural)[m_level];	}
	static ROSAPIUser::Level level(const QString &levelName);

	explicit ROSAPIUser(const QString &routerName) : ROSDataBase(DataTypeID::APIUser, routerName),
		m_level(NoRights)
	{	}

	inline const QString &userName()const			{ return m_uname;	}
	inline void setUserName(const QString &uname)	{ m_uname = uname;	}

	inline const QString &userPass()const			{ return m_upass;	}
	inline void setUserPass(const QString &upass)	{ m_upass = upass;	}

	inline const QString &groupName()const			{ return m_group;	}
	inline void setGroupName(const QString group)	{ m_group = group;	}

	inline Level userLevel()const					{ return m_level;	}
	inline void setUserLevel(Level level)			{ m_level = level;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosAPIUser) const;
};
#endif // ROSAPIUSER_H
