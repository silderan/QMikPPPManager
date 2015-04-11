#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>
#include "Comm.h"
#include "QSecretData.h"
#include "QConfigData.h"
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QCheckBox>
#include "DlgNuevoUsuario.h"

namespace Ui
{
class QMikPPPManager;
}

class QMikPPPManager : public QMainWindow
{
	Q_OBJECT
	Ui::QMikPPPManager *ui;
	DlgNuevoUsuario *dlgNuevoUsuario;
	ROS::Comm mktAPI;
	QStringList perfiles;

	enum Estado
	{
		Desconectado,
		ReciviendoUsuarios,
		UsuariosRecividos
	}estado;
	QSecretsList secretList;

	void pideInfoUsuarioAPI();
	void pidePerfiles();
	void pideUsuarios();
	void pideCambios();
	void pideActivos();
	void addLogText(const QString &txt);
	void addSecret(const ROS::QSentence &s);
	void addSecretToTable(const QSecretData &s, int row);
	void onAPIUserInfoRecibida(const ROS::QSentence &s);
	void onUsuarioRecibido(const ROS::QSentence &s);
	void onPerfilRecibido(const ROS::QSentence &s);
	void onActivoRecibido(const ROS::QSentence &s);

	void actualizaUsuario(const ROS::QSentence &s);

	void reiniciaConexionRemota(QSecretData *sd);
	void actualizaComentariosRemoto(QSecretData *sd);
	void actualizaPerfilRemoto(QSecretData *sd);
	void actualizaIPRemota(QSecretData *sd);

	void setNivelUsuario(QConfigData::NivelUsuario lvl);
private slots:
	void on_pbConnect_clicked();
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onReceive(ROS::QSentence &s);
	void onStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

	void on_anyadeUsuario_clicked();
	void on_btConfig_clicked();

	void onDatoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &id);
public slots:
	void updateConfig();

public:
	explicit QMikPPPManager(QWidget *parent = 0);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
