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

#ifndef PORTFORWARD_H
#define PORTFORWARD_H

#include <QString>
#include <QComboBox>
#include <QSpinBox>

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

class QIPProtocolComboBox : public QComboBox
{

public:
	QIPProtocolComboBox(QWidget *papi = Q_NULLPTR);
	QIPProtocolComboBox(const QString &protoName, QWidget *papi = Q_NULLPTR);
	QIPProtocolComboBox(IPProtocol::Type type, QWidget *papi = Q_NULLPTR);
	void setProtocol(const QString &protoName);
	void setProtocol(IPProtocol::Type type);
	IPProtocol::Type protocol() const;
};

class QPortSpinBox : public QSpinBox
{

public:
	QPortSpinBox(QWidget *papi = Q_NULLPTR);
	QPortSpinBox(quint16 port, QWidget *papi = Q_NULLPTR);
	quint16 port() const	{ return static_cast<quint16>( value() );	}
	void setPort(quint16 p)	{ setValue(p);	}
};

class PortForward
{
	QString m_name;
	IPProtocol::Type m_protocol;

	quint16 m_publicPortIni;
	quint16 m_publicPortEnd;
	quint16 m_privatePortIni;
	quint16 m_privatePortEnd;
	IPv4 m_destIP;

public:
	PortForward()
		: m_protocol(IPProtocol::Unkown)
		, m_publicPortIni(0)
		, m_publicPortEnd(0)
		, m_privatePortIni(0)
		, m_privatePortEnd(0)
	{	}
	PortForward(const QString name, const IPProtocol::Type &protocol, quint16 publicPort, quint16 privatePort, IPv4 destIP)
		: m_name(name)
		, m_protocol( protocol )
		, m_publicPortIni(publicPort)
		, m_publicPortEnd(publicPort)
		, m_privatePortIni(privatePort)
		, m_privatePortEnd(privatePort)
		, m_destIP(destIP)
	{	}
	PortForward(const QString name, const IPProtocol::Type &protocol, quint16 publicPortIni, quint16 publicPortEnd, quint16 privatePortIni, quint16 privatePortEnd, IPv4 destIP)
		: m_name(name)
		, m_protocol( protocol )
		, m_publicPortIni(publicPortIni)
		, m_publicPortEnd(publicPortEnd)
		, m_privatePortIni(privatePortIni)
		, m_privatePortEnd(privatePortEnd)
		, m_destIP(destIP)
	{	}
	explicit PortForward(const QString &saveString)
	{
		fromSaveString(saveString);
	}

	const QString &name() const		{ return m_name;	}
	void setName(const QString &n)	{ m_name = n;		}

	const IPProtocol::Type &protocol() const			{ return m_protocol;	}
	void setProtocol(const IPProtocol::Type &protocol)	{ m_protocol = protocol;  }
	void setProtocol(const QString &protocol)			{ setProtocol( IPProtocol::fromString(protocol) ); }

	quint16 publicPortIni() const		{ return m_publicPortIni;	}
	void setPublicPortIni(quint16 p)	{ m_publicPortIni = p;		}
	quint16 publicPortEnd() const		{ return m_publicPortEnd;	}
	void setPublicPortEnd(quint16 p)	{ m_publicPortEnd = p;		}

	quint16 privatePortIni() const		{ return m_privatePortIni;	}
	void setPrivatePortIni(quint16 p)	{ m_privatePortIni = p;		}
	quint16 privatePortEnd() const		{ return m_privatePortEnd;	}
	void setPrivatePortEnd(quint16 p)	{ m_privatePortEnd = p;		}

	IPv4 destIP() const						{ return m_destIP;	}
	void setDestIP(const IPv4 &ip)		 	{ m_destIP = ip;	}

	QString toSaveString() const;
	void fromSaveString(const QString &saveString);
	bool operator ==(const PortForward &other)const;
	bool operator !=(const PortForward &other)const;
};

class QPortForwardList : public QList<PortForward>
{

public:
	QString toSaveString()const;
	void fromSaveString(const QString &saveString);

	bool operator==(const QPortForwardList &other) const;
	bool operator!=(const QPortForwardList &other) const;
};

#endif // PORTFORWARD_H
