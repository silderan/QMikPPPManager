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
#include <QDesktopServices>
#include <QUrl>
#include <QInputEvent>
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

	void pideInfoUsuarioAPI();
	void pidePerfiles();
	void pideUsuarios();
	void pideCambios();
	void pideActivos();
	void setStatusText(const QString &txt);
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
	void filtraFilas();

	bool codigoClienteValido(const QString &code, const QSecretData *sdOri);
private slots:
	void on_pbConnect_clicked();
	void onComError(ROS::Comm::CommError, QAbstractSocket::SocketError);
	void onReceive(ROS::QSentence &s);
	void onStateChanged(ROS::Comm::CommState s);
	void onLoginChanged(ROS::Comm::LoginState s);

	void on_anyadeUsuario_clicked();
	void on_btConfig_clicked();

	void onDatoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &id, bool *isValid);
	void onDobleClicUsuario(const QSecretData &sd);
	void onClicUsuario(const QSecretData &sd);
	void on_leFiltro_textChanged(const QString &);

	void on_cbFiltro_currentIndexChanged(int);

	void on_btExportar_clicked();

	void on_btPortScan_clicked();

public slots:
	void updateConfig();

public:
	explicit QMikPPPManager(QWidget *parent = 0);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
