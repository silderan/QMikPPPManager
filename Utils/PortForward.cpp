#include "PortForward.h"

QString IPProtocol::toString(IPProtocol::Type type)
{
	switch( type )
	{
	case IPProtocol::Unkown:	return "unknown";
	case IPProtocol::TCP:		return "tcp";
	case IPProtocol::UDP:		return "udp";
	case IPProtocol::Both:		return "tcp/udp";
	}
	return QString("");
}

IPProtocol::Type IPProtocol::fromString(const QString protocol)
{
	if( protocol == "tcp" )
		return IPProtocol::TCP;
	else
	if( protocol == "udp" )
		return IPProtocol::UDP;
	else
	if( protocol == "tcp/udp" )
		return IPProtocol::Both;
	return IPProtocol::Unkown;
}


QIPProtocolComboBox::QIPProtocolComboBox(QWidget *papi) : QComboBox(papi)
{
	addItems( QStringList() << "unknown" << "tcp" << "udp" << "tcp/udp" );
}

QIPProtocolComboBox::QIPProtocolComboBox(const QString &protoName, QWidget *papi) : QComboBox(papi)
{
	addItems( QStringList() << "unknown" << "tcp" << "udp" << "tcp/udp" );
	setProtocol(protoName);
}

QIPProtocolComboBox::QIPProtocolComboBox(IPProtocol::Type type, QWidget *papi) : QComboBox(papi)
{
	addItems( QStringList() << "unknown" << "tcp" << "udp" << "tcp/udp" );
	setProtocol(type);
}

void QIPProtocolComboBox::setProtocol(const QString &protoName)
{
	setCurrentIndex( findData(protoName, Qt::EditRole) );
}

void QIPProtocolComboBox::setProtocol(IPProtocol::Type type)
{
	Q_ASSERT( type <= IPProtocol::Both );
	setCurrentIndex( static_cast<int>(type) );
}

IPProtocol::Type QIPProtocolComboBox::protocol() const
{
	return static_cast<IPProtocol::Type>(currentIndex());
}

QPortSpinBox::QPortSpinBox(QWidget *papi) : QSpinBox(papi)
{
	setMinimum(1);
	setMaximum(0xFFFF);
}

QPortSpinBox::QPortSpinBox(quint16 port, QWidget *papi) : QSpinBox(papi)
{
	setMinimum(1);
	setMaximum(0xFFFF);
	setValue(port);
}

QString PortForward::toString() const
{
	QString rtn;
	// tcp:8080>192.168.1.1
	if( (m_publicPortTo == m_privatePortTo) && (m_publicPortTo == m_publicPortFrom) )
		return QString("%1:%2>%3").arg( IPProtocol::toString(m_protocol), QString::number(m_publicPortTo), m_destIP.toString() );

	// tcp:8080>192.168.1.1:80
	if( m_publicPortTo == m_publicPortFrom )
		return QString("%1:%2>%3:%4").arg( IPProtocol::toString(m_protocol), QString::number(m_publicPortTo), m_destIP.toString(), QString::number(m_privatePortTo) );

	// tcp:8080-8088>192.168.1.1:80-88
	return QString("%1:%2-%3>%4:%5-%6").arg( IPProtocol::toString(m_protocol),
											 QString::number(m_publicPortFrom), QString::number(m_publicPortTo),
											 m_destIP.toString(),
											 QString::number(m_privatePortFrom), QString::number(m_privatePortTo) );
}

void PortForward::fromString(const QString &saveString)
{
	QStringList data = saveString.split( QRegExp("[:->]") );
	if( data.count() == 3 )
	{
		setProtocol( data[0] );
		m_publicPortFrom = static_cast<quint16>(data[1].toUInt());
		m_destIP.fromString( data[2] );
		m_publicPortTo = m_privatePortTo = m_privatePortFrom = m_publicPortFrom;
	}
	else
	if( data.count() == 4 )
	{
		setProtocol( data[0] );
		m_publicPortFrom = static_cast<quint16>(data[1].toUInt());
		m_destIP.fromString( data[2] );
		m_privatePortFrom = static_cast<quint16>(data[3].toUInt());
		m_publicPortTo = m_publicPortFrom;
		m_privatePortTo = m_privatePortFrom;
	}
	else
	if( data.count() == 6 )
	{
		setProtocol( data[0] );
		m_publicPortFrom = static_cast<quint16>(data[1].toUInt());
		m_publicPortTo = static_cast<quint16>(data[2].toUInt());
		m_destIP.fromString( data[3] );
		m_privatePortFrom = static_cast<quint16>(data[4].toUInt());
		m_privatePortTo = static_cast<quint16>(data[5].toUInt());
	}
}

bool PortForward::operator ==(const PortForward &other) const
{
	return	(m_destIP == other.m_destIP) &&
			(m_publicPortTo == other.m_publicPortTo) &&
			(m_publicPortFrom == other.m_publicPortFrom) &&
			(m_privatePortTo == other.m_privatePortTo) &&
			(m_privatePortFrom == other.m_privatePortFrom) &&
			(m_protocol == other.m_protocol);
}

bool PortForward::operator !=(const PortForward &other) const
{
	return	(m_destIP != other.m_destIP) ||
			(m_publicPortTo != other.m_publicPortTo) ||
			(m_publicPortFrom != other.m_publicPortFrom) ||
			(m_privatePortTo != other.m_privatePortTo) ||
			(m_privatePortFrom != other.m_privatePortFrom) ||
			(m_protocol != other.m_protocol);
}

bool QPortForwardList::operator==(const QPortForwardList &other) const
{
	if( count() != other.count() )
		return false;
	for( int i = 0; i < count(); i++ )
		if( at(i) != other.at(i) )
			return false;
	return true;
}

bool QPortForwardList::operator!=(const QPortForwardList &other) const
{
	if( count() != other.count() )
		return true;
	for( int i = 0; i < count(); i++ )
		if( at(i) != other.at(i) )
			return true;
	return false;
}
