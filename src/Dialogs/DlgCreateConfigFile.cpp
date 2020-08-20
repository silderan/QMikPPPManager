/**************************************************************************

  Copyright 2015-2020 Rafael Dellà Bort. silderan (at) gmail (dot) com

  This file is part of MuNeDO (Multiple Network Device Observer)

  MuNeDO is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  MuNeDO is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  and GNU Lesser General Public License. along with MuNeDO.
  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************/
#include "DlgCreateConfigFile.h"
#include "ui_DlgCreateConfigFile.h"
#include <QFile>
#include <QDir>

#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>

#include "../ROSData/ROSSecret.h"
#include "../Utils/Utils.h"

void DlgCreateConfigFile::fillTemplateFiles()
{
	ui->templateComboBox->clear();
	ui->templateComboBox->addItem("Escoge plantilla");
	QDir templateDir( templatePath() );
	int extDot, fileDot;
	for( const QString &file : templateDir.entryList(QDir::Files) )
	{
		for( extDot = file.length()-1; extDot > 0; --extDot )
		{
			if( file.at(extDot) == '.' )
			{
				for( fileDot = extDot-1; fileDot > 0; --fileDot )
				{
					if( file.at(fileDot) == '.' )
					{
						QString desc = file.mid(0, fileDot);
						QString outFile = file.mid(fileDot+1);
						ui->templateComboBox->addItem(desc, outFile);
						break;
					}
				}
				break;
			}
		}
		if( (extDot <= 1) || (fileDot <= 1) )
			qWarning() << "File" << file << " has no valid file name to be a template config file. This must be with the form 'description.default_out_file.ext";
	}
}

void DlgCreateConfigFile::clearTableAndOutFile()
{
	ui->valuesTable->setRowCount(0);
	ui->outFileLineEdit->clear();
}

void DlgCreateConfigFile::appendRow(const QString &desc, const QString &name, const QString &value)
{
	int row = ui->valuesTable->rowCount();
	ui->valuesTable->insertRow( row );
	QTableWidgetItem *nameItem = new QTableWidgetItem(desc);
	nameItem->setData(Qt::UserRole, name);
	ui->valuesTable->setItem( row, 0, nameItem );
	ui->valuesTable->setItem( row, 1, new QTableWidgetItem(value) );
}

QString DlgCreateConfigFile::value(const QString &name)
{
	for( int row = ui->valuesTable->rowCount()-1; row>=0; --row )
	{
		if( ui->valuesTable->item(row, 0)->data(Qt::UserRole).toString() == name )
			return ui->valuesTable->item(row, 1)->text();
	}
	return QString();
}

QString DlgCreateConfigFile::templatePath()
{
	return QString("%1/%2").arg(QDir::currentPath()).arg("templates");
}

QString DlgCreateConfigFile::templateFile(const QString &desc, const QString &fileName)
{
	return QString("%1/%2.%3").arg(templatePath()).arg(desc).arg(fileName);
}

DlgCreateConfigFile::DlgCreateConfigFile(const ROSPPPSecret *rosSecret, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgCreateConfigFile)
	, mRosSecret(rosSecret)
{
	ui->setupUi(this);
	fillTemplateFiles();
}

DlgCreateConfigFile::~DlgCreateConfigFile()
{
	delete ui;
}

void DlgCreateConfigFile::on_templateComboBox_currentIndexChanged(int index)
{
	clearTableAndOutFile();
	if( index > 0 )
	{
		ui->outFileLineEdit->setText(ui->templateComboBox->itemData(index).toString());
		QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
		ui->outPathLineEdit->setText(paths.count() ? paths.at(0) : "");

		QFile file(templateFile(ui->templateComboBox->itemText(index), ui->templateComboBox->itemData(index).toString()));
		if( !file.open(QIODevice::ReadOnly) )
		{
			qWarning() << "File" << file << " cannot be opened";
			return;
		}
		QString str = QString::fromLatin1(file.readAll());
		QStringList list;

		QRegExp rx("\\{\\{([^:]+)\\:([^:]+)\\:([^:]*)\\}\\}");
		for( int pos = 0; (pos = rx.indexIn(str, pos)) != -1; pos += rx.matchedLength() )
		{
			QString desc =  rx.cap(1);
			QString nombre = rx.cap(2);
			QString valor = rx.cap(3);
			if( mRosSecret )
			{
				if( nombre == "pppoe_uname" )			valor = mRosSecret->userName();
				else if( nombre == "pppoe_upass" )		valor = mRosSecret->userPass();

				else if( nombre == "ont_sn" )			valor = mRosSecret->ontSN();

				else if( nombre == "wifi2_ssid" )		valor = mRosSecret->wifi2SSID();
				else if( nombre == "wifi2_wpa2" )		valor = mRosSecret->wifi2WPA();
				else if( nombre == "wifi5_ssid" )		valor = mRosSecret->wifi5SSID();
				else if( nombre == "wifi5_wpa2" )		valor = mRosSecret->wifi5WPA();
			}
			appendRow(desc, nombre, valor);
		}
		ui->createButton->setEnabled(true);
	}
	else
		ui->createButton->setEnabled(false);
}

void DlgCreateConfigFile::on_choosePathButton_clicked()
{
	ui->outPathLineEdit->setText(QFileDialog::getExistingDirectory(this, "Carpeta donde colocar el fichero", ui->outPathLineEdit->text()));
}

void DlgCreateConfigFile::on_createButton_clicked()
{
	int index = ui->templateComboBox->currentIndex();
	if( index > 0 )
	{
		ui->outFileLineEdit->setText(ui->templateComboBox->itemData(index).toString());
		QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
		ui->outPathLineEdit->setText(paths.count() ? paths.at(0) : "");

		QFile file(templateFile(ui->templateComboBox->itemText(index), ui->templateComboBox->itemData(index).toString()));
		if( !file.open(QIODevice::ReadOnly) )
		{
			qWarning() << "File" << file << " cannot be opened";
			return;
		}
		QString str = QString::fromLatin1(file.readAll());
		QString out;

		QRegExp rx("\\{\\{([^:]+)\\:([^:]+)\\:([^:]*)\\}\\}");
		int ini = 0;
		int pos = 0;
		while( (pos = rx.indexIn(str, pos)) != -1 )
		{
			QString nombre = rx.cap(2);
			QString newValue = value(rx.cap(2));
			if( !newValue.isEmpty() )
			{
				out += str.mid(ini, pos-ini);
				out += newValue;
				ini = pos + rx.matchedLength();
			}
			else
			{
				Utils::raiseWarning(this, tr("Falta el valor para %1").arg(rx.cap(1)) );
				return ;
			}
			pos += rx.matchedLength();
		}
		out += str.mid(ini, pos-ini);
		QFile outFile( QString("%1/%2").arg(ui->outPathLineEdit->text()).arg(ui->outFileLineEdit->text()) );
		if( !outFile.open(QIODevice::WriteOnly) )
		{
			qWarning() << "File" << outFile << " cannot be opened to write";
			return;
		}
		outFile.write( out.toLatin1() );
	}
}
