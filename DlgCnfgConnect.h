#ifndef DLGCNFGCONNECT_H
#define DLGCNFGCONNECT_H

#include <QDialog>

#include "QConfigData.h"

namespace Ui
{
	class DlgCnfgConnect;
}

class DlgCnfgConnect : public QDialog
{
    Q_OBJECT
	Ui::DlgCnfgConnect *ui;

	void setup();
	bool checkData();
	void copyDataToGlobalConfig();

public:
	explicit DlgCnfgConnect(QWidget *parent = Q_NULLPTR);
    ~DlgCnfgConnect();

private slots:
	void addRow( int row = -1, const QString &hostAddr = QString(), quint16 hostPort = 8728);
	void removeCurrentRow();
	void on_connectButton_clicked();
	void on_acceptButton_clicked();
	void on_cancelButton_clicked();

public slots:
	void show();

signals:
	void connectToHosts();
	void globalConfigChanged();
};

#endif // DLGCNFGCONNECT_H
