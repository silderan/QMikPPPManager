#ifndef CONNECTINFO_H
#define CONNECTINFO_H

#include <QStringList>

#include "IPv4Range.h"

struct ConnectInfo
{
	QString m_uname;
	QString m_upass;
	IPv4 m_hostIPv4;
	quint16 m_hostPort;

	ConnectInfo()
	{	}
	ConnectInfo(const ConnectInfo &connectInfo) :
		m_uname(connectInfo.m_uname),
		m_upass(connectInfo.m_upass),
		m_hostIPv4(connectInfo.m_hostIPv4),
		m_hostPort(connectInfo.m_hostPort)
	{

	}
	explicit ConnectInfo(const QString &loadLine)
	{
		fromString(loadLine);
	}
	ConnectInfo( const QString &userName, const QString &userPass, const IPv4 &hostAddr, quint16 hostPort ):
		m_uname(userName), m_upass(userPass),
		m_hostIPv4(hostAddr), m_hostPort(hostPort)
	{

	}

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
