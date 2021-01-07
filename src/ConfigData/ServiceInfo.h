#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QStringList>
#include <QDateTime>

struct ServiceInfo
{
	enum ServiceType
	{
		Unk = 0,
		WiFi,
		FTTH,
		WTTB,
		FTTB,
		PtP_WiFi,
		PtP_FO,
		Cantidad
	};
	ServiceType serviceType;
	bool hasToF;	// (Television Overlay) Only if type==FTTH.
	bool hasIoC;	// (Internet over Coaxial) Only if type==FTTB or WTTB
	QList<int> mPermanencias;	// Cantidad de meses de permanencia por cada tipo de servicio.

	ServiceInfo()
		: serviceType(ServiceType::Unk)
		, hasToF(false)
		, hasIoC(false)
	{	}
	static const QStringList &serviceTypeNameList();
	template<typename T>
	static const QString serviceTypeName(const T &st)	{ return isValidServiceType(static_cast<ServiceType>(st)) ? serviceTypeNameList()[st] : "Error";	}
	quint32 toUInt() const
	{
		return quint32( serviceType + ((hasToF?1:0)<<8) + ((hasIoC?1:0)<<9) );
	}
	void fromUInt(quint32 coded)
	{
		serviceType = ServiceType(coded & 0xF);
		hasToF = (coded & 0x100);
		hasIoC = (coded & 0x200);
	}
	int permanencia(const ServiceType &st)
	{
		if( (st >= Unk) && (st <= PtP_FO) )
			return mPermanencias[st];
		return 6;	// Normalmente, 6 meses.
	}
	QString toCommentString() const
	{
		return QString("%1").arg(toUInt(), 0, 16);
	}
	void fromCommentString(const QString &coded)
	{
		fromUInt( coded.toUInt(Q_NULLPTR, 16) );
	}
	static bool isValidServiceType(const ServiceType &st)	{ return (st>=Unk) && (st <ServiceType::Cantidad);	}
};

// Permanencias mínimas según servicio.
struct ServicePerm : public QList<int>
{
	QString toSaveString() const;
	void fromSaveString(const QString &str);
	void setPermanencia(const ServiceInfo::ServiceType &st, int meses);
	int getPermanencia(const ServiceInfo::ServiceType &st);
	// Retorna el tiempo que queda de la permanencia según el tipo de servicio y la fecha de la instalación.
	// La fecha de la instalación se obtiene a partir de la contraseña PPPoE.
	QDate permDate(const ServiceInfo::ServiceType &st, const QDateTime &installTime);
	bool inPermTime(const ServiceInfo::ServiceType &st, const QDateTime &installTime);
};

#endif // SERVICEINFO_H
