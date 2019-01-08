#ifndef DLGROSIPPOOL_H
#define DLGROSIPPOOL_H

#include <QDialog>

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

private slots:
	void on_closeButton_clicked();
};

#endif // DLGROSIPPOOL_H
