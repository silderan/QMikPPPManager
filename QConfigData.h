#ifndef QCONFIGDATA_H
#define QCONFIGDATA_H
#include "QIniFile.h"
#include <QString>

class QConfigData
{
	QString configFName;
	QIniData iniData;

public:
	void defaults()
	{
		iniData["remoteHost"] = "192.168.1.1";
		iniData["remotePort"] = QString("%1").arg(8728);
		iniData["username"] = "admin";
		iniData["userpass"] = "";
		iniData["inactProf"] = "SinAcceso";
		iniData["basicProf"] = "5/1";
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

	void setHost(const QString &host) { iniData["remoteHost"] = host; }
	QString getHost() const { return iniData["remoteHost"]; }

	void setPort(const quint16 &port) { iniData["remotePort"] = QString("%1").arg(port); }
	quint16 getPort() const { return iniData["remotePort"].toUShort(); }

	void setUserName(const QString &uname) { iniData["username"] = uname;	}
	QString getUserName() const { return iniData["username"]; }

	void setUserPass(const QString &upass) { iniData["userpass"] = upass;	}
	QString getUserPass() const { return iniData["userpass"]; }

	void setPerfilInactivo(const QString &p) { iniData["inactProf"] = p; }
	QString getPerfilInactivo() const { return iniData["inactProf"]; }

	void setPerfilBasico(const QString &p) { iniData["basicProf"] = p; }
	QString getPerfilBasico() const { return iniData["basicProf"]; }
};

extern QConfigData gGlobalConfig;

#endif // QCONFIGDATA_H
