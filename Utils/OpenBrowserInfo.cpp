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
