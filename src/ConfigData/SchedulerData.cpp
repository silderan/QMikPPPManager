#include "SchedulerData.h"

#include <QDir>

using namespace ServiceScheduler;

const DataList SchedulerMap::dummyData = DataList();

QString Data::toSaveString() const
{
	return QString("%1,%2,%3,%4,%5").arg(1).arg(mYear).arg(mMonth).arg(mProfileName).arg(mServiceAction);
}

void Data::fromSaveString(const QString &saveString)
{
	QStringList bits = saveString.split(',');
	if( !bits.count() )
		return;

	switch( bits.at(0).toUInt() )
	{
	case 1:	// Versión 1.
		if( bits.count() == 5 )
		{
			mYear = quint16(bits.at(1).toUInt());
			mMonth = quint16(bits.at(2).toUInt());
			mProfileName = bits.at(3);
			mServiceAction = ServiceAction(bits.at(4).toUInt());
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

QString Data::serviceActionName() const
{
	return serviceActionNames().at(mServiceAction);
}

void Data::setServiceAction(const QString &s)
{
	int i = serviceActionNames().indexOf(s);
	if( i != -1 )
		mServiceAction = ServiceAction(i);
}


QString Data::monthName() const
{
	if( isMonthValid() )
		return months().at(mMonth);
	return QString("Error mes %1").arg(mMonth);
}
bool Data::isMonthValid() const
{
	return mMonth <= 11;
}

const QStringList &Data::months()
{
	static const QStringList m = QStringList() << "enero" << "febrero" << "marzo" << "abril" << "mayo" << "junio" << "julio" << "agosto" << "septiembre" << "octubre" << "noviembre" << "diciembre";
	return m;
}

quint16 Data::monthNumber(const QString &monthName)
{
	return quint16(Data::months().indexOf(monthName));
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
	QMapIterator<QString, DataList> it(mData);
	while( it.hasNext() )
	{
		it.next();
		for( Data data : it.value() )
			saveData[it.key()] += QString("%1;").arg( data.toSaveString() );
	}
	QIniFile::save(saveFName(), saveData);
}

void SchedulerMap::load()
{
	QIniData saveData;
	QIniFile::load(saveFName(), &saveData);
	QMapIterator<QString, QString> it(saveData);
	mData.clear();
	if( it.hasNext() )
	{
		it.next();
		for( const QString &data : it.value().split(';', QString::SkipEmptyParts) )
			mData[it.key()].append(Data(data));
	}
}

SchedulerMap gSchedulerData;
