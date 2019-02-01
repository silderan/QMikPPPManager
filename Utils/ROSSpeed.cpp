/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "ROSSpeed.h"

ROSSpeed::ROSSpeed(const QString &bps)
{
	fromString(bps);
}

void ROSSpeed::fromString(const QString &bps)
{
	m_bps = 0;
	if( !bps.isEmpty() )
	{
		int i;
		for( i = 0; (i < bps.count()) && bps.at(i).isDigit(); ++i )
			m_bps = m_bps * 10 + static_cast<quint64>((bps.at(i).toLatin1() - '0'));

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
