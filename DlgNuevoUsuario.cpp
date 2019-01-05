#include "DlgNuevoUsuario.h"
#include "ui_DlgNuevoUsuario.h"

#include "Utils/QRegistro.h"

DlgNuevoUsuario::DlgNuevoUsuario(ROS::Comm *api, const QSecretData &sd, QSecretDataModel &secrets, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgNuevoUsuario), mktAPI(api), m_secrets(secrets), m_secret(sd)
{
	ui->setupUi(this);
	gGlobalConfig.setupCBPerfilesUsables( ui->cbPerfil, sd.perfilOriginal().isEmpty() ? gGlobalConfig.perfiles().defaultProfile().profileName() : sd.perfilOriginal() );
	gGlobalConfig.setupCBInstaladores( ui->cbInstalador, sd.secretID().isEmpty() ? gGlobalConfig.userName() : sd.instalador().isEmpty() ? "no-definido" : sd.instalador() );
	gGlobalConfig.setupCBPoblaciones(ui->cbPoblacion, secrets.poblaciones(), sd.poblacion());
	ui->cbIPPublica->setup(gGlobalConfig.staticIPv4Map(), secrets.ipsEstaticasUsadas(), IPv4(sd.IPEstatica()) );
	gGlobalConfig.setupCBVendedores(ui->cbComercial, sd.comercial());

	ui->leUser->setText(sd.usuario());
	if( sd.contra().isEmpty() )
		on_btPass_clicked();
	else
		ui->lePass->setText(sd.contra());
	ui->leNombre->setText(sd.nombre());
	ui->leDireccion->setText(sd.direccion());
	ui->leEmail->setText(sd.email());
	ui->leNotas->setText(sd.notas());
	ui->leSSID->setText(sd.SSID());
	ui->leTelefonos->setText(sd.telefonos());
	ui->leWPass->setText(sd.wPass());

	ui->chVozIP->setChecked(sd.usaIPPublica(IPPUBLICA_VOZIP));
	ui->chDVR->setChecked(sd.usaIPPublica(IPPUBLICA_DVR));
	ui->chPuertos->setChecked(sd.usaIPPublica(IPPUBLICA_PUERTOS));
	ui->chOtros->setChecked(sd.usaIPPublica(IPPUBLICA_OTROS));
	ui->leUser->setFocus();
	ui->leUser->selectAll();

	if( gGlobalConfig.nivelUsuario() < QConfigData::Instalador )
		this->setDisabled(true);
	updateDialog();
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
	if( !checkField(papi, tr("Correo electrónico"), email, true, "", "ASCII@._-", 5, 0, 0) )
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

void DlgNuevoUsuario::onSecretAdded(const ROS::QSentence &s)
{
	if( s.attribute("name") == m_secret.usuario() )
	{
		m_secret.setSecretID(s.getID());
		updateDialog();
	}
}

void DlgNuevoUsuario::onSecretDeleted(const ROS::QSentence &s)
{
	if( s.getID() == m_secret.secretID() )
	{
		m_secret.setSecretID( "" );
		updateDialog();
	}
}

void DlgNuevoUsuario::onActivoConectado(const ROS::QSentence &s)
{
	// Si se ha conectado el usuario que estamos editando ahora.
	if( s.attribute("name") == m_secret.usuario() )
	{
		m_secret.setSesionID( s.getID() );
		updateDialog();
	}
}

void DlgNuevoUsuario::onActivoDesconectado(const ROS::QSentence &s)
{
	// Si se ha desconectado el usuario que estamos editando ahora.
	if( !m_secret.sesionID().isEmpty() && (m_secret.sesionID() == s.getID()) )
	{
		m_secret.setSesionID( "" );
		updateDialog();
	}
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

void DlgNuevoUsuario::updateDialog()
{
	if( m_secret.sesionID().isEmpty() && m_secret.secretID().isEmpty() )
	{
		ui->leUser->setReadOnly(false);
		ui->lePass->setReadOnly(false);
		ui->cbPerfil->setEnabled(true);
		ui->btPass->setEnabled(true);
		ui->lbText->setText("");
		ui->cbIPPublica->setEnabled(true);
		ui->btCrear->setText(tr("Crear nuevo"));
		setWindowTitle(tr("Nuevo usuario"));
	}
	else
	if( m_secret.sesionID().isEmpty() )
	{
		ui->leUser->setReadOnly(false);
		ui->lePass->setReadOnly(false);
		ui->cbPerfil->setEnabled(true);
		ui->btPass->setEnabled(true);
		ui->lbText->setText("");
		ui->cbIPPublica->setEnabled(true);
		ui->btCrear->setText( tr("Modificar %1").arg(m_secret.secretID()) );
		setWindowTitle( tr("Modificando usuario desconectado [%1]").arg(m_secret.secretID()) );
	}
	else
	{
		ui->leUser->setReadOnly(true);
		ui->lePass->setReadOnly(true);
		ui->cbPerfil->setEnabled(false);
		ui->btPass->setEnabled(false);
		ui->cbIPPublica->setEnabled(false);
		ui->lbText->setText( tr("(OjO)\n¡No puedes modificar los datos de login porque el usuario está activo!\nPara ello, usa la ventana principal del programa.") );
		ui->btCrear->setText( tr("Modificar") );
		setWindowTitle( tr("Modificando usuario conectado [%1] (%2)").arg(m_secret.secretID(), m_secret.sesionID()) );
	}
}

QString DlgNuevoUsuario::contactInfo()
{
	/* Formato creado:
	 * <nombre> <User>/<Pass>
	 * <dirección> <Pueblo>
	 * <teléfonos>
	 * Contrato [alta/baja] de <perfil>. Estado actual [activo <fecha> /inactivo <fecha>]
	 * (Tiene VozIP, DVR, etc)
	 * (Notas)
	 * */
	QString txt = tr("%1 (%2/%3)\n").arg(ui->leNombre->text(), ui->leUser->text(), ui->lePass->text());
	txt.append(tr("%1. %2.\n").arg(ui->leDireccion->text(), ui->cbPoblacion->currentText()));
	txt.append( tr("%1\n").arg( ui->leTelefonos->text().isEmpty()? tr("Sin teléfonos conocidos.") : tr("Teléfono: %1").arg(ui->leTelefonos->text()) ) );

	if( m_secret.dadoDeBaja() )
		txt.append( tr("Contrato de %1 dado de baja.\n").arg(ui->cbPerfil->currentText()) );
	else
		txt.append( tr("Contrato de alta de %1.\n").arg(ui->cbPerfil->currentText()) );
	if( m_secret.conectado() )
		txt.append( tr("Router/Antena conectado con IP %1 hace %2\n").arg(m_secret.IPActiva(), m_secret.uptime()) );
	else
		txt.append( tr("Router/Antena no conectado desde %1\n").arg(m_secret.lastLogedOff()) );

	QDateTime dt = QDateTime::fromString( ui->lePass->text(), "ddMMyyyyhhmm" );
	if( (ui->lePass->text().count() == 12) && dt.isValid() )
		txt.append( tr("Instalado el %1 por %2.\n").arg(dt.toString("dd/MM/yyyy hh:mm"), ui->cbInstalador->currentText()));
	else
		txt.append( tr("Instalado por %1.\n").arg(ui->cbInstalador->currentText()) );

	if( ui->chDVR->isChecked() ||
		ui->chVozIP->isChecked() ||
		ui->chOtros->isChecked() ||
		ui->chPuertos->isChecked() )
	{
		txt.append( tr("El cliente requiere IP pública porque:\n") );
		if( ui->chDVR->isChecked() )
			txt.append( tr("Tiene equipos DVR.\n") );
		if( ui->chVozIP->isChecked() )
			txt.append( tr("Tiene telefonía VoIP.\n") );
		if( ui->chPuertos->isChecked() )
			txt.append( tr("Tiene puertos redirigidos.\n") );
		if( ui->chOtros->isChecked() )
			txt.append( tr("Razón desconocida.\n") );
	}
	if( ui->leSSID->text().isEmpty() )
		txt.append( tr("No tenemos información sobre su red WiFi\n") );
	else
		txt.append( tr("WiFi: SSID=%1 PASS=%2\n").arg(ui->leSSID->text(), ui->leWPass->text()) );
	txt.append( ui->leNotas->text() );
	return txt;
}

void DlgNuevoUsuario::on_btCerrar_clicked()
{
	reject();
}

void DlgNuevoUsuario::on_btCrear_clicked()
{
	QSecretData secretOld = m_secret;
	if( (m_secret.secretID().isEmpty() || (m_secret.instalador() != ui->cbInstalador->currentText())) && !checkValidInstalador(this, ui->cbInstalador->currentText()) )
		return;
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
	if( ui->grWiFi->isChecked() )
	{
		if( (m_secret.secretID().isEmpty() || (m_secret.SSID() != ui->leSSID->text())) && !checkValidSSID(this, ui->leSSID->text()) )
			return;
		if( (m_secret.secretID().isEmpty() || (m_secret.wPass() != ui->leWPass->text())) && !checkValidWPA(this, ui->leWPass->text()) )
			return;
	}
	else
	{
		m_secret.setSSID("");
		m_secret.setWPass("");
	}
	if( (m_secret.secretID().isEmpty() || (m_secret.comercial() != ui->cbComercial->currentText())) && !checkValidComercial(this, ui->cbComercial->currentText()) )
		return;

	m_secret.setUsuario(ui->leUser->text());
	m_secret.setContra(ui->lePass->text());
	m_secret.setPerfilOriginal(ui->cbPerfil->currentText());
	if( ui->cbIPPublica->currentIndex() > 0 )
		m_secret.setIPEstatica(ui->cbIPPublica->currentText());
	else
		m_secret.setIPEstatica("");
	m_secret.setNombre(ui->leNombre->text());
	m_secret.setDireccion(ui->leDireccion->text());
	m_secret.setPoblacion(ui->cbPoblacion->currentText());
	m_secret.setEmail(ui->leEmail->text());
	m_secret.setInstalador(ui->cbInstalador->currentText());
	m_secret.setTelefonos(ui->leTelefonos->text());
	m_secret.setSSID(ui->leSSID->text());
	m_secret.setWPass(ui->leWPass->text());
	m_secret.setFlagUsaIPPublica(ui->chVozIP->isChecked(), IPPUBLICA_VOZIP);
	m_secret.setFlagUsaIPPublica(ui->chPuertos->isChecked(), IPPUBLICA_PUERTOS);
	m_secret.setFlagUsaIPPublica(ui->chDVR->isChecked(), IPPUBLICA_DVR);
	m_secret.setFlagUsaIPPublica(ui->chOtros->isChecked(), IPPUBLICA_OTROS);
	m_secret.setComercial(ui->cbComercial->currentText());
	if( !ui->leNotas->text().isEmpty() )
		m_secret.setNotas(ui->leNotas->text());

	ROS::QSentence s;
	m_secret.toSentence(&s);

	if( m_secret.secretID().isEmpty() )
	{
		s.setCommand("/ppp/secret/add");
		logService.addRegistro(m_secret, tr("Creado nuevo usuario con perfil %1").arg(m_secret.perfilOriginal()));
	}
	else
	{
		s.setCommand("/ppp/secret/set");
		logService.registraCambios(secretOld, m_secret);
	}

	s.setTag( gGlobalConfig.tagNuevo );
	s.setID( m_secret.secretID() );
	mktAPI->sendSentence(s);
}

#include <QDateTime>
void DlgNuevoUsuario::on_btPass_clicked()
{
	QDateTime d = QDateTime::currentDateTime();

	QString str = d.toString("ddMMyyyyhhmm");
	ui->lePass->setText(str);
}


#include <QGuiApplication>
#include <QClipboard>
void DlgNuevoUsuario::on_btUserCopy_clicked()
{
	QClipboard *cb = QGuiApplication::clipboard();
	cb->setText(ui->leUser->text());
	ui->leUser->setFocus();
	ui->leUser->selectAll();
}

void DlgNuevoUsuario::on_btPassCopy_clicked()
{
	QClipboard *cb = QGuiApplication::clipboard();
	cb->setText(ui->lePass->text());
	ui->lePass->setFocus();
	ui->lePass->selectAll();
}

void DlgNuevoUsuario::on_btCopyContactInfo_clicked()
{
	QGuiApplication::clipboard()->setText(contactInfo());
}

void DlgNuevoUsuario::on_btShowContactInfo_clicked()
{
	QMessageBox::information(this, tr("Información de %1 (%2)").arg(ui->leNombre->text(), ui->leUser->text()),
							 contactInfo());
}
