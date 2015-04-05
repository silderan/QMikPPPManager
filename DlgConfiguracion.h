#ifndef DLGCONFIGURACION_H
#define DLGCONFIGURACION_H

#include <QDialog>

#include "QConfigData.h"

namespace Ui
{
	class DlgConfiguracion;
}

class DlgConfiguracion : public QDialog
{
	Q_OBJECT

	Ui::DlgConfiguracion *ui;

public:
	explicit DlgConfiguracion(QWidget *parent = 0);
	~DlgConfiguracion();

private slots:
	void on_btAceptar_clicked();
	void on_btCancelar_clicked();
	void on_sbTamTxt_valueChanged(int arg1);
	void on_sbAltFilas_valueChanged(int arg1);
};

#endif // DLGCONFIGURACION_H
