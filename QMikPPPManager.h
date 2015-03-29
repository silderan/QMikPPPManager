#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>
#include "Comm.h"
#include "QSentences.h"
#include "QIniFile.h"
#include <QTreeWidgetItem>
#include <QComboBox>

namespace Ui
{
class QMikPPPManager;
}

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
};

extern QConfigData gGlobalConfig;

class QMikPPPManager : public QMainWindow
{
	Q_OBJECT
	Ui::QMikPPPManager *ui;
	ROS::Comm mktAPI;
	QStringList perfiles;
	QString tagPerfiles;
	QString tagUsuarios;
	QString tagListening;
	enum Estado
	{
		Desconectado,
		ReciviendoUsuarios,
		UsuariosRecividos
	}estado;

	QComboBox *newListaPerfiles(const ROS::QSentence &s);
	void pidePerfiles();
	void pideUsuarios();
	void pideCambios();
	void addLogText(const QString &txt);
	void addUsuario(const ROS::QSentence &s);
	void onUsuarioRecibido(const ROS::QSentence &s);
	void addPerfil(const ROS::QSentence &s);
	void onPerfilRecibido(const ROS::QSentence &s);
	void actualizaUsuario(const ROS::QSentence &s);

private slots:
	void on_pbConnect_clicked();
	void onLoginRequest(QString *user, QString *pass);
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onReceive(ROS::QSentence &s);
	void onStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);
	void onNewProfileSelected(const QString &profileName);

public:
	explicit QMikPPPManager(QWidget *parent = 0);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
