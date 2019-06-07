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

#ifndef CONNECTINFO_H
#define CONNECTINFO_H

#include <QStringList>

#include "Utils/IPv4Range.h"

class ConnectInfo
{
	QString m_uname;
	QString m_upass;
	IPv4 m_hostIPv4;
	quint16 m_hostPort;

public:
	ConnectInfo()
	{	}
	ConnectInfo(const ConnectInfo &connectInfo) :
		m_uname(connectInfo.m_uname),
		m_upass(connectInfo.m_upass),
		m_hostIPv4(connectInfo.m_hostIPv4),
		m_hostPort(connectInfo.m_hostPort)
	{	}
	explicit ConnectInfo(const QString &loadLine)
	{
		fromString(loadLine);
	}

	ConnectInfo( const QString &userName, const QString &userPass, const IPv4 &hostAddr, quint16 hostPort ):
		m_uname(userName), m_upass(userPass),
		m_hostIPv4(hostAddr), m_hostPort(hostPort)
	{	}
	// For now, router name will be auto-formed with IP:port
	QString routerName() const		{ return QString("%1:%2").arg(m_hostIPv4.toString(), QString::number(m_hostPort)); }

	const QString &userName() const			{ return m_uname;	}
	void setUserName(const QString &uname)	{ m_uname = uname;	}

	const QString &userPass() const			{ return m_upass;	}
	void setUserPass(const QString &upass)	{ m_upass = upass;	}

	const IPv4 &hostIPv4() const			{ return m_hostIPv4;	}
	void setHostIPv4(const IPv4 &hostIPv4)	{ m_hostIPv4 = hostIPv4;}

	quint16 hostPort() const			{ return m_hostPort;	}
	void setHostPort(quint16 hostPort)	{ m_hostPort = hostPort;}

	void fromString(const QString &line);
	QString toString() const;
};

class QConnectInfoList : public QList<ConnectInfo>
{
public:
	void load(const QIniData &iniData);
	void save(QIniData &iniData)const;
};

#endif // CONNECTINFO_H
