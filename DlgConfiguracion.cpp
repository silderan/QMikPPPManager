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
	ui->tableWidget->setRowCount( qMax(10, ins.count()+4) );
	for( int row = 0; row < ins.count(); row++ )
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ins.at(row)));

	if( gGlobalConfig.perfiles().nombres().isEmpty() )
	{
		ui->cbBasico->addItem(gGlobalConfig.perfilBasico());
		ui->cbInactivo->addItem(gGlobalConfig.perfilInactivo());

	}
	else
	{
		ui->cbBasico->addItems(gGlobalConfig.perfiles().nombres());
		ui->cbInactivo->addItems(gGlobalConfig.perfiles().nombres());

	}
	ui->cbBasico->setCurrentText(gGlobalConfig.perfilBasico());
	ui->cbInactivo->setCurrentText(gGlobalConfig.perfilInactivo());
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
	QStringList ins;
	for( int row = 0; row < ui->tableWidget->rowCount(); row++ )
		if( (ui->tableWidget->item(row, 0) != Q_NULLPTR) && !(s = ui->tableWidget->item(row, 0)->text()).isEmpty() )
			ins.append(s);
	gGlobalConfig.setInstaladores(ins);
	gGlobalConfig.setPerfilBasico(ui->cbBasico->currentText());
	gGlobalConfig.setPerfilInactivo(ui->cbInactivo->currentText());
	accept();
}

void DlgConfiguracion::on_btCancelar_clicked()
{
	reject();
}

void DlgConfiguracion::on_sbTamTxt_valueChanged(int tamFuente)
{
	QFont tableFont = ui->tableWidget->font();
	tableFont.setPixelSize(tamFuente);
	ui->tableWidget->setFont(tableFont);
}

void DlgConfiguracion::on_sbAltFilas_valueChanged(int alturaFila)
{
	ui->tableWidget->verticalHeader()->setDefaultSectionSize(alturaFila);
}
