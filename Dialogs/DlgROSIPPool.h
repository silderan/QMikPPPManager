#ifndef DLGROSIPPOOL_H
#define DLGROSIPPOOL_H

#include <QDialog>

#include "../ROSData/ROSIPPool.h"

namespace Ui
{
	class DlgROSIPPool;
}

class DlgROSIPPool : public QDialog
{
	Q_OBJECT

	Ui::DlgROSIPPool *ui;

public:
	explicit DlgROSIPPool(QWidget *parent = Q_NULLPTR);
	~DlgROSIPPool();

	void onDataReceived(const ROSDataBase &rosData);

private slots:
	void on_closeButton_clicked();
};

#endif // DLGROSIPPOOL_H
