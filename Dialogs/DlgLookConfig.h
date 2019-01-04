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
