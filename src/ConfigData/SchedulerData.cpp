#include "SchedulerData.h"

#include <QDir>

using namespace ServiceScheduler;

const DataList SchedulerMap::dummyData = DataList();

QString Data::toSaveString() const
{
	return QString("%1,%2,%3,%4,%5,%6")
			.arg(1)	// Version
			.arg(mYear).arg(mMonth)
			.arg(mServiceAction)
			.arg(mSpeedProfileName)
			.arg(mDay);
}

void Data::fromSaveString(const QString &saveString)
{
	QStringList bits = saveString.split(',');
	if( !bits.count() )
		return;

	switch( bits.at(0).toUInt() )
	{
	case 1:	// Versión 1.
		if( bits.count() >= 6 )
		{
			mYear = quint16(bits.at(1).toUInt());
			mMonth = quint16(bits.at(2).toUInt());
			mServiceAction = ServiceAction(bits.at(3).toUInt());
			mSpeedProfileName = bits.at(4);
			mDay = bits.at(5).toInt();
		}
		break;
	default:
		break;
	}
}

const QStringList &Data::serviceActionNames()
{
	static const QStringList l = QStringList() << QObject::tr("Sin cambios") << QObject::tr("Activar") << QObject::tr("Cancelar");
	return l;
}

QString Data::serviceActionName(const ServiceAction &s)
{
	return serviceActionNames().at(s);
}

QString Data::serviceActionName() const
{
	return serviceActionName(mServiceAction);
}

void Data::setServiceAction(const QString &s)
{
	int i = serviceActionNames().indexOf(s);
	if( i != -1 )
		mServiceAction = ServiceAction(i);
}

bool Data::operator!=(const Data &other) const
{
	return	(other.mYear != mYear) ||
			(other.mMonth != mMonth) ||
			(other.mDay != mDay) ||
			(other.mServiceAction != mServiceAction) ||
			(other.mSpeedProfileName != mSpeedProfileName);
}

bool Data::operator==(const Data &other) const
{
	return	(other.mYear == mYear) &&
			(other.mMonth == mMonth) &&
			(other.mDay == mDay) &&
			(other.mServiceAction == mServiceAction) &&
			(other.mSpeedProfileName == mSpeedProfileName);
}

QString Data::monthName(quint16 m)
{
	Q_ASSERT( (m>0) && (m<=12) );
	return months().at(m);
}

quint16 Data::nextMonth(quint16 m)
{
	Q_ASSERT( (m>0) && (m<=12) );

	return (m>=12) ? 1 : m + 1;
}

quint16 Data::prevMonth(quint16 m)
{
	Q_ASSERT( (m>0) && (m<=12) );

	return (m<=1) ? 12 : m - 1;
}

QString Data::monthName() const
{
	if( isMonthValid() )
		return monthName(mMonth);
	return QString("Error mes %1").arg(mMonth);
}

bool Data::isMonthValid() const
{
	return (mMonth >= 1) && (mMonth <= 12);
}

const QStringList &Data::months()
{
	static const QStringList m = QStringList() << "" << "enero" << "febrero" << "marzo" << "abril" << "mayo" << "junio" << "julio" << "agosto" << "septiembre" << "octubre" << "noviembre" << "diciembre";
	return m;
}

quint16 Data::monthNumber(const QString &monthName)
{
	return quint16(Data::months().indexOf(monthName));
}

const QStringList &Data::dayNames()
{
	static const QStringList names = { QObject::tr("Ultimos días"), QObject::tr("Primeros días"),
									   "1", "2", "3", "4", "5", "6", "7", "8", "9",
									   "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
									   "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
									   "30", "31" };

	return names;
}

int Data::lastDaysIndex()
{
	return 0;
}

int Data::firstDaysIndex()
{
	return 1;
}

int Data::monthDayToArrayIndex(int d)	{ return d + 1;	}
int Data::arrayIndexToMonthDay(int d)	{ return d - 1;	}

int Data::dayIndex()
{
	Q_ASSERT(isMonthDay());
	return monthDayToArrayIndex(mDay);
}

int Data::monthDay() const
{
	Q_ASSERT(isMonthDay());
	return mDay - 1;
}

bool Data::isMonthDay() const
{
	return !isFirstsDays() && !isLastsDays();
}

bool Data::isFirstsDays() const
{
	return mDay == firstDaysIndex();
}

bool Data::isLastsDays() const
{
	return mDay == lastDaysIndex();
}

void Data::setDay(int d)
{
	Q_ASSERT((d>1)&&(d<32));
	mDay = d;
}

void Data::setFirstsDays()
{
	mDay = 1;
}

void Data::setLastsDays()
{
	mDay = 0;
}

void Data::setDay(QString name)
{
	Q_ASSERT( dayNames().contains(name) );
	mDay = dayNames().indexOf(name);
	if( mDay < 0 )
		mDay = 0;
}

QString Data::dayName(int d)
{
	return dayNames().at(d);
}

QString Data::dayName() const
{
	return dayName(mDay);
}

QString SchedulerMap::saveFName() const
{
	static QString fname;
	if( fname.isEmpty() )
	{
#ifdef QT_NO_DEBUG
		fname = QString( "SchedulerData.ini" );
#else
		fname = QString( "SchedulerDataDebug.ini" );
#endif
	}
	return fname;
}

void SchedulerMap::save()
{
	QIniData saveData;
	QMapIterator<QString, DataList> it(*this);
	while( it.hasNext() )
	{
		it.next();
		for( Data data : it.value() )
			saveData[it.key()] += QString("%1;").arg( data.toSaveString() );
	}
	QIniFile::save(saveFName(), saveData);
}

bool SchedulerMap::setDataList(const QString &userName, const DataList &list)
{
	if( constDataList(userName) == list )
		return false;

	if( list.isEmpty() )
		remove(userName);
	else
		dataList(userName) = list;

	return true;
}

void SchedulerMap::changeUserName(const QString &oldUserName, const QString &newUserName)
{
	if( !oldUserName.isEmpty() && !newUserName.isEmpty() && (oldUserName != newUserName) && contains(oldUserName) )
	{
		setDataList( newUserName, dataList(oldUserName) );
		remove(oldUserName);
	}
}

void SchedulerMap::load()
{
	QIniData saveData;
	QIniFile::load(saveFName(), &saveData);
	QMapIterator<QString, QString> it(saveData);
	clear();
	Data data;
	if( it.hasNext() )
	{
		it.next();
		for( const QString &saveString : it.value().split(';', QString::SkipEmptyParts) )
		{
			data.fromSaveString(saveString);
			dataList(it.key()).append(data);
		}
	}
}

bool DataList::operator==(const DataList &dataList) const
{
	if( QList::operator==(dataList) )
		return true;
	if( count() != dataList.count() )
		return false;
	for( int i = count()-1; i >= 0; i-- )
	{
		if( at(i) != dataList.at(i) )
			return false;
	}
	return true;
}

SchedulerMap gServiceSchedulerMap;
