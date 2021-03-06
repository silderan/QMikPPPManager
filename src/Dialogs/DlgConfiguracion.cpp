/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "DlgConfiguracion.h"
#include "ui_DlgConfiguracion.h"

#include <QTableWidgetItem>
#include <QLineEdit>
#include <QMessageBox>

//#include "DlgConfigPrivate.h"

#include "../Widgets/QComboBoxItemDelegate.h"
#include "../ROSMultiConnectorManager.h"
#include "../Utils/Utils.h"

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

	multiConnectionManager.requestAll(DataTypeID::PPPProfile);
	ui->profilesTable->setItemDelegateForColumn( 0,
												 new QComboBoxItemDelegated( this, "", "", false,
						/*add list*/				[] (int)			{ return multiConnectionManager.pppProfileNameList();	},
						/*skip list*/				[this] (int)		{ return Utils::allColumnTexts(ui->profilesTable->model(), 0); },
						/*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

	ui->profilesTable->setItemDelegateForColumn( 1,
												 new QComboBoxItemDelegated( this, "", "", true,
						/*add list*/				[this] (int row)	{ return selectableGroupNames(row);	},
						/*skip list*/				[] (int)			{ return QStringList(); },
						/*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

	ui->staticIPv4Table->setItemDelegateForColumn( 2,
												   new QComboBoxItemDelegated( this, "", "", false,
						/*add list*/				[this] (int)		{ return Utils::allColumnTexts(ui->profilesTable->model(), 1);	},
						/*skip list*/				[] (int)			{ return QStringList() << ClientProfileData::serviceCanceledGroupName(); },
						/*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

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

	for( const ClientProfileData &clientProfileData : m_clientProfileMap )
		addProfileTableRow(clientProfileData);

	refillDialogUsedData();

	for( int st = ServiceInfo::ServiceType::Unk + 1; st < ServiceInfo::ServiceType::Cantidad; ++st  )
	{
		ui->permTable->insertRow(st-1);
		ui->permTable->setItem( st-1, 0, new QTableWidgetItem(ServiceInfo::serviceTypeName(st)) );
		QSpinBox *meses = new QSpinBox();
		meses->setRange(0, 36);
		meses->setValue( gGlobalConfig.getPermanencia( static_cast<ServiceInfo::ServiceType>(st)) );
		ui->permTable->setCellWidget( st-1, 1, meses);
	}
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

QStringList DlgConfiguracion::selectableGroupNames(int row) const
{
	QStringList rtn = Utils::allColumnTexts(ui->profilesTable->model(), 1);
	if( (ui->profilesTable->item(row, 1)->text() != ClientProfileData::serviceCanceledGroupName()) )
	{
		if( !rtn.contains(ClientProfileData::serviceCanceledGroupName()) )
			rtn.prepend(ClientProfileData::serviceCanceledGroupName());
		else
			rtn.removeOne(ClientProfileData::serviceCanceledGroupName());
	}
	return rtn;
}

void DlgConfiguracion::addProfileTableRow(const ClientProfileData &clientProfileData)
{
	int row = ui->profilesTable->rowCount();

	ui->profilesTable->insertRow(row);

	ui->profilesTable->setItem( row, 0, new QTableWidgetItem(clientProfileData.pppProfileName()) );
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
	if( groupName.contains( QRegExp("[^a-zA-Z0-9\\/\\-]") ) )
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

		if( clientProfileData.pppProfileName().isEmpty() )
			return raisesWarning( tr("El nombre del perfil en la fila %1 está vacío").arg(row+1) );
		if( m_clientProfileMap.containsProfileName(clientProfileData.pppProfileName()) )
			return raisesWarning( tr("El perfil %1 de la fila %2 está duplicado").arg(clientProfileData.pppProfileName()).arg(row+1) );
		if( clientProfileData.pppProfileName().contains( QRegExp("[[^a-zA-Z0-9\\/\\- \\()]]") ) )
			return raisesWarning( tr("El perfil %1 de la fila %2 contiene caracteres no válidos").arg(clientProfileData.pppProfileName()).arg(row+1) );

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

	for( int st = ServiceInfo::ServiceType::Unk + 1; st < ServiceInfo::ServiceType::Cantidad; ++st )
		gGlobalConfig.setPermanencia(static_cast<ServiceInfo::ServiceType>(st), static_cast<QSpinBox*>(ui->permTable->cellWidget(st-1, 1))->value());

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
	Q_UNUSED(row)
	Q_UNUSED(column)
	// Need to redo all list because I cannot know the old group name and may be deleted.
	refillDialogUsedData();
}

void DlgConfiguracion::on_upButton_clicked()
{
	int row = Utils::selectedRow(ui->profilesTable);
	Utils::moveTableRow(ui->profilesTable, row, row-1);
	ui->profilesTable->selectRow(row-1);
}

void DlgConfiguracion::on_downButton_clicked()
{
	int row = Utils::selectedRow(ui->profilesTable);
	Utils::moveTableRow(ui->profilesTable, row, row+1);
	ui->profilesTable->selectRow(row+1);
}
