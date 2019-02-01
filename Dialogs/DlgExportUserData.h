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

#ifndef DLGEXPORTUSERDATA_H
#define DLGEXPORTUSERDATA_H

#include <QList>
#include <QStringList>
#include <QDialog>
#include <QTableWidget>

namespace Ui
{
	class DlgExportUserData;
}

class DlgExportUserData : public QDialog
{
	Q_OBJECT
	Ui::DlgExportUserData *ui;
	QList<QStringList> m_exportData;

public:
	explicit DlgExportUserData(QList<QStringList> exportData, QWidget *parent);
	~DlgExportUserData();

	static void exportData(QList<QStringList> exportData, QWidget *papi);
private slots:
	void on_exportFileButton_clicked();
	void on_exportUsersDataButton_clicked();
	void on_openFileButton_clicked();
	void on_openFolderButton_clicked();
};

#endif // DLGEXPORTUSERDATA_H
