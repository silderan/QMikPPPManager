#include "ROSSecret.h"

#include "../Utils/Utils.h"

bool ServiceState::isActiveState(ServiceState::Type type)
{
	return  type <= ServiceState::ActiveTemporally;
}

QString ServiceState::toSaveString(const ServiceState::Type type)
{
	switch( type )
	{
	case Type::ActiveTemporally:	return "AT";
	case Type::ActiveUndefined:		return "AU";
	case Type::CanceledNoPay:		return "CN";
	case Type::CanceledTemporally:	return "CT";
	case Type::CanceledTechnically:	return "CH";
	case Type::CanceledRetired:		return "CR";
	case Type::CanceledUndefined:	return "CU";
	}
	return QString();
}

ServiceState::Type ServiceState::fromSaveString(const QString &c)
{
	// c="[AU|AT|CN|CT|CH|CR|CU]"
	if( c.count() == 2 )
	{
		QByteArray ba = c.toLatin1();
		const char *data = ba.constData();
		if( data[0] ==  'A' )
		{
			if( data[1] == 'T' )
				return ServiceState::ActiveTemporally;
			else
				return ServiceState::ActiveUndefined;
		}
		else
		if( data[0] == 'C' )
		{
			switch( data[1] )
			{
			case 'N':	return ServiceState::CanceledNoPay;
			case 'T':	return ServiceState::CanceledTemporally;
			case 'H':	return ServiceState::CanceledTechnically;
			case 'R':	return ServiceState::CanceledRetired;
			default:	return ServiceState::CanceledUndefined;
			}
		}
	}
	else
	if( !c.isEmpty() )
	{
		if( c.contains("lta") )
			return ServiceState::ActiveUndefined;
		else
		if( c.contains("emporal") )
			return ServiceState::CanceledTemporally;
		else
		if( c.contains("retira") )
			return ServiceState::CanceledRetired;
		else
		if( c.contains("debe") )
			return ServiceState::CanceledNoPay;
		return ServiceState::CanceledUndefined;
	}
	return ServiceState::ActiveUndefined;
}

QString ServiceState::readableString(const ServiceState::Type &type)
{
	switch( type )
	{
	case Type::ActiveTemporally:	return QObject::tr("Activo temporal");
	case Type::ActiveUndefined:		return QObject::tr("Activo");
	case Type::CanceledNoPay:		return QObject::tr("Cancelado: debe facturas");
	case Type::CanceledTemporally:	return QObject::tr("Cancelado temporal");
	case Type::CanceledTechnically:	return QObject::tr("Cancelado técnico");
	case Type::CanceledRetired:		return QObject::tr("Cancelado: equipos retirados");
	case Type::CanceledUndefined:	return QObject::tr("Cancelado ...");
	}
	return QString();
}

const QStringList &ServiceState::serviceStateNameList()
{
	static QStringList rtn;
	if( rtn.isEmpty() )
	{
		QString s;
		int i = 0;

		while( !(s = readableString(static_cast<ServiceState::Type>(i++))).isEmpty() )
			rtn.append(s);
	}
	return rtn;
}

ServiceState::Type ServiceState::fromNameString(const QString &nameString)
{
	return static_cast<ServiceState::Type>(serviceStateNameList().indexOf(nameString));
}

const QString &ROSPPPSecret::commentString() const
{
	if( m_commentString.isEmpty() )
	{
		QString wifiSaveString;
		if( !wifi2SSID().isEmpty() )
			wifiSaveString = QString("%1|%2").arg(wifi2SSID(),wifi2WPA());
		if( !wifi5SSID().isEmpty() )
			wifiSaveString += QString("|%1|%2").arg(wifi5SSID(),wifi5WPA());

		QString lanSaveString;
		if( installLANIP().isValid() )	lanSaveString += QString("i%1").arg( installLANIP().toString() );
		if( installLANDMZ().isValid() )	lanSaveString += QString("d%1").arg( installLANDMZ().toString() );
		if( portForwardList().count() ) lanSaveString += QString("p%1").arg( portForwardList().toSaveString() );

		QString voipSaveString;
		if( !voipPhoneNumber().isEmpty() )
			voipSaveString = QString("%1 %2 %3 %4").arg(voipPhoneNumber(), voipSIPServer(), voipSIPUserName(), voipSIPUserPass());

		const_cast<ROSPPPSecret*>(this)->
		m_commentString =
			QString("%1$%2$%3$%4$%5$%6$%7$%8$%9$%10$%11$%12$%13$%14$%15")
				.arg(originalProfile())
				.arg(clientName())
				.arg(clientAddress())
				.arg(clientCity())
				.arg(clientPhones())
				.arg(installerName())
				.arg(clientNotes())
				.arg(clientEmail())
				.arg(needsPublicIP())
				.arg(installNotes())
				.arg(wifiSaveString)
				.arg(voipSaveString)
				.arg(clientCode())
				.arg(lanSaveString)
				.arg(ServiceState::toSaveString(serviceState()) );

	}
	return m_commentString;
}

void ROSPPPSecret::parseCommentString(const QString &commentString)
{
	QStringList fields = commentString.split('$');
	if( fields.count() > 1 )
	{
		int i = fields.count();
		QString wifiSaveString;
		QString lanSaveString;
		QString voipSaveString;
		switch( i )
		{
		case 15:	setServiceState( fields[--i] );					[[clang::fallthrough]];
		case 14:	lanSaveString		= fields[--i];				[[clang::fallthrough]];
		case 13:	m_clientCode		= fields[--i];				[[clang::fallthrough]];
		case 12:	voipSaveString		= fields[--i];				[[clang::fallthrough]];
		case 11:	wifiSaveString		= fields[--i];				[[clang::fallthrough]];
		case 10:	m_installNotes		= fields[--i];				[[clang::fallthrough]];
		case 9:		m_needsPublicIP		= !fields[--i].isEmpty();	[[clang::fallthrough]];
		case 8:		m_clientEmail		= fields[--i];				[[clang::fallthrough]];
		case 7:		m_clientNotes		= fields[--i];				[[clang::fallthrough]];
		case 6:		m_installerName		= fields[--i];				[[clang::fallthrough]];
		case 5:		m_clientPhones		= fields[--i];				[[clang::fallthrough]];
		case 4:		m_clientCity		= fields[--i];				[[clang::fallthrough]];
		case 3:		m_clientAddress		= fields[--i];				[[clang::fallthrough]];
		case 2:		m_clientName		= fields[--i];
					m_originalProfile	= fields[--i];
			break;
		}
		m_wifi2SSID.clear();
		m_wifi2WPA.clear();
		m_wifi5SSID.clear();
		m_wifi5WPA.clear();
		if( !wifiSaveString.isEmpty() )
		{
			if( wifiSaveString.contains('|') )	// In this field is saved all 2,4 and 5 Ghz WiFi info.
			{
				QStringList data = wifiSaveString.split('|'); // Don't skip empty because if there is only 5Ghz there are 3 elements and first is empty.
				if( data.count() >= 2 )
				{
					if( data.count() == 3 )
					{
						m_wifi5SSID = data[1];
						m_wifi5WPA = data[2];
					}
					else
					{
						m_wifi2SSID = data[0];
						m_wifi2WPA = data[1];
						if( data.count()  >= 4 )
						{
							m_wifi5SSID = data[2];
							m_wifi5WPA = data[3];
						}
					}
				}
			}
			else	// It's just SSID and next field is the WPA2.
			{
				m_wifi2SSID = wifiSaveString;
				m_wifi2WPA = voipSaveString;
				voipSaveString.clear();
			}
		}
		QStringList data = voipSaveString.split(' ');
		if( data.count() == 4 )
		{
			m_voipPhoneNumber	= data[0];
			m_voipSIPServer		= data[1];
			m_voipSIPUserName	= data[2];
			m_voipSIPUserPass	= data[3];
		}
		else
		{
			m_voipPhoneNumber.clear();
			m_voipSIPServer.clear();
			m_voipSIPUserName.clear();
			m_voipSIPUserPass.clear();
		}
		m_installLANDMZ.clear();
		m_installLANIP.clear();
		m_portForwardList.clear();
		if( !lanSaveString.isEmpty() )
		{
			int i, e;
			for( i = 0; i < lanSaveString.count(); ++i )
			{
				switch( lanSaveString.at(i).toLatin1() )
				{
				case 'i':
					for( e = ++i; (e < lanSaveString.count()) && (lanSaveString.at(e).isDigit() || (lanSaveString.at(e) == '.')); ++e )
					   ;
					m_installLANIP.fromString(lanSaveString.mid(i, e-i));
					i = e-1;
					break;
				case 'd':
					for( e = ++i; (e < lanSaveString.count()) && (lanSaveString.at(e).isDigit() || (lanSaveString.at(e) == '.')); ++e )
					   ;
					m_installLANDMZ.fromString(lanSaveString.mid(i, e-i));
					i = e-1;
					break;
				case 'p':
					m_portForwardList.fromSaveString( lanSaveString.mid(i+1) );
					i = lanSaveString.count();	// To force for break.
					break;
				}
			}
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
	m_lastLogOff = Utils::fromROSStringDateTime(s.attribute("last-logged-out"));
	parseCommentString(s.attribute("comment"));
}

ROS::QSentence &ROSPPPSecret::toSentence(ROS::QSentence &sentence) const
{
	Q_ASSERT( !m_profile.isEmpty() );

	sentence.addAttribute( "name", m_userName );
	sentence.addAttribute( "password", m_userPass );
	sentence.addAttribute( "profile", m_profile );
	sentence.addAttribute( "service", "pppoe" );
	if( m_staticIP.isValid() )
		sentence.addAttribute( "remote-address", m_staticIP.toString() );
	else
		sentence.addAttribute( "!remote-address", "" );

	ROSDataBase::toSentence(sentence);
	// This must be after base toSentence because it sets the comment attribute.
	sentence.addAttribute( "comment", commentString() );
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
#define SIMULATED_USERS_COUNT 10
#define SIMULATED_USER_NAME(user_index)	(QString("User-Name-%1").arg(user_index))
#define SIMULATED_USER_ID(user_index)	( QString("s%1").arg(user_index) )
#define SIMULATED_ACTIVE_ID(user_index)	( QString("s%1").arg(user_index) )
QList<ROS::QSentence> ROSPPPSecret::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;
	static QMap<QString, QList<ROS::QSentence> >initialMapList;
	static QMap<QString, QList<ROS::QSentence> >currentMapList;
	int rA = random & 0xF;
	int rB = (random >> 4) & 0xF;
	int rC = (random >> 8) & 0xF;
	int rD = (random >> 12) & 0xF;

	if( step == 1 )
	for( int i = 1; i <= SIMULATED_USERS_COUNT; ++i )
	{
		ROSPPPSecret secret(routerName);
		secret.setUserName( SIMULATED_USER_NAME(i) );
		secret.setUserPass( "PASS" );
		secret.setClientCity( "Ciudad" );
		secret.setClientAddress( "dirección" );
		secret.setWiFi2SSID( QString("SSID-%1").arg(i) );
		secret.setClientEmail( QString("Email-%1").arg(i) );
		secret.setClientNotes( QString("Notas %1").arg(i) );
		secret.setWiFi2WPA( QString("WPASS%1").arg(i) );
		secret.setClientPhones( QString("96441234%1").arg(i) );
		secret.setPPPProfile( (i < 3) ? "Basico" : (i < 6) ? "Medio" : "Alto" );
		secret.setStaticIP( (i == 3) ? IPv4("192.168.1.3") : (i == 6) ? IPv4("192.168.1.6") : IPv4() );
		secret.setComercial( "Comercial" );
		secret.setClientCode( QString("1234%1").arg(i) );
		secret.setClientName( QString("Nombre cliente %1").arg(i) );
		secret.setLastLogOff( QDateTime::currentDateTime() );
		secret.setServiceState( static_cast<ServiceState>(i % 7) );
		secret.setInstallerName( "Instalador" );
		secret.setNeedsPublicIP( i % 2 );
		secret.setOriginalProfile( secret.profile() );
		secret.setROSObjectID( SIMULATED_USER_ID(i) );
		ROS::QSentence sentence;
		secret.toSentence(sentence);
		// last-logged-out is not generated by toSentence as this is a incoming (from ROS) information only and toSentence is for outgoing data (to ROS)
		sentence.addAttribute( "last-logged-out", QString("jan/01/2019 %1").arg(QTime::currentTime().toString()) );
		initialMapList[routerName].append(sentence);
	}

	if( !(rA & 3) )
	{
		if( initialMapList[routerName].count() )
		{
			int i = rB % initialMapList[routerName].count();
			ROS::QSentence sentence = initialMapList[routerName].at(i);

			sentence.setTag( QString::number(DataTypeID::PPPSecret) );
			sentence.setResultType( ROS::QSentence::Result::Reply );
			rtn.append( sentence );
			currentMapList[routerName].append(sentence);
			initialMapList[routerName].removeAt(i);
			if( initialMapList[routerName].count() == 0 )
			{
				sentence.setResultType( ROS::QSentence::Result::Done );
				rtn.append( sentence );
			}
		}
		else
		{
			int i = rB % currentMapList[routerName].count();
			ROS::QSentence sentence = currentMapList[routerName].at(i);
			ROSPPPSecret secret(routerName);
			secret.fromSentence(routerName, sentence);
			if( !(rC & 2) )
				secret.setClientAddress( QString("Dirección %1").arg(random) );
			else
			{
				secret.setServiceState( static_cast<ServiceState>(rD % 7) );
				if( secret.serviceState() < ServiceState::CanceledNoPay )
					secret.setPPPProfile( secret.originalProfile() );
				else
					secret.setPPPProfile("SinServicio");
			}
			secret.toSentence(sentence);
			currentMapList[routerName][i] = sentence;
			sentence.setTag( QString::number(DataTypeID::PPPSecret) );
			sentence.setResultType( ROS::QSentence::Result::Reply );
			rtn.append( sentence );
		}
	}

	return rtn;
}

QList<ROS::QSentence> ROSPPPActive::simulatedStepSentences(const QString &routerName, quint32 random, int step)
{
	QList<ROS::QSentence> rtn;
	int rA = (random >> 16) & 0xF;
	int rB = (random >> 20) & 0xF;
	int rC = (random >> 24) & 0xF;

	if( !(rA % 3) )
	{
		static QMap<QString, ROS::QSentence> activeData;
		int userIndex = (rB % SIMULATED_USERS_COUNT)+1;
		QString userName = SIMULATED_USER_NAME(userIndex);
		QString id = SIMULATED_ACTIVE_ID(userIndex);

		// Activate it.
		if( activeData[id].attribute("name").isEmpty() )
		{
			if( !(rC % 5) )
			{
				activeData[id].addAttribute( ".dead", "" );
				activeData[id].addAttribute( "name", userName );
				activeData[id].addAttribute( "router", routerName );
				activeData[id].addAttribute( "address", QString("192.168.1.%1").arg(userIndex) );
				activeData[id].addAttribute( "uptime", QString("%1s").arg(userIndex) );
				activeData[id].setID(id);
				activeData[id].setTag( QString::number(DataTypeID::PPPActive) );
				activeData[id].setResultType( ROS::QSentence::Result::Reply );
				rtn.append( activeData[id] );
			}
		}
		else
		{
			if( activeData[id].attribute("router") == routerName )
			{
				activeData[id].addAttribute( ".dead", "true" );
				activeData[id].addAttribute( "name", "" );
				Q_ASSERT( activeData[id].getID() == id);
				Q_ASSERT( activeData[id].tag( ) == QString::number(DataTypeID::PPPActive) );
				rtn.append( activeData[id] );
			}
		}
	}
	return rtn;
}
#endif

