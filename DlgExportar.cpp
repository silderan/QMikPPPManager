#include "DlgExportar.h"
#include "ui_DlgExportar.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "QConfigData.h"

DlgExportar::DlgExportar(QWidget *parent, const QSecretDataTable *secrets) :
	QDialog(parent),
	ui(new Ui::DlgExportar)
{
	ui->setupUi(this);
	ui->twTabla->setColumnCount(6);
	ui->twTabla->setHorizontalHeaderLabels(
				QStringList() << "CCliente" << "Contrato" << "Perfil" << "Nombre Cliente" << "Direción" << "Población");
	ui->leFichero->setText(gGlobalConfig.exportFile());

	for( int i = 0, r = 0; i < secrets->count(); i++ )
	{
		if( !secrets->isRowHidden(i) )
		{
			ui->twTabla->insertRow( r );
			ui->twTabla->setItem( r, 0, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColCCliente)->text()) );
			ui->twTabla->setItem( r, 1, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColContrato)->text()) );
			ui->twTabla->setItem( r, 2, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColPerfil)->text()) );
			ui->twTabla->setItem( r, 3, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColNombre)->text()) );
			ui->twTabla->setItem( r, 4, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColDireccion)->text()) );
			ui->twTabla->setItem( r, 5, new QTableWidgetItem(secrets->secrets().item(i,QSecretDataModel::ColPoblacion)->text()) );
			r++;
		}
	}
}

DlgExportar::~DlgExportar()
{
	delete ui;
}

void DlgExportar::on_btExportar_clicked()
{
	if( ui->leFichero->text().isEmpty() )
	{
		on_btFichero_clicked();
		if( ui->leFichero->text().isEmpty() )
			return;
	}
	QFile f(ui->leFichero->text());
	if( !f.open(QIODevice::WriteOnly) )
	{
		QMessageBox::warning(this, tr("Exportando datos"),
							 tr("No se ha podido abrir el fichero %1 en modo escritura para exportar los datos.\n"
								"Quizá el nombre fichero esté mal escrito o no tienes permiso de escritura sobre él"
								"o sobre la carpeta que lo contiene.").arg(ui->leFichero->text()));
		return;
	}
	QTextStream out(&f);

	for( int i = 0; i < ui->twTabla->rowCount(); i++ )
	{
		out << QString("%1\t%2\t%3\t%4\t%5\t%6\n").arg(
				   ui->twTabla->item(i, 0)->text(),
				   ui->twTabla->item(i, 1)->text(),
				   ui->twTabla->item(i, 2)->text(),
				   ui->twTabla->item(i, 3)->text(),
				   ui->twTabla->item(i, 4)->text(),
				   ui->twTabla->item(i, 5)->text());
	}
	gGlobalConfig.setExportFile(ui->leFichero->text());
	QMessageBox::information(this, objectName(), tr("Datos exportados.\n"));
}

#include <QFileDialog>
void DlgExportar::on_btFichero_clicked()
{
	QString file = QFileDialog::getSaveFileName(this, objectName(), ui->leFichero->text(), QString("Tablas (.tsv)"));
	if( file.isEmpty() )
		return;
	if( !file.endsWith(".tsv") )
	{
		if( file.endsWith(".") )
			file.append("tsv");
		else
			file.append(".tsv");
	}
	ui->leFichero->setText(file);
}

#include <QDesktopServices>
#include <QProcess>
void DlgExportar::on_pbAbrirCarpeta_clicked()
{
	QString pathIn = QDir::toNativeSeparators(ui->leFichero->text());
	if( ui->leFichero->text().isEmpty() )
	{
		QMessageBox::warning(this, objectName(), tr("No hay ningún fichero para poder mostrar"));
		return;
	}
	// Mac, Windows support folder or file.
#if defined(Q_OS_WIN)
	QProcess::startDetached( QString("explorer.exe /select,\"%1\"").arg(pathIn));
#elif defined(Q_OS_MAC)
	QStringList scriptArgs;
	scriptArgs << QLatin1String("-e")
			   << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
									 .arg(pathIn);
	QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
	scriptArgs.clear();
	scriptArgs << QLatin1String("-e")
			   << QLatin1String("tell application \"Finder\" to activate");
	QProcess::execute("/usr/bin/osascript", scriptArgs);
#else
	// we cannot select a file here, because no file browser really supports it...
	const QFileInfo fileInfo(pathIn);
	const QString folder = fileInfo.absoluteFilePath();
	const QString app = Utils::UnixUtils::fileBrowser(Core::ICore::instance()->settings());
	QProcess browserProc;
	const QString browserArgs = Utils::UnixUtils::substituteFileBrowserParameters(app, folder);
	if (debug)
		qDebug() <<  browserArgs;
	bool success = browserProc.startDetached(browserArgs);
	const QString error = QString::fromLocal8Bit(browserProc.readAllStandardError());
	success = success && error.isEmpty();
	if (!success)
		showGraphicalShellError(this, app, error);
#endif
}


void DlgExportar::on_btAbrirFichero_clicked()
{
	if( ui->leFichero->text().isEmpty() )
		QMessageBox::warning(this, objectName(), tr("No hay ningún fichero para poderlo abrir"));
	else
		QDesktopServices::openUrl( QUrl::fromLocalFile(ui->leFichero->text()) );
}
