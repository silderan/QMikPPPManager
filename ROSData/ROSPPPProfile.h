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

	inline const ROSRateLimit &rateLimit() const		{ return m_rateLimit;	}
	inline ROSRateLimit &rateLimit()					{ return m_rateLimit;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosPPPProfile) const;
	virtual void copyData(const ROSDataBase &rosPPPProfile);
};

#endif // ROSPPPPROFILE_H
