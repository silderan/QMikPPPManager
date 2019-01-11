#include "ROSSecret.h"

#include "../Utils/Utils.h"

const QString &ROSSecretData::commentString() const
{
	if( m_commentString.isEmpty() )
	{
		const_cast<ROSSecretData*>(this)->
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
				.arg(serviceCancelReason());

	}
	return m_commentString;
}

void ROSSecretData::setCommentString(const QString &commentString)
{
	QStringList fields = commentString.split('$');
	if( fields.count() > 1 )
	{

		int i = fields.count();
		switch( i )
		{
		case 15:	setServiceCancelReason( fields[--i] );		[[fallthrough]];
		case 14:	--i;/*There was EB/AP, now is deprecated*/	[[fallthrough]];
		case 13:	setClientCode( fields[--i] );				[[fallthrough]];
		case 12:	setWPass( fields[--i] );					[[fallthrough]];
		case 11:	setSSID( fields[--i] );						[[fallthrough]];
		case 10:	setNotes( fields[--i] );					[[fallthrough]];
		case 9:		setNeedsPublicIP( !fields[--i].isEmpty() );	[[fallthrough]];
		case 8:		setEmail( fields[--i] );					[[fallthrough]];
		case 7:		setComercial( fields[--i] );				[[fallthrough]];
		case 6:		setInstallerName( fields[--i] );			[[fallthrough]];
		case 5:		setPhones( fields[--i] );					[[fallthrough]];
		case 4:		setCity( fields[--i] );						[[fallthrough]];
		case 3:		setAddress( fields[--i] );					[[fallthrough]];
		case 2:		setClientName( fields[--i] );
					setOriginalProfile( fields[--i] );
			break;
		}
	}
	m_commentString = commentString;
}

void ROSSecretData::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_userName = s.attribute("name");
	m_userPass = s.attribute("password");
	m_profile = s.attribute("profile");
	m_staticIP = s.attribute("remote-address");
	m_lastLogOff = Utils::fromROSDateTime(s.attribute("last-logged-out"));
	setCommentString( s.attribute("comment") );
}

ROS::QSentence &ROSSecretData::toSentence(ROS::QSentence &sentence) const
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

bool ROSSecretData::hasSameData(const ROSDataBase &rosData) const
{
	return
		(m_userName == static_cast<const ROSSecretData &>(rosData).m_userName) &&
		(m_userPass == static_cast<const ROSSecretData &>(rosData).m_userPass) &&
		(m_profile == static_cast<const ROSSecretData &>(rosData).m_profile) &&
		(m_staticIP == static_cast<const ROSSecretData &>(rosData).m_staticIP) &&
		(commentString() == static_cast<const ROSSecretData &>(rosData).commentString());
}



void ROSSecretActive::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
}

ROS::QSentence &ROSSecretActive::toSentence(ROS::QSentence &sentence) const
{
}

bool ROSSecretActive::hasSameData(const ROSDataBase &rosData) const
{
}
