#include "IPv4Range.h"

#include <QStringList>
#include <QRegExp>
#include <QtMath>
#define KEY_IPV4					("ipv4")
#define KEY_IPV4RANGE				("ipv4-range")
#define KEY_IPV4RANGELISTNAME		("ipv4-range-list-name")
#define KEY_IPV4RANGELISTDATA(_l)	(QString("ipv4-range-list-data-%1").arg(_l))
#define KEY_IPV4RANGELISTMAPDATA(_l)	(QString("ipv4-range-list-map-data-%1").arg(_l))

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

QString IPv4Range::toLoadString() const
{
	return QString("%1-%2").arg( m_first.toString(), m_last.toString() );
}

void IPv4Range::fromLoadString(const QString &line)
{
	QStringList l = line.split( '-', QString::SkipEmptyParts );
	if( l.count() >= 2 )
	{
		m_first.fromString( l[0] );
		m_last.fromString( l[1] );
	}
}

const IPv4Range &IPv4Range::fromNotationString(QString ip)
{
	int splitIndex;

	//clean all whitespaces.
	ip.replace(" ", "");

	// Check A.B.C.D/M format
	if( (splitIndex = ip.indexOf('/')) != -1 )
	{
		int mask = ip.mid(splitIndex+1).toInt();
		if( mask > 0 )
		{
			quint32 lastIP = static_cast<quint32>(qPow(2, mask)) - 1;
			setRange( IPv4(ip.left(mask)), IPv4(lastIP) );
		}
	}
	else
	// Check A1.B1.C1.D1-A2.B2.C2.D2 format
	if( (splitIndex = ip.indexOf('-')) != -1 )
		setRange( IPv4(ip.right(splitIndex)), IPv4(ip.mid(splitIndex+1)) );
	return *this;
}

void IPv4Range::save(QIniData &iniData) const
{
	iniData[KEY_IPV4RANGE] = toLoadString();
}

void IPv4Range::load(const QIniData &iniData)
{
	fromLoadString( iniData[KEY_IPV4RANGE] );
}

QStringList IPv4Range::rangeStringList() const
{
	QStringList rtn;
	for( IPv4 ip = first(); ip <= last(); ++ip )
		rtn.append(ip.toString());
	return rtn;
}

QStringList IPv4RangeListMap::staticIPv4StringList(const QString &name) const
{
	QStringList rtn;
	if( contains(name) )
	{
		const IPv4RangeList &ipv4RangeList = value(name);

		foreach( const IPv4Range &ipv4Range, ipv4RangeList )
		{
			rtn.append( ipv4Range.rangeStringList() );
		}
	}
	return rtn;
}

QStringList IPv4RangeListMap::staticIPv4StringList() const
{
	QStringList rtn;
	foreach( const IPv4RangeList ipv4RangeList, *this )
	{
		foreach( const IPv4Range &ipv4Range, ipv4RangeList )
		{
			rtn.append( ipv4Range.rangeStringList() );
		}
	}
	return rtn;
}

void IPv4RangeListMap::save(QIniData &iniData) const
{
	IPv4RangeListMapIterator it(*this);
	int i = 0;
	while( it.hasNext() )
	{
		it.next();
		QString loadString;
		foreach( const IPv4Range &ipv4Range, it.value() )
			loadString += QString("%1,").arg( ipv4Range.toLoadString() );

		iniData[KEY_IPV4RANGELISTMAPDATA(++i)] = QString("%1:%2").arg(it.key(), loadString);
	}
}

void IPv4RangeListMap::load(const QIniData &iniData)
{
	clear();
	QString line;
	for( int i = 0; !(line = iniData[KEY_IPV4RANGELISTMAPDATA(i+1)]).isEmpty(); i++ )
	{
		int sep = line.indexOf(':');
		if( sep != -1 )
		{
			IPv4RangeList ipv4RangeList;
			QString key = line.left(sep);
			QString ipv4RangeList_loadString = line.mid(sep+1);

			foreach( QString ipv4Range_LoadString,  ipv4RangeList_loadString.split(',', QString::SkipEmptyParts) )
				ipv4RangeList.append( IPv4Range(ipv4Range_LoadString) );

			insert(key, ipv4RangeList);
		}
	}
}
