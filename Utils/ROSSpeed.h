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

	quint64 toInt()const	{ return m_bps;	}

	ROSSpeed &operator=(quint64 bps)				{ m_bps = bps;	return *this;		}
	bool operator==(const ROSSpeed &speed)const	{ return m_bps == speed.m_bps;}
	template<typename T>
	bool operator==(const T &bps)const		{ return m_bps == static_cast<quint64>(bps);		}
	template<typename T>
	bool operator!=(const T &bps)const		{ return m_bps != static_cast<quint64>(bps);		}

	operator bool()		{ return m_bps != 0 ;	}
	bool operator ! ()	{ return m_bps == 0;	}
	bool operator &&(const ROSSpeed &speed) const	{ return m_bps && speed.m_bps;	}
	bool operator ||(const ROSSpeed &speed) const	{ return m_bps || speed.m_bps;	}
};


#endif // ROSSPEED_H
