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

#include "QPortForwardTableWidget.h"

#include <QHeaderView>

QPortForwardTableWidget::QPortForwardTableWidget(QWidget *papi) : QTableWidget(papi)
{
	setColumnCount( 7 );
	setHorizontalHeaderLabels( QStringList()
							   << tr("Nombre")
							   << tr("Protocolo")
							   << tr("Publico Desde")
							   << tr("Publico Hasta")
							   << tr("Privado Desde")
							   << tr("Privado Hasta")
							   << tr("IP Destino") );

	Q_ASSERT( horizontalHeader()->count() );
}

void QPortForwardTableWidget::addPortForwardRow(const PortForward &port)
{
	int row = rowCount();
	insertRow(row);

	setCellWidget( row, Columns::Protocol,			new QIPProtocolComboBox(port.protocol()) );
	setCellWidget( row, Columns::PublicPortIni,		new QPortSpinBox(port.publicPortIni()) );
	setCellWidget( row, Columns::PublicPortEnd,		new QPortSpinBox(port.publicPortEnd()) );
	setCellWidget( row, Columns::PrivatePortIni,	new QPortSpinBox(port.privatePortIni()) );
	setCellWidget( row, Columns::PrivatePortEnd,	new QPortSpinBox(port.privatePortEnd()) );

	setItem( row, Columns::Name,	new QTableWidgetItem(port.name()) );
	setItem( row, Columns::IP,		new QTableWidgetItem(port.destIP().toString()) );
}

PortForward QPortForwardTableWidget::portForwardRow(int row)
{
	m_lastError.clear();

	QString prot			= static_cast<QComboBox*>(cellWidget(row, Columns::Protocol))->currentText();
	quint16 publicPortFrom	= static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, Columns::PublicPortIni))->value());
	quint16 publicPortTo	= static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, Columns::PublicPortEnd))->value());
	quint16 privatePortFrom	= static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, Columns::PrivatePortIni))->value());
	quint16 privatePortTo	= static_cast<quint16>(static_cast<QSpinBox*>(cellWidget(row, Columns::PrivatePortEnd))->value());
	QString name = item(row, Columns::Name)->text();
	IPv4 destIP( item(row, Columns::IP)->text() );

	if( name.isEmpty() )
		m_lastError = tr("Debes poner un nombre informativo para la redirección de puertos de la linea %1").arg(row);
	else
	if( name.contains(QRegExp("[^A-Za-z0-9 ]")) )
		m_lastError = tr("El nombre para la redirección de puertos contiene caracteres no válidos").arg(row);
	else
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
				return PortForward( name, IPProtocol::fromString(prot), publicPortFrom, publicPortTo, privatePortFrom, privatePortTo, destIP );
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

void QPortForwardTableWidget::parsePortLine(const QStringList &words, int i)
{
}

void QPortForwardTableWidget::parsePortText(const QString &txt)
{
}
