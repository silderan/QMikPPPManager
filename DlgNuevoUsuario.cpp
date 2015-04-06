#include "DlgNuevoUsuario.h"
#include "ui_DlgNuevoUsuario.h"

DlgNuevoUsuario::DlgNuevoUsuario(ROS::Comm *api, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgNuevoUsuario), mktAPI(api)
{
	ui->setupUi(this);
}

DlgNuevoUsuario::~DlgNuevoUsuario()
{
	delete ui;
}
#include <QMessageBox>

bool DlgNuevoUsuario::checkRequiredField(const QString &fieldName, const QString &fieldTxt)
{
	if( fieldTxt.isEmpty() )
	{
		QMessageBox::warning(this,
							 tr("Creando usuario nuevo"),
							 tr("El campo %1 debe contener un valor válido").arg(fieldName));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkSpaces(const QString &fieldName, const QString &fieldTxt)
{
	if( fieldTxt.contains(" ") )
	{
		QMessageBox::warning(this,
							 tr("Creando usuario nuevo"),
							 tr("El campo %1 no puede contener espacios en blanco").arg(fieldName));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkInvalidChars(const QString &fieldName, const QString &fieldTxt, const QString &invalidChars)
{
	foreach( QChar c, invalidChars )
		if( fieldTxt.contains(c) )
		{
			QMessageBox::warning(this,
								 tr("Creando usuario nuevo"),
								 tr("El campo %1 no puede contener el caracter %2").arg(fieldName).arg(c));
			return false;
		}
	return true;
}

bool DlgNuevoUsuario::checkValidChars(const QString &fieldName, const QString &fieldTxt, const QString &validChars)
{
	foreach( QChar c, fieldTxt )
		if( !validChars.contains(c) )
		{
			QMessageBox::warning(this,
								 tr("Creando usuario nuevo"),
								 tr("El campo %1 no puede contener el caracter %2").arg(fieldName).arg(c));
			return false;
		}
	return true;
}

bool DlgNuevoUsuario::checkFieldMinSize(const QString &fieldName, const QString &fieldTxt, int minSize)
{
	if( fieldTxt.count() < minSize )
	{
		QMessageBox::warning(this,
							 tr("Creando usuario nuevo"),
							 tr("El campo %1 no puede tener menos de %2 caracteres").arg(fieldName).arg(minSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkFieldFixSize(const QString &fieldName, const QString &fieldTxt, int fixedSize)
{
	if( fieldTxt.count() < fixedSize )
	{
		QMessageBox::warning(this,
							 tr("Creando usuario nuevo"),
							 tr("El campo %1 debe contener exactamente %2 caracteres").arg(fieldName).arg(fixedSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkFieldMaxSize(const QString &fieldName, const QString &fieldTxt, int maxSize)
{
	if( fieldTxt.count() < maxSize )
	{
		QMessageBox::warning(this,
							 tr("Creando usuario nuevo"),
							 tr("El campo %1 no puede tener más de %2 caracteres").arg(fieldName).arg(maxSize));
		return false;
	}
	return true;
}

bool DlgNuevoUsuario::checkField(const QString &fieldName, const QString &fieldTxt, bool required, bool spaces, const QString &invalidChars, const QString &validChars, int minSize, int fixSize, int maxSize)
{
	if( required && !checkRequiredField(fieldName, fieldTxt) )
		return false;
	if( spaces && !checkSpaces(fieldName, fieldTxt) )
		return false;
	if( invalidChars.count() && !checkInvalidChars(fieldName, fieldTxt, invalidChars) )
		return false;
	if( validChars.count() && !checkValidChars(fieldName, fieldTxt, validChars) )
		return false;
	if( minSize && checkFieldMinSize(fieldName, fieldTxt, minSize) )
		return false;
	if( fixSize && checkFieldFixSize(fieldName, fieldTxt, fixSize) )
		return false;
	if( maxSize && checkFieldMaxSize(fieldName, fieldTxt, maxSize) )
		return false;
	return true;
}

void DlgNuevoUsuario::on_btCerrar_clicked()
{
	s.setCommand("/ppp/secret/add");
}

void DlgNuevoUsuario::on_btCrear_clicked()
{
	if( !checkField(tr("Nombre de usuario"), ui->leUser->text(), true, true, "'?¿¡!\"·$%&/()=^*{},;.:-ªº\\ñÑ", "", 10, 0, 15) )
		return false;

	if( !checkField(tr("Contraseña"), ui->lePass->text(), true, true, "", "0123456789", 0, 12, 0) )
		return false;

	if( !checkField(tr("Nombre del cliente"), ui->leNombre->text(), true, false, "", "", 0, 0, 0) )
		return false;

	if( !checkField(tr("Nombre del cliente"), ui->leNombre->text(), true, false, "", "", 0, 0, 0) )
		return false;

	s.addAttribute("name", ui->leUser);
}
