#include "DlgServiceScheduler.h"
#include "ui_DlgServiceScheduler.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/SchedulerData.h"
#include "../Widgets/QROSSecretTableWidget.h"

enum Columns
{
	ColSelect,
	ColUserName,
	ColCClient,
	ColName,
	ColYear,
	ColMonth,
	ColChange,
	ColCount
};

const QStringList columnNames = QStringList() << QObject::tr("")
											  << QObject::tr("Nombre usuario")
											  << QObject::tr("CCliente")
											  << QObject::tr("Nombre")
											  << QObject::tr("Año")
											  << QObject::tr("Mes")
											  << QObject::tr("Cambio");

DlgServiceScheduler::DlgServiceScheduler(ROSMultiConnectManager &rosMultiConnectManager, QROSSecretTableWidget &rosSecretTable, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgServiceScheduler)
	, mRosMultiConnectManager(rosMultiConnectManager)
	, mRosSecretTable(rosSecretTable)
{
	ui->setupUi(this);
	QDate curDate = QDate::currentDate();

	Q_ASSERT(Columns::ColCount == columnNames.count());
	ui->tableWidget->setColumnCount(Columns::ColCount);
	ui->tableWidget->setHorizontalHeaderLabels(columnNames);

	for( int year = curDate.year()-10, toYear = year+20; year <= toYear; year++ )
		ui->yearComboBox->addItem( QString::number(year) );
	ui->monthComboBox->insertItems( 0, ServiceScheduler::Data::months() );

	// For the lasts 5 days of the month, let's select the next month.
	if( curDate.daysInMonth() >=25 )
	{
		if( curDate.month() < 12 )
		{
			ui->monthComboBox->setCurrentIndex( 1 );
			ui->yearComboBox->setCurrentIndex( 10 );
		}
		else
		{
			ui->monthComboBox->setCurrentIndex( curDate.month()+1 );
			ui->yearComboBox->setCurrentIndex( 9 );
		}
	}
	else
	{
		ui->monthComboBox->setCurrentIndex( curDate.month() );
		ui->yearComboBox->setCurrentIndex( 9 );
	}
	ui->monthComboBox->setCurrentIndex( curDate.month() );
	connect( ui->yearComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable(int)) );
	connect( ui->monthComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable(int)) );

	gSchedulerData.load();
	updateTable();
}

void DlgServiceScheduler::updateTable(int )
{
	ServiceScheduler::SchedulerMapIterator it(gSchedulerData);
	const ROSPPPSecret *secret;
	QCheckBox *ch;
	QTableWidgetItem *item;

	int row;
	quint16 showYear = quint16(ui->yearComboBox->currentText().toUInt());
	quint16 showMonth = quint16(ui->monthComboBox->currentIndex());
	ui->tableWidget->setRowCount(0);
	while( it.hasNext() )
	{
		it.next();
		for( const ServiceScheduler::Data &data : it.value() )
		{
			if( (data.year() == showYear) && (data.month() == showMonth) )
			{
				secret = mRosSecretTable.rosPppSecret(it.key());
				if( secret )
				{
					row = ui->tableWidget->rowCount();
					ui->tableWidget->insertRow(row);
					ui->tableWidget->setCellWidget(row, Columns::ColSelect, ch = new QCheckBox());
					ch->setChecked(true);

					ui->tableWidget->setItem( row, Columns::ColUserName, item = new QTableWidgetItem(secret->userName()) );
					item->setFlags( item->flags() & ~Qt::ItemIsEditable );

					ui->tableWidget->setItem( row, Columns::ColCClient, item = new QTableWidgetItem(secret->clientCode()) );
					item->setFlags( item->flags() & ~Qt::ItemIsEditable );

					ui->tableWidget->setItem( row, Columns::ColName, item = new QTableWidgetItem(secret->clientName()) );
					item->setFlags( item->flags() & ~Qt::ItemIsEditable );

					ui->tableWidget->setItem( row, Columns::ColYear, item = new QTableWidgetItem(QString::number(data.year())) );
					item->setFlags( item->flags() & ~Qt::ItemIsEditable );

					ui->tableWidget->setItem( row, Columns::ColMonth, item = new QTableWidgetItem(data.monthName()) );
					item->setFlags( item->flags() & ~Qt::ItemIsEditable );

					QString changeDescription;
					if( ServiceState::isCanceledState(secret->serviceState()) && (data.serviceAction() == ServiceScheduler::ServiceAction::Activate) )
						changeDescription = tr("Activar servicio");
					else
					if( !ServiceState::isCanceledState(secret->serviceState()) && (data.serviceAction() == ServiceScheduler::ServiceAction::Cancel) )
						changeDescription = tr("Desactivar servicio");

					if( !data.profileName().isEmpty() && (data.profileName() != secret->pppProfileName()) )
					{
						if( !changeDescription.isEmpty() )
							changeDescription += ", ";
						changeDescription += tr("Cambiar perfil de %1 a %2").arg(secret->pppProfileName()).arg(data.profileName());
					}

					if( changeDescription.isEmpty() )
					{
						changeDescription = tr("¡Ningún cambio a realizar!");
						ch->setDisabled(true);
						ch->setChecked(false);
					}
					ui->tableWidget->setItem(row, Columns::ColChange, new QTableWidgetItem(changeDescription) );
				}
				break;
			}
		}
	}
	ui->tableWidget->resizeColumnsToContents();
}

void DlgServiceScheduler::changeSelection(bool newSel)
{
	for( int row = ui->tableWidget->rowCount()-1; row >= 0; row-- )
	{
		if( ui->tableWidget->cellWidget(row, Columns::ColSelect)->isEnabled() )
			static_cast<QCheckBox*>(ui->tableWidget->cellWidget(row, Columns::ColSelect))->setChecked(newSel);
	}
}

DlgServiceScheduler::~DlgServiceScheduler()
{
	delete ui;
}

void DlgServiceScheduler::on_selectAllButton_clicked()
{
	changeSelection(true);
}

void DlgServiceScheduler::on_unselectAllButton_clicked()
{
	changeSelection(false);
}

void DlgServiceScheduler::on_applyButton_clicked()
{

}

const int startLineTop = 50;
const int startLineLeft = 40;
const int userNameBoxWidth = 150;
const int clientCodeBoxWidth = 60;
const int lineHeight = 14;
const int linesPerPage = 70;

void DlgServiceScheduler::paintLine( QPainter &painter, int line,
									 const QString &userName,
									 const QString &clientCode,
									 const QString &changeDescription )
{
	static QRect rect;

	rect.setTop( line * lineHeight );
	rect.setHeight( lineHeight );

	rect.setLeft( startLineLeft );
	rect.setWidth( userNameBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, userName );

	rect.setLeft( rect.right() + 8 );
	rect.setWidth( clientCodeBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, clientCode );

	rect.setLeft( rect.right() + 8 );
	rect.setWidth( 800 );
	painter.drawText( rect, Qt::AlignLeft, changeDescription );
}

void DlgServiceScheduler::paintTable(QPainter &painter, int firstRow, int lastRow)
{

}

void DlgServiceScheduler::paintPage(QPainter &painter, int currentPage, int pageCount, int firstRow, int lastRow)
{
	painter.setFont( QFont("Arial", 12) );
	painter.drawText( startLineLeft, startLineTop, tr("Cambios del servicio a los clientes para el %1 del %2. Página %3 de %4")
					  .arg(ui->monthComboBox->currentText()).arg(ui->yearComboBox->currentText())
					  .arg(currentPage).arg(pageCount));

	painter.setFont( QFont("Arial", 8, 2) );

	paintLine(painter, 6, "NOMBRE USUARIO", "CCLIENTE", "CAMBIO EN EL SERVICIO");
	painter.drawLine( startLineLeft, startLineTop + lineHeight * 4, startLineLeft + 8 + userNameBoxWidth + 8 + clientCodeBoxWidth + 400, startLineTop + lineHeight * 4 );

	painter.setFont( QFont("Arial", 8, 1) );

//	for( int row = 0; row < ui->tableWidget->rowCount(); row++ )
	for( int line = 0; line < linesPerPage; line++ )
	{
		paintLine( painter, line + 8, "PPPoE_Novatel", "12345", "Cambia perfil de asdfasfasfasfd a asfasfasfasf y activa servicio" );
	}
}

void DlgServiceScheduler::on_printButton_clicked()
{
	QPrinter printer;
	QPrintDialog dlg(&printer, this);
	dlg.setWindowTitle("Imprimir programación");
	if( dlg.exec() == QDialog::Accepted )
	{
		QPainter painter;
		if( !painter.begin(&printer) )
		{
			QMessageBox::warning(this, tr("Imprimiendo"), tr("No se ha podido abrir la impresora. Es posible que esté ocupada.") );
			return;
		}

		int totalPages = (ui->tableWidget->rowCount() / linesPerPage)+3;
		for( int page = 0; page < totalPages; page++ )
		{
			paintPage( painter, page+1, totalPages, page * linesPerPage, linesPerPage );
			if( (page+1) != totalPages )
				printer.newPage();
		}
		painter.end();
	}
}

void DlgServiceScheduler::on_exportButton_clicked()
{
	QString fileNameTip = QString("%1/%2_%3.tsv")
			.arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation))
			.arg(ui->yearComboBox->currentText()).arg(ui->monthComboBox->currentText());

	QString fname = QFileDialog::getSaveFileName(this, tr("Exportar datos"), fileNameTip, "*.tsv");
	if( !fname.isEmpty() )
	{
		QFile f(fname);
		if( !f.open(QIODevice::WriteOnly) )
		{
			QMessageBox::warning(this, tr("Exportando datos"), tr("No se ha podido abrir el fichero %1 para guardar los datos.\n%2")
								 .arg(fname).arg(f.errorString()));
			return;
		}
		QString csv;
		for( int row = ui->tableWidget->rowCount()-1; row >= 0; --row )
		{
			csv += QString("%1\t%2\t%3\n")
					.arg(ui->tableWidget->item(row, Columns::ColUserName)->text())
					.arg(ui->tableWidget->item(row, Columns::ColCClient)->text())
					.arg(ui->tableWidget->item(row, Columns::ColChange)->text());
		}
		f.write( csv.toLatin1() );
		f.flush();
		f.close();
		QMessageBox::information(this, tr("Exportando datos"), tr("Datos exportados") );
	}
}
