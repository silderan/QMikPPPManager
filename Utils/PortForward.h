#ifndef PORTFORWARD_H
#define PORTFORWARD_H

#include <QString>
#include "IPv4Range.h"

class IPProtocol
{
public:
	enum Type
	{
		Unkown,
		TCP,
		UDP,
		Both
	};
	static QString toString(IPProtocol::Type type);
	static IPProtocol::Type fromString(const QString type);
};

class PortForward
{
	IPProtocol::Type m_protocol;

	quint16 m_publicPortFrom;
	quint16 m_publicPortTo;
	quint16 m_privatePortFrom;
	quint16 m_privatePortTo;
	IPv4 m_destIP;

public:
	PortForward() :
		m_protocol(IPProtocol::Unkown)
	  , m_publicPortFrom(0)
	  , m_publicPortTo(0)
	  , m_privatePortFrom(0)
	  , m_privatePortTo(0)
	{	}
	PortForward(const IPProtocol::Type &protocol, quint16 publicPort, quint16 privatePort, IPv4 destIP) :
		m_protocol( protocol )
	  , m_publicPortFrom(publicPort)
	  , m_publicPortTo(publicPort)
	  , m_privatePortFrom(privatePort)
	  , m_privatePortTo(privatePort)
	  , m_destIP(destIP)
	{	}
	PortForward(const IPProtocol::Type &protocol, quint16 publicPortFrom, quint16 publicPortTo, quint16 privatePortFrom, quint16 privatePortTo, IPv4 destIP) :
		m_protocol( protocol )
	  , m_publicPortFrom(publicPortTo)
	  , m_publicPortTo(publicPortFrom)
	  , m_privatePortFrom(privatePortTo)
	  , m_privatePortTo(privatePortFrom)
	  , m_destIP(destIP)
	{	}

	const IPProtocol::Type &protocol() const	{ return m_protocol;	}
	void setProtocol(const IPProtocol::Type &protocol)	{ m_protocol = protocol;  }
	void setProtocol(const QString &protocol)			{ setProtocol( IPProtocol::fromString(protocol) ); }

	QString toString() const;
	void fromString(const QString &saveString);
	bool operator ==(const PortForward &other)const;
	bool operator !=(const PortForward &other)const;
};

class QPortForwardList : public QList<PortForward>
{
public:
	bool operator==(const QPortForwardList &other) const;
	bool operator!=(const QPortForwardList &other) const;
};

#endif // PORTFORWARD_H
