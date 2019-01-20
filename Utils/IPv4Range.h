#ifndef IPV4RANGE_H
#define IPV4RANGE_H

#include <QString>
#include <QList>
#include <QMap>

#include "QIniFile.h"

#define IPV4_TO_UINT(_A, _B, _C, _D)	(static_cast<quint32>(((static_cast<quint8>(_A)&255)<<24)+((static_cast<quint8>(_B)&255)<<16)+((static_cast<quint8>(_C)&255)<<8)+(static_cast<quint8>(_D)&255)))
#define UINT_TO_IPV4A(_IPV4_)			((static_cast<quint32>(_IPV4_)>>24) & 255)
#define UINT_TO_IPV4B(_IPV4_)			((static_cast<quint32>(_IPV4_)>>16) & 255)
#define UINT_TO_IPV4C(_IPV4_)			((static_cast<quint32>(_IPV4_)>>8) & 255)
#define UINT_TO_IPV4D(_IPV4_)			(static_cast<quint32>(_IPV4_) & 255)
#define UINT_TO_SIPV4(_IPV4_)			(QString("%1.%2.%3.%4").arg(UINT_TO_IPV4A(_IPV4_)).arg(UINT_TO_IPV4B(_IPV4_)).arg(UINT_TO_IPV4C(_IPV4_)).arg(UINT_TO_IPV4D(_IPV4_)))

class IPv4
{
	quint32 m_ip;

public:
	IPv4() : m_ip(0)
	{	}
	IPv4(const IPv4 &ipv4) :
		m_ip(ipv4.m_ip)
	{	}
	explicit IPv4(const quint32 &ipv4) :
		m_ip(ipv4)
	{	}
	IPv4(quint8 A, quint8 B, quint8 C, quint8 D) :
		m_ip(static_cast<quint32>(((static_cast<quint8>(A)&255)<<24)+
								  ((static_cast<quint8>(B)&255)<<16)+
								  ((static_cast<quint8>(C)&255)<<8)+
								   (static_cast<quint8>(D)&255)) )
	{	}
	explicit IPv4(const QString &ipv4)
	{
		fromString(ipv4);
	}

	bool isValid() const	{ return m_ip != 0;	}

	QString toString() const						{ return UINT_TO_SIPV4(m_ip);	}
	static QString toString(const quint32 &ipv4)	{ return UINT_TO_SIPV4(ipv4);	}

	void fromString(const QString &ipv4)			{ (*this) = IPv4::FromString(ipv4);	}
	static IPv4 FromString(const QString &ipv4String);

	void save(QIniData &iniData) const;
	void load(const QIniData &iniData);

	IPv4 &operator=(const IPv4 &ipv4)	{ this->m_ip = ipv4.m_ip; return *this;	}
	IPv4 &operator=(const QString &ipv4){ fromString(ipv4);	return *this;		}

	bool operator ==(const IPv4 &ipv4) const	{ return this->m_ip == ipv4.m_ip;	}
	bool operator ==(const quint32 &ipv4) const	{ return this->m_ip == ipv4;		}
	bool operator ==(const QString &ipv4) const	{ return this->m_ip == IPv4::FromString(ipv4).m_ip;	}

	bool operator !=(const IPv4 &ipv4) const	{ return this->m_ip != ipv4.m_ip;	}
	bool operator !=(const quint32 &ipv4) const	{ return this->m_ip != ipv4;		}
	bool operator !=(const QString &ipv4) const	{ return this->m_ip != IPv4::FromString(ipv4).m_ip;	}

	bool operator >=(const IPv4 &ipv4) const	{ return this->m_ip >= ipv4.m_ip;	}
	bool operator >=(const quint32 &ipv4) const	{ return this->m_ip >= ipv4;		}
	bool operator >=(const QString &ipv4) const	{ return this->m_ip >= IPv4::FromString(ipv4).m_ip;	}

	bool operator >(const IPv4 &ipv4) const		{ return this->m_ip > ipv4.m_ip;}
	bool operator >(const quint32 &ipv4) const	{ return this->m_ip > ipv4;		}
	bool operator >(const QString &ipv4) const	{ return this->m_ip > IPv4::FromString(ipv4).m_ip;	}

	bool operator <(const IPv4 &ipv4) const		{ return this->m_ip < ipv4.m_ip;}
	bool operator <(const quint32 &ipv4) const	{ return this->m_ip < ipv4;		}
	bool operator <(const QString &ipv4) const	{ return this->m_ip < IPv4::FromString(ipv4).m_ip;	}

	bool operator <=(const IPv4 &ipv4) const	{ return this->m_ip <= ipv4.m_ip;	}
	bool operator <=(const quint32 &ipv4) const	{ return this->m_ip <= ipv4;		}
	bool operator <=(const QString &ipv4) const	{ return this->m_ip <= IPv4::FromString(ipv4).m_ip;	}

	IPv4 operator+(quint32 i)	{ return IPv4(this->m_ip+i);	}
	IPv4 operator-(quint32 i)	{ return IPv4(this->m_ip-i);	}

	IPv4 &operator++()			{ m_ip++; return *this;	}
	IPv4 &operator--()			{ m_ip--; return *this;	}

	IPv4 operator++(int)		{ m_ip++; return IPv4(this->m_ip+1);	}
	IPv4 operator--(int)		{ m_ip--; return IPv4(this->m_ip-1);	}

	IPv4 &operator+=(const quint32 &i)	{ m_ip+=i; return *this;	}
	IPv4 &operator-=(const quint32 &i)	{ m_ip-=i; return *this;	}
};

inline bool operator ==(const quint32 &ipv4A, const IPv4 &ipv4B)	{ return ipv4B == ipv4A;}
inline bool operator ==(const QString &ipv4A, const IPv4 &ipv4B)	{ return ipv4B == ipv4A;}
inline bool operator >=(const quint32 &ipv4A, const IPv4 &ipv4B)	{ return ipv4B <= ipv4A;}
inline bool operator >=(const QString &ipv4A, const IPv4 &ipv4B)	{ return ipv4B <= ipv4A;}
inline bool operator >(const quint32 &ipv4A, const IPv4 &ipv4B)		{ return ipv4B < ipv4A; }
inline bool operator >(const QString &ipv4A, const IPv4 &ipv4B)		{ return ipv4B < ipv4A; }
inline bool operator <=(const quint32 &ipv4A, const IPv4 &ipv4B)	{ return ipv4B >= ipv4A;}
inline bool operator <=(const QString &ipv4A, const IPv4 &ipv4B)	{ return ipv4B >= ipv4A;}
inline bool operator <(const quint32 &ipv4A, const IPv4 &ipv4B)		{ return ipv4B > ipv4A; }
inline bool operator <(const QString &ipv4A, const IPv4 &ipv4B)		{ return ipv4B > ipv4A; }

typedef QList<IPv4> IPv4List;

class IPv4Range
{
	IPv4 m_first;
	IPv4 m_last;

public:
	IPv4Range() :
		m_first(0), m_last(0xFFFFFFFF)
	{	}
	IPv4Range(const IPv4Range &ipv4Range) :
		m_first(ipv4Range.m_first),
		m_last(ipv4Range.m_last)
	{	}
	explicit IPv4Range(const QString &line)
	{
		fromLoadString(line);
	}
	IPv4Range(const IPv4 &first, const IPv4 &last):
		m_first(first), m_last(last)
	{	}

	inline const IPv4 &first() const		{ return m_first;	}
	inline void setFirst(const IPv4 &ipv4)	{ m_first = ipv4;	}

	inline const IPv4 &last() const			{ return m_last;	}
	inline void setLast(const IPv4 &last)	{ m_last = last;	}

	inline void setRange(const IPv4 &first, const IPv4 &last)	{ setFirst(first); setLast(last);	}

	QString toLoadString() const;
	void fromLoadString(const QString &line);

	const IPv4Range &fromNotationString(QString ip);

	void save(QIniData &iniData) const;
	void load(const QIniData &iniData);
	QStringList rangeStringList()const;

	template <class T>
	bool inRange(const T &ipv4) const	{ return ipv4 >= m_first && ipv4 <= m_last; }
};

typedef QList<IPv4Range> IPv4RangeList;

class IPv4RangeListMap : public QMap<QString, IPv4RangeList>
{
public:
	IPv4RangeList rangeList(const QString &name)			{ return value(name, IPv4RangeList());	}
	void insert( const QString &name, const IPv4RangeList &ipv4RangeList)	{ QMap::insert(name, ipv4RangeList);	}
	void append( const QString &name, const IPv4RangeList &ipv4RangeList)	{ insert(name, IPv4RangeList() << rangeList(name) << ipv4RangeList);}
	void append( const QString &name, const IPv4Range &ipv4Range )			{ insert(name, IPv4RangeList() << rangeList(name) << ipv4Range);	}
	QStringList staticIPv4StringList(const QString &name) const;
	QStringList staticIPv4StringList() const;

	void save(QIniData &iniData) const;
	void load(const QIniData &iniData);
};
typedef QMapIterator<QString,IPv4RangeList> IPv4RangeListMapIterator;


#endif // IPV4RANGE_H
