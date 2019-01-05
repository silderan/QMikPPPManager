#include "ROSSpeed.h"

ROSSpeed::ROSSpeed(const QString &kbps)
{
	fromString(kbps);
}

void ROSSpeed::fromString(const QString &kbps)
{
	if( kbps.isEmpty() )
		m_kbps = 0;
	else
	{
		int i;
		for( i = 0; (i < kbps.count()) && kbps.at(i).isDigit(); ++i )
			m_kbps = m_kbps * 10 + (kbps.at(i).toLatin1() - ('0'));

		if( i < kbps.count() )
			switch( kbps.at(i).toLower().toLatin1() )
			{
			case 'g':	// Gbps
				m_kbps <<= 16;
				break;
			case 'm':	// Mbps
				m_kbps <<= 8;
				break;
			case 'k':	// Kbps.
				break;
			default:
				m_kbps >>= 8;
				break;
			}
	}
}

QString ROSSpeed::toString() const
{
	if( !m_kbps )
		return "0M";
	if( m_kbps % 1024 )
		return QString("%1K").arg(m_kbps);
	else
	if( m_kbps % (1024*1024) )
		return QString("%1M").arg(m_kbps);;
	return QString("%1G").arg(m_kbps);
}
