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

#ifndef DLGLOOKCONFIG_H
#define DLGLOOKCONFIG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QTableWidgetItem>

#include "ConfigData/TableCellLook.h"

namespace Ui
{
	class DlgLookConfig;
}

class DlgLookConfig : public QDialog
{
	Q_OBJECT
	Ui::DlgLookConfig *ui;

	void updateCellLook(QTableWidgetItem *item, const CellLook &cellLook);
	void updateCellLook(int row, int col, const CellLook &cellLook);
	void updateTableCellLook();

	void retrieveCellLook(QTableWidgetItem *item, CellLook &cellLook);
	void retrieveTableCellLook();

public:
	explicit DlgLookConfig(QWidget *parent = Q_NULLPTR);
	~DlgLookConfig();

private slots:
	void onItemSelected();
	void updateCellLook(QTableWidgetItem *item);
	void updateTableFontSize(int size = -1);
	void updateTableRowHeight(int size = -1);
	void updateCurrentCellLook(int);

	void on_acceptButton_clicked();
	void on_cancelButton_clicked();
	void on_boldCheckBox_clicked();
	void on_italicCheckBox_clicked();
	void on_textColorButton_clicked();
	void on_textFontButton_clicked();
	void on_backColorButton_clicked();

private:
};

#endif // DLGLOOKCONFIG_H
