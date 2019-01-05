#ifndef ROSSPEED_H
#define ROSSPEED_H

#include <QString>

class ROSSpeed
{
	quint32 m_kbps;

public:
	ROSSpeed(quint32 kbps = 0) :
		m_kbps(kbps)
	{	}
	explicit ROSSpeed(const ROSSpeed &speed) : m_kbps(speed.m_kbps)
	{	}
	explicit ROSSpeed(const QString &kbps);

	void fromString(const QString &kbps);
	QString toString()const;

	inline quint32 toInt()const	{ return m_kbps;	}
	inline ROSSpeed &operator=(quint32 kbps)	{ m_kbps = kbps;	return *this;		}
	inline bool operator==(const ROSSpeed &speed)const	{ return m_kbps == speed.m_kbps;}
	inline bool operator==(const quint32 &kbps)const	{ return m_kbps == kbps;		}
	operator bool() { return m_kbps != 0 ;	}
	bool operator &&(const ROSSpeed &speed) const	{ return m_kbps && speed.m_kbps;	}
	bool operator ||(const ROSSpeed &speed) const	{ return m_kbps || speed.m_kbps;	}
};


#endif // ROSSPEED_H
