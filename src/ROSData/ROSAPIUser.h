/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ROSAPIUSER_H
#define ROSAPIUSER_H

#include "../UnitTests.h"

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

	const QString &userName()const			{ return m_uname;	}
	bool setUserName(const QString &uname)	{ return updateMember(m_uname, uname, userNamePattern, 4);	}

	const QString &userPass()const			{ return m_upass;	}
	bool setUserPass(const QString &upass)	{ return updateMember(m_upass, upass, userPassPattern, 8);	}

	const QString &groupName()const			{ return m_group;	}
	bool setGroupName(const QString group)	{ return updateMember(m_group, group, userNamePattern, 4);	}

	Level userLevel()const					{ return m_level;	}
	bool setUserLevel(Level level)			{ m_level = level; setComment(levelName());	return true; }
	bool setUserLevel(const QString &levelName)	{ return setUserLevel(ROSAPIUser::level(levelName));	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosAPIUser) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};
#endif // ROSAPIUSER_H
