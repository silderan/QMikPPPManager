#ifndef QREMOTEIPCELLITEM_H
#define QREMOTEIPCELLITEM_H

#include <QTableWidgetItem>
#include "../Utils/IPv4Range.h"

class QRemoteIPCellItem : public QTableWidgetItem
{
	IPv4 m_currentIP;
	IPv4 m_staticIP;

	void updateData()
	{
		if( m_currentIP.isValid() )
		{
			setData( Qt::EditRole, m_currentIP.toString() );
			QFont f = font();
			setForeground( QBrush(QColor()) );
			f.setItalic(false);
			setFont(f);
		}
		else
		{
			if( m_staticIP.isValid() )
			{
				QFont f = font();
				setForeground( QBrush(Qt::gray) );
				f.setItalic(true);
				setFont(f);
				setData( Qt::DisplayRole, m_staticIP.toString() );
			}
			else
				setData( Qt::DisplayRole, QString() );
		}
	}

public:
	QRemoteIPCellItem(const IPv4 &currentIP, const IPv4 &staticIP = IPv4()) : QTableWidgetItem()
	  , m_currentIP(currentIP)
	  , m_staticIP(staticIP)
	{
		updateData();
	}
	void setCurrentIP(const IPv4 ipv4)
	{
		m_currentIP = ipv4;
		updateData();
	}
	void setStaticIP(const IPv4 ipv4)
	{
		m_staticIP = ipv4;
		updateData();
	}
	void setRemoteIPs(const IPv4 &currentIP, const IPv4 &staticIP)
	{
		m_currentIP = currentIP;
		m_staticIP = staticIP;
		updateData();
	}
};


#endif // QREMOTEIPCELLITEM_H
