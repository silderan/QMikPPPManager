#include "IPv4Range.h"

#include <QStringList>
#include <QRegExp>

#define KEY_IPV4					("ipv4")
#define KEY_IPV4RANGE				("ipv4-range")
#define KEY_IPV4RANGELISTNAME		("ipv4-range-list-name")
#define KEY_IPV4RANGELISTDATA(_l)	(QString("ipv4-range-list-data-%1").arg(_l))

IPv4 IPv4::FromString(const QString &ipv4String)
{
	QStringList split = ipv4String.split( QRegExp("[.,]") );

	if( split.count() == 4 )
	{
		return IPv4( ((split[0].toUInt()&0xFF)<<24) +
					 ((split[1].toUInt()&0xFF)<<16) +
					 ((split[2].toUInt()&0xFF)<<8) +
					  (split[3].toUInt()&0xFF) );
	}
	return IPv4();
}

void IPv4::save(QIniData &iniData) const
{
	iniData[KEY_IPV4] = toString();
}

void IPv4::load(const QIniData &iniData)
{
	fromString(iniData[KEY_IPV4]);
}

QString IPv4Range::toString() const
{
	return QString("%1:%2-%3").arg( m_name, m_first.toString(), m_last.toString() );
}

void IPv4Range::fromString(const QString &line)
{
	QStringList l = line.split( QRegExp("[:-]"), QString::SkipEmptyParts );
	if( l.count() == 3 )
	{
		m_name = l[0];
		m_first.fromString( l[1] );
		m_last.fromString( l[2] );
	}
}

void IPv4Range::save(QIniData &iniData) const
{
	iniData[KEY_IPV4RANGE] = toString();
}

void IPv4Range::load(const QIniData &iniData)
{
	fromString( iniData[KEY_IPV4RANGE] );
}

void IPv4RangeMap::save(QIniData &iniData) const
{
	iniData[KEY_IPV4RANGELISTNAME] = m_name;
	IPv4RangeMapIterator it(*this);
	int i = 0;
	while( it.hasNext() )
	{
		it.next();
		iniData[KEY_IPV4RANGELISTDATA(i++)] = it.value().toString();
	}
}

void IPv4RangeMap::load(const QIniData &iniData)
{
	clear();
	m_name = iniData[KEY_IPV4RANGELISTNAME];
	QString line;
	for( int i = 0; !(line = iniData[KEY_IPV4RANGELISTDATA(i+1)]).isEmpty(); i++ )
	{
		IPv4Range ipv4Range(line);
		insert(ipv4Range.name(), ipv4Range);
	}
}

//QString IPv4RangeMap::range(const IPv4 &ipv4) const
//{
//	IPv4RangeMapIterator it(*this);
//	while( it.hasNext() )
//	{
//		it.next();
//		if( it.value().inRange(ipv4))
//			return it.key();
//	}
//	return QString();
//}
