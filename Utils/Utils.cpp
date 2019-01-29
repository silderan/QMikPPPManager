#include "Utils.h"


QDate Utils::fromStringDate(const char *date)
{
	// 15/12/2018
	return QDate( 1000*(date[6]-'0') + 100*(date[7]-'0') + 10*(date[8]-'0') + (date[9]-'0'),
				  10*(date[3]-'0') + (date[4]-'0'),
				  10*(date[0]-'0') + (date[1]-'0') );
}

QDate Utils::fromStringDate(const QString &date)
{
	if( date.count() >= 10 )
		return fromStringDate(date.toLatin1().constData());
	return QDate();
}

QDate Utils::fromROSStringDate(const char *date)
{
	int M;
	// [jan|feb|mar|may|jun|jul|aug|sep|oct|nov|dec]/01/2019
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
	default:	return QDate();
	}
	return QDate(1000*(date[7]-'0') + 100*(date[8]-'0') + 10*(date[9]-'0') + (date[10]-'0'), M, 10*(date[4]-'0') + (date[5]-'0'));
}

QDate Utils::fromROSStringDate(const QString &date)
{
	if( date.count() >= 11 )
		return fromROSStringDate(date.toLatin1().constData());
	return QDate();
}

QTime Utils::fromStringTime(const char *date)
{
	// 11:20:30
	return QTime( 10*(date[0]-'0') + (date[1]-'0'),
				  10*(date[3]-'0') + (date[4]-'0'),
				  10*(date[6]-'0') + (date[7]-'0') );
}

QTime Utils::fromStringTime(const QString &time)
{
	if( time.count() >= 8 )
		return fromStringTime(time.toLatin1().constData());
	return QTime();
}

QDateTime Utils::fromROSStringDateTime(const QString &rosDateTime)
{
	// jan/10/2019 07:34:07
	if( rosDateTime.count() == 20 )
	{
		QByteArray _rosDateTime = rosDateTime.toLatin1();
		const char *date = _rosDateTime.constData();

		return QDateTime( fromROSStringDate(date), fromStringTime(date+12) );
	}
	return QDateTime();
}

QString Utils::toStringDate(const QDate &date)
{
	return date.toString("dd/MM/yyyy");
}

qint64 Utils::fromROSStringTimeToSecs(const QString &rosTime)
{
	qint64 t, n;
	int i;
	// 1w2d3h4m5s
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
	return t + n;
}

QStringList Utils::allColumnTexts(const QAbstractItemModel *model, int col, Qt::ItemDataRole role)
{
	QStringList rtn;
	if( col < model->columnCount() )
	{
		rtn.reserve(model->rowCount());
		QString s;
		for( int row = model->rowCount(); row >= 0; --row )
		{
			s = model->index(row, col).data(role).toString();
			if( !s.isEmpty() && !rtn.contains(s) )
				rtn.append(s);
		}
	}
	return rtn;
}

#ifdef UNIT_TESTS_UTILS
void Utils::UTests()
{
	UT_COMPARE( fromStringDate("01/01/1999"), QDate(1999, 1, 1) );
	UT_COMPARE( toStringDate(QDate(1999, 1, 1)), "01/01/1999" );

	UT_COMPARE( fromROSStringDate( QString("sep/01/1970") ), QDate(1970,  9,  1) );
	UT_COMPARE( fromROSStringDate( QString("jan/10/2019 07:34:07") ), QDate(2019,  1, 10) );
	UT_COMPARE( fromROSStringDate( QString("aug/07/2000 01:02:03") ), QDate(2000,  8,  7) );

	UT_COMPARE( fromROSStringDateTime("sep/01/1970 00:00:01"), QDateTime( QDate(1970,  9,  1), QTime( 0,  0,  1)) );
	UT_COMPARE( fromROSStringDateTime("jan/10/2019 07:34:07"), QDateTime( QDate(2019,  1, 10), QTime( 7, 34,  7)) );
	UT_COMPARE( fromROSStringDateTime("aug/07/2000 01:02:03"), QDateTime( QDate(2000,  8,  7), QTime( 1,  2,  3)) );

	UT_COMPARE( fromROSStringTimeToSecs(""), 0 );
	UT_COMPARE( fromROSStringTimeToSecs("1"), 1 );
	UT_COMPARE( fromROSStringTimeToSecs("1m"), 60 );
	UT_COMPARE( fromROSStringTimeToSecs("1h"), 60*60 );
	UT_COMPARE( fromROSStringTimeToSecs("1d"), 24*60*60 );
	UT_COMPARE( fromROSStringTimeToSecs("1w"), 7*24*60*60 );

	UT_COMPARE( fromROSStringTimeToSecs("0"), 0 );
	UT_COMPARE( fromROSStringTimeToSecs("0m"), 0 );
	UT_COMPARE( fromROSStringTimeToSecs("00h"), 0 );
	UT_COMPARE( fromROSStringTimeToSecs("00d"), 0 );
	UT_COMPARE( fromROSStringTimeToSecs("000w"), 0 );

	UT_COMPARE( fromROSStringTimeToSecs("10"), 10 );
	UT_COMPARE( fromROSStringTimeToSecs("10m"), 600 );
	UT_COMPARE( fromROSStringTimeToSecs("10h"), (600*60) );
	UT_COMPARE( fromROSStringTimeToSecs("10d"), (24*600*60) );
	UT_COMPARE( fromROSStringTimeToSecs("10w"), (7*24*600*60) );

	UT_COMPARE( fromROSStringTimeToSecs("2w 3d 4h 5m 6s"), (2*7*24*60*60 + 3*24*60*60 + 4*60*60 + 5*60 + 6) );
}
#endif

#include <QMessageBox>
void Utils::raiseWarning(QWidget *papi, const QString &info, QString title)
{
	QMessageBox::warning(papi, title.isEmpty() ? papi->windowTitle() : title, info );
}

void Utils::raiseInfo(QWidget *papi, const QString &info, QString title)
{
	QMessageBox::information( papi, title.isEmpty() ? papi->windowTitle() : title, info );
}
