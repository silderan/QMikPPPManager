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

#ifndef OPENBROWSERINFO_H
#define OPENBROWSERINFO_H

#include <QString>
#include <QList>

#include "PortForward.h"

struct OpenBrowserInfo
{
	QString name;
	QString httpProtocol;	// http or https
	QString port;
	QString ip;
	bool operator == (const OpenBrowserInfo &o)const;
	bool operator != (const OpenBrowserInfo &o)const;

	OpenBrowserInfo(const PortForward &pf)
	{
		fromPortForward(pf);
	}
	OpenBrowserInfo(const QString &name, const QString &httpProtocol, const QString &port, const QString &ip)
		: name(name)
		, httpProtocol(httpProtocol)
		, port(port)
		, ip(ip)
	{	}

	void fromPortForward(const PortForward &pf);
	QString toURL()const;
};

class OpenBrowserInfoList : public QList<OpenBrowserInfo>
{

public:
	OpenBrowserInfoList()
	{	}
	OpenBrowserInfoList(const QPortForwardList &pfl)
	{
		fromPortForwardList(pfl);
	}

	void append( const OpenBrowserInfo &o );
	void append(const OpenBrowserInfoList &obfl );
	void fromPortForwardList( const QPortForwardList &pfl );
};

#endif // OPENBROWSERINFO_H
