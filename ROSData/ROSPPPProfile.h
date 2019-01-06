#ifndef ROSPPPPROFILE_H
#define ROSPPPPROFILE_H

#include "ROSDataBasics.h"
#include "../Utils/ROSRateLimit.h"

class ROSPPPProfile : public ROSDataBase
{
	QString m_name;
	QString m_localAdress;
	QString m_remoteAdress;
	QString m_bridgeName;
	ROSRateLimit m_rateLimit;

public:
	ROSPPPProfile(const QString &routerName) : ROSDataBase(routerName, QString())
	{	}
	ROSPPPProfile(const QString &routerName, const ROS::QSentence &sentence) : ROSDataBase(routerName, QString())
	{
		fromSentence(routerName, sentence);
	}

	inline const QString &profileName() const		{ return m_name;	}
	inline void setProfileName(const QString &n)	{ m_name = n;		}

	inline const ROSRateLimit &rateLimit() const	{ return m_rateLimit;	}
	inline ROSRateLimit &rateLimit()				{ return m_rateLimit;	}

	inline const QString &localAddress()const					{ return m_localAdress;	}
	inline void setLocalAddress(const QString &localAddress)	{ m_localAdress = localAddress;	}

	inline const QString &remoteAddress()const					{ return m_remoteAdress;}
	inline void setRemoteAddress(const QString &remoteAddress)	{ m_remoteAdress = remoteAddress;	}

	inline const QString &bridgeName() const				{ return m_bridgeName;	}
	inline void setBridgeName(const QString &bridgeName)	{ m_bridgeName = bridgeName;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosPPPProfile) const;
};

#endif // ROSPPPPROFILE_H
