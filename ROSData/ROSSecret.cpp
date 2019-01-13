#include "ROSSecret.h"

#include "../Utils/Utils.h"

const QString &ROSPPPSecret::commentString() const
{
	if( m_commentString.isEmpty() )
	{
		const_cast<ROSPPPSecret*>(this)->
		m_commentString =
			QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10$%11$%12$%13$%14$%15")
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
		case 15:	setServiceState( fields[--i] );				[[clang::fallthrough]];
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

void ROSPPPSecret::setServiceState(ROSPPPSecret::ServiceState st)
{
	if( m_serviceState != st )
	{
		m_serviceState = st;
		m_commentString.clear();
	}
}

QString ROSPPPSecret::serviceStateROSString(ServiceState st)
{
	switch( st )
	{
	case ROSPPPSecret::ActiveTemporally:	return "AT";
	case ROSPPPSecret::ActiveUndefined:		return "AU";
	case ROSPPPSecret::CanceledNoPay:		return "CN";
	case ROSPPPSecret::CanceledTemporally:	return "CT";
	case ROSPPPSecret::CanceledTechnically:	return "CH";
	case ROSPPPSecret::CanceledRetired:		return "CR";
	case ROSPPPSecret::CanceledUndefined:	return "CU";
	}
}
QString ROSPPPSecret::serviceStateROSString() const
{
	return ROSPPPSecret::serviceStateROSString(m_serviceState);
}

QString ROSPPPSecret::serviceStateString(ROSPPPSecret::ServiceState st)
{
	switch( st )
	{
	case ROSPPPSecret::ActiveTemporally:	return QObject::tr("Activo temporal");
	case ROSPPPSecret::ActiveUndefined:		return QObject::tr("Activo");
	case ROSPPPSecret::CanceledNoPay:		return QObject::tr("Cancelado: debe facturas");
	case ROSPPPSecret::CanceledTemporally:	return QObject::tr("Cancelado temporal");
	case ROSPPPSecret::CanceledTechnically:	return QObject::tr("Cancelado técnico");
	case ROSPPPSecret::CanceledRetired:		return QObject::tr("Cancelado: equipos retirados");
	case ROSPPPSecret::CanceledUndefined:	return QObject::tr("Cancelado ...");
	}
}
QString ROSPPPSecret::serviceStateString() const
{
	return ROSPPPSecret::serviceStateString(m_serviceState);
}


void ROSPPPSecret::setServiceState(const QString &c)
{
	// c="[AU|AT|CN|CT|CH|CR|CU]"
	if( c.count() == 2 )
	{
		QByteArray ba = c.toLatin1();
		const char *data = ba.constData();
		if( data[0] ==  'A' )
		{
			if( data[1] == 'T' )
				m_serviceState = ServiceState::ActiveTemporally;
			else
				m_serviceState = ServiceState::ActiveUndefined;
		}
		else
		if( data[0] == 'C' )
		{
			switch( data[1] )
			{
			case 'N': m_serviceState = ServiceState::CanceledNoPay;			break;
			case 'T': m_serviceState = ServiceState::CanceledTemporally;	break;
			case 'H': m_serviceState = ServiceState::CanceledTechnically;	break;
			case 'R': m_serviceState = ServiceState::CanceledRetired;		break;
			default: m_serviceState = ServiceState::CanceledUndefined;		break;
			}
		}
	}
	else
	{
		if( c.contains("lta") )
			m_serviceState = ServiceState::ActiveUndefined;
		else
		if( c.contains("emporal") )
			m_serviceState = ServiceState::CanceledTemporally;
		else
		if( c.contains("retira") )
			m_serviceState = ServiceState::CanceledRetired;
		else
		if( c.contains("debe") )
			m_serviceState = ServiceState::CanceledNoPay;
		else
			m_serviceState = ServiceState::CanceledUndefined;
	}
}

void ROSPPPSecret::fromSentence(const QString &routerName, const ROS::QSentence &s)
{
	ROSDataBase::fromSentence(routerName, s);
	m_userName = s.attribute("name");
	m_userPass = s.attribute("password");
	m_profile = s.attribute("profile");
	m_staticIP = s.attribute("remote-address");
	m_lastLogOff = Utils::fromROSStringDateTime(s.attribute("last-logged-out"));
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

	return ROSDataBase::toSentence(sentence);
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
	m_uptime = QDateTime::currentDateTime().addSecs( -Utils::fromROSStringTimeToSecs(s.attribute("uptime")) );
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

#ifdef SIMULATE_ROS_INPUTS
QList<ROS::QSentence> ROSPPPSecret::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;
	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::PPPSecret) );
	sentence.setResultType( ROS::QSentence::Result::Reply );
	static QMap<QString, QList<ROSPPPSecret *> >secretMapList;

	if( step == 1 )
	for( int i = 1; i <= 10; ++i )
	{
		ROSPPPSecret *secret = new ROSPPPSecret(routerName);
		secret->setUserName( QString("UserName-%1").arg(i) );
		secret->setUserPass( "PASS" );
		secret->setCity( "Ciudad" );
		secret->setSSID( QString("SSID-%1").arg(i) );
		secret->setEmail( QString("Email-%1").arg(i) );
		secret->setNotes( QString("Notas %1").arg(i) );
		secret->setWPass( QString("WPASS%1").arg(i) );
		secret->setPhones( QString("96441234%1").arg(i) );
		secret->setProfile( (i < 3) ? "Bajo" : (i < 6) ? "Medio" : "Alto" );
		secret->setStaticIP( (i == 3) ? IPv4("192.168.1.3") : (i == 6) ? IPv4("192.168.1.6") : IPv4() );
		secret->setComercial( "Comercial" );
		secret->setClientCode( QString("1234%1").arg(i) );
		secret->setClientName( QString("Nombre cliente %1").arg(i) );
		secret->setLastLogOff( QDateTime::currentDateTime() );
		secret->setServiceState( static_cast<ServiceState>(i % 7) );
		secret->setInstallerName( "Instalador" );
		secret->setNeedsPublicIP( i % 2 );
		secret->setOriginalProfile( (i < 3) ? "Bajo" : (i < 6) ? "Medio" : "Alto" );
		secret->setROSObjectID( QString("s%1").arg(i) );
		secretMapList[routerName].append(secret);
	}

	if( !(random & 3) && secretMapList[routerName].count() )
	{
		int i = random % secretMapList[routerName].count();

		ROSPPPSecret *secret = secretMapList[routerName].at(i);
		secret->toSentence(sentence);
		sentence.setResultType( ROS::QSentence::Result::Reply );
		rtn.append( sentence );
		secretMapList[routerName].removeAt(i);
		delete secret;
		if( secretMapList[routerName].count() == 0 )
		{
			sentence.setResultType( ROS::QSentence::Result::Done );
			rtn.append( sentence );
		}
	}
	else
	{
		// TODO: Simulate changes.
	}

	return rtn;
}

QList<ROS::QSentence> ROSPPPActive::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;
	ROS::QSentence sentence;
	sentence.setTag( QString::number(DataTypeID::PPPActive) );
	sentence.setResultType( ROS::QSentence::Result::Reply );


	sentence.setResultType( ROS::QSentence::Result::Done );
	rtn.append( sentence );
	return rtn;
}
#endif
