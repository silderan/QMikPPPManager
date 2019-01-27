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
