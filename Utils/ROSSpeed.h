#ifndef ROSSPEED_H
#define ROSSPEED_H

#include <QString>

class ROSSpeed
{
	quint64 m_bps;

public:
	ROSSpeed(quint64 bps = 0) :
		m_bps(bps)
	{	}
	explicit ROSSpeed(const ROSSpeed &speed) : m_bps(speed.m_bps)
	{	}
	explicit ROSSpeed(const QString &bps);

	void fromString(const QString &bps);
	QString toString()const;

	inline quint64 toInt()const	{ return m_bps;	}

	inline ROSSpeed &operator=(quint64 bps)				{ m_bps = bps;	return *this;		}
	inline bool operator==(const ROSSpeed &speed)const	{ return m_bps == speed.m_bps;}
	inline bool operator==(const quint64 &bps)const		{ return m_bps == bps;		}
	inline operator bool()		{ return m_bps != 0 ;	}
	inline bool operator ! ()	{ return m_bps == 0;	}
	inline bool operator &&(const ROSSpeed &speed) const	{ return m_bps && speed.m_bps;	}
	inline bool operator ||(const ROSSpeed &speed) const	{ return m_bps || speed.m_bps;	}
};


#endif // ROSSPEED_H
