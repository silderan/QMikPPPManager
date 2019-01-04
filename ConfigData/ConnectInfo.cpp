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
