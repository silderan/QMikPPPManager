#include "DlgConfiguracion.h"
#include "ui_DlgConfiguracion.h"

#include <QTableWidgetItem>
#include <QLineEdit>
#include <QMessageBox>

#include "DlgConfigPrivate.h"

DlgConfiguracion::DlgConfiguracion(const QStringList &installerList, const QStringList &comercialList, const IPv4RangeListMap &staticIPv4RangeListMap, const QClientProfileMap &clientProfileMap, ROSMultiConnectManager &multiConManager, QWidget *papi) :
	QDialog(papi), ui(new Ui::DlgConfiguracion)
  , m_installerList(installerList)
  , m_comercialList(comercialList)
  , m_staticIPv4RangeListMap(staticIPv4RangeListMap)
  , m_clientProfileMap(clientProfileMap)
  , m_multiConManager(multiConManager)
{
	int row;
	ui->setupUi(this);

	ui->profilesTable->setItemDelegateForColumn( 0, new QROSProfileNameDelegate(&m_multiConManager, &m_selectedProfiles,this ) );
	ui->profilesTable->setItemDelegateForColumn( 1, new QProfileTypeDelegate(&m_groupNames, this) );

	ui->staticIPv4Table->setItemDelegateForColumn( 2, new QProfileGroupNameDelegate( &m_groupNames, false, Q_NULLPTR, this ) );

	if( staticIPv4RangeListMap.count() )
	{
		IPv4RangeListMapIterator it(staticIPv4RangeListMap);
		while( it.hasNext() )
		{
			it.next();
			foreach( const IPv4Range &ipv4Range, it.value() )
				addStaticIPRangeRow( ipv4Range, it.key() );
		}
	}

	for( row = 0; row < qMax(m_installerList.count(), m_comercialList.count())+10; ++row )
	{
		ui->listaInstaladores->insertRow(row);
		ui->listaInstaladores->setItem(row, 0, new QTableWidgetItem());
		ui->listaInstaladores->setItem(row, 1, new QTableWidgetItem());
	}

	for( row = 0; row < m_installerList.count(); ++row )
		ui->listaInstaladores->setItem(row, 0, new QTableWidgetItem(m_installerList[row]));

	for( row = 0; row < m_comercialList.count(); ++row )
		ui->listaInstaladores->item(row, 1)->setText(m_comercialList[row]);

	foreach( const ClientProfileData &clientProfileData, m_clientProfileMap )
		addProfileTableRow(clientProfileData);

	refillDialogUsedData();

//	switch( m_configData.nivelUsuario() )
//	{
//	case QConfigData::SinPermisos:
//	case QConfigData::Comercial:
//		this->setDisabled(true);
//		ui->btCancelar->setDisabled(false);
//		break;
//	case QConfigData::Supervisor:
//		ui->listaInstaladores->setDisabled(false);
//		break;
//	case QConfigData::Instalador:
//		ui->listaInstaladores->setDisabled(true);
//		[[fallthrough]];
//	case QConfigData::Administrador:
//		ui->grRangosIP->setDisabled(true);
//		break;
//	}
}

DlgConfiguracion::~DlgConfiguracion()
{
	delete ui;
}

void DlgConfiguracion::addProfileTableRow(const ClientProfileData &clientProfileData)
{
	int row = ui->profilesTable->rowCount();

	ui->profilesTable->insertRow(row);

	ui->profilesTable->setItem( row, 0, new QTableWidgetItem(clientProfileData.profileName()) );
	QTableWidgetItem *item = new QTableWidgetItem(clientProfileData.groupName());
	ui->profilesTable->setItem( row, 1, item );
}

void DlgConfiguracion::addStaticIPRangeRow(const IPv4Range &ipv4Range, const QString &profileName)
{
	int row = ui->staticIPv4Table->rowCount();
	ui->staticIPv4Table->insertRow(row);
	ui->staticIPv4Table->setItem(row, 0, new QTableWidgetItem(ipv4Range.first().toString()));
	ui->staticIPv4Table->setItem(row, 1, new QTableWidgetItem(ipv4Range.last().toString()));
	ui->staticIPv4Table->setItem(row, 2, new QTableWidgetItem(profileName));
}

void DlgConfiguracion::refillDialogUsedData()
{
	m_groupNames.clear();
	m_selectedProfiles.clear();

	for( int row = 0; row < ui->profilesTable->rowCount(); ++row )
	{
		if( ui->profilesTable->item(row, 1) != Q_NULLPTR )
		{
			QString groupName = ui->profilesTable->item(row, 1)->text();
			if( !groupName.isEmpty() &&
					checkValidGroupName(groupName, row) &&
					!m_groupNames.contains(groupName) &&
					(groupName != ClientProfileData::serviceCanceledGroupName()) )
				m_groupNames.append(ui->profilesTable->item(row, 1)->text());
		}
		if( ui->profilesTable->item(row, 0) != Q_NULLPTR )
			m_selectedProfiles.append( ui->profilesTable->item(row, 0)->text() );
	}
}

void DlgConfiguracion::raisesWarning(const QString &error)
{
	QMessageBox::warning(this, this->windowTitle(), error);
}

bool DlgConfiguracion::checkValidGroupName(const QString &groupName, int row)
{
	if( groupName.isEmpty() )
		raisesWarning( tr("El grupo del perfil en la fila %1 está vacío").arg(row+1) );
	else
	if( groupName == ClientProfileData::serviceCanceledGroupName() )
		return true;
	else
	if( groupName.contains( QRegExp("[^a-zA-z0-9\\/\\-]")) )
		raisesWarning( tr("El grupo %1 de la fila %2 contiene caracteres no válidos").arg(groupName).arg(row+1) );
	else
		return true;
	return false;
}

void DlgConfiguracion::on_btAceptar_clicked()
{
	QString s;

	int row;
	m_clientProfileMap.clear();
	for( row = 0; row < ui->profilesTable->rowCount(); ++row )
	{
		ClientProfileData clientProfileData;
		clientProfileData.setProfileName( ui->profilesTable->item(row, 0)->text().trimmed() );
		clientProfileData.setGroupName( ui->profilesTable->item(row, 1)->text().trimmed() );

		if( clientProfileData.profileName().isEmpty() )
			return raisesWarning( tr("El nombre del perfil en la fila %1 está vacío").arg(row+1) );
		if( m_clientProfileMap.containsProfileName(clientProfileData.profileName()) )
			return raisesWarning( tr("El perfil %1 de la fila %2 está duplicado").arg(clientProfileData.profileName()).arg(row+1) );
		if( clientProfileData.profileName().contains(QRegExp("[^a-zA-z0-9\\/\\-]")))
			return raisesWarning( tr("El perfil %1 de la fila %2 contiene caracteres no válidos").arg(clientProfileData.profileName()).arg(row+1) );

		if( !checkValidGroupName(clientProfileData.groupName(), row) )
			return;
		m_clientProfileMap.insert( clientProfileData );
	}
	if( !m_clientProfileMap.serviceCanceledProfile().isValid() )
		return raisesWarning( tr("Debes elegir un perfil para los servicios cancelados") );

	m_staticIPv4RangeListMap.clear();
	for( row = 0; row < ui->staticIPv4Table->rowCount(); ++row )
	{
		QString profileGroupName = ui->staticIPv4Table->item(row, 2)->text();
		if( profileGroupName.isEmpty() )
			return raisesWarning( tr("El nombre del grupo de perfiles en la fila %1 de ips estáticas está vacío").arg(row+1) );

		if( !m_clientProfileMap.containsGroupName(profileGroupName) )
			return raisesWarning( tr("El grupo de perfiles %1 en la fila %2 no existe.").arg(profileGroupName).arg(row+1) );

		IPv4 first(ui->staticIPv4Table->item(row, 0)->text());
		if( !first.isValid() )
			return raisesWarning( tr("La IP %1 del grupo de perfiles %2 en la fila %3 no es válida.").arg(first.toString(), profileGroupName).arg(row+1) );

		IPv4 last(ui->staticIPv4Table->item(row, 1)->text());
		if( !last.isValid() )
			return raisesWarning( tr("La IP %1 del grupo de perfiles %2 en la fila %3 no es válida.").arg(last.toString(), profileGroupName).arg(row+1) );

		if( first > last )
			return raisesWarning( tr("La primera IP (%1) es mayor que la última (%2) del grupo de perfiles %3 en la fila %4 no es válida.").arg(first.toString(), last.toString(), profileGroupName).arg(row+1) );

		if( profileGroupName.count() )
			m_staticIPv4RangeListMap.append(profileGroupName, IPv4Range(first, last) );
	}
	m_installerList.clear();
	m_comercialList.clear();
	for( row = 0; row < ui->listaInstaladores->rowCount(); ++row )
	{
		if( (ui->listaInstaladores->item(row, 0) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 0)->text()).isEmpty() )
			m_installerList.append(s);
		if( (ui->listaInstaladores->item(row, 1) != Q_NULLPTR) && !(s = ui->listaInstaladores->item(row, 1)->text()).isEmpty() )
			m_comercialList.append(s);
	}
	accept();
}

void DlgConfiguracion::on_btCancelar_clicked()
{
	reject();
}

void DlgConfiguracion::on_addProfileButton_clicked()
{
	addProfileTableRow();
}

void DlgConfiguracion::on_delProfileButton_clicked()
{
	ui->profilesTable->removeRow(ui->profilesTable->currentRow());
	refillDialogUsedData();
}

void DlgConfiguracion::on_addStaticRangeButton_clicked()
{
	addStaticIPRangeRow();
}

void DlgConfiguracion::on_delStaticRangeButton_clicked()
{
	ui->staticIPv4Table->removeRow( ui->staticIPv4Table->currentRow() );
	refillDialogUsedData();
}

void DlgConfiguracion::on_profilesTable_cellChanged(int row, int column)
{
	Q_UNUSED(row);
	Q_UNUSED(column);
	// Need to redo all list because I cannot know the old group name and may be deleted.
	refillDialogUsedData();
}
