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

#ifndef ROSSPEED_H
#define ROSSPEED_H

#include <QString>

class ROSSpeed
{
	quint64 m_bps;

public:
	explicit ROSSpeed(quint64 bps = 0) : m_bps(bps)
	{	}
	explicit ROSSpeed(const ROSSpeed &speed) : m_bps(speed.m_bps)
	{	}
	explicit ROSSpeed(const QString &bps);

	void fromString(const QString &bps);
	QString toString()const;

	quint64 toInt()const	{ return m_bps;	}

	ROSSpeed &operator=(const ROSSpeed &sp)		{ m_bps = sp.m_bps; return *this;	}
	template<typename T>
	bool operator=(const T &bps)const			{ return m_bps == static_cast<quint64>(bps);		}

	bool operator>=(const ROSSpeed &sp) const	{ return m_bps >= sp.m_bps;	}
	bool operator<=(const ROSSpeed &sp) const	{ return m_bps <= sp.m_bps;	}

	bool operator>(const ROSSpeed &sp) const	{ return m_bps > sp.m_bps;	}
	bool operator<(const ROSSpeed &sp) const	{ return m_bps < sp.m_bps;	}

	bool operator==(const ROSSpeed &speed)const	{ return m_bps == speed.m_bps;}
	template<typename T>
	bool operator==(const T &bps)const		{ return m_bps == static_cast<quint64>(bps);		}

	bool operator!=(const ROSSpeed &speed)const	{ return m_bps != speed.m_bps;}
	template<typename T>
	bool operator!=(const T &bps)const		{ return m_bps != static_cast<quint64>(bps);		}

	bool operator &&(const ROSSpeed &speed) const	{ return m_bps && speed.m_bps;	}
	bool operator ||(const ROSSpeed &speed) const	{ return m_bps || speed.m_bps;	}
};


#endif // ROSSPEED_H
