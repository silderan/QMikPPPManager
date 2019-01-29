#include "DlgPPPLogViewer.h"
#include "ui_DlgPPPLogViewer.h"

#include <QElapsedTimer>
#include <QTableWidgetItem>

DlgPPPLogViewer::DlgPPPLogViewer(const QString &userName, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgPPPLogViewer)
{
	ui->setupUi(this);
	ui->logsTable->hide();
	QPPPLogDataList pppLogDatalist = logService.readLogs(userName);
	QElapsedTimer m_viewTime;
	m_viewTime.start();

	if( userName.isEmpty() )
	{
		ui->logsTable->setColumnCount(6);
		ui->logsTable->setHorizontalHeaderLabels( QStringList() << "Hora" << "Quien" << "Cliente" << "Dato" << "Original" << "Nuevo" );
		Q_ASSERT( ui->logsTable->columnCount() == 6 );
		for( int row = 0; row < pppLogDatalist.count(); ++row )
		{
			ui->logsTable->insertRow(row);
			ui->logsTable->setItem( row, 0, new QTableWidgetItem(pppLogDatalist.at(row).timestamp) );
			ui->logsTable->setItem( row, 1, new QTableWidgetItem(pppLogDatalist.at(row).appUserName) );
			ui->logsTable->setItem( row, 2, new QTableWidgetItem(pppLogDatalist.at(row).pppUserName) );
			ui->logsTable->setItem( row, 3, new QTableWidgetItem(pppLogDatalist.at(row).field) );
			ui->logsTable->setItem( row, 4, new QTableWidgetItem(pppLogDatalist.at(row).oldValue) );
			ui->logsTable->setItem( row, 5, new QTableWidgetItem(pppLogDatalist.at(row).newValue) );
		}
	}
	else
	{
		setWindowTitle( tr("Visor de registros del usuario %1").arg(userName));
		ui->logsTable->setColumnCount(5);
		ui->logsTable->setHorizontalHeaderLabels( QStringList() << "Hora" << "Quien" << "Dato" << "Original" << "Nuevo" );
		Q_ASSERT( ui->logsTable->columnCount() == 5 );
		for( int row = 0; row < pppLogDatalist.count(); ++row )
		{
			ui->logsTable->insertRow(row);
			ui->logsTable->setItem( row, 0, new QTableWidgetItem(pppLogDatalist.at(row).timestamp) );
			ui->logsTable->setItem( row, 1, new QTableWidgetItem(pppLogDatalist.at(row).appUserName) );
			ui->logsTable->setItem( row, 2, new QTableWidgetItem(pppLogDatalist.at(row).field) );
			ui->logsTable->setItem( row, 3, new QTableWidgetItem(pppLogDatalist.at(row).oldValue) );
			ui->logsTable->setItem( row, 4, new QTableWidgetItem(pppLogDatalist.at(row).newValue) );
		}
	}
	qint64 msSetingUP = m_viewTime.restart();
	ui->logsTable->setSortingEnabled(true);
	ui->logsTable->resizeColumnsToContents();
	ui->logsTable->show();
	qint64 msShowing = m_viewTime.elapsed();

	QString info = tr("Leidos %1 registros de %2 ficheros con %3 registros únicos encontrados en %4 ms\n")
			.arg( logService.logsReaded() )
			.arg( logService.filesReaded() )
			.arg( pppLogDatalist.count() )
			.arg( logService.msReading() );
	info.append( tr("Los %1 registros han sido organizados en %2 ms y mostrados en pantalla en %3 ms")
				 .arg(pppLogDatalist.count())
				 .arg(msSetingUP)
				 .arg(msShowing));
	ui->infoLabel->setText(info);
}

DlgPPPLogViewer::~DlgPPPLogViewer()
{
	delete ui;
}

void DlgPPPLogViewer::on_compactLogsButton_clicked()
{

}
