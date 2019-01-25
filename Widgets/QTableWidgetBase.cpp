#include "QTableWidgetBase.h"

#include <QTreeWidgetItem>

#include "QRoutersLineEdit.h"

QTableWidgetBase::QTableWidgetBase(QWidget *papi) : QTableWidget(papi),
	m_routerIDColumn(-1), m_routerColumn(-1)
{
	connect( this, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChanged(int,int)) );
}

QTableWidgetBase::~QTableWidgetBase()
{

}

int QTableWidgetBase::rowOf(const QString &routerName, const QString &rosObjectID)
{
	Q_ASSERT( !routerName.isEmpty() );

	// It's not an error because could be some lookup events before the table data has been populated.
	if( (m_routerIDColumn == -1) && (m_routerColumn == -1) )
	{
		qWarning("Cannot lookup row by router or router/rosObjectID if nor routerColumn neither routerIDColumn are not defined yet");
		return -1;
	}

	if( (m_routerIDColumn != -1) || (m_routerColumn != -1) )
	{
		for( int row = 0; row < rowCount(); ++row )
		{
			if( cellWidget(row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn) )
			{
				QRoutersLineEdit* routerLineEdit = static_cast<QRoutersLineEdit*>(cellWidget(row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn));
				Q_ASSERT( routerLineEdit );
				if( !rosObjectID.isEmpty() )
				{
					if( routerLineEdit->rosObjectID(routerName) == rosObjectID )
						return row;
				}
				else
				{
					if( !routerLineEdit->rosObjectID(routerName).isEmpty() )
						return row;
				}
			}
		}
	}

	return -1;
}

int QTableWidgetBase::rowOf(int colKey, const QString &cellText)
{
	Q_ASSERT( (colKey >= 0) && (colKey < columnCount()) );
	Q_ASSERT( !cellText.isEmpty() );

	for( int row = 0; row < rowCount(); ++row )
		if( item(row, colKey)->text() == cellText )
			return row;

	return -1;
}

void QTableWidgetBase::setCellText(int row, int col, const QString &text, Qt::ItemFlags itemFlags)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( !item(row, col) )
		setItem(row, col, new QTableWidgetItem() );

	item(row, col)->setText(text);
	item(row, col)->setFlags(itemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

QString QTableWidgetBase::cellText(int row, int col, const QString &defaultValue) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

int QTableWidgetBase::cellInt(int row, int col, int defaultValue) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text().toInt();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

void QTableWidgetBase::addCellRoutersID(int row, int col, const QString &routerName, const QString &rosObjectID)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );
	Q_ASSERT( (m_routerIDColumn == -1) || (m_routerIDColumn == col) );

	if( cellWidget(row, col) == Q_NULLPTR )
	{
		setCellWidget( row, col, new QRoutersLineEdit() );
		m_routerIDColumn = col; // This is used later to increase the deletion speed.
	}
	static_cast<QRoutersLineEdit*>(cellWidget(row, col))->addRouterID(routerName, rosObjectID);
}

void QTableWidgetBase::delCellRoutersID(int row, const QString &routerName)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (m_routerIDColumn >= 0) && (m_routerIDColumn < columnCount()) );
	Q_ASSERT( cellWidget(row, m_routerIDColumn) != Q_NULLPTR );
	Q_ASSERT( static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn)) != Q_NULLPTR );

	static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn))->delRouter(routerName);
}

const QRouterIDMap &QTableWidgetBase::routerIDMap(int row) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (m_routerIDColumn >= 0) && (m_routerIDColumn < columnCount()) );
	Q_ASSERT( cellWidget(row, m_routerIDColumn) != Q_NULLPTR );
	Q_ASSERT( static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn)) != Q_NULLPTR );

	return static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn))->routerIDMap();
}

int QTableWidgetBase::rowOf(const ROSDataBase &rosData)
{
	return rowOf(rosData.routerName(), rosData.rosObjectID());
}

void QTableWidgetBase::setupRow(int row, const ROSDataBase &rosData)
{
	if( (m_routerIDColumn != -1) || (m_routerColumn != -1) )
		addCellRoutersID( row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn, rosData.routerName(), rosData.rosObjectID() );
}

void QTableWidgetBase::addNewRow(const ROSDataBase &rosData)
{
	Q_ASSERT( rosData.routerName().isEmpty() );
	Q_ASSERT( rosData.rosObjectID().isEmpty() );

	blockSignals(true);

	int row = rowCount();
	insertRow( row );
	setupRow( row, rosData );

	blockSignals(false);
}

void QTableWidgetBase::onROSModReply(const ROSDataBase &rosData)
{
	Q_ASSERT( !rosData.routerName().isEmpty() );
	Q_ASSERT( !rosData.rosObjectID().isEmpty() );

	blockSignals(true);
	int row = rowOf( rosData );

	if( (row >= rowCount()) || (row < 0) )
		insertRow( row = rowCount() );
	setupRow( row, rosData );

	blockSignals(false);
}

void QTableWidgetBase::onROSDelReply(const QString &routerName, const QString &rosObjectID)
{
	// It's not an error because could be some lookup events before the table data has been populated.
	if( (m_routerIDColumn == -1) && (m_routerColumn == -1) )
	{
		qWarning("Cannot lookup row by router or router/rosObjectID if nor routerColumn neither routerIDColumn are not defined yet");
		return;
	}

	blockSignals(true);
	int row;
	while( (row = rowOf(routerName, rosObjectID)) != -1 )
	{
		delCellRoutersID(row, routerName);
		if( routersCount(row) == 0 )
			removeRow(row);
	}
	blockSignals(false);
}

void QTableWidgetBase::removeData(int row)
{
	if( (row != -1) )
	{
		ROSDataBase *rosData = getRosData(row);
		rosData->setDeleting(true);
		emit dataModified( *rosData, routerIDMap(row) );
		delete rosData;
	}
}

void QTableWidgetBase::onCellChanged(int row, int col)
{
	Q_UNUSED(col);
	ROSDataBase *rosData = getRosData(row);
	emit dataModified( *rosData, routerIDMap(row) );
	delete rosData;
}
