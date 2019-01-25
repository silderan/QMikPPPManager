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

	const ROSSpeed &uploadSpeed() const			{ return m_txKbps;	}
	ROSSpeed &uploadSpeed()						{ return m_txKbps;	}
	void setUploadSpeed(const ROSSpeed &upKbps)	{ m_txKbps = upKbps;}

	const ROSSpeed &downloadSpeed() const			{ return m_rxKbps;	}
	ROSSpeed &downloadSpeed()						{ return m_rxKbps;	}
	void setDownloadSpeed(ROSSpeed dwKbps)			{ m_rxKbps = dwKbps;}

	const ROSSpeed &uploadBurstSpeed() const					{ return m_txBurstKbps;	}
	ROSSpeed &uploadBurstSpeed()								{ return m_txBurstKbps;	}
	void setUploadBurstSpeed(const ROSSpeed &upBurstKbps)		{ m_txBurstKbps = upBurstKbps;}

	const ROSSpeed &downloadBurstSpeed() const					{ return m_rxBurstKbps;	}
	ROSSpeed &downloadBurstSpeed()								{ return m_rxBurstKbps;	}
	void setDownloadBurstSpeed(const ROSSpeed &dwBurstKbps)		{ m_rxBurstKbps = dwBurstKbps;}

	const ROSSpeed &uploadAverageSpeed() const					{ return m_txAverageKbps;	}
	ROSSpeed &uploadAverageSpeed()								{ return m_txAverageKbps;	}
	void setUploadAverageSpeed(const ROSSpeed &upAverageKbps)	{ m_txAverageKbps = upAverageKbps;}

	const ROSSpeed &downloadAverageSpeed() const				{ return m_rxAverageKbps;	}
	ROSSpeed &downloadAverageSpeed()							{ return m_rxAverageKbps;	}
	void setDownloadAverageSpeed(const ROSSpeed &dwAverageKbps)	{ m_rxAverageKbps = dwAverageKbps;}

	quint32 uploadAverageSeconds() const						{ return m_txAverageSeconds;	}
	quint32 &uploadAverageSeconds()								{ return m_txAverageSeconds;	}
	void setUploadAverageSeconds(quint32 upAverageSeconds)		{ m_txAverageSeconds = upAverageSeconds;}

	quint32 downloadAverageSeconds() const						{ return m_rxAverageSeconds;	}
	quint32 &downloadAverageSeconds()							{ return m_rxAverageSeconds;	}
	void setDownloadAverageSeconds(quint32 dwAverageSeconds)	{ m_rxAverageSeconds = dwAverageSeconds;}

	bool isUnlimited() const { return (m_txKbps.toInt() == 0) || (m_rxKbps.toInt() == 0); }
	bool operator==(const ROSRateLimit &rateLimit)const;
	void clear();
	void fromString(const QString &str);
	QString toString()const;
};

#endif // ROSRATELIMIT_H
