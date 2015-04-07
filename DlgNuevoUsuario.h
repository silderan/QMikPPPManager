#ifndef DLGNUEVOUSUARIO_H
#define DLGNUEVOUSUARIO_H

#include <QDialog>
#include "Comm.h"

namespace Ui
{
	class DlgNuevoUsuario;
}

class DlgNuevoUsuario : public QDialog
{
	Q_OBJECT
	Ui::DlgNuevoUsuario *ui;
	ROS::Comm *mktAPI;
	ROS::QSentence s;

	bool checkRequiredField(const QString &fieldName, const QString &fieldTxt);
	bool checkSpaces(const QString &fieldName, const QString &fieldTxt);
	bool checkInvalidChars(const QString &fieldName, const QString &fieldTxt, const QString &invalidChars);
	bool checkValidChars(const QString &fieldName, const QString &fieldTxt, const QString &validChars);
	bool checkFieldMinSize(const QString &fieldName, const QString &fieldTxt, int minSize);
	bool checkFieldFixSize(const QString &fieldName, const QString &fieldTxt, int fixedSize);
	bool checkFieldMaxSize(const QString &fieldName, const QString &fieldTxt, int maxSize);

	bool checkField(const QString &fieldName, const QString &fieldTxt,
					bool required, bool spaces,
					const QString &invalidChars, const QString &validChars,
					int minSize, int fixedSize, int maxSize);
public:
	explicit DlgNuevoUsuario(ROS::Comm *api, QWidget *parent = 0);
	~DlgNuevoUsuario();

private slots:
	void on_btCerrar_clicked();
	bool on_btCrear_clicked();
};

#endif // DLGNUEVOUSUARIO_H
