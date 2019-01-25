#include "QSpeedTableWidget.h"

#include <QTableWidgetItem>

#include <QMessageBox>

QSpeedTableWidget::QSpeedTableWidget(QWidget *parent) : QTableWidget(parent)
  , m_inverted(false)
{
	setColumnCount(2);
	setHorizontalHeaderLabels( QStringList() << "Descarga" << "Subida" );
	setRowCount(4);
	setVerticalHeaderLabels( QStringList() << "Límite normal" << "Pico" << "Media" << "Tiempo" );
	connect( this, SIGNAL(cellChanged(int,int)), this, SLOT(onSpeedChanged(int,int)) );
	updateTable();
}

void QSpeedTableWidget::setROSRateLimit(const ROSRateLimit &rosRateLimit, bool inverted)
{
	m_ROSRateLimit = rosRateLimit;
	m_inverted = inverted;
	updateTable();
}

void QSpeedTableWidget::setROSRateLimit(const QString &rosRateLimitString, bool inverted)
{
	m_ROSRateLimit.fromString(rosRateLimitString);
	m_inverted = inverted;
	updateTable();
}

bool QSpeedTableWidget::getROSRateLimit(ROSRateLimit &rosRateLimit) const
{
	rosRateLimit.downloadSpeed().fromString(item(0, (0 ^ m_inverted))->text());
	rosRateLimit.uploadSpeed().fromString(item(0, (1 ^ m_inverted))->text());
	rosRateLimit.downloadBurstSpeed().fromString(item(1, (0 ^ m_inverted))->text());
	rosRateLimit.uploadBurstSpeed().fromString(item(1, (1 ^ m_inverted))->text());
	rosRateLimit.downloadAverageSpeed().fromString(item(2, (0 ^ m_inverted))->text());
	rosRateLimit.uploadAverageSpeed().fromString(item(1, (1 ^ m_inverted))->text());
	rosRateLimit.downloadAverageSeconds() = item(3, (0 ^ m_inverted))->text().toUInt();
	rosRateLimit.uploadAverageSeconds() = item(1, (1 ^ m_inverted))->text().toUInt();

	QString error;
	if( !(error = checkSpeeds( m_inverted ? "descarga" : "subida",
							   rosRateLimit.downloadSpeed(),
							   rosRateLimit.downloadBurstSpeed(),
							   rosRateLimit.downloadAverageSpeed(),
							   rosRateLimit.downloadAverageSeconds())).isEmpty() )
		raiseWarning( error );
	else
	if( !(error = checkSpeeds( m_inverted ? "descarga" : "subida",
							   rosRateLimit.uploadSpeed(),
							   rosRateLimit.uploadBurstSpeed(),
							   rosRateLimit.uploadAverageSpeed(),
							   rosRateLimit.uploadAverageSeconds())).isEmpty() )
		raiseWarning( error );
	else
		return true;
	return false;
}

void QSpeedTableWidget::setItemText(int row, int col, const QString &text)
{
	if( !item(row, col) )
		setItem(row, col, new QTableWidgetItem(text) );
	else
		item(row, col)->setText(text);
}

void QSpeedTableWidget::setItemSpeed(int row, int col, const ROSSpeed &rosSpeed)
{
	setItemText( row, col, rosSpeed.toString() );
}

void QSpeedTableWidget::setItemTime(int row, int col, quint32 time)
{
	setItemText( row, col, QString::number(time) );
}

void QSpeedTableWidget::updateTable()
{
	setItemSpeed( 0, (0 ^ m_inverted) & 1, m_ROSRateLimit.downloadSpeed() );
	setItemSpeed( 0, (1 ^ m_inverted) & 1, m_ROSRateLimit.uploadSpeed() );

	setItemSpeed( 1, (0 ^ m_inverted) & 1, m_ROSRateLimit.downloadBurstSpeed() );
	setItemSpeed( 1, (1 ^ m_inverted) & 1, m_ROSRateLimit.uploadBurstSpeed() );

	setItemSpeed( 2, (0 ^ m_inverted) & 1, m_ROSRateLimit.downloadAverageSpeed() );
	setItemSpeed( 2, (1 ^ m_inverted) & 1, m_ROSRateLimit.uploadAverageSpeed() );

	setItemTime( 3, (0 ^ m_inverted) & 1, m_ROSRateLimit.downloadAverageSeconds() );
	setItemTime( 3, (1 ^ m_inverted) & 1, m_ROSRateLimit.uploadAverageSeconds() );
}

QString QSpeedTableWidget::checkSpeeds(const QString &direction, ROSSpeed normal, ROSSpeed burst, ROSSpeed average, quint32 seconds) const
{
	if( burst == 0 )
	{
		if( average != 0 )
			return tr("La media de %1 no debe configurarse si no hay pico en la velocidad de %1.").arg(direction);
		else
		if( seconds != 0 )
			return tr("El tiempo para media de %1, no debe configurarse si no hay pico en la velocidad de %1.").arg(direction);
	}
	else
	{
		if( normal >= burst )
			return tr("El pico de %1 debe ser mayor a la velocidad de %1.").arg(direction);
		if( normal >= average )
			return tr("La media de %1 debe ser menor a la velocidad de %1.").arg(direction);
	}
	return QString();
}

void QSpeedTableWidget::raiseWarning(const QString &error) const
{
	QMessageBox::warning( const_cast<QSpeedTableWidget*>(this), tr("Límites de velocidad"), error);
}
