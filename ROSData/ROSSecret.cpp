#include "ROSSecret.h"

#include "../Utils/Utils.h"

const QString &ROSPPPSecret::commentString() const
{
	if( m_commentString.isEmpty() )
	{
		const_cast<ROSPPPSecret*>(this)->
		m_commentString =
			QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10$%11$%12$%13")
				.arg(originalProfile())
				.arg(clientName())
				.arg(address())
				.arg(city())
				.arg(phones())
				.arg(installerName())
				.arg(comercial())
				.arg(email())
				.arg(needsPublicIP())
				.arg(notes())
				.arg(SSID())
				.arg(wPass())
				.arg(clientCode())
				.arg("")	// Old EB/AP field.
				.arg(serviceState());

	}
	return m_commentString;
}

void ROSPPPSecret::setCommentString(const QString &commentString)
{
	QStringList fields = commentString.split('$');
	if( fields.count() > 1 )
	{

		int i = fields.count();
		switch( i )
		{
		case 15:	setServiceCancelReason( fields[--i] );		[[clang::fallthrough]];
		case 14:	--i;/*There was EB/AP, now is deprecated*/	[[clang::fallthrough]];
		case 13:	setClientCode( fields[--i] );				[[clang::fallthrough]];
		case 12:	setWPass( fields[--i] );					[[clang::fallthrough]];
		case 11:	setSSID( fields[--i] );						[[clang::fallthrough]];
		case 10:	setNotes( fields[--i] );					[[clang::fallthrough]];
		case 9:		setNeedsPublicIP( !fields[--i].isEmpty() );	[[clang::fallthrough]];
		case 8:		setEmail( fields[--i] );					[[clang::fallthrough]];
		case 7:		setComercial( fields[--i] );				[[clang::fallthrough]];
		case 6:		setInstallerName( fields[--i] );			[[clang::fallthrough]];
		case 5:		setPhones( fields[--i] );					[[clang::fallthrough]];
		case 4:		setCity( fields[--i] );						[[clang::fallthrough]];
		case 3:		setAddress( fields[--i] );					[[clang::fallthrough]];
		case 2:		setClientName( fields[--i] );
					setOriginalProfile( fields[--i] );
			break;
		}
	}
	m_commentString = commentString;
}

void ROSPPPSecret::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_userName = s.attribute("name");
	m_userPass = s.attribute("password");
	m_profile = s.attribute("profile");
	m_staticIP = s.attribute("remote-address");
	m_lastLogOff = Utils::fromROSDateTime(s.attribute("last-logged-out"));
	setCommentString( s.attribute("comment") );
}

ROS::QSentence &ROSPPPSecret::toSentence(ROS::QSentence &sentence) const
{
	Q_ASSERT( !m_profile.isEmpty() );

	ROS::QSentence *s = &sentence;
	s->addAttribute( "name", m_userName );
	s->addAttribute( "password", m_userPass );
	s->addAttribute( "profile", m_profile );
	s->addAttribute( "service", "pppoe" );
	if( m_staticIP.isValid() )
		s->addAttribute( "remote-address", m_staticIP.toString() );
	else
		s->addAttribute( "!remote-address", "" );

	s->addAttribute( "comment", commentString() );

	return sentence;
}

bool ROSPPPSecret::hasSameData(const ROSDataBase &rosData) const
{
	return
		(m_userName == static_cast<const ROSPPPSecret &>(rosData).m_userName) &&
		(m_userPass == static_cast<const ROSPPPSecret &>(rosData).m_userPass) &&
		(m_profile == static_cast<const ROSPPPSecret &>(rosData).m_profile) &&
		(m_staticIP == static_cast<const ROSPPPSecret &>(rosData).m_staticIP) &&
		(commentString() == static_cast<const ROSPPPSecret &>(rosData).commentString());
}


/*
 * address=194.179.48.253
 * caller-id=44:D9:E7:A0:9B:E1
 * comment=5/1 (Movistar)$Vicente Jose Prats Roca$Pda Collet 95$Benicarló$609762779$Victor$Novatel$info@pratsinjenieria.com$$$NovatelWifi$collet95$$
 * encoding=
 * limit-bytes-in=0
 * limit-bytes-out=0
 * name=eb0S0_18933833A
 * radius=false
 * service=pppoe
 * session-id=0x81C00002
 * uptime=3w4d12h23m12s
 *
*/
void ROSPPPActive::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_userName = s.attribute("name");
	m_currentIPv4 = s.attribute("address");
	m_uptime = Utils::fromROSTime( s.attribute("uptime") );
}

ROS::QSentence &ROSPPPActive::toSentence(ROS::QSentence &sentence) const
{
	return ROSDataBase::toSentence(sentence);
}

bool ROSPPPActive::hasSameData(const ROSDataBase &rosData) const
{
	Q_UNUSED(rosData);
	return false;
}
