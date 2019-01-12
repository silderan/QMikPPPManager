#include "ROSRateLimit.h"

#include <QStringList>
#include <QRegExp>

bool ROSRateLimit::operator==(const ROSRateLimit &rateLimit) const
{
	return
		(m_txKbps == rateLimit.m_txKbps) &&
		(m_rxKbps == rateLimit.m_rxKbps) &&
		(m_txBurstKbps == rateLimit.m_txBurstKbps) &&
		(m_rxBurstKbps == rateLimit.m_rxBurstKbps) &&
		(m_txAverageKbps == rateLimit.m_txAverageKbps) &&
		(m_rxAverageKbps == rateLimit.m_rxAverageKbps) &&
		(m_txAverageSeconds == rateLimit.m_txAverageSeconds) &&
		(m_rxAverageSeconds == rateLimit.m_rxAverageSeconds) ;
}

void ROSRateLimit::clear()
{
	m_txKbps = 0;
	m_rxKbps = 0;
	m_txBurstKbps = 0;
	m_rxBurstKbps = 0;
	m_txAverageKbps = 0;
	m_rxAverageKbps = 0;
	m_txAverageSeconds = 0;
	m_rxAverageSeconds = 0;
}

void ROSRateLimit::fromString(const QString &str)
{
	clear();
	QStringList speeds = str.split( QRegExp("[/ ]"), QString::SkipEmptyParts );
	switch( speeds.count() )
	{
	case 8:	m_rxAverageSeconds = speeds.at(7).toUInt(); [[clang::fallthrough]];
	case 7:	m_txAverageSeconds = speeds.at(6).toUInt(); [[clang::fallthrough]];
	case 6:	m_rxAverageKbps.fromString( speeds.at(5) ); [[clang::fallthrough]];
	case 5:	m_txAverageKbps.fromString( speeds.at(4) ); [[clang::fallthrough]];
	case 4:	m_rxBurstKbps.fromString( speeds.at(3) ); [[clang::fallthrough]];
	case 3:	m_txBurstKbps.fromString( speeds.at(2) ); [[clang::fallthrough]];
	case 2:	m_rxKbps.fromString( speeds.at(1) ); [[clang::fallthrough]];
	case 1:	m_txKbps.fromString( speeds.at(0) );
		// Ensures that if only one value is present, uses it in both upload and download.
		if( !m_rxKbps )
			m_rxKbps = m_txKbps;
		break;
	case 0:
		m_txKbps = 0;
		m_rxKbps = 0;
		break;
	}
}

QString ROSRateLimit::toString() const
{
	QString rtn;
	if( isUnlimited() )
		return "";
	rtn = QString("%1/%2").arg( m_txKbps.toString(), m_rxKbps.toString() );
	if( m_rxBurstKbps && m_txBurstKbps )
	{
		rtn += QString(" %1/%2").arg( m_txBurstKbps.toString(), m_rxBurstKbps.toString() );
		if( m_txAverageKbps && m_rxAverageKbps )
		{
			rtn += QString(" %1/%2").arg( m_txAverageKbps.toString(), m_rxAverageKbps.toString() );
			if( m_txAverageSeconds && m_rxAverageSeconds )
				rtn += QString(" %1/%2").arg(m_txAverageSeconds).arg(m_rxAverageSeconds);
		}
	}
	return rtn;
}

