#ifndef DLGVOIPDATA_H
#define DLGVOIPDATA_H

#include <QDialog>

namespace Ui
{
	class DlgVoIPData;
}

class QTableWidgetItem;
class VoIPData;
class QROSSecretTableWidget;

class DlgVoIPData : public QDialog
{
	Q_OBJECT
	Ui::DlgVoIPData *ui;

	QROSSecretTableWidget &mRosSecretTable;

	bool validCell(int row, int col);
	bool validRow(int row);
	bool validTable();
	void addRow(const VoIPData &voipData);

public:
	DlgVoIPData(QROSSecretTableWidget &rosSecretTable, QWidget *parent = nullptr);
	~DlgVoIPData();

private slots:
	void on_addButton_clicked();
	void on_delButton_clicked();
	void on_acceptButton_clicked();

	void on_exportButton_clicked();

private:
};

#endif // DLGVOIPDATA_H
