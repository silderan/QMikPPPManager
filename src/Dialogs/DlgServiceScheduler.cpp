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
#include "../ConfigData/QConfigData.h"
#include "../Widgets/QROSSecretTableWidget.h"

//#define INCLUDE_YEAR_MONTH

enum Columns
{
	ColSelect,
	ColUserName,
	ColClientCode,
	ColName,
#ifdef INCLUDE_YEAR_MONTH
	ColYear,
	ColMonth,
#endif
	ColServiceChange,
	ColProfileChange,
	ColCount
};

const QStringList columnNames = QStringList() << QObject::tr("")
											  << QObject::tr("Nombre usuario")
											  << QObject::tr("CCliente")
											  << QObject::tr("Nombre")
#ifdef INCLUDE_YEAR_MONTH
											  << QObject::tr("Año")
											  << QObject::tr("Mes")
#endif
											  << QObject::tr("Cambio estado servicio")
											  << QObject::tr("Cambio velocidad");

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

	ui->actionComboBox->addItems( ServiceScheduler::Data::dayNames() );

	int day = curDate.day();
	if( day >= 25 )
		ui->actionComboBox->setCurrentIndex( ServiceScheduler::Data::lastDaysIndex() );
	else
	if( day <= 10 )
		ui->actionComboBox->setCurrentIndex( ServiceScheduler::Data::firstDaysIndex() );
	else
		ui->actionComboBox->setCurrentIndex( ServiceScheduler::Data::monthDayToArrayIndex(day) );

	ui->monthComboBox->setCurrentIndex( curDate.month() );
	ui->yearComboBox->setCurrentIndex( 10 );

	ui->monthComboBox->setCurrentIndex( curDate.month() );
	connect( ui->yearComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable(int)) );
	connect( ui->monthComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable(int)) );
	connect( ui->actionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable(int)) );

	gServiceSchedulerMap.load();
	updateTable();
}

void DlgServiceScheduler::updateTable(int )
{
	ServiceScheduler::SchedulerMapIterator it(gServiceSchedulerMap);
	const ROSPPPSecret *secret;
	QCheckBox *ch;
	QTableWidgetItem *item;

	int row;
	quint16 showYear = quint16(ui->yearComboBox->currentText().toUInt());
	quint16 showMonth = quint16(ui->monthComboBox->currentIndex());
	ui->tableWidget->setRowCount(0);
	bool onlyFirstsDays = false;
	bool onlyLastsDays = false;
	int specificDay = 0;
	if( ui->actionComboBox->currentIndex() == ServiceScheduler::Data::firstDaysIndex() )
		onlyFirstsDays = true;
	else
	if( ui->actionComboBox->currentIndex() == ServiceScheduler::Data::lastDaysIndex() )
		onlyLastsDays = true;
	else
		specificDay = ServiceScheduler::Data::arrayIndexToMonthDay( ui->actionComboBox->currentIndex() );
	while( it.hasNext() )
	{
		it.next();
		for( const ServiceScheduler::Data &data : it.value() )
		{
			if( data.year() != showYear )
				continue;
			if( data.month() != showMonth )
				continue;

			if( (onlyFirstsDays && data.isFirstsDays()) ||
				(onlyLastsDays && data.isLastsDays()) ||
				(data.isMonthDay() && (specificDay == data.monthDay())) )
			{
				row = ui->tableWidget->rowCount();
				ui->tableWidget->insertRow(row);

				ui->tableWidget->setCellWidget(row, Columns::ColSelect, ch = new QCheckBox("Cambiar"));

				ui->tableWidget->setItem( row, Columns::ColUserName, item = new QTableWidgetItem(it.key()) );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

				ui->tableWidget->setItem( row, Columns::ColClientCode, item = new QTableWidgetItem("??") );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

				ui->tableWidget->setItem( row, Columns::ColName, item = new QTableWidgetItem("??") );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

				ui->tableWidget->setItem( row, Columns::ColServiceChange, item = new QTableWidgetItem("??") );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

				ui->tableWidget->setItem( row, Columns::ColProfileChange, item = new QTableWidgetItem("??") );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

#ifdef INCLUDE_YEAR_MONTH
				ui->tableWidget->setItem( row, Columns::ColYear, item = new QTableWidgetItem(QString::number(data.year())) );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );

				ui->tableWidget->setItem( row, Columns::ColMonth, item = new QTableWidgetItem(data.monthName()) );
				item->setFlags( item->flags() & ~Qt::ItemIsEditable );
#endif

				static QColor green = QColor(0xF0, 0xFF, 0xF0);
				static QColor red = QColor(0xFF, 0xF0, 0xF0);

				ui->tableWidget->item(row, Columns::ColServiceChange)->setData(Qt::UserRole, data.serviceAction());
				switch( data.serviceAction() )
				{
				case ServiceScheduler::NoChange:ui->tableWidget->item(row, Columns::ColServiceChange)->setText( tr("Sin cambios") );break;
				case ServiceScheduler::Activate:
					ui->tableWidget->item(row, Columns::ColServiceChange)->setText( tr("Activar") );
					ui->tableWidget->item(row, Columns::ColServiceChange)->setBackground(green);
					break;
				case ServiceScheduler::Cancel:
					ui->tableWidget->item(row, Columns::ColServiceChange)->setText( tr("Cancelar") );
					ui->tableWidget->item(row, Columns::ColServiceChange)->setBackground(red);
					break;
				}
				if( data.profileName().isEmpty() )
					ui->tableWidget->item(row, Columns::ColProfileChange)->setText( tr("Sin cambios") );
				else
					ui->tableWidget->item(row, Columns::ColProfileChange)->setText( data.profileName() );

				secret = mRosSecretTable.rosPppSecret(it.key());
				bool changeSomethng = false;
				if( secret )
				{
					QString changeDescription;
					ui->tableWidget->item(row, Columns::ColName)->setText( secret->clientName() );
					ui->tableWidget->item(row, Columns::ColClientCode)->setText( secret->clientCode() );
					if( data.serviceAction() != ServiceScheduler::NoChange )
					{
						if( ServiceState::isCanceledState(secret->serviceState()) && (data.serviceAction() == ServiceScheduler::ServiceAction::Cancel) )
							ui->tableWidget->item(row, Columns::ColServiceChange)->setForeground(Qt::gray);
						else
						if( !ServiceState::isCanceledState(secret->serviceState()) && (data.serviceAction() == ServiceScheduler::ServiceAction::Activate) )
							ui->tableWidget->item(row, Columns::ColServiceChange)->setForeground(Qt::gray);
						else
							changeSomethng = true;
					}

					if( !data.profileName().isEmpty() )
					{
						changeDescription = tr("%1 -> %2").arg(secret->pppProfileName()).arg(data.profileName());

						if( data.profileName() == secret->pppProfileName() )
							ui->tableWidget->item(row, Columns::ColProfileChange)->setForeground(Qt::gray);
						else
							changeSomethng = true;
					}
				}
				if( !changeSomethng )
					ch->setDisabled(true);
				else
					ch->setChecked(true);
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

const int fontSize = 8;
const int startLineTop = 50;
const int startLineLeft = 40;
const int userNameBoxWidth = 150;
const int clientCodeBoxWidth = 60;
const int clientServiceBoxWidth = 200;
const int clientProfileBoxWidth = 200;
const int lineHeight = 14;
const int linesPerPage = 74;
const int pageHeaderLines = 4;
const int pageFooterLines = 2;
const int tableHeaderLines = 4;
const int tableFooterLines = 0;
const int rowsPerPage = linesPerPage - pageHeaderLines - pageFooterLines - tableHeaderLines - tableFooterLines;

void DlgServiceScheduler::writeLine( QPainter &painter, int line,
									 const QString &userName,
									 const QString &clientCode,
									 const QString &serviceChange,
									 const QString &profileChange,
									 const QColor &textClr)
{
	static QRect rect;

	painter.setPen(textClr);
	rect.setTop( line * lineHeight );
	rect.setHeight( lineHeight );

	rect.setLeft( startLineLeft );
	rect.setWidth( userNameBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, userName );

	rect.setLeft( rect.right() + fontSize );
	rect.setWidth( clientCodeBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, clientCode );

	rect.setLeft( rect.right() + fontSize );
	rect.setWidth( clientServiceBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, serviceChange );

	rect.setLeft( rect.right() + fontSize );
	rect.setWidth( clientProfileBoxWidth );
	painter.drawText( rect, Qt::AlignLeft, profileChange );
}

void DlgServiceScheduler::paintTable(QPainter &painter, int page)
{
	painter.setFont( QFont("Arial", fontSize) );

	writeLine(painter, pageHeaderLines + 2, "NOMBRE USUARIO", "CCLIENTE", "CAMBIO SERVICIO", "CAMBIO VELOCIDAD", Qt::black);
	painter.drawLine( startLineLeft,
					  startLineTop + lineHeight * pageHeaderLines,
					  startLineLeft + fontSize + userNameBoxWidth + fontSize + clientCodeBoxWidth + clientServiceBoxWidth + clientProfileBoxWidth,
					  startLineTop + lineHeight * 4 );

	painter.setFont( QFont("Arial", fontSize) );

	static QColor red(0x80, 0x00, 0x00);
	static QColor green(0x00, 0x80, 0x00);
	for( int line = 0; line < rowsPerPage; line++ )
	{
		int row = line + ((page - 1) * rowsPerPage);
		if( row >= ui->tableWidget->rowCount() )
			break;
		writeLine( painter, pageHeaderLines + tableHeaderLines + line,
				   ui->tableWidget->item(row, Columns::ColUserName)->text(),
				   ui->tableWidget->item(row, Columns::ColClientCode)->text(),
				   ui->tableWidget->item(row, Columns::ColServiceChange)->text(),
				   ui->tableWidget->item(row, Columns::ColProfileChange)->text(),
				   (ui->tableWidget->item(row, Columns::ColServiceChange)->data(Qt::UserRole).toInt() == ServiceScheduler::Activate) ? green :
				   (ui->tableWidget->item(row, Columns::ColServiceChange)->data(Qt::UserRole).toInt() == ServiceScheduler::Cancel) ? red : Qt::black );
	}
}

void DlgServiceScheduler::paintPage(QPainter &painter, int currentPage, int pageCount)
{
	painter.setFont( QFont("Arial", fontSize + 4) );
	painter.drawText( startLineLeft, startLineTop, tr("Cambios del servicio a los clientes para el %1 del %2")
					  .arg(ui->monthComboBox->currentText()).arg(ui->yearComboBox->currentText()) );

	paintTable(painter, currentPage);

	painter.setPen(Qt::black);
	painter.drawLine( startLineLeft,
					  startLineTop + lineHeight * (linesPerPage - 1),
					  startLineLeft + fontSize + userNameBoxWidth + fontSize + clientCodeBoxWidth + 400,
					  startLineTop + lineHeight * (linesPerPage - 1) );

	painter.drawText( startLineLeft, startLineTop + (linesPerPage * lineHeight), tr("Página %3 de %4").arg(currentPage).arg(pageCount) );
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

		int totalPages = (ui->tableWidget->rowCount() / rowsPerPage) + 1;
		for( int page = 0; page < totalPages; page++ )
		{
			paintPage( painter, page+1, totalPages );
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
			csv += QString("%1\t%2\t%3\t%4\n")
					.arg(ui->tableWidget->item(row, Columns::ColUserName)->text())
					.arg(ui->tableWidget->item(row, Columns::ColClientCode)->text())
					.arg(ui->tableWidget->item(row, Columns::ColServiceChange)->text())
					.arg(ui->tableWidget->item(row, Columns::ColProfileChange)->text());
		}
		f.write( csv.toLatin1() );
		f.flush();
		f.close();
		QMessageBox::information(this, tr("Exportando datos"), tr("Datos exportados") );
	}
}
