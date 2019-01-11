#ifndef ROSSECRET_H
#define ROSSECRET_H


#include <QDateTime>

#include "ROSDataBasics.h"
#include "../Utils/IPv4Range.h"

class ROSSecretData : public ROSDataBase
{
	// Direct ROS data.
	QString m_userName;
	QString m_userPass;
	QString m_profile;		// User's current profile. Can be a profile without Internet access for people in stand by.
	QDateTime m_lastLogOff;
	QString m_commentString;

	// Data encoded in comment ROS data field.
	QString m_originalProfile;	// That's the client's desired profile. Needs to be saved as client can pause their payment and current profile can change.
	QString m_clientCode;		// Client code for join this data to contable.
	QString m_installerName;
	QString m_clientName;
	QString m_address;
	QString m_city;
	QString m_phones;
	QString m_comercial;
	QString m_email;
	QString m_SSID;
	QString m_WPass;
	QString m_notes;
	IPv4 m_staticIP;
	QString m_serviceCancelReason;
	bool m_needsPublicIP;

	void fromCommentString(const QString &commentString);
	void updateNonROSMember( QString &member, const QString &newData )	{ if(member != newData) { member = newData; m_commentString.clear(); }	}
	void updateNonROSMember( bool &member, bool newData )	{ if(member != newData) { member = newData; m_commentString.clear(); }	}
	void updateNonROSMember( IPv4 &member, const IPv4 &newData )	{ if( !(member == newData) ) { member = newData; m_commentString.clear(); }	}
public:
	explicit ROSSecretData(const QString &routerName) : ROSDataBase(DataTypeID::APIUser, routerName),
	  m_needsPublicIP(false)
	{	}


public:
	const QString &userName() const				{ return m_userName;	}
	void setUserName(const QString &userName)	{ m_userName = userName;}

	const QString &userPass() const				{ return m_userPass;	}
	void setUserPass(const QString &userPass)	{ m_userPass = userPass;}

	const QString & profile() const				{ return m_profile;		}
	void setProfile(const QString &profile)		{ m_profile = profile;	}

	const QDateTime &lastLogOff() const			{ return m_lastLogOff;	}
	void setLastLogOff(const QDateTime &l)		{ m_lastLogOff = l;		}

	const QString &commentString() const;
	void setCommentString(const QString &commentString);

	const QString & originalProfile() const		{ return m_originalProfile;	}
	void setOriginalProfile(const QString &pfl)	{ updateNonROSMember(m_originalProfile, pfl); }

	const QString & clientCode() const			{ return m_clientCode;	}
	void setClientCode(const QString &cc)		{ updateNonROSMember(m_clientCode, cc);	}

	const QString & installerName() const		{ return m_installerName;	}
	void setInstallerName(const QString &in)	{ updateNonROSMember(m_installerName, in);		}

	const QString & clientName() const			{ return m_clientName;		}
	void setClientName(const QString &cn)		{ updateNonROSMember(m_clientName, cn);}

	const QString & address() const				{ return m_address;		}
	void setAddress(const QString &address)		{ updateNonROSMember(m_address, address);	}

	const QString & city() const				{ return m_city;	}
	void setCity(const QString &city)			{ updateNonROSMember(m_city, city);	}

	const QString & phones() const				{ return m_phones;		}
	void setPhones(const QString &phones)		{ updateNonROSMember(m_phones, phones);	}

	const QString & comercial() const			{ return m_comercial;		}
	void setComercial(const QString &comercial)	{ updateNonROSMember(m_comercial, comercial);	}

	const QString & email() const				{ return m_email;	}
	void setEmail(const QString &email)			{ updateNonROSMember(m_email, email);	}

	const QString & SSID() const				{ return m_SSID;	}
	void setSSID(const QString &SSID)			{ updateNonROSMember(m_SSID, SSID);	}

	const QString & wPass() const				{ return m_WPass;	}
	void setWPass(const QString &WPass)			{ updateNonROSMember(m_WPass, WPass);	}

	const QString & notes() const				{ return m_notes;	}
	void setNotes(const QString &notes)			{ updateNonROSMember(m_notes, notes);	}

	const IPv4 &staticIP() const				{ return m_staticIP;	}
	void setStaticIP(const IPv4 &staticIP)		{ updateNonROSMember(m_staticIP, staticIP);}

	bool needsPublicIP() const					{ return m_needsPublicIP;			}
	void setNeedsPublicIP(bool needsPublicIP)	{ updateNonROSMember(m_needsPublicIP, needsPublicIP);	}

	const QString &serviceCancelReason() const	{ return m_serviceCancelReason;	}
	void setServiceCancelReason(const QString c){ updateNonROSMember(m_serviceCancelReason, c);	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;
};

class ROSSecretActive : ROSDataBase
{
	QTime m_uptime;
	IPv4 m_currentIPv4;

public:
	explicit ROSSecretActive(const QString &routerName) : ROSDataBase(DataTypeID::APIUser, routerName)
	{	}

public:
	const QTime &uptime() const			{ return m_uptime;	}
	void setUptime(const QTime &uptime)	{ m_uptime = uptime;}

	const IPv4 &currentIPv4() const					{ return m_currentIPv4;	}
	void setCurrentIPv4(const IPv4 &currentIPv4)	{ m_currentIPv4 = currentIPv4;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;
};

#endif // ROSSECRET_H
