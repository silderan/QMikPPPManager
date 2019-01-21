#ifndef ROSSECRET_H
#define ROSSECRET_H


#include <QDateTime>

#include "ROSDataBasics.h"
#include "../UnitTests.h"
#include "../Utils/IPv4Range.h"
#include "../Utils/PortForward.h"

class ROSPPPSecret : public ROSDataBase
{

public:
	enum ServiceState
	{
		ActiveUndefined,
		ActiveTemporally,
		CanceledNoPay,
		CanceledTemporally,
		CanceledTechnically,
		CanceledRetired,
		CanceledUndefined
	};

private:
	// Direct ROS data.
	QString m_userName;
	QString m_userPass;
	QString m_profile;		// User's current profile. Can be a profile without Internet access for people with canceled service.
	QDateTime m_lastLogOff;
	QString m_commentString;
	QString m_ontSN;

	// Data encoded in comment ROS data field.
	QString m_originalProfile;	// That's the client's desired profile. Needs to be saved as client can pause their payment and current profile can change.
	QString m_clientCode;		// Client code for join this data to contable.
	QString m_installerName;
	QString m_clientName;
	QString m_clientAddress;
	QString m_clientCity;
	QString m_clientPhones;
	QString m_clientEmail;
	QString m_wifi2SSID;
	QString m_wifi2WPA;
	QString m_wifi5SSID;
	QString m_wifi5WPA;
	QString m_clientNotes;
	QString m_installNotes;
	QString m_voipPhoneNumber;
	QString m_voipSIPUserName;
	QString m_voipSIPUserPass;
	IPv4 m_installLANIP;
	IPv4 m_installLANDMZ;
	QPortForwardList m_portForwardList;
	IPv4 m_staticIP;
	ServiceState m_serviceState;
	bool m_needsPublicIP;

	void fromCommentString(const QString &commentString);

	template<typename T>
	void updateNonROSMember( T &member, const T &newData )				{ if(member != newData) { member = newData; m_commentString.clear(); }	}

public:
	explicit ROSPPPSecret(const QString &routerName) : ROSDataBase(DataTypeID::PPPSecret, routerName),
	  m_serviceState(ServiceState::ActiveUndefined), m_needsPublicIP(false)
	{	}

	const QString &userName() const				{ return m_userName;	}
	void setUserName(const QString &userName)	{ m_userName = userName;}

	const QString &userPass() const				{ return m_userPass;	}
	void setUserPass(const QString &userPass)	{ m_userPass = userPass;}

	const QString & profile() const				{ return m_profile;		}
	void setPPPProfile(const QString &profile)	{ m_profile = profile;	}

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

	const QString & clientAddress() const			{ return m_clientAddress;		}
	void setClientAddress(const QString &address)	{ updateNonROSMember(m_clientAddress, address);	}

	const QString & clientCity() const				{ return m_clientCity;	}
	void setClientCity(const QString &city)			{ updateNonROSMember(m_clientCity, city);	}

	const QString & clientPhones() const			{ return m_clientPhones;		}
	void setClientPhones(const QString &phones)		{ updateNonROSMember(m_clientPhones, phones);	}

	const QString & clientEmail() const				{ return m_clientEmail;	}
	void setClientEmail(const QString &email)		{ updateNonROSMember(m_clientEmail, email);	}

	const QString & wifi2SSID() const				{ return m_wifi2SSID;	}
	void setWiFi2SSID(const QString &SSID)			{ updateNonROSMember(m_wifi2SSID, SSID);	}

	const QString & wifi2WPA() const				{ return m_wifi2WPA;	}
	void setWiFi2WPA(const QString &WPass)			{ updateNonROSMember(m_wifi2WPA, WPass);	}

	const QString & wifi5SSID() const				{ return m_wifi5SSID;	}
	void setWiFi5SSID(const QString &SSID)			{ updateNonROSMember(m_wifi5SSID, SSID);	}

	const QString & wifi5WPA() const				{ return m_wifi5WPA;	}
	void setWiFi5WPA(const QString &WPass)			{ updateNonROSMember(m_wifi5WPA, WPass);	}

	const QString & clientNotes() const				{ return m_clientNotes;	}
	void setClientNotes(const QString &notes)		{ updateNonROSMember(m_clientNotes, notes);	}

	const QString & installNotes() const			{ return m_installNotes;	}
	void setInstallNotes(const QString &notes)		{ updateNonROSMember(m_installNotes, notes);	}

	const IPv4 &staticIP() const					{ return m_staticIP;	}
	void setStaticIP(const IPv4 &staticIP)			{ updateNonROSMember(m_staticIP, staticIP);}

	const QString &voipPhoneNumber() const			{ return m_voipPhoneNumber;	}
	void setVoIPPhoneNumber(const QString &p)		{ updateNonROSMember(m_voipPhoneNumber, p);	}

	const QString &voipSIPUserName() const			{ return m_voipSIPUserName;	}
	void setVoIPSIPUserName(const QString &p)		{ updateNonROSMember(m_voipSIPUserName, p);	}

	const QString &voipSIPUserPass() const			{ return m_voipSIPUserPass;	}
	void setVoIPSIPUserPass(const QString &p)		{ updateNonROSMember(m_voipSIPUserPass, p);	}

	const IPv4 &installLANIP() const				{ return m_installLANIP;	}
	void setInstallLANIP(const IPv4 &ip)			{ updateNonROSMember(m_installLANIP, ip);	}

	const IPv4 &installLANDMZ() const				{ return m_installLANDMZ;	}
	void setInstallLANDMZ(const IPv4 &ip)			{ updateNonROSMember(m_installLANDMZ, ip);	}

	const QPortForwardList &portForwardList() const			{ return m_portForwardList;	}
	QPortForwardList &portForwardList()						{ return m_portForwardList;	}
	void setPortForwardList(const QPortForwardList &ports)	{ updateNonROSMember(m_portForwardList, ports);	}

	bool needsPublicIP() const					{ return m_needsPublicIP;			}
	void setNeedsPublicIP(bool needsPublicIP)	{ updateNonROSMember(m_needsPublicIP, needsPublicIP);	}

	const QString &ontSN() const				{ return m_ontSN;	}
	void setONTSN(const QString &ontSN)			{ updateNonROSMember(m_ontSN, ontSN);	}

	void setServiceState(const QString &c);
	void setServiceState(ServiceState st);
	static QString serviceStateROSString(ServiceState);
	QString serviceStateROSString() const;
	static QString serviceStateString(ServiceState st);
	QString serviceStateString() const;
	ServiceState serviceState() const			{ return m_serviceState;	}
	static QStringList serviceStateNames();

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

class ROSPPPActive : public ROSDataBase
{
	QString m_userName;
	QDateTime m_uptime;
	IPv4 m_currentIPv4;

public:
	explicit ROSPPPActive(const QString &routerName) : ROSDataBase(DataTypeID::PPPActive, routerName)
	{	}

	const QString &userName() const		{ return m_userName;	}
	void setUserName(const QString &u)	{ m_userName = u;		}

	QDateTime uptime() const				{ return m_uptime;	}
	void setUptime(QDateTime uptime)		{ m_uptime = uptime;}

	const IPv4 &currentIPv4() const					{ return m_currentIPv4;	}
	void setCurrentIPv4(const IPv4 &currentIPv4)	{ m_currentIPv4 = currentIPv4;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSSECRET_H
