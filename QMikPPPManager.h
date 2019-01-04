#ifndef QMIKPPPMANAGER_H
#define QMIKPPPMANAGER_H

#include <QMainWindow>

#include "ROSMultiConnectorManager.h"
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
#include "DlgCnfgConnect.h"
#include "DlgROSAPIUsers.h"

#include "ROSAPIUser.h"

namespace Ui
{
	class QMikPPPManager;
}

class QMikPPPManager : public QMainWindow
{
	Q_OBJECT
	Ui::QMikPPPManager *ui;
	DlgNuevoUsuario *dlgNuevoUsuario;
	DlgCnfgConnect dlgCnfgConnect;
	DlgROSAPIUsers dlgROSAPIUsers;

	QString createRouterName(const ConnectInfo &conInfo)const;

	void requestROSAPIUsers(const QString &routerName);
	void requestROSAPIUserGroups(const QString &routerName);
	void pidePerfiles(const QString &routerName);
	void pideUsuarios(const QString &routerName);
	void pideCambios(const QString &routerName);
	void pideActivos(const QString &routerName);
	void addSecret(const ROS::QSentence &s);
	void addSecretToTable(const QSecretData &s, int row);
	void onAPIUserInfoRecibida(const QString &routerName, const ROS::QSentence &s);
	void onPPPoEUsersReceived(const QString &routerName, const ROS::QSentence &s);
	void onPerfilRecibido(const QString &routerName, const ROS::QSentence &s);
	void onActivoRecibido(const QString &routerName, const ROS::QSentence &s);

	void actualizaUsuario(const QString &routerName, const ROS::QSentence &s);

	void reiniciaConexionRemota(QSecretData *sd);
	void actualizaComentariosRemoto(QSecretData *sd);
	void actualizaPerfilRemoto(QSecretData *sd);
	void actualizaIPRemota(QSecretData *sd);

	void setNivelUsuario(QConfigData::NivelUsuario lvl);
	void filtraFilas();

	bool codigoClienteValido(const QString &code, const QSecretData *sdOri);

	bool checkRouterUsersIntegrity()const;
	void onAllROSAPIUsersReceived();

private slots:
	void setStatusText(QString errorString, const QString routerName = QString());
	void onComError(const QString &errorString, const QString &routerName);

	void onRouterConnected(const QString &routerName);
	void onAllRoutersConnected();
	void onRouterDisconnected(const QString &routerName);
	void onAllRoutersDisconnected();
	void onLogued(const QString &routerName);


	void onDatoModificado(QSecretDataModel::Columnas col, const QString &dato, const QString &id, bool *isValid);
	void onDobleClicUsuario(const QSecretData &sd);
	void onClicUsuario(const QSecretData &sd);

	void on_leFiltro_textChanged(const QString &);
	void on_cbFiltro_currentIndexChanged(int);

	void on_connectButton_clicked();
	void on_exportButton_clicked();
	void on_portScanButton_clicked();
	void on_localConfigButton_clicked();
	void on_connectionConfigButton_clicked();
	void on_advancedConfigButton_clicked();
	void on_addUserButton_clicked();

	void on_disconnectButton_clicked();

	void on_apiUsersButton_clicked();

public slots:
	void onOneAPIUsersReceived(const QString &routerName, ROSAPIUser *apiUser);
	void onAllAPIUsersReceived(const QString &routerName);
	void onAPIUsersErrorReceived(const QString &routerName, const QString &errorString);

	void onOneAPIUsersGroupReceived(const QString &routerName, ROSAPIUsersGroup *apiUsersGroup);
	void onAllAPIUsersGroupsReceived(const QString &routerName);
	void onAPIUsersGroupsErrorReceived(const QString &routerName, const QString &errorString);

	void updateConfig();

public:
	explicit QMikPPPManager(QWidget *parent = Q_NULLPTR);
	~QMikPPPManager();
};

#endif // QMIKPPPMANAGER_H
