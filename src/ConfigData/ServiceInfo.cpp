#include "ServiceInfo.h"

const QStringList gInstallTypeNameList = {"No definida",
										  "WiFi (Antena WiFi directa cliente)",
										  "FTTH (Fibra directa cliente)",
										  "WTTB (Antena WiFi al edificio)",
										  "FTTB (Fibra al edificio)",
										  "PtP WiFi (PtP WiFi dedicado)",
										  "PtP FO (PtP fibra óptica dedicado)"};

const QStringList &ServiceInfo::serviceTypeNameList()
{
	return gInstallTypeNameList;
}

QString ServicePerm::toSaveString() const
{
	QString rtn;
	for( const auto &p : *this )
	{
		if( rtn.length() )
			rtn+=",";
		rtn += QString("%1").arg(p);
	}
	return rtn;
}

void ServicePerm::fromSaveString(const QString &str)
{
	clear();
	for( const QString &p : str.split(",") )
		append(p.toInt());
}

void ServicePerm::setPermanencia(const ServiceInfo::ServiceType &st, int meses)
{
	Q_ASSERT(ServiceInfo::isValidServiceType(st));

	if( ServiceInfo::isValidServiceType(st) )
	{
		while( count() <= st )
			append(6);
		(*this)[st] = meses;
	}
}

int ServicePerm::getPermanencia(const ServiceInfo::ServiceType &st)
{
	Q_ASSERT(ServiceInfo::isValidServiceType(st));

	if( ServiceInfo::isValidServiceType(st) && (count() > st) )
		return at(st);
	return 6;
}

QDate ServicePerm::permDate(const ServiceInfo::ServiceType &st, const QDateTime &installTime)
{
	if( int meses = getPermanencia(st) )
	{
		QDate rtn = installTime.date().addMonths(meses+1);
		rtn = rtn.addDays(-rtn.day());

		return rtn;
	}
	else
		return QDate();
}

bool ServicePerm::inPermTime(const ServiceInfo::ServiceType &st, const QDateTime &installTime)
{
	QDate perm = permDate(st, installTime);
	return perm.isValid() ? permDate(st, installTime) >= QDate::currentDate() : false;
}
