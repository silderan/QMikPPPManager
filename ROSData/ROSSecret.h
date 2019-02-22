/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ROSSECRET_H
#define ROSSECRET_H


#include <QDateTime>

#include "ROSDataBasics.h"
#include "../UnitTests.h"
#include "../Utils/IPv4Range.h"
#include "../Utils/PortForward.h"

struct ServiceState
{
	enum Type
	{
		ActiveUndefined,
		ActiveTemporally,
		CanceledNoPay,
		CanceledTemporally,
		CanceledTechnically,
		CanceledRetired,
        CanceledUndefined,
        Undefined
	};

	static bool isCanceledState(ServiceState::Type type);
	static QString toSaveString(const ServiceState::Type type);
	static ServiceState::Type fromSaveString(const QString &saveString);
	static ServiceState::Type fromNameString(const QString &nameString);
	static QString readableString(const ServiceState::Type &type);
	static const QStringList &serviceStateNameList();
};
struct ServiceStateScheduler
{
	ServiceState::Type newState;
	QDate changeDate;

	ServiceStateScheduler(ServiceState::Type state = ServiceState::Type::ActiveUndefined)
		: newState(state)
	{	}
};

class ServiceStateSchedulerList : public QList<ServiceStateScheduler>
{

};

class ROSPPPSecret : public ROSDataBase
{

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
	QString m_voipSIPServer;
	QString m_voipSIPUserName;
	QString m_voipSIPUserPass;
	IPv4 m_installLANIP;
	IPv4 m_installLANDMZ;
	QPortForwardList m_portForwardList;
	IPv4 m_staticIP;
	ServiceState::Type m_serviceState;
	ServiceStateSchedulerList m_serviceStateSchedulerList;
	bool m_needsPublicIP;

	void parseCommentString(const QString &commentString);
	const QString &commentString() const;

	template<typename T>
	void updateNonROSMember( T &member, const T &newData )				{ if(member != newData) { member = newData; m_commentString.clear(); }	}
	bool updateNonROSMember( QString &member, const QString &text, const QString &pattern, int minLenght )
	{
		if( !checkValidData(text, pattern, minLenght) )
			return false;
		updateNonROSMember(member, text);
		return true;
	}

public:
	explicit ROSPPPSecret(const QString &routerName) : ROSDataBase(DataTypeID::PPPSecret, routerName),
	  m_serviceState(ServiceState::ActiveUndefined), m_needsPublicIP(false)
	{	}

	const QString &userName() const				{ return m_userName;	}
	bool setUserName(const QString &userName)	{ return updateMember(m_userName, userName, userNamePattern, 8);	}

	const QString &userPass() const				{ return m_userPass;	}
	bool setUserPass(const QString &userPass)	{ return updateMember(m_userPass, userPass, userPassPattern, 8);	}

	const QString & pppProfileName() const		{ return m_profile;		}
	bool setPPPProfileName(const QString &profile)	{ return updateMember(m_profile, profile, profilePattern, 4);	}

	const QDateTime &lastLogOff() const			{ return m_lastLogOff;	}
	bool setLastLogOff(const QDateTime &l)		{ m_lastLogOff = l;	 return true;	}

	const QString & originalProfile() const		{ return m_originalProfile;	}
	bool setOriginalProfile(const QString &pfl)	{ return updateNonROSMember(m_originalProfile, pfl, profilePattern, -4); }

	const QString & clientCode() const			{ return m_clientCode;	}
	bool setClientCode(const QString &cc)		{ return updateNonROSMember(m_clientCode, cc, basicNonROSMemberPatern, 0);	}

	const QString & installerName() const		{ return m_installerName;	}
	bool setInstallerName(const QString &in)	{ return updateNonROSMember(m_installerName, in, basicNonROSMemberPatern, 0);		}

	const QString & clientName() const			{ return m_clientName;		}
	bool setClientName(const QString &cn)		{ return updateNonROSMember(m_clientName, cn, basicNonROSMemberPatern, 1);	}

	const QString & clientAddress() const			{ return m_clientAddress;		}
	bool setClientAddress(const QString &address)	{ return updateNonROSMember(m_clientAddress, address, basicNonROSMemberPatern, 1);	}

	const QString & clientCity() const				{ return m_clientCity;	}
	bool setClientCity(const QString &city)			{ return updateNonROSMember(m_clientCity, city, basicNonROSMemberPatern, 1);	}

	const QString & clientPhones() const			{ return m_clientPhones;		}
	bool setClientPhones(const QString &phones)		{ return updateNonROSMember(m_clientPhones, phones, basicNonROSMemberPatern, 1);	}

	const QString & clientEmail() const				{ return m_clientEmail;	}
	bool setClientEmail(const QString &email)		{ return updateNonROSMember(m_clientEmail, email, emailPattern, 1);	}

	const QString & wifi2SSID() const				{ return m_wifi2SSID;	}
	bool setWiFi2SSID(const QString &SSID)			{ return updateNonROSMember(m_wifi2SSID, SSID, ssidPattern, -4);	}

	const QString & wifi2WPA() const				{ return m_wifi2WPA;	}
	bool setWiFi2WPA(const QString &WPass)			{ return updateNonROSMember(m_wifi2WPA, WPass, wpaPattern, -8);	}

	const QString & wifi5SSID() const				{ return m_wifi5SSID;	}
	bool setWiFi5SSID(const QString &SSID)			{ return updateNonROSMember(m_wifi5SSID, SSID, ssidPattern, -4);	}

	const QString & wifi5WPA() const				{ return m_wifi5WPA;	}
	bool setWiFi5WPA(const QString &WPass)			{ return updateNonROSMember(m_wifi5WPA, WPass, wpaPattern, -8);	}

	const QString & clientNotes() const				{ return m_clientNotes;	}
	bool setClientNotes(const QString &notes)		{ return updateNonROSMember(m_clientNotes, notes, basicNonROSMemberPatern, 0);	}

	const QString & installNotes() const			{ return m_installNotes;	}
	bool setInstallNotes(const QString &notes)		{ return updateNonROSMember(m_installNotes, notes, basicNonROSMemberPatern, 0);	}

	const IPv4 &staticIP() const					{ return m_staticIP;	}
	bool setStaticIP(const IPv4 &staticIP)			{ updateNonROSMember(m_staticIP, staticIP); return true;	}

	const QString &voipSIPServer() const			{ return m_voipSIPServer;	}
	bool setVoIPSIPServer(const QString &p)			{ return updateNonROSMember(m_voipSIPServer, p, urlPattern, -6);	}

	const QString &voipPhoneNumber() const			{ return m_voipPhoneNumber;	}
	bool setVoIPPhoneNumber(const QString &p)		{ return updateNonROSMember(m_voipPhoneNumber, p, phonePattern, -9);	}

	const QString &voipSIPUserName() const			{ return m_voipSIPUserName;	}
	bool setVoIPSIPUserName(const QString &p)		{ return updateNonROSMember(m_voipSIPUserName, p, userNamePattern, -8);	}

	const QString &voipSIPUserPass() const			{ return m_voipSIPUserPass;	}
	bool setVoIPSIPUserPass(const QString &p)		{ return updateNonROSMember(m_voipSIPUserPass, p, userPassPattern, -8);	}

	const IPv4 &installLANIP() const				{ return m_installLANIP;	}
	bool setInstallLANIP(const IPv4 &ip)			{ updateNonROSMember(m_installLANIP, ip); return true;		}

	const IPv4 &installLANDMZ() const				{ return m_installLANDMZ;	}
	bool setInstallLANDMZ(const IPv4 &ip)			{ updateNonROSMember(m_installLANDMZ, ip);	return true;	}

	const QPortForwardList &portForwardList() const			{ return m_portForwardList;	}
	bool setPortForwardList(const QPortForwardList &ports)	{ updateNonROSMember(m_portForwardList, ports);	return true;	}

	bool needsPublicIP() const					{ return m_needsPublicIP;			}
	bool setNeedsPublicIP(bool needsPublicIP)	{ updateNonROSMember(m_needsPublicIP, needsPublicIP); return true;	}

	const QString &ontSN() const				{ return m_ontSN;	}
	bool setONTSN(const QString &ontSN)			{ return updateNonROSMember(m_ontSN, ontSN, basicNonROSMemberPatern, -9);	}

	bool setServiceState(ServiceState::Type st)	{ updateNonROSMember(m_serviceState, st);	return true;	}
	bool setServiceState(const QString &st)		{ return setServiceState(ServiceState::fromSaveString(st));	}
	ServiceState::Type serviceState() const		{ return m_serviceState;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

class QPPPSecretMap : public QMap<QString, ROSPPPSecret>
{

public:
	void insert(const ROSPPPSecret &pppSecret )				{ QMap::insert(pppSecret.routerName(), pppSecret);	}
	ROSPPPSecret pppSecret(const QString &routerName) const	{ return value(routerName, ROSPPPSecret(""));		}
	QRouterIDMap toRouterIDMap() const;
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

	QDateTime uptime() const				{ return m_uptime;	}

	const IPv4 &currentIPv4() const					{ return m_currentIPv4;	}

	void fromSentence(const QString &routerName, const ROS::QSentence &s) override;
	ROS::QSentence &toSentence(ROS::QSentence &sentence) const override;
	bool hasSameData(const ROSDataBase &rosData) const override;

#ifdef SIMULATE_ROS_INPUTS
	static QList<ROS::QSentence> simulatedStepSentences(const QString &routerName, quint32 random, int step);
#endif
};

#endif // ROSSECRET_H
