#ifndef DLGPORTSCAN_H
#define DLGPORTSCAN_H

#include <QDialog>
#include <QProcess>

#include "QSecretData.h"

namespace Ui
{
	class DlgPortScan;
}

struct DeviceInfo
{
	QString IP;
	QList<int> tiempos;
	DeviceInfo(QString _IP) : IP(_IP)
	{	}
};

class QDeviceInfoList : public QList<DeviceInfo>
{
public:
	void addDeviceInfo(const QString &IP);
};

class DlgPortScan : public QDialog
{
	Q_OBJECT
	Ui::DlgPortScan *ui;
	QSecretDataTable *m_secrets;
	QDeviceInfoList deviceInfoList;
	QList<quint16> m_puertos;
	QList<QProcess*> procesos;
	// Valor que indica el "paso" que a comprobar.
	// Por ejemplo con una configuración de 2 puertos 2 dos intentos:
	// Paso 1 será la 1ª IP con el primer puerto y el primer intento.
	// Paso 2 será la 1ª IP con el primer puerto y el segundo intento.
	// Paso 3 será la 1ª IP con el segundo puerto y el primer intento.
	// Paso 4 será la 1ª IP con el segundo puerto y el segundo intento.
	// Paso 5 será la 2ª IP con el primer puerto y el primer intento.
	// Paso 6 será la 2ª IP con el primer puerto y el segundo intento.
	// Paso 7 será la 2ª IP con el segundo puerto y el primer intento.
	// Paso 8 será la 2ª IP con el segundo puerto y el segundo intento.
	qint32 m_paso, m_pasos;
	quint8 m_intentos;

	bool isRunning();
	bool isStopping();
	void onNewIPRangeClicked();
	void listarIPsArbitrarias();
	void listarIPsActivas();

	void procesaDatosGUI();
	void setupProgressBar();

	void addPuerto(quint16 p)	{ m_puertos.append(p);	}
	void clearPuertos()			{ m_puertos.clear();	}

	void pararEscaneo();
	void cancelarEscaneo();
	void crearListaProcesos();
	void calcularPasos();
	int siguientePaso();
	struct _InfoPaso
	{
		quint16 indice;	// El índice en la tabla.
		QString IP;
		quint16 puerto;
		quint8 intento;
		qint32 resultado;
	};

	_InfoPaso infoPaso(int paso);

public:
	explicit DlgPortScan(QWidget *parent, QSecretDataTable *secrets);
	~DlgPortScan();

private slots:
	void on_rdArbitrarias_clicked();
	void on_rbActivas_clicked();
	void on_lePuertos_textChanged(const QString &);
	void on_btIniciar_clicked();

private:
};

#endif // DLGPORTSCAN_H
