#include "DlgConfiguracion.h"
#include "ui_DlgConfiguracion.h"

DlgConfiguracion::DlgConfiguracion(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgConfiguracion)
{
	ui->setupUi(this);
	ui->sbTamTxt->setValue(gGlobalConfig.tamFuente());
	ui->sbAltFilas->setValue(gGlobalConfig.alturaLinea());

	quint32 ip = gGlobalConfig.deIPV4();
	ui->sbDeIPA->setValue(UINT_TO_IPV4A(ip));
	ui->sbDeIPB->setValue(UINT_TO_IPV4B(ip));
	ui->sbDeIPC->setValue(UINT_TO_IPV4C(ip));
	ui->sbDeIPD->setValue(UINT_TO_IPV4D(ip));

	ip = gGlobalConfig.aIPV4();
	ui->sbAIPA->setValue(UINT_TO_IPV4A(ip));
	ui->sbAIPB->setValue(UINT_TO_IPV4B(ip));
	ui->sbAIPC->setValue(UINT_TO_IPV4C(ip));
	ui->sbAIPD->setValue(UINT_TO_IPV4D(ip));

	const QStringList &ins = gGlobalConfig.instaladores();
	QStringList com = gGlobalConfig.comerciales(true);
	const QStringList &ppI = gGlobalConfig.perfilesInternos();
	const QStringList &pp = gGlobalConfig.perfiles().nombres();
	ui->listaInstaladores->setRowCount( qMax(com.count(), qMax(pp.count(), qMax(10, ins.count()+4))) );

	for( int row = 0; row < ins.count(); row++ )
		ui->listaInstaladores->setItem(row, 1, new QTableWidgetItem(ins.at(row)));

	for( int row = 0; row < com.count(); row++ )
		ui->listaInstaladores->setItem(row, 2, new QTableWidgetItem(com.at(row)));

	for( int row = 0; row < pp.count(); row++ )
	{
		QTableWidgetItem *it = new QTableWidgetItem(pp.at(row));
		it->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable );
		it->setCheckState( ppI.contains(pp.at(row)) ? Qt::Checked : Qt::Unchecked );
		ui->listaInstaladores->setItem(row, 0, it);
	}

	if( gGlobalConfig.perfiles().nombres().isEmpty() )
	{
		ui->cbBasico->addItem(gGlobalConfig.perfilBasico());
		ui->cbInactivo->addItem(gGlobalConfig.perfilDadoDeBaja());
		ui->cbBasico->setCurrentIndex(0);
		ui->cbInactivo->setCurrentIndex(0);
	}
	else
	{
		gGlobalConfig.setupCBPerfiles(ui->cbBasico, gGlobalConfig.perfilBasico());
		gGlobalConfig.setupCBPerfiles(ui->cbInactivo, gGlobalConfig.perfilDadoDeBaja());
	}
	switch( gGlobalConfig.nivelUsuario() )
	{
	case QConfigData::SinPermisos:
	case QConfigData::Comercial:
		this->setDisabled(true);
		ui->btCancelar->setDisabled(false);
		break;
	case QConfigData::Supervisor:
		ui->listaInstaladores->setDisabled(false);
		break;
	case QConfigData::Instalador:
		ui->listaInstaladores->setDisabled(true);
	case QConfigData::Administrador:
		ui->cbBasico->setDisabled(true);
		ui->cbInactivo->setDisabled(true);
		ui->grRangosIP->setDisabled(true);
		break;
	}
	on_sbTamTxt_valueChanged(gGlobalConfig.tamFuente());
	on_sbAltFilas_valueChanged(gGlobalConfig.alturaLinea());
}

DlgConfiguracion::~DlgConfiguracion()
{
	delete ui;
}

void DlgConfiguracion::on_btAceptar_clicked()
{
	gGlobalConfig.setAlturaLinea(ui->sbAltFilas->value());
	gGlobalConfig.setTamFuente(ui->sbTamTxt->value());

	gGlobalConfig.setDeIPV4(ui->sbDeIPA->value(), ui->sbDeIPB->value(), ui->sbDeIPC->value(), ui->sbDeIPD->value());
	gGlobalConfig.setAIPV4(ui->sbAIPA->value(), ui->sbAIPB->value(), ui->sbAIPC->value(), ui->sbAIPD->value());

	QString s;
	QStringList ins, com;
	QStringList ppI;
	for( int row = 0; row < ui->listaInstaladores->rowCount(); row++ )
	{
		if( (ui->listaInstaladores->item(row, 0) != Q_NULLPTR) && (ui->listaInstaladores->item(row, 0)->checkState() == Qt::Checked) )
			ppI.append(ui->listaInstaladores->item(row, 0)->text());
		if( (ui->listaInstaladores->item(row, 1) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 1)->text()).isEmpty() )
			ins.append(s);
		if( (ui->listaInstaladores->item(row, 2) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 2)->text()).isEmpty() )
			com.append(s);
	}
	gGlobalConfig.setInstaladores(ins);
	gGlobalConfig.setComerciales(com);
	gGlobalConfig.setPerfilBasico(ui->cbBasico->currentText());
	gGlobalConfig.setPerfilDadoDeBaja(ui->cbInactivo->currentText());
	gGlobalConfig.setPerfilesInternos(ppI);
	accept();
}

void DlgConfiguracion::on_btCancelar_clicked()
{
	reject();
}

void DlgConfiguracion::on_sbTamTxt_valueChanged(int tamFuente)
{
	QFont tableFont = ui->listaInstaladores->font();
	tableFont.setPixelSize(tamFuente);
	ui->listaInstaladores->setFont(tableFont);
}

void DlgConfiguracion::on_sbAltFilas_valueChanged(int alturaFila)
{
	ui->listaInstaladores->verticalHeader()->setDefaultSectionSize(alturaFila);
}
