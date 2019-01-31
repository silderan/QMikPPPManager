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
