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

QComboBox *QConfigData::setupCBVendedores(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, true, select, comerciales() );
}

QComboBox *QConfigData::setupCBIPsPublicas(QComboBox *cb, const QStringList &ipsUsadas, const QString &ipActual)
{
	cb->addItem("IP dinámica"); // El primer elemento será para borrar la IP estática

	for( quint32 ip = gGlobalConfig.deIPV4(); ip <= gGlobalConfig.aIPV4(); ip++ )
	{
		QString sip = UINT_TO_SIPV4(ip);
		if( !ipsUsadas.contains(sip) || (sip == ipActual) )
			cb->addItem(sip);
	}
	select(cb, ipActual);
	return cb;
}

QComboBox *QConfigData::setupCBPoblaciones(QComboBox *cb, const QStringList &poblaciones, const QString &poblacion)
{
	return setupComboBox(cb, true, poblacion, poblaciones);
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

void QConfigData::save() const
{
	QIniFile::save(m_userFName, m_userData);
	if( nivelUsuario() > Instalador )
		QIniFile::save(m_rosFName, m_rosData);
}

quint32 QConfigData::toVIPV4(const QString &sip)
{
	QStringList slip = sip.split('.');
	quint32 vip = 0;
	if( slip.count() == 4 )
	{
		vip = ((slip[0].toInt()<<24)&0xFF) +
			  ((slip[1].toInt()<<16)&0xFF) +
			  ((slip[2].toInt()<<8)&0xFF) +
			  (slip[3].toInt()&0xFF);
	}
	return vip;
}

bool QConfigData::esIPEstatica(quint32 vip) const
{
	if( deIPV4() > vip )
		return false;
	if( aIPV4() < vip )
		return false;
	return true;
}

bool QConfigData::esIPEstatica(const QString &sip) const
{
	return esIPEstatica(toVIPV4(sip));
}
