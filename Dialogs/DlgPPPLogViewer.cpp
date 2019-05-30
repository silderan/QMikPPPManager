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

#include "DlgPPPLogViewer.h"
#include "ui_DlgPPPLogViewer.h"

#include <QElapsedTimer>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "ConfigData/QConfigData.h"
#include "../Utils/Utils.h"

DlgPPPLogViewer::DlgPPPLogViewer(const QString &userName, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgPPPLogViewer)
	, m_userName(userName)
	, m_localCompactButtonEnable(false)
	, m_localCompactButtonVisible(false)
{
	ui->setupUi(this);
	ui->logsTable->hide();
	m_pppLogDatalist = logService.readLogs(m_userName);
	QElapsedTimer m_viewTime;
	m_viewTime.start();

	if( m_userName.isEmpty() )
	{
		showCompactButton(true);
		ui->logsTable->setColumnCount(6);
		ui->logsTable->setHorizontalHeaderLabels( QStringList() << "Hora" << "Quien" << "Cliente" << "Dato" << "Original" << "Nuevo" );
		Q_ASSERT( ui->logsTable->columnCount() == 6 );
		for( int row = 0; row < m_pppLogDatalist.count(); ++row )
		{
			ui->logsTable->insertRow(row);
			ui->logsTable->setItem( row, 0, new Utils::QDateTimeTableItem(m_pppLogDatalist.at(row).timestamp) );
			ui->logsTable->setItem( row, 1, new QTableWidgetItem(m_pppLogDatalist.at(row).appUserName) );
			ui->logsTable->setItem( row, 2, new QTableWidgetItem(m_pppLogDatalist.at(row).pppUserName) );
			ui->logsTable->setItem( row, 3, new QTableWidgetItem(m_pppLogDatalist.at(row).field) );
			ui->logsTable->setItem( row, 4, new QTableWidgetItem(m_pppLogDatalist.at(row).oldValue) );
			ui->logsTable->setItem( row, 5, new QTableWidgetItem(m_pppLogDatalist.at(row).newValue) );
		}
		enableCompactButton( !m_pppLogDatalist.isEmpty() );
	}
	else
	{
		ui->compactLogsButton->setHidden(true);
		setWindowTitle( tr("Visor de registros del usuario %1").arg(m_userName));
		ui->logsTable->setColumnCount(5);
		ui->logsTable->setHorizontalHeaderLabels( QStringList() << "Hora" << "Quien" << "Dato" << "Original" << "Nuevo" );
		Q_ASSERT( ui->logsTable->columnCount() == 5 );
		for( int row = 0; row < m_pppLogDatalist.count(); ++row )
		{
			ui->logsTable->insertRow(row);

			ui->logsTable->setItem( row, 0, new Utils::QDateTimeTableItem(m_pppLogDatalist.at(row).timestamp) );
			ui->logsTable->setItem( row, 1, new QTableWidgetItem(m_pppLogDatalist.at(row).appUserName) );
			ui->logsTable->setItem( row, 2, new QTableWidgetItem(m_pppLogDatalist.at(row).field) );
			ui->logsTable->setItem( row, 3, new QTableWidgetItem(m_pppLogDatalist.at(row).oldValue) );
			ui->logsTable->setItem( row, 4, new QTableWidgetItem(m_pppLogDatalist.at(row).newValue) );
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
			.arg( m_pppLogDatalist.count() )
			.arg( logService.msReading() );
	info.append( tr("Los %1 registros han sido organizados en %2 ms y mostrados en pantalla en %3 ms")
				 .arg(m_pppLogDatalist.count())
				 .arg(msSetingUP)
				 .arg(msShowing));
	ui->infoLabel->setText(info);
}

void DlgPPPLogViewer::enableCompactButton(bool enable)
{
	ui->compactLogsButton->setEnabled( (gGlobalConfig.userLevel() == ROSAPIUser::Level::Supervisor) && (m_localCompactButtonEnable = enable) );
}

void DlgPPPLogViewer::showCompactButton(bool visible)
{
	ui->compactLogsButton->setVisible( (gGlobalConfig.userLevel() == ROSAPIUser::Level::Supervisor) && (m_localCompactButtonVisible = visible) );
}

DlgPPPLogViewer::~DlgPPPLogViewer()
{
	delete ui;
}

void DlgPPPLogViewer::on_compactLogsButton_clicked()
{
	// Compacting data only allowed when all files where readed.
	// It's just for beign clearer to user. In fact, the compact algorith works allways with all records in all files.
	if( m_userName.isEmpty() && !m_pppLogDatalist.isEmpty() )
	{
		if( logService.compactAllFiles() )
		{
			if( QMessageBox::information( this, tr("Compactar ficheros"), tr("Ficheros de registro compactados.\n¿Quieres borrar los ficheros usados en el proceso"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes )
				QMessageBox::information( this, tr("Compactar ficheros"), tr("Borrados %1 ficheros al crear el fichero %2").arg(logService.removeOldFiles()).arg(logService.currentCompactFName()) );
		}
	}
}
