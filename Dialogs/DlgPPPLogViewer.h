#ifndef DLGPPPLOGVIEWER_H
#define DLGPPPLOGVIEWER_H

#include <QDialog>

#include "Utils/QPPPLogger.h"

namespace Ui
{
	class DlgPPPLogViewer;
}

class DlgPPPLogViewer : public QDialog
{
	Q_OBJECT
	Ui::DlgPPPLogViewer *ui;

public:
	explicit DlgPPPLogViewer(const QString &userName = QString(), QWidget *parent = Q_NULLPTR);
	~DlgPPPLogViewer();
private slots:
	void on_compactLogsButton_clicked();
};

#endif // DLGPPPLOGVIEWER_H
