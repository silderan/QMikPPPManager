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

#ifndef ROSAPIUSERGROUP_H
#define ROSAPIUSERGROUP_H

#include "../UnitTests.h"
#include "ROSDataBasics.h"

class ROSAPIUsersGroup : public ROSDataBase
{
	QString m_name;
	QStringList m_policy;

public:
	explicit ROSAPIUsersGroup(const QString &routerName) : ROSDataBase(DataTypeID::APIUsersGroup, routerName)
	{	}

	const QString &groupName()const			{ return m_name;	}
	void setGroupName(const QString &group)	{ m_name = group;	}

	const QStringList &policy() const			{ return m_policy;		}
	QStringList &policy()						{ return m_policy;		}
	void setPolicy(const QStringList &policy)	{ m_policy = policy;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosAPIUsersGrup) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSAPIUSERGROUP_H
