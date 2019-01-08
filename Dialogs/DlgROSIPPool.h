#ifndef DLGROSIPPOOL_H
#define DLGROSIPPOOL_H

#include <QDialog>

namespace Ui {
class DlgROSIPPool;
}

class DlgROSIPPool : public QDialog
{
	Q_OBJECT

public:
	explicit DlgROSIPPool(QWidget *parent = nullptr);
	~DlgROSIPPool();

private slots:
	void on_closeButton_clicked();

private:
	Ui::DlgROSIPPool *ui;
};

#endif // DLGROSIPPOOL_H
