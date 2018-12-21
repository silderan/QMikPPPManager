#ifndef DLGCONFIGURACION_H
#define DLGCONFIGURACION_H

#include <QDialog>

#include "QConfigData.h"
#include "ClientProfile.h"

namespace Ui
{
	class DlgConfiguracion;
}

class DlgConfiguracion : public QDialog
{
	Q_OBJECT

	Ui::DlgConfiguracion *ui;

	QStringList m_profilesGroupNameList;

	void addProfileTableRow(const ClientProfileData &clientProfileData);

public:
	explicit DlgConfiguracion(QWidget *parent = Q_NULLPTR);
	~DlgConfiguracion();

private slots:
	void on_cbEditingFinished();
	void on_btAceptar_clicked();
	void on_btCancelar_clicked();
	void on_sbTamTxt_valueChanged(int arg1);
	void on_sbAltFilas_valueChanged(int arg1);
};

#endif // DLGCONFIGURACION_H
