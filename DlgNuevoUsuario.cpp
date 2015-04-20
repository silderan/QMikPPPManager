#include "DlgNuevoUsuario.h"
#include "ui_DlgNuevoUsuario.h"

#include "QConfigData.h"

DlgNuevoUsuario::DlgNuevoUsuario(ROS::Comm *api, const QSecretData &sd, QSecretDataModel &secrets, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgNuevoUsuario), mktAPI(api), m_secrets(secrets), m_secret(sd)
{
	ui->setupUi(this);
	gGlobalConfig.setupCBPerfilesUsables(ui->cbPerfil, sd.perfilOriginal().isEmpty() ? gGlobalConfig.perfilBasico():sd.perfilOriginal());
	gGlobalConfig.setupCBInstaladores(ui->cbInstalador, sd.instalador().isEmpty() ? gGlobalConfig.userName() : sd.instalador());
	gGlobalConfig.setupCBPoblaciones(ui->cbPoblacion, secrets.poblaciones(), sd.poblacion());
	gGlobalConfig.setupCBIPsPublicas(ui->cbIPPublica, secrets.ipsEstaticas(), sd.IPEstatica());
	gGlobalConfig.setupCBVendedores(ui->cbComercial, sd.comercial());

	ui->leUser->setText(sd.usuario());
	ui->lePass->setText(sd.contra());
	ui->leNombre->setText(sd.nombre());
	ui->leDireccion->setText(sd.direccion());
	ui->leEmail->setText(sd.email());
	ui->leNotas->setText(sd.notas());
	ui->leSSID->setText(sd.SSID());
	ui->leTelefonos->setText(sd.telefonos());
	ui->leWPass->setText(sd.wPass());

	ui->chVozIP->setChecked(sd.VozIP());

	checkEditables();
}

DlgNuevoUsuario::~DlgNuevoUsuario()
{
	delete ui;
}

bool DlgNuevoUsuario::checkValidUsername(QWidget *papi, const QString &user)
{
	return checkField(papi, tr("Usuario"), user, true, "", "ASCII_", 10, 0, 20);
}

bool DlgNuevoUsuario::checkValidPassword(QWidget *papi, const QString &pass)
{
	return checkField(papi, tr("Contraseña"), pass, true, "", "0123456789", 0, 12, 0);
}

bool DlgNuevoUsuario::checkValidClientName(QWidget *papi, const QString &client)
{
	return checkField(papi, tr("Nombre"), client, false, "", "", 0, 0, 0);
}

bool DlgNuevoUsuario::checkValidDirection(QWidget *papi, const QString &direction)
{
	return checkField(papi, tr("Dirección"), direction, false, "", "", 5, 0, 0);
}

bool DlgNuevoUsuario::checkValidPhoneNumber(QWidget *papi, const QString &phone)
{
	return checkField(papi, tr("Teléfonos"), phone, true, "", "0123456789,", 9, 0, 0);
}

bool DlgNuevoUsuario::checkValidCity(QWidget *papi, const QString &city)
{
	return checkField(papi, tr("Población"), city, false, "", "", 5, 0, 0);
}

bool DlgNuevoUsuario::checkValidEMail(const QString &email)
{
	int i = email.indexOf('@');
	if( (i == 0) || (i == -1) || (i == (email.count()-1)) )
		return false;
	if( email.count('@') != 1 )
		return false;
	if( (i == 0) || (i == -1) || (i == (email.count()-1)) )
		return false;
	return true;
}

#include <QMessageBox>
bool DlgNuevoUsuario::checkValidEMail(QWidget *papi, const QString &email)
{
	if( !checkField(papi, tr("Correo electrónico"), email, true, "", "ASCII@._", 5, 0, 0) )
		return false;
	if( checkValidEMail(email) )
		return true;
	QMessageBox::warning(papi,
						 papi->windowTitle(),
						 tr("El correo electrónico no es válido"));
	return false;
}

bool DlgNuevoUsuario::checkValidSSID(QWidget *papi, const QString &ssid)
{
	return checkField(papi, tr("SSID"), ssid, true, "", "ASCII_-", 4, 0, 0);
}

bool DlgNuevoUsuario::checkValidWPA(QWidget *papi, const QString &wpa)
{
	return checkField(papi, tr("Contraseña WiFi"), wpa, true, "", "ASCII_-", 8, 0, 0);
}

bool DlgNuevoUsuario::checkValidInstalador(QWidget *papi, const QString &ins)
{
	return gGlobalConfig.instaladores().isEmpty() || checkField(papi, tr("Instalador"), ins, false, "", "", 4, 0, 0);
}

bool DlgNuevoUsuario::checkValidComercial(QWidget *papi, const QString &com)
{
	return com.isEmpty() || checkField(papi, tr("Comercial"), com, false, "", "", 0, 0, 25);
}

void DlgNuevoUsuario::onReceive(const ROS::QSentence &s)
{
	checkEditables();
	if( s.getResultType() == ROS::QSentence::Done )
	{
		if( !s.attribute("ret").isEmpty() )
			m_secret.setSecretID(s.attribute("ret"));

		m_secrets.addSecret(m_secret, true);
	}
	else
		QMessageBox::warning(this, windowTitle(), tr("Error añadiendo usuario: %1").arg(s.attribute("message")));
}

bool DlgNuevoUsuario::checkRequiredField(QWidget *papi, const QString &fieldName, const QString &fieldTxt)
{
	if( fieldTxt.isEmpty() )
	{
		QMessageBox::warning(papi,
							 papi->windowTitle(),
							 tr("El campo '%1' debe contener un valor válido").arg(fieldName));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkSpaces(QWidget *papi, const QString &fieldName, const QString &fieldTxt)
{
	if( fieldTxt.contains(" ") )
	{
		QMessageBox::warning(papi,
							 papi->windowTitle(),
							 tr("El campo '%1' no puede contener espacios en blanco").arg(fieldName));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkInvalidChars(QWidget *papi, const QString &fieldName, const QString &fieldTxt, const QString &invalidChars)
{
	foreach( QChar c, invalidChars )
		if( fieldTxt.contains(c) )
		{
			QMessageBox::warning(papi,
								 papi->windowTitle(),
								 tr("El campo '%1' no puede contener el caracter %2").arg(fieldName).arg(c));
			return false;
		}
	return true;
}

bool DlgNuevoUsuario::checkValidChars(QWidget *papi, const QString &fieldName, const QString &fieldTxt, QString validChars)
{
	bool ASCIIAllowed = validChars.startsWith("ASCII");
	if( ASCIIAllowed )
		validChars = validChars.mid(5);
	foreach( QChar qc, fieldTxt )
	{
		if( ASCIIAllowed )
		{
			char c = qc.toLatin1();
			if( (c >= '0') && (c <= '9') )
				continue;
			if( (c >= 'A') && (c <= 'Z') )
				continue;
			if( (c >= 'a') && (c <= 'z') )
				continue;
		}
		if( !validChars.contains(qc) )
		{
			QMessageBox::warning(papi,
								 papi->windowTitle(),
								 tr("El campo '%1' no puede contener el caracter %2").arg(fieldName).arg(qc));
			return false;
		}
	}
	return true;
}

bool DlgNuevoUsuario::checkFieldMinSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int minSize)
{
	if( fieldTxt.count() < minSize )
	{
		QMessageBox::warning(papi,
							 papi->windowTitle(),
							 tr("El campo '%1' no puede tener menos de %2 caracteres").arg(fieldName).arg(minSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkFieldFixSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int fixedSize)
{
	if( fieldTxt.count() != fixedSize )
	{
		QMessageBox::warning(papi,
							 papi->windowTitle(),
							 tr("El campo '%1' debe contener exactamente %2 caracteres").arg(fieldName).arg(fixedSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkFieldMaxSize(QWidget *papi, const QString &fieldName, const QString &fieldTxt, int maxSize)
{
	if( fieldTxt.count() > maxSize )
	{
		QMessageBox::warning(papi,
							 papi->windowTitle(),
							 tr("El campo '%1' no puede tener más de %2 caracteres").arg(fieldName).arg(maxSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkField(QWidget *papi, const QString &fieldName, const QString &fieldTxt, bool spaces, const QString &invalidChars, const QString &validChars, int minSize, int fixSize, int maxSize)
{
	if( !checkRequiredField(papi, fieldName, fieldTxt) )
		return false;
	if( spaces && !checkSpaces(papi, fieldName, fieldTxt) )
		return false;
	if( invalidChars.count() && !checkInvalidChars(papi, fieldName, fieldTxt, invalidChars) )
		return false;
	if( validChars.count() && !checkValidChars(papi, fieldName, fieldTxt, validChars) )
		return false;
	if( minSize && !checkFieldMinSize(papi, fieldName, fieldTxt, minSize) )
		return false;
	if( fixSize && !checkFieldFixSize(papi, fieldName, fieldTxt, fixSize) )
		return false;
	if( maxSize && !checkFieldMaxSize(papi, fieldName, fieldTxt, maxSize) )
		return false;
	return true;
}

void DlgNuevoUsuario::checkEditables()
{
	if( m_secret.sesionID().isEmpty() )
	{
		ui->leUser->setEnabled(true);
		ui->lePass->setEnabled(true);
		ui->lbText->setText("");
		ui->btCrear->setText("Crear nuevo");
	}
	else
	{
		ui->leUser->setEnabled(false);
		ui->lePass->setEnabled(false);
		ui->lbText->setText( tr("(OjO)\n¡No puedes modificar los datos de login porque el usuario está activo!") );
		ui->btCrear->setText("Modificar");
	}
}

void DlgNuevoUsuario::on_btCerrar_clicked()
{
	reject();
}

void DlgNuevoUsuario::on_btCrear_clicked()
{
	if( (m_secret.secretID().isEmpty() || (m_secret.usuario() != ui->leUser->text())) && !checkValidUsername(this, ui->leUser->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.contra() != ui->lePass->text())) && !checkValidPassword(this, ui->lePass->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.nombre() != ui->leNombre->text())) && !checkValidClientName(this, ui->leNombre->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.direccion() != ui->leDireccion->text())) && !checkValidDirection(this, ui->leDireccion->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.poblacion() != ui->cbPoblacion->currentText())) && !checkValidCity(this, ui->cbPoblacion->currentText()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.email() != ui->leEmail->text())) && !checkValidEMail(this, ui->leEmail->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.telefonos() != ui->leTelefonos->text())) && !checkValidPhoneNumber(this, ui->leTelefonos->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.SSID() != ui->leSSID->text())) && !checkValidSSID(this, ui->leSSID->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.instalador() != ui->cbInstalador->currentText())) && !checkValidInstalador(this, ui->cbInstalador->currentText()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.wPass() != ui->leWPass->text())) && !checkValidWPA(this, ui->leWPass->text()) )
		return;
	if( (m_secret.secretID().isEmpty() || (m_secret.comercial() != ui->cbComercial->currentText())) && !checkValidComercial(this, ui->cbComercial->currentText()) )
		return;

	m_secret.setUsuario(ui->leUser->text());
	m_secret.setContra(ui->lePass->text());
	m_secret.setPerfilOriginal(ui->cbPerfil->currentText());
	if( ui->cbIPPublica->currentIndex() > 0 )
		m_secret.setIPEstatica(ui->cbIPPublica->currentText());
	m_secret.setNombre(ui->leNombre->text());
	m_secret.setDireccion(ui->leDireccion->text());
	m_secret.setPoblacion(ui->cbPoblacion->currentText());
	m_secret.setEmail(ui->leEmail->text());
	m_secret.setInstalador(ui->cbInstalador->currentText());
	m_secret.setTelefonos(ui->leTelefonos->text());
	m_secret.setSSID(ui->leSSID->text());
	m_secret.setWPass(ui->leWPass->text());
	m_secret.setVozIP(ui->chVozIP->isChecked());
	m_secret.setComercial(ui->cbComercial->currentText());
	if( !ui->leNotas->text().isEmpty() )
		m_secret.setNotas(ui->leNotas->text());

	ROS::QSentence s;
	m_secret.toSentence(&s);

	if( m_secret.secretID().isEmpty() )
		s.setCommand("/ppp/secret/add");
	else
		s.setCommand("/ppp/secret/set");

	s.setTag( gGlobalConfig.tagNuevo );
	s.setID( m_secret.secretID() );
	mktAPI->sendSentence(s);
}
