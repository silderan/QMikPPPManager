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

#ifndef ROSIPADDRESS_H
#define ROSIPADDRESS_H

#include "../UnitTests.h"
#include "../../SildeQtUtils/src/IPv4Range.h"
#include "ROSDataBasics.h"

class ROSIPAddress : public ROSDataBase
{
	IPv4 m_address;
	QString m_ifaceName;

public:
	explicit ROSIPAddress(const QString &routerName) : ROSDataBase(DataTypeID::IPAddress, routerName)
	{	}

	void setAddress(const IPv4 &address)		{ m_address = address;	}
	const IPv4 &address() const					{ return m_address;		}

	inline void setIfaceName(const QString &ifaceName)	{ m_ifaceName = ifaceName;	}
	inline const QString &ifaceName() const				{ return m_ifaceName;		}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosData) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSIPADDRESS_H
