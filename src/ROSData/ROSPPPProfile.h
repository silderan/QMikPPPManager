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

#ifndef ROSPPPPROFILE_H
#define ROSPPPPROFILE_H

#include "../UnitTests.h"
#include "ROSDataBasics.h"
#include "../Utils/ROSRateLimit.h"

class ROSPPPProfile : public ROSDataBase
{
	QString m_name;
	QString m_localAdress;
	QString m_remoteAdress;
	QString m_bridgeName;
	ROSRateLimit m_rateLimit;

public:
	explicit ROSPPPProfile(const QString &routerName) : ROSDataBase(DataTypeID::PPPProfile, routerName)
	{	}

	const QString &profileName() const		{ return m_name;	}
	bool setProfileName(const QString &n)	{ return updateMember(m_name, n, profilePattern, 4);		}

	const ROSRateLimit &rateLimit() const	{ return m_rateLimit;	}
	ROSRateLimit &rateLimit()				{ return m_rateLimit;	}

	const QString &localAddress()const					{ return m_localAdress;	}
	bool setLocalAddress(const QString &localAddress)	{ return updateMember(m_localAdress, localAddress, userNamePattern, -4);	}

	const QString &remoteAddress()const					{ return m_remoteAdress;}
	bool setRemoteAddress(const QString &remoteAddress)	{ return updateMember(m_remoteAdress, remoteAddress, userNamePattern, -4);	}

	const QString &bridgeName() const				{ return m_bridgeName;	}
	bool setBridgeName(const QString &bridgeName)	{ return updateMember(m_bridgeName, bridgeName, userNamePattern, -4);	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosPPPProfile) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSPPPPROFILE_H
