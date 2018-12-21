#include "DlgConfiguracion.h"
#include "ui_DlgConfiguracion.h"

#include <QTableWidgetItem>
#include <QLineEdit>

DlgConfiguracion::DlgConfiguracion(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgConfiguracion)
{
	int row;
	ui->setupUi(this);
	ui->sbTamTxt->setValue(gGlobalConfig.tamFuente());
	ui->sbAltFilas->setValue(gGlobalConfig.alturaFila());

	IPv4RangeMapIterator it(gGlobalConfig.staticIPv4Map());
	while( it.hasNext() )
	{
		it.next();
		row = ui->staticIPv4Table->rowCount();
		ui->staticIPv4Table->insertRow(row);
		ui->staticIPv4Table->setItem(row, 0, new QTableWidgetItem(it.value().first().toString()));
		ui->staticIPv4Table->setItem(row, 1, new QTableWidgetItem(it.value().last().toString()));
		ui->staticIPv4Table->setItem(row, 0, new QTableWidgetItem(it.key()));
	}

	for( row = 0; row < gGlobalConfig.instaladores().count(); ++row )
	{
		ui->listaInstaladores->insertRow(row);
		ui->listaInstaladores->setItem(row, 0, new QTableWidgetItem(gGlobalConfig.instaladores()[row]));
	}

	for( row = 0; row < gGlobalConfig.comerciales().count(); ++row )
	{
		if( row >= ui->listaInstaladores->rowCount() )
			ui->listaInstaladores->insertRow(row);
		ui->listaInstaladores->setItem(row, 1, new QTableWidgetItem(gGlobalConfig.instaladores()[row]));
	}

	m_profilesGroupNameList.append( tr("Básico") );
	m_profilesGroupNameList.append( tr("Interno") );
	m_profilesGroupNameList.append( tr("Baja") );

	for( row = 0; row < gGlobalConfig.perfiles().count(); ++row )
	{
		if( !m_profilesGroupNameList.contains(gGlobalConfig.perfiles().at(row).group()) )
			m_profilesGroupNameList.append(gGlobalConfig.perfiles().at(row).group());
	}
	for( row = 0; row < gGlobalConfig.perfiles().count(); ++row )
		addProfileTableRow(gGlobalConfig.perfiles().at(row));

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
		[[fallthrough]];
	case QConfigData::Administrador:
		ui->grRangosIP->setDisabled(true);
		break;
	}
	on_sbTamTxt_valueChanged(gGlobalConfig.tamFuente());
	on_sbAltFilas_valueChanged(gGlobalConfig.alturaFila());
}

DlgConfiguracion::~DlgConfiguracion()
{
	delete ui;
}

void DlgConfiguracion::on_cbEditingFinished()
{
	QString text = static_cast<QLineEdit*>(sender())->text();
	if( !m_profilesGroupNameList.contains(text) )
	{
		m_profilesGroupNameList.append(text);
		for( int row = 0; row < ui->profilesTable->rowCount(); ++row )
			static_cast<QComboBox*>(ui->profilesTable->cellWidget(row, 1))->addItem(text);
	}
}

void DlgConfiguracion::addProfileTableRow(const ClientProfileData &clientProfileData)
{
	/*
	 * The combo box for the profile group has some special tractment so needs
	 * to keep track of all them to keep their data up to date.
	*/
	int row = ui->profilesTable->rowCount();

	ui->profilesTable->insertRow(row);
	gGlobalConfig.perfiles()[row].name();

	QComboBox *profileCB = new QComboBox();
	profileCB->addItem( tr("[Básico]"), "defaultProfile" );
	profileCB->addItem( tr("[Baja]"), "disabledProfile" );
	profileCB->addItem( tr("[Interno]"), "internalProfile" );

	profileCB->addItems(m_profilesGroupNameList);
	connect( profileCB->lineEdit(), SIGNAL(editingFinished()), this, SLOT(on_cbEditingFinished()) );

	ui->profilesTable->setItem(row, 0, new QTableWidgetItem(clientProfileData.name()) );
	ui->profilesTable->setCellWidget(row, 1, profileCB );
}

void DlgConfiguracion::on_btAceptar_clicked()
{
	gGlobalConfig.setAlturaFila(ui->sbAltFilas->value());
	gGlobalConfig.setTamFuente(ui->sbTamTxt->value());

	QString s;
	QStringList ins, com;
	int row;
	for( row = 0; row < ui->listaInstaladores->rowCount(); ++row )
	{
		if( (ui->listaInstaladores->item(row, 0) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 0)->text()).isEmpty() )
			ins.append(s);
		if( (ui->listaInstaladores->item(row, 1) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 1)->text()).isEmpty() )
			com.append(s);
	}
	gGlobalConfig.setInstaladores(ins);
	gGlobalConfig.setComerciales(com);

	for( row = 0; row < ui->profilesTable->rowCount(); ++row )
	{
		QString profileName = ui->profilesTable->item(row, 0)->text();
		QComboBox *profileCB = static_cast<QComboBox*>(ui->profilesTable->cellWidget(row, 1));

		if( profileCB->currentData().toString() == "defaultProfile" )
			gGlobalConfig.perfiles().setDefaultProfile(row);

		if( profileCB->currentData().toString() == "disabledProfile" )
			gGlobalConfig.perfiles().setDisabledProfile(row);

		gGlobalConfig.perfiles().setProfileGroupName(row, profileCB->currentText());
	}
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
