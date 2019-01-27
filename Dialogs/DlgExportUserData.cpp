#include "DlgExportUserData.h"
#include "ui_DlgExportUserData.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFile>

#include "ConfigData/QConfigData.h"

DlgExportUserData::DlgExportUserData(QList<QStringList> exportData, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgExportUserData)
	, m_exportData(exportData)
{
	ui->setupUi(this);

	ui->exportFileLineEdit->setText( gGlobalConfig.exportFile() );
	if( m_exportData.count() != 0 )
	{
		QString t = tr("Exportar %1 usuario%2").arg(m_exportData.count()).arg( (m_exportData.count()>1) ? "s" : "" );
		setWindowTitle( t );
	}
	else
	{
		setWindowTitle( tr("Exportando datos de usuarios (ninguno disponible)") );
		ui->exportFileButton->setDisabled(true);
	}
}

DlgExportUserData::~DlgExportUserData()
{
	delete ui;
}

void DlgExportUserData::exportData(QList<QStringList> exportData, QWidget *papi)
{
	DlgExportUserData dlg(exportData, papi);
	dlg.exec();
}

#include <QFileDialog>
void DlgExportUserData::on_exportFileButton_clicked()
{
	QString file = QFileDialog::getSaveFileName(this, objectName(), ui->exportFileLineEdit->text(), QString("Tablas (.tsv)"));
	if( file.isEmpty() )
		return;
	if( !file.endsWith(".tsv") )
	{
		if( file.endsWith(".") )
			file.append("tsv");
		else
			file.append(".tsv");
	}
	ui->exportFileLineEdit->setText(file);
}

void DlgExportUserData::on_exportUsersDataButton_clicked()
{
	if( ui->exportFileLineEdit->text().isEmpty() )
	{
		on_exportFileButton_clicked();
		if( ui->exportFileLineEdit->text().isEmpty() )
			return;
	}
	QFile f(ui->exportFileLineEdit->text());
	if( !f.open(QIODevice::WriteOnly) )
	{
		QMessageBox::warning(this, tr("Exportando datos"),
							 tr("No se ha podido abrir el fichero %1 en modo escritura para exportar los datos.\n"
								"Quizá el nombre fichero esté mal escrito o no tienes permiso de escritura sobre él"
								"o sobre la carpeta que lo contiene.").arg(ui->exportFileLineEdit->text()));
		return;
	}
	QTextStream out(&f);

	foreach( const QStringList &data, m_exportData )
		out << data.join('\t') << "\n";

	gGlobalConfig.setExportFile(ui->exportFileLineEdit->text());
	QMessageBox::information(this, objectName(), tr("Datos exportados.\n"));
}

#include <QDesktopServices>
#include <QProcess>
void DlgExportUserData::on_openFileButton_clicked()
{
	if( ui->exportFileLineEdit->text().isEmpty() )
		QMessageBox::warning(this, objectName(), tr("No hay ningún fichero para poderlo abrir"));
	else
		QDesktopServices::openUrl( QUrl::fromLocalFile(ui->exportFileLineEdit->text()) );
}

void DlgExportUserData::on_openFolderButton_clicked()
{
	QString pathIn = QDir::toNativeSeparators(ui->exportFileLineEdit->text());
	if( ui->exportFileLineEdit->text().isEmpty() )
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
