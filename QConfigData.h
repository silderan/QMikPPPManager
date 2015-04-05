#ifndef QCONFIGDATA_H
#define QCONFIGDATA_H
#include "QIniFile.h"
#include <QStringList>

#define IPV4_TO_UINT(_A, _B, _C, _D)	((quint32)(((((quint8)_A)&255)<<24)+((((quint8)_B)&255)<<16)+((((quint8)_C)&255)<<8)+(((quint8)_D)&255)))
#define UINT_TO_IPV4A(_IPV4_)			((((quint32)_IPV4_)>>24)&255)
#define UINT_TO_IPV4B(_IPV4_)			((((quint32)_IPV4_)>>16)&255)
#define UINT_TO_IPV4C(_IPV4_)			((((quint32)_IPV4_)>>8)&255)
#define UINT_TO_IPV4D(_IPV4_)			(((quint32)_IPV4_)&255)

class QConfigData
{
	QString configFName;
	QIniData iniData;

public:
	void defaults()
	{
		setRemoteHost("192.168.1.1");
		setRemotePort(8728);
		setUserName("admin");
		setUserPass("");
		setPerfilInactivo("SinAcceso");
		setPerfilBasico("5/1");
		setTamFuente(8);
		setAlturaLinea(17);
		setDeIPV4(192,168,1,50);
		setAIPV4(192,168,1,254);
	}

	QConfigData() : configFName("config.ini")
	{
		defaults();
	}
	~QConfigData()
	{
		save();
	}
	void load() { QIniFile::load(configFName, &iniData); }
	void save() const { QIniFile::save(configFName, iniData); }

	void setRemoteHost(const QString &host) { iniData["RemoteHost"] = host; }
	QString remoteHost() const { return iniData["RemoteHost"]; }

	void setRemotePort(const quint16 &port) { iniData["RemotePort"] = QString("%1").arg(port); }
	quint16 remotePort() const { return iniData["RemotePort"].toUShort(); }

	void setUserName(const QString &uname) { iniData["UserName"] = uname;	}
	QString getUserName() const { return iniData["UserName"]; }

	void setUserPass(const QString &upass) { iniData["UserPass"] = upass;	}
	QString getUserPass() const { return iniData["UserPass"]; }

	void setPerfilInactivo(const QString &p) { iniData["PerfilInactivo"] = p; }
	QString getPerfilInactivo() const { return iniData["PerfilInactivo"]; }

	void setPerfilBasico(const QString &p) { iniData["PerfilBasico"] = p; }
	QString getPerfilBasico() const { return iniData["PerfilBasico"]; }

	void setTamFuente(int s) { iniData["TamFuente"] = QString("%1").arg(s); }
	int tamFuente() const { return iniData["TamFuente"].toInt(); }

	void setAlturaLinea(int s) { iniData["AlturaLinea"] = QString("%1").arg(s); }
	int alturaLinea() const { return iniData["AlturaLinea"].toInt(); }

	void setDeIPV4(quint32 ip) { iniData["DeIPV4"] = QString("%1").arg(ip); }
	void setDeIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setDeIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 deIPV4() const { return iniData["DeIPV4"].toUInt(); }
	void setAIPV4(quint32 ip) { iniData["AIPV4"] = QString("%1").arg(ip); }
	void setAIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setAIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 aIPV4() const { return iniData["AIPV4"].toUInt(); }

	void setInstaladores(const QStringList &l) { iniData["Instaladores"] = l.join(","); }
	QStringList instaladores() const { return iniData["Instaladores"].split(","); }
	void addInstalador(const QString &i)
	{
		QStringList ins = instaladores();
		ins.append(i);
		setInstaladores(ins);
	}
};

extern QConfigData gGlobalConfig;

#endif // QCONFIGDATA_H
