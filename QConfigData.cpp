#include "QConfigData.h"

const QString QConfigData::tagSecret = "Secret";
const QString QConfigData::tagPerfil = "Perfil";
const QString QConfigData::tagActivo = "Activo";
const QString QConfigData::tagCambio = "Cambio";
const QString QConfigData::tagNuevo = "Nuevo";
const QString QConfigData::tagAPIUser = "APIUser";

QConfigData gGlobalConfig;


QComboBox *QConfigData::setupCBPerfiles(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, perfiles().nombres());
}

QComboBox *QConfigData::setupCBPerfilesUsables(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, perfilesUsables());
}

QComboBox *QConfigData::setupCBInstaladores(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, instaladores() );
}

void QConfigData::select(QComboBox *cb, const QString &str)
{
	int i = cb->findText(str);
	if( i != -1 )
		cb->setCurrentIndex(i);
	else
		cb->setCurrentText(str);
}

QComboBox *QConfigData::setupComboBox(QComboBox *cb, bool editable, const QString &select, const QStringList &items)
{
	cb->setEditable(editable);
	cb->addItems(items);
	QConfigData::select(cb, select);
	return cb;
}
