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

#include "OpenBrowserInfo.h"


bool OpenBrowserInfo::operator ==(const OpenBrowserInfo &o) const
{
	return	(name == o.name) &&
			(httpProtocol == o.httpProtocol) &&
			(ip == o.ip) &&
			(port == o.port);
}

bool OpenBrowserInfo::operator !=(const OpenBrowserInfo &o) const
{
	return	(name != o.name) ||
			(httpProtocol != o.httpProtocol) ||
			(ip != ip) ||
			(port != o.port);
}

void OpenBrowserInfo::fromPortForward(const PortForward &pf)
{
	if( QString::number(pf.privatePortIni()).startsWith('4') )
		httpProtocol = "https";
	else
		httpProtocol = "http";
	name = pf.name();
	port = QString::number(pf.publicPortIni());
	ip = pf.destIP().toString();
}

QString OpenBrowserInfo::toURL() const
{
	return QString("%1://%2:%3").arg( httpProtocol, ip, port );
}

void OpenBrowserInfoList::append(const OpenBrowserInfo &o)
{
	if( !contains(o) )
		QList::append(o);
}

void OpenBrowserInfoList::append(const OpenBrowserInfoList &obfl)
{
	foreach( OpenBrowserInfo obf, obfl )
		append(obf);
}

void OpenBrowserInfoList::fromPortForwardList(const QPortForwardList &pfl)
{
	foreach( const PortForward &pf, pfl )
		append( OpenBrowserInfo(pf) );
}
