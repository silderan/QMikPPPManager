#include "ROSSpeed.h"

ROSSpeed::ROSSpeed(const QString &bps)
{
	fromString(bps);
}

void ROSSpeed::fromString(const QString &bps)
{
	if( bps.isEmpty() )
		m_bps = 0;
	else
	{
		int i;
		for( i = 0; (i < bps.count()) && bps.at(i).isDigit(); ++i )
			m_bps = m_bps * 10 + (bps.at(i).toLatin1() - ('0'));

		if( i < bps.count() )
			switch( bps.at(i).toLower().toLatin1() )
			{
			case 'g':	// Gbps
				m_bps <<= 30;
				break;
			case 'm':	// Mbps
				m_bps <<= 20;
				break;
			case 'k':	// Kbps.
				m_bps <<= 10;
				break;
			default:
				break;
			}
	}
}

QString ROSSpeed::toString() const
{
	if( m_bps == 0 )
		return "0M";
	if( (m_bps & 0x3FFFFFFF) == 0 )
		return QString("%1G").arg(m_bps>>30);
	else
	if( (m_bps & 0xFFFFF) == 0 )
		return QString("%1M").arg(m_bps>>20);
	else
	if( (m_bps & 0x3FF) == 0 )
		return QString("%1K").arg(m_bps>>10);;
	return QString::number(m_bps);
}
