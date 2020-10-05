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

#ifndef ROSIPPOOL_H
#define ROSIPPOOL_H

#include "../UnitTests.h"
#include "../../SildeQtUtils/src/IPv4Range.h"
#include "ROSDataBasics.h"

class ROSIPPool : public ROSDataBase
{
	QString m_name;
	IPv4RangeList m_pool;

public:
	explicit ROSIPPool(const QString &routerName) : ROSDataBase(DataTypeID::IPPool, routerName)
	{	}

	const QString &poolName() const				{ return m_name;	}
	void setPoolName(const QString &poolName)	{ m_name = poolName;	}

	const IPv4RangeList &poolRanges() const				{ return m_pool;		}
	IPv4RangeList &poolRanges()							{ return m_pool;		}
	void setPoolRanges(const IPv4RangeList &poolRanges)	{ m_pool = poolRanges;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSIPPOOL_H
