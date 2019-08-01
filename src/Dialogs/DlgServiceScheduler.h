#ifndef DLGSERVICESCHEDULER_H
#define DLGSERVICESCHEDULER_H

#include <QDialog>

class ROSMultiConnectManager;
class QROSSecretTableWidget;

namespace Ui
{
	class DlgServiceScheduler;
}

class DlgServiceScheduler : public QDialog
{
	Q_OBJECT
	Ui::DlgServiceScheduler *ui;
	ROSMultiConnectManager &mRosMultiConnectManager;
	QROSSecretTableWidget &mRosSecretTable;

	void changeSelection(bool newSel);

	void paintLine(QPainter &painter, int line, const QString &userName, const QString &clientCode, const QString &changeDescription);
	void paintTable(QPainter &painter, int firstRow, int lastRow);
	void paintPage(QPainter &painter, int currentPage, int pageCount, int firstRow, int lastRow);

public:
	explicit DlgServiceScheduler(ROSMultiConnectManager &rosMultiConnectManager, QROSSecretTableWidget &rosSecretTable, QWidget *parent = nullptr);
	~DlgServiceScheduler();


private slots:
	void updateTable(int = 0);

	void on_selectAllButton_clicked();
	void on_unselectAllButton_clicked();
	void on_applyButton_clicked();
	void on_printButton_clicked();
	void on_exportButton_clicked();

};

#endif // DLGSERVICESCHEDULER_H
