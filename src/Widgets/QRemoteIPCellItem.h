#ifndef QREMOTEIPCELLITEM_H
#define QREMOTEIPCELLITEM_H

#include <QTableWidgetItem>
#include "../../SildeQtUtils/src/IPv4Range.h"

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

	const IPv4 &staticIP() const	{ return m_staticIP;	}
	const IPv4 &currentIP() const	{ return m_currentIP;	}

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
	virtual bool operator< ( const QTableWidgetItem &cellIP ) const override
	{
		return  (m_currentIP.isValid() ? m_currentIP : m_staticIP) <
				(static_cast<const QRemoteIPCellItem &>(cellIP).m_currentIP.isValid() ? static_cast<const QRemoteIPCellItem &>(cellIP).m_currentIP : static_cast<const QRemoteIPCellItem &>(cellIP).m_staticIP);
	}
};


#endif // QREMOTEIPCELLITEM_H
