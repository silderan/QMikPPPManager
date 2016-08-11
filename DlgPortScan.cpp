#include "DlgPortScan.h"
#include "ui_DlgPortScan.h"

#include <QMessageBox>


void QDeviceInfoList::addDeviceInfo(const QString &IP)
{
	append(DeviceInfo(IP));
}

DlgPortScan::DlgPortScan(QWidget *parent, QSecretDataTable *secrets) :
	QDialog(parent), ui(new Ui::DlgPortScan),
	m_secrets(secrets)
{
	ui->setupUi(this);
}


DlgPortScan::~DlgPortScan()
{
	delete ui;
}

void DlgPortScan::on_rdArbitrarias_clicked()
{
	onNewIPRangeClicked();
}

void DlgPortScan::on_rbActivas_clicked()
{
	onNewIPRangeClicked();
}

// Debe retornar true cuando el escaneo está en marcha para proteger de cambios las estructuras.
bool DlgPortScan::isRunning()
{
	return ui->btIniciar->text() != "Iniciar";
}

bool DlgPortScan::isStopping()
{
	return ui->btIniciar->text() == "Cancelar";
}

void DlgPortScan::onNewIPRangeClicked()
{
	if( isRunning() )
		return;

	if( ui->rdArbitrarias->isChecked() )
		listarIPsArbitrarias();
	else
		listarIPsActivas();
}

void DlgPortScan::listarIPsActivas()
{
	if( isRunning() )
		return;

	QString IP;
	deviceInfoList.clear();
	ui->tbResultados->clear();
	ui->tbResultados->setColumnCount(2);
	ui->tbResultados->setHorizontalHeaderLabels( QStringList() << "Usuario" << "IP" );
	for( int i = 0, r = 0; i < m_secrets->count(); i++ )
	{
		if( !(IP = m_secrets->secrets().secretData(i)->IPActiva()).isEmpty() )
		{
			deviceInfoList.append(DeviceInfo(IP));
			ui->tbResultados->insertRow(r);
			ui->tbResultados->setItem( r, 0, new QTableWidgetItem(m_secrets->secrets().secretData(i)->usuario()) );
			ui->tbResultados->setItem( r++, 1, new QTableWidgetItem(IP) );
		}
	}
	setupProgressBar();
}

void DlgPortScan::listarIPsArbitrarias()
{
	if( isRunning() )
		return;

	deviceInfoList.clear();
	ui->tbResultados->clear();
	ui->tbResultados->setColumnCount(2);
	ui->tbResultados->setHorizontalHeaderLabels( QStringList() << "Usuario" << "IP" );

	// ToDo: Rellenar las listas de IP y la tabla.
	setupProgressBar();
}

void DlgPortScan::procesaDatosGUI()
{
	if( isRunning() )
		return;

	QStringList puertos = ui->lePuertos->text().split(",");
	quint16 p;
	clearPuertos();
	for( int i = 0; i < puertos.count(); i++ )
	{
		if( !(puertos[i] = puertos[i].trimmed()).isEmpty() &&
			((p = quint16(puertos[i].toInt())) > 0) &&
			!(m_puertos().contains(p)) )
		{
			addPuerto(p);
		}
	}
	// TODO: Comprobar si el valor es válido?
	intentos = ui->sbIntentos->value();
	pasos = deviceInfoList.count() * puertos.count() * intentos;
}

void DlgPortScan::setupProgressBar()
{
	if( pasos > 0 )
	{
		ui->pbProgreso->setMaximum(m);
		ui->pbProgreso->setValue(0);
	}
	else
	{
		ui->pbProgreso->setMaximum(0);
		ui->pbProgreso->setValue(0);
	}
}

void DlgPortScan::pararEscaneo()
{

}

void DlgPortScan::cancelarEscaneo()
{

}

void DlgPortScan::crearListaProcesos()
{
	// ToDo: En vez de borrar y crear de nuevo, sería más eficiente añadir si faltan o borrar si sobran.
	while( procesos.count() )
		procesos.takeAt(0)->deleteLater();

	for( int i = 0; ui->sbTareas->value()-1; i-- )
		procesos.append(new QProcess(this));
}

void DlgPortScan::calcularPasos()
{
	pasos = deviceInfoList.count() * m_puertos.count();
}

int DlgPortScan::siguientePaso()
{
	paso++;
}

// Obtiene la información del paso.
DlgPortScan::_InfoPaso DlgPortScan::infoPaso(int paso)
{
	// ToDo: mensage de debug si ocurre esto.
	if( paso >= m_pasos )
		return;

	_InfoPaso info;
	info.indice = paso / m_puertos.count() / m_intentos;
	info.intento = paso % m_intentos;
	paso -= info.intento;
	info.puerto = paso % m_puertos.count();
}

void DlgPortScan::on_lePuertos_textChanged(const QString &)
{
	setupProgressBar();
}

void DlgPortScan::on_btIniciar_clicked()
{
	if( isRunning() )
		pararEscaneo();
	else
	if( isStopping() )
		cancelarEscaneo();
	else
	{
		if( !deviceInfoList.count() )
			QMessageBox::warning(this, tr("Escaneando puertos..."), tr("No hay ninguna IP para escanear"));
		else
		if( !m_puertos.count() )
			QMessageBox::warning(this, tr("Escaneando puertos..."), tr("No hay ningún puerto para escanear"));
		else
		{
			ui->btIniciar->setText("Parar");
			crearListaProcesos();
			calcularPasos();
		}
	}
}
