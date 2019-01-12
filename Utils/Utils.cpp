#include "Utils.h"

QDateTime Utils::fromROSDateTime(const QString &rosDateTime)
{
	// jan/10/2019 07:34:07
	if( rosDateTime.count() == 20 )
	{
		QByteArray _rosDateTime = rosDateTime.toLatin1();
		const char *date = _rosDateTime.constData();
		int Y, M, D;
		int h, m, s;
		// jan,feb,mar,may,jun,jul,aug,sep,oct,nov,dec
		switch( *date )
		{
		case 'j':
			if( date[1] == 'a' )
				M = 1;
			else
			if( date[2] == 'n')
				M = 5;
			else
				M = 6;
			break;
		case 'f':	M = 2;	break;
		case 'm':	M = date[2] == 'r' ? 3 : 4; break;
		case 'a':	M = 8;	break;
		case 's':	M = 9;	break;
		case 'o':	M = 10;	break;
		case 'n':	M = 11;	break;
		case 'd':	M = 12;	break;
		default:	return QDateTime();
		}
		D = 10*(date[4]-'0') + (date[5]-'0');
		Y = 1000*(date[7]-'0') + 100*(date[8]-'0') + 10*(date[9]-'0') + (date[10]-'0');

		h = 10*(date[12]-'0') + (date[13]-'0');
		m = 10*(date[15]-'0') + (date[16]-'0');
		s = 10*(date[18]-'0') + (date[19]-'0');
		return QDateTime( QDate(Y, M, D), QTime(h, m, s) );
	}
	return QDateTime();
}

QDateTime Utils::fromROSTime(const QString &rosTime)
{
	qint64 t, n;
	int i;
	for( t = 0, n = 0, i = 0; i < rosTime.count(); ++i )
	{
		char c = rosTime.at(i).toLatin1();
		if( isdigit(c) )
		{
			n *= 10;
			n += (c - '0');
		}
		else
		{
			switch( c )
			{
			case 'w':	t += n*7*24*60*60;	break;
			case 'd':	t += n*24*60*60;	break;
			case 'h':	t += n*60*60;	break;
			case 'm':	t += n*60;	break;
			default:	t += n;	break;
			}
			n = 0;
		}
	}
	return QDateTime::currentDateTime().addSecs(-(t+n));
}

#ifdef UNIT_TESTS_UTILS
void Utils::UTests()
{
	UT_COMPARE( fromROSDateTime("sep/01/1970 00:00:01"), QDateTime( QDate(1970,  9,  1), QTime( 0,  0,  1)) );
	UT_COMPARE( fromROSDateTime("jan/10/2019 07:34:07"), QDateTime( QDate(2019,  1, 10), QTime( 7, 34,  7)) );
	UT_COMPARE( fromROSDateTime("aug/07/2000 01:02:03"), QDateTime( QDate(2000,  8,  7), QTime( 1,  2,  3)) );

	UT_COMPARE( fromROSTime(""), QDateTime::currentDateTime() );
	UT_COMPARE( fromROSTime("1"), QDateTime::currentDateTime().addSecs(-1) );
	UT_COMPARE( fromROSTime("1m"), QDateTime::currentDateTime().addSecs(-60) );
	UT_COMPARE( fromROSTime("1h"), QDateTime::currentDateTime().addSecs(-(60*60)) );
	UT_COMPARE( fromROSTime("1d"), QDateTime::currentDateTime().addSecs(-(24*60*60)) );
	UT_COMPARE( fromROSTime("1w"), QDateTime::currentDateTime().addSecs(-(7*24*60*60)) );

	UT_COMPARE( fromROSTime("0"), QDateTime::currentDateTime() );
	UT_COMPARE( fromROSTime("0m"), QDateTime::currentDateTime() );
	UT_COMPARE( fromROSTime("00h"), QDateTime::currentDateTime() );
	UT_COMPARE( fromROSTime("00d"), QDateTime::currentDateTime() );
	UT_COMPARE( fromROSTime("000w"), QDateTime::currentDateTime() );

	UT_COMPARE( fromROSTime("10"), QDateTime::currentDateTime().addSecs(-10) );
	UT_COMPARE( fromROSTime("10m"), QDateTime::currentDateTime().addSecs(-600) );
	UT_COMPARE( fromROSTime("10h"), QDateTime::currentDateTime().addSecs(-(600*60)) );
	UT_COMPARE( fromROSTime("10d"), QDateTime::currentDateTime().addSecs(-(24*600*60)) );
	UT_COMPARE( fromROSTime("10w"), QDateTime::currentDateTime().addSecs(-(7*24*600*60)) );

	UT_COMPARE( fromROSTime("2w 3d 4h 5m 6s"), QDateTime::currentDateTime().addSecs(-(2*7*24*60*60 + 3*24*60*60 + 4*60*60 + 5*60 + 6)) );
}
#endif
