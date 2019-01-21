#include "QPortForwardTableWidget.h"

QPortForwardTableWidget::QPortForwardTableWidget(QWidget *papi) : QTableWidget(papi)
{
	setColumnCount( 6 );
	setHorizontalHeaderLabels( QStringList()
							   << tr("Protcolo")
							   << tr("Publico Desde")
							   << tr("Publico Hasta")
							   << tr("Privado Desde")
							   << tr("Privado Hasta")
							   << tr("IP Destino") );
}

void QPortForwardTableWidget::addPortForwardRow(const PortForward &port)
{
	int row = rowCount();
	insertRow(row);

	setCellWidget( row, 0, new QIPProtocolComboBox(port.protocol()) );
	setCellWidget( row, 1, new QPortSpinBox(port.publicPortFrom()) );
	setCellWidget( row, 2, new QPortSpinBox(port.publicPortTo()) );
	setCellWidget( row, 3, new QPortSpinBox(port.privatePortFrom()) );
	setCellWidget( row, 4, new QPortSpinBox(port.privatePortTo()) );
	setItem( row, 5, new QTableWidgetItem(port.destIP().toString()) );
}


PortForward QPortForwardTableWidget::portForwardRow(int row)
{
	m_lastError.clear();
	QString prot = static_cast<QComboBox*>(cellWidget(row, 0))->currentText();
	quint16 publicPortFrom = static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, 1))->value());
	quint16 publicPortTo = static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, 2))->value());
	quint16 privatePortFrom = static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, 3))->value());
	quint16 privatePortTo = static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, 4))->value());
	IPv4 destIP( item(row, 5)->text() );

	if( !destIP.isValid() )
		m_lastError = tr("La IP destino para la redirección de puertos de la linea %1 no es válida").arg(row);
	else
	if( (publicPortTo == 0) && (publicPortFrom == 0) )
		m_lastError = tr("Los puertos públicos 'Desde' y 'hasta' son 0 en la linea %1").arg(row);
	else
	{
		if( publicPortTo == 0 )
			publicPortTo = publicPortFrom;

		if( publicPortFrom == 0 )
			publicPortFrom = publicPortTo;

		if( publicPortFrom > publicPortTo )
			m_lastError = tr("El puerto público 'Desde' de la linea %1 es mayor que el puerto 'hasta'").arg(row);
		else
		{
			if( (privatePortTo == 0) && (privatePortFrom == 0) )
			{
				privatePortTo = publicPortTo;
				privatePortFrom = publicPortFrom;
			}
			else
			{
				if( privatePortTo == 0 )
					privatePortTo = privatePortFrom;

				if( privatePortFrom == 0 )
					privatePortFrom = privatePortTo;
			}
			if( (publicPortTo - publicPortFrom) != (privatePortTo - privatePortFrom) )
				m_lastError = tr("El rango de puertos públicos y privados en la linea %1 no coinciden").arg(row);
			else
			if( IPProtocol::fromString(prot) == IPProtocol::Unkown )
				m_lastError = tr("El protocolo en la linea %1 no es válido").arg(row);
			else
			{
				return PortForward( IPProtocol::fromString(prot), publicPortFrom, publicPortTo, privatePortFrom, privatePortTo, destIP );
			}
		}
	}
	return PortForward();
}

void QPortForwardTableWidget::setup(const QPortForwardList &portForwardList)
{
	setRowCount(0);
	foreach( const PortForward &port, portForwardList )
		addPortForwardRow(port);
}

QPortForwardList QPortForwardTableWidget::portForwardList()
{
	PortForward port;
	QPortForwardList rtn;
	for( int row = 0; row < rowCount(); ++row )
	{
		port = portForwardRow(row);
		if( port.protocol() == IPProtocol::Unkown )
			return QPortForwardList();
		rtn.append(port);
	}
	return rtn;
}
