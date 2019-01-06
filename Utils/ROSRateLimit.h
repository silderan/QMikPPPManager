#ifndef ROSRATELIMIT_H
#define ROSRATELIMIT_H

#include "ROSSpeed.h"

class ROSRateLimit
{
	ROSSpeed m_txKbps;				// Carga
	ROSSpeed m_rxKbps;				// Descarga
	ROSSpeed m_txBurstKbps;		// Pico de carga
	ROSSpeed m_rxBurstKbps;		// Pico de descarga
	ROSSpeed m_txAverageKbps;		// Media de carga que desactiva el pico de carga
	ROSSpeed m_rxAverageKbps;		// Media de descarga que desactiva el pico de descarga
	quint32 m_txAverageSeconds;	// Tiempo de cálculo de la media de carga
	quint32 m_rxAverageSeconds;	// Tiempo de cálculo de la media de descarga

public:
	ROSRateLimit() :
		m_txKbps(0), m_rxKbps(0), m_txBurstKbps(0), m_rxBurstKbps(0),
		m_txAverageKbps(0), m_rxAverageKbps(0), m_txAverageSeconds(0), m_rxAverageSeconds(0)
	{	}

	inline const ROSSpeed &uploadSpeed() const			{ return m_txKbps;	}
	inline void setUploadSpeed(const ROSSpeed &upKbps)	{ m_txKbps = upKbps;}

	inline const ROSSpeed &downloadSpeed() const			{ return m_rxKbps;	}
	inline void setDownloadSpeed(ROSSpeed dwKbps)	{ m_rxKbps = dwKbps;}

	inline const ROSSpeed &uploadBurstSpeed() const				{ return m_txBurstKbps;	}
	inline void setUploadBurstSpeed(const ROSSpeed &upBurstKbps)	{ m_txBurstKbps = upBurstKbps;}

	inline const ROSSpeed &downloadBurstSpeed() const					{ return m_rxBurstKbps;	}
	inline void setDownloadBurstSpeed(const ROSSpeed &dwBurstKbps)		{ m_rxBurstKbps = dwBurstKbps;}

	inline const ROSSpeed &uploadAverageSpeed() const					{ return m_txAverageKbps;	}
	inline void setUploadAverageSpeed(const ROSSpeed &upAverageKbps)	{ m_txAverageKbps = upAverageKbps;}

	inline const ROSSpeed &downloadAverageSpeed() const				{ return m_rxAverageKbps;	}
	inline void setDownloadAverageSpeed(const ROSSpeed &dwAverageKbps)	{ m_rxAverageKbps = dwAverageKbps;}

	inline quint32 uploadAverageSeconds() const						{ return m_txAverageSeconds;	}
	inline void setUploadAverageSeconds(quint32 upAverageSeconds)	{ m_txAverageSeconds = upAverageSeconds;}

	inline quint32 downloadAverageSeconds() const					{ return m_rxAverageSeconds;	}
	inline void setDownloadAverageSeconds(quint32 dwAverageSeconds)	{ m_rxAverageSeconds = dwAverageSeconds;}
	inline bool isUnlimited() const { return (m_txKbps.toInt() == 0) || (m_rxKbps.toInt() == 0); }
	bool operator==(const ROSRateLimit &rateLimit)const;
	void clear();
	void fromString(const QString &str);
	QString toString()const;
};

#endif // ROSRATELIMIT_H
