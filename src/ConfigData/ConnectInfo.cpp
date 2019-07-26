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

#include "ConnectInfo.h"

#define KEY_CONNECT_INFO			("connect-info")
#define KEY_CONNECT_INFO_LIST(_i)	(QString("connect-info-list-%1").arg(_i))

QString ConnectInfo::toString() const
{
	return QString("%1,%2,%3,%4,%5").arg(
				"1",	// Version.
				m_hostIPv4.toString(),
				QString::number(m_hostPort),
				m_uname,
				m_upass );
}

void ConnectInfo::fromString(const QString &line)
{
	QStringList data = line.split(",");
	if( data.count() > 1 )
	{
		switch( data[0].toInt() )
		{
		case 1:
			if( data.count() == 5 )
			{
				m_hostIPv4 = data[1];
				m_hostPort = static_cast<quint16>(data[2].toInt());
				m_uname = data[3];
				m_upass = data[4];
			}
			break;
		default:
			break;
		}
	}
}

void QConnectInfoList::save(QIniData &iniData) const
{
	for( int i = 0; i < count(); i++ )
		iniData[KEY_CONNECT_INFO_LIST(i)] = at(i).toString();
}

void QConnectInfoList::load(const QIniData &iniData)
{
	clear();
	QString line;
	for( int i = 0; !(line = iniData[KEY_CONNECT_INFO_LIST(i)]).isEmpty(); i++ )
		append( ConnectInfo(line) );
}
