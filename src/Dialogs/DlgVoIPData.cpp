#include "DlgVoIPData.h"
#include "ui_DlgVoIPData.h"

#include <QTableWidgetItem>
#include <QMessageBox>

#include "../ConfigData/VoIPData.h"
#include "../Widgets/QROSSecretTableWidget.h"

#include "DlgExportUserData.h"

enum Columns
{
	ColPhone,
	ColSIPUsername,
	ColSIPPassword,
	ColSIPServer,
	ColUsername,
	ColClientName,
	ColComments,
	ColCount
};

const QStringList columnNames = QStringList() << QObject::tr("Teléfono")
											  << QObject::tr("Usuario SIP")
											  << QObject::tr("Contraseña SIP")
											  << QObject::tr("Servidor SIP")
											  << QObject::tr("Usuario")
											  << QObject::tr("Nombre cliente")
											  << QObject::tr("Notas");

DlgVoIPData::DlgVoIPData(QROSSecretTableWidget &rosSecretTable, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgVoIPData)
	, mRosSecretTable(rosSecretTable)
{
	ui->setupUi(this);


	ui->voipTable->setColumnCount(Columns::ColCount);
	ui->voipTable->setHorizontalHeaderLabels( columnNames );

	for( const VoIPData &d : gVoipData )
		addRow(d);
}

DlgVoIPData::~DlgVoIPData()
{
	delete ui;
}


bool DlgVoIPData::validCell(int row, int col)
{
	if( ui->voipTable->item(row, col)->text().isEmpty() )
	{
		QMessageBox::warning(this, this->windowTitle(), tr("La columna %1 en la fila %2 no tiene nada escrito")
							 .arg(columnNames.at(col))
							 .arg(row+1) );
		return false;
	}
	return true;
}

bool DlgVoIPData::validRow(int row)
{
	return	validCell(row, Columns::ColPhone) &&
			validCell(row, Columns::ColSIPUsername) &&
			validCell(row, Columns::ColSIPPassword) &&
			validCell(row, Columns::ColSIPServer) ;
}

bool DlgVoIPData::validTable()
{
	for( int row = 0; row < ui->voipTable->rowCount(); ++row )
		if( !validRow(row) )
			return false;
	return true;
}

void DlgVoIPData::addRow(const VoIPData &voipData)
{
	int row = ui->voipTable->rowCount();
	QTableWidgetItem *item;

	ui->voipTable->insertRow(row);
	ui->voipTable->setItem( row, Columns::ColPhone, new QTableWidgetItem(voipData.mSipPhone) );
	ui->voipTable->setItem( row, Columns::ColSIPUsername, new QTableWidgetItem(voipData.mSipUsername) );
	ui->voipTable->setItem( row, Columns::ColSIPPassword, new QTableWidgetItem(voipData.mSipPassword) );
	ui->voipTable->setItem( row, Columns::ColSIPServer, new QTableWidgetItem(voipData.mSipServer) );
	ui->voipTable->setItem( row, Columns::ColUsername, new QTableWidgetItem(voipData.mSecretUsername) );
	ui->voipTable->setItem( row, Columns::ColComments, new QTableWidgetItem(voipData.mComments) );

	const ROSPPPSecret *rosSecret = mRosSecretTable.rosPppSecret(voipData.mSecretUsername);
	ui->voipTable->setItem( row, Columns::ColClientName, item = new QTableWidgetItem( (rosSecret && rosSecret->isValid()) ? rosSecret->clientName() : "" ) );
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
}

void DlgVoIPData::on_addButton_clicked()
{
	addRow(VoIPData());
}

void DlgVoIPData::on_delButton_clicked()
{
	int row = ui->voipTable->currentRow();
	if( row != -1 )
	{
		if( QMessageBox::warning(this, tr("Borrando cuenta SIP para VoIP"),
								 tr("Borrar una cuenta SIP se debe hacer en casos donde se ha recibido una petición de portabilidad por parte de otra empresa porque el cliente cambia de operador.\n"
									"Por lo tanto, el teléfono %1 que ahora tiene el cliente %2 (%3) quedara borrado y ya no podrá ser asignado a otro cliente.\n\n"
									"¿Es este el caso y puedo proceder al borrado de la cuenta?")
								 .arg(ui->voipTable->item(row, Columns::ColPhone)->text())
								 .arg(ui->voipTable->item(row, Columns::ColUsername)->text())
								 .arg(ui->voipTable->item(row, Columns::ColClientName)->text()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes )
		{
			ui->voipTable->removeRow(row);
			QMessageBox::information(this, tr("Borrando cuenta SIP"),
							tr("Teléfono %1 borrado.\n\n"
							   "Para que el cambio sea efectivo, debes salir de este diálogo con el botón de Aceptar.")
									 .arg(ui->voipTable->item(row, Columns::ColPhone)->text()) );
		}
	}
}

void DlgVoIPData::on_acceptButton_clicked()
{
	if( !validTable() )
		return;

	gVoipData.save( QString("%1").arg(QDateTime::currentDateTime().toTime_t()) );
	gVoipData.clear();
	VoIPData voipData;
	for( int row = 0; row < ui->voipTable->rowCount(); row++ )
	{
		voipData.mSipPhone			= ui->voipTable->item(row, Columns::ColPhone)->text() ;
		voipData.mSipUsername		= ui->voipTable->item(row, Columns::ColSIPUsername)->text() ;
		voipData.mSipPassword		= ui->voipTable->item(row, Columns::ColSIPPassword)->text() ;
		voipData.mSipServer			= ui->voipTable->item(row, Columns::ColSIPServer)->text() ;
		voipData.mSecretUsername	= ui->voipTable->item(row, Columns::ColUsername)->text() ;
		voipData.mComments			= ui->voipTable->item(row, Columns::ColComments)->text() ;
		gVoipData.setVoipData(voipData);
	}
	gVoipData.save();
	accept();
}

void DlgVoIPData::on_exportButton_clicked()
{
	if( ui->voipTable->rowCount() )
	{
		QList<QStringList> exportData;
		for( int row = 0; row < ui->voipTable->rowCount(); row++ )
		{
			QStringList sipData = QStringList()
					<< ui->voipTable->item(row, Columns::ColPhone)->text()
					<< ui->voipTable->item(row, Columns::ColSIPUsername)->text()
					<< ui->voipTable->item(row, Columns::ColSIPPassword)->text()
					<< ui->voipTable->item(row, Columns::ColSIPServer)->text();

			if( ui->includeUsernameCheckbox->isChecked() )
				sipData.append( ui->voipTable->item(row, Columns::ColUsername)->text() );
			if( ui->includeClientnameCheckbox->isChecked() )
				sipData.append( ui->voipTable->item(row, Columns::ColClientName)->text() );
			if( ui->includeCommentsCheckbox->isChecked() )
				sipData.append( ui->voipTable->item(row, Columns::ColComments)->text() );

			exportData.append( sipData );
		}
		DlgExportUserData::exportData(exportData,
									  exportData.count() == 1 ?
										  tr("Exportando 1 cuenta SIP") :
										  tr("Exportando %1 cuentas SIP").arg(exportData.count()),
									  this);
	}
}
