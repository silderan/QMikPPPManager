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

namespace Ui
{
class QMikPPPManager;
}

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
	enum columnas
	{
		ColUsuario,
		ColPerfil,
		ColEstado,
		ColNombre,
		ColDireccion,
		ColPoblacion,
		ColTelefonos,
		ColInstalador,
		ColNotas,
		NumColumnas
	};
	QSecretsList secretList;
	QStringList nombresColumnas;

	QTableWidgetItem *newTextItem(const QSecretData &s, const QString &txt);
	QComboBox *newListaPerfiles(const QSecretData &s);
	QCheckBox *newEstado(const QSecretData &s);
	void setCellData(int row, int col, const QSecretData &s, const QString &txt, QWidget*w);
	void pidePerfiles();
	void pideUsuarios();
	void pideCambios();
	void addLogText(const QString &txt);
	void addSecret(const ROS::QSentence &s);
	void addSecretToTable(const QSecretData &s, int row);
	void onUsuarioRecibido(const ROS::QSentence &s);
	void llenaTabla();
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
