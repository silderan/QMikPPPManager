#ifndef ROSPPPPROFILE_H
#define ROSPPPPROFILE_H

#include "../UnitTests.h"
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
	explicit ROSPPPProfile(const QString &routerName) : ROSDataBase(DataTypeID::PPPProfile, routerName)
	{	}

	const QString &profileName() const		{ return m_name;	}
	void setProfileName(const QString &n)	{ m_name = n;		}

	const ROSRateLimit &rateLimit() const	{ return m_rateLimit;	}
	ROSRateLimit &rateLimit()				{ return m_rateLimit;	}

	const QString &localAddress()const					{ return m_localAdress;	}
	void setLocalAddress(const QString &localAddress)	{ m_localAdress = localAddress;	}

	const QString &remoteAddress()const					{ return m_remoteAdress;}
	void setRemoteAddress(const QString &remoteAddress)	{ m_remoteAdress = remoteAddress;	}

	const QString &bridgeName() const				{ return m_bridgeName;	}
	void setBridgeName(const QString &bridgeName)	{ m_bridgeName = bridgeName;	}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &sentence);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	virtual bool hasSameData(const ROSDataBase &rosPPPProfile) const;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSPPPPROFILE_H
