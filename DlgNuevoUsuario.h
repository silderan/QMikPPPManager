#ifndef DLGNUEVOUSUARIO_H
#define DLGNUEVOUSUARIO_H

#include <QDialog>
#include "Comm.h"
#include "QSecretData.h"

namespace Ui
{
	class DlgNuevoUsuario;
}

class DlgNuevoUsuario : public QDialog
{
	Q_OBJECT
	Ui::DlgNuevoUsuario *ui;
	ROS::Comm *mktAPI;
	QSecretDataModel &m_secrets;
	QSecretData m_secret;

	static bool checkRequiredField(QWidget *papi, const QString &fieldName, const QString &fieldTxt);
	static bool checkSpaces(QWidget *papi, const QString &fieldName, const QString &fieldTxt);
	static bool checkInvalidChars(QWidget *papi, const QString &fieldName, const QString &fieldTxt, const QString &invalidChars);
	static bool checkValidChars(QWidget *papi, const QString &fieldName, const QString &fieldTxt, QString validChars);
	static bool checkFieldMinSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int minSize);
	static bool checkFieldFixSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int fixedSize);
	static bool checkFieldMaxSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int maxSize);
	static bool checkValidEMail(const QString &email);

	static bool checkField(QWidget *papi, const QString &fieldName, const QString &fieldTxt, bool spaces,
						const QString &invalidChars, const QString &validChars,
						int minSize, int fixedSize, int maxSize);

	void checkEditables();
public:
	explicit DlgNuevoUsuario(ROS::Comm *api, const QSecretData &sd, QSecretDataModel &secrets, QWidget *parent = 0);
	~DlgNuevoUsuario();

	static bool checkValidUsername(QWidget *papi, const QString &user);
	static bool checkValidPassword(QWidget *papi, const QString &pass);
	static bool checkValidClientName(QWidget *papi, const QString &client);
	static bool checkValidDirection(QWidget *papi, const QString &direction);
	static bool checkValidPhoneNumber(QWidget *papi, const QString &phone);
	static bool checkValidCity(QWidget *papi, const QString &city);
	static bool checkValidEMail(QWidget *papi, const QString &email);
	static bool checkValidSSID(QWidget *papi, const QString &ssid);
	static bool checkValidWPA(QWidget *papi, const QString &wpa);
	static bool checkValidInstalador(QWidget *papi, const QString &ins);
	static bool checkValidComercial(QWidget *papi, const QString &ins);

public slots:
	void onReceive(const ROS::QSentence &s);

private slots:
	void on_btCerrar_clicked();
	void on_btCrear_clicked();
};

#endif // DLGNUEVOUSUARIO_H
