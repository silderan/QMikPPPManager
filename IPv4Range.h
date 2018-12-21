#ifndef IPV4RANGE_H
#define IPV4RANGE_H

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

	friend bool operator ==(const quint32 &ipv4A, const IPv4 &ipv4B);
	friend bool operator ==(const QString &ipv4A, const IPv4 &ipv4B);
	bool operator ==(const IPv4 &ipv4) const	{ return this->m_ip == ipv4.m_ip;	}
	bool operator ==(const quint32 &ipv4) const	{ return this->m_ip == ipv4;		}
	bool operator ==(const QString &ipv4) const	{ return this->m_ip == IPv4::FromString(ipv4);	}

	friend bool operator >=(const quint32 &ipv4, const IPv4 &ipv4B);
	friend bool operator >=(const QString &ipv4, const IPv4 &ipv4B);
	bool operator >=(const IPv4 &ipv4) const	{ return this->m_ip >= ipv4.m_ip;	}
	bool operator >=(const quint32 &ipv4) const	{ return this->m_ip >= ipv4;		}
	bool operator >=(const QString &ipv4) const	{ return this->m_ip >= IPv4::FromString(ipv4);	}

	friend bool operator >(const quint32 &ipv4, const IPv4 &ipv4B);
	friend bool operator >(const QString &ipv4, const IPv4 &ipv4B);
	bool operator >(const IPv4 &ipv4) const		{ return this->m_ip > ipv4.m_ip;}
	bool operator >(const quint32 &ipv4) const	{ return this->m_ip > ipv4;		}
	bool operator >(const QString &ipv4) const	{ return this->m_ip > IPv4::FromString(ipv4);	}

	friend bool operator <(const quint32 &ipv4, const IPv4 &ipv4B);
	friend bool operator <(const QString &ipv4, const IPv4 &ipv4B);
	bool operator <(const IPv4 &ipv4) const		{ return this->m_ip < ipv4.m_ip;}
	bool operator <(const quint32 &ipv4) const	{ return this->m_ip < ipv4;		}
	bool operator <(const QString &ipv4) const	{ return this->m_ip < IPv4::FromString(ipv4);	}

	friend bool operator <=(const quint32 &ipv4, const IPv4 &ipv4B);
	friend bool operator <=(const QString &ipv4, const IPv4 &ipv4B);
	bool operator <=(const IPv4 &ipv4) const	{ return this->m_ip <= ipv4.m_ip;	}
	bool operator <=(const quint32 &ipv4) const	{ return this->m_ip <= ipv4;		}
	bool operator <=(const QString &ipv4) const	{ return this->m_ip <= IPv4::FromString(ipv4);	}

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
inline bool operator >=(const quint32 &ipv4A, const IPv4 &ipv4B)	{ return ipv4B >= ipv4A;}
inline bool operator >=(const QString &ipv4A, const IPv4 &ipv4B)	{ return ipv4B >= ipv4A;}
inline bool operator >(const quint32 &ipv4A, const IPv4 &ipv4B)		{ return ipv4B > ipv4A; }
inline bool operator >(const QString &ipv4A, const IPv4 &ipv4B)		{ return ipv4B > ipv4A; }
inline bool operator <=(const quint32 &ipv4A, const IPv4 &ipv4B)	{ return ipv4B <= ipv4A;}
inline bool operator <=(const QString &ipv4A, const IPv4 &ipv4B)	{ return ipv4B <= ipv4A;}
inline bool operator <(const quint32 &ipv4A, const IPv4 &ipv4B)		{ return ipv4B < ipv4A; }
inline bool operator <(const QString &ipv4A, const IPv4 &ipv4B)		{ return ipv4B < ipv4A; }

typedef QList<IPv4> IPv4List;

class IPv4Range
{
	IPv4 m_first;
	IPv4 m_last;
	QString m_name;	// Just a name to identify it when necessary.

public:
	IPv4Range() :
		m_first(0), m_last(0xFFFFFFFF)
	{	}
	IPv4Range(const IPv4Range &ipv4Range) :
		m_first(ipv4Range.m_first),
		m_last(ipv4Range.m_last),
		m_name(ipv4Range.m_name)
	{	}
	explicit IPv4Range(const QString &line)
	{
		fromString(line);
	}
	IPv4Range(const IPv4 &first, const IPv4 &last):
		m_first(first), m_last(last)
	{

	}

	const QString &name() const { return m_name;	}
	const IPv4 &first() const	{ return m_first;	}
	const IPv4 &last() const	{ return m_last;	}

	QString toString() const;
	void fromString(const QString &line);
	void save(QIniData &iniData) const;
	void load(const QIniData &iniData);

	template <class T>
	bool inRange(const T &ipv4) const	{ return ipv4 >= m_first && ipv4 <= m_last; }
};

class IPv4RangeMap : public QMap<QString, IPv4Range>
{
	QString m_name;

public:
	const QString &name() const			{ return m_name;	}
	void setName(const QString name)	{ m_name = name;	}

	void addRange(const IPv4Range &ipv4Range)			{ insert(ipv4Range.name(), ipv4Range);	}
	IPv4Range range(const QString &ipv4RangeName) const	{ return value(ipv4RangeName);			}

	void delRange(const QString &ipv4RangeName)			{ remove(ipv4RangeName);	}

	void save(QIniData &iniData) const;
	void load(const QIniData &iniData);
	QString rangeName(const IPv4 &ipv4) const;
	bool inRange(const IPv4 &ipv4) const { return !rangeName(ipv4).isEmpty(); }
};
typedef QMapIterator<QString,IPv4Range> IPv4RangeMapIterator;

#endif // IPV4RANGE_H
