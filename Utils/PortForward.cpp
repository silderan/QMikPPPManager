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

QString PortForward::toSaveString() const
{
	QString rtn;
	// name=tcp:8080>192.168.1.1
	if( (m_publicPortEnd == m_privatePortEnd) && (m_publicPortEnd == m_publicPortIni) )
		return QString("%1=%2:%3>%4").arg( m_name, IPProtocol::toString(m_protocol), QString::number(m_publicPortEnd), m_destIP.toString() );

	// name=tcp:8080>192.168.1.1:80
	if( m_publicPortEnd == m_publicPortIni )
		return QString("%1=%2:%3>%4:%5").arg( m_name, IPProtocol::toString(m_protocol), QString::number(m_publicPortEnd), m_destIP.toString(), QString::number(m_privatePortEnd) );

	// name=tcp:8080-8088>192.168.1.1:80-88
	return QString("%1=%2:%3-%4>%5:%6-%7").arg( m_name, IPProtocol::toString(m_protocol),
											 QString::number(m_publicPortIni), QString::number(m_publicPortEnd),
											 m_destIP.toString(),
											 QString::number(m_privatePortIni), QString::number(m_privatePortEnd) );
}

void PortForward::fromSaveString(const QString &saveString)
{
	QStringList data = saveString.split( QRegExp("[=:\\->]") );
	if( data.count() == 4 )
	{
		m_name = data[0];
		setProtocol( data[1] );
		m_publicPortIni = static_cast<quint16>(data[2].toUInt());
		m_destIP.fromString( data[3] );
		m_publicPortEnd = m_privatePortEnd = m_privatePortIni = m_publicPortIni;
	}
	else
	if( data.count() == 5 )
	{
		m_name = data[0];
		setProtocol( data[1] );
		m_publicPortIni = static_cast<quint16>(data[2].toUInt());
		m_destIP.fromString( data[3] );
		m_privatePortIni = static_cast<quint16>(data[4].toUInt());
		m_publicPortEnd = m_publicPortIni;
		m_privatePortEnd = m_privatePortIni;
	}
	else
	if( data.count() == 6 )
	{
		m_name = data[0];
		setProtocol( data[1] );
		m_publicPortIni = static_cast<quint16>(data[2].toUInt());
		m_publicPortEnd = static_cast<quint16>(data[3].toUInt());
		m_destIP.fromString( data[4] );
		m_privatePortIni = static_cast<quint16>(data[5].toUInt());
		m_privatePortEnd = static_cast<quint16>(data[6].toUInt());
	}
}

bool PortForward::operator ==(const PortForward &other) const
{
	return	(m_name == other.m_name) &&
			(m_destIP == other.m_destIP) &&
			(m_publicPortEnd == other.m_publicPortEnd) &&
			(m_publicPortIni == other.m_publicPortIni) &&
			(m_privatePortEnd == other.m_privatePortEnd) &&
			(m_privatePortIni == other.m_privatePortIni) &&
			(m_protocol == other.m_protocol);
}

bool PortForward::operator !=(const PortForward &other) const
{
	return	(m_name != other.m_name) ||
			(m_destIP != other.m_destIP) ||
			(m_publicPortEnd != other.m_publicPortEnd) ||
			(m_publicPortIni != other.m_publicPortIni) ||
			(m_privatePortEnd != other.m_privatePortEnd) ||
			(m_privatePortIni != other.m_privatePortIni) ||
			(m_protocol != other.m_protocol);
}

QString QPortForwardList::toSaveString() const
{
	QString rtn;
	foreach( const PortForward &port, *this )
	{
		Q_ASSERT( !port.toSaveString().contains(',') );
		rtn.append( QString("%1,").arg(port.toSaveString()) );
	}
	return  rtn;
}

void QPortForwardList::fromSaveString(const QString &saveString)
{
	clear();
	foreach( QString portSaveString, saveString.split(',', QString::SkipEmptyParts) )
		append( PortForward(portSaveString) );
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
