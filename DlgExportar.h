#ifndef DLGEXPORTAR_H
#define DLGEXPORTAR_H

#include <QDialog>

#include "QSecretData.h"

namespace Ui
{
	class DlgExportar;
}

class DlgExportar : public QDialog
{
	Q_OBJECT
	Ui::DlgExportar *ui;

public:
	explicit DlgExportar(QWidget *parent, const QSecretDataTable *secrets);
	~DlgExportar();

private slots:
	void on_btExportar_clicked();
	void on_btFichero_clicked();
	void on_pbAbrirCarpeta_clicked();
	void on_btAbrirFichero_clicked();
};

#endif // DLGEXPORTAR_H
