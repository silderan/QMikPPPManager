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

#include <QSpinBox>

#include "DlgPPPUser.h"
#include "ui_DlgPPPUser.h"
#include "DlgPPPLogViewer.h"

#include "../Widgets/QComboBoxItemDelegate.h"

enum SchedulerTableColums
{
	STC_Year,
	STC_Month,
	STC_Profile,
	STC_Service
};

DlgPPPUser::DlgPPPUser(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *papi)
	: QDlgMultiDataBase(configData, rosMultiConnectManager, papi)
	, ui(new Ui::DlgPPPUser)
	, m_pppSecret("")
	, m_pppActive("")
{
	ui->setupUi(this);
	onConfigDataChanged();

	ui->serviceTypeComboBox->addItems(ServiceInfo::serviceTypeNameList());

	gSchedulerData.load();
	ui->schedulerTable->setColumnCount(4);
	ui->schedulerTable->setHorizontalHeaderLabels( QStringList() << tr("Año") << tr("Mes") << tr("Perfil") << tr("Servicio") );
	ui->schedulerTable->
	setItemDelegateForColumn( SchedulerTableColums::STC_Profile,
							  new QComboBoxItemDelegated( this, "", "", false,
		/*add list*/			  [] (int)			{ return gGlobalConfig.clientProfileMap().regularProfileNames();	},
		/*skip list*/			  [] (int)			{ return QStringList(); },
		/*allow change*/		  [] (const QModelIndex &,const QString &)	{ return true; } ) );

	ui->schedulerTable->
	setItemDelegateForColumn( SchedulerTableColums::STC_Month,
							  new QComboBoxItemDelegated( this, "", "", false,
		/*add list*/			  [] (int)			{ return ServiceScheduler::Data::months();	},
		/*skip list*/			  [] (int)			{ return QStringList(); },
		/*allow change*/		  [] (const QModelIndex &,const QString &)	{ return true; } ) );

	ui->schedulerTable->
	setItemDelegateForColumn( SchedulerTableColums::STC_Service,
							  new QComboBoxItemDelegated( this, "", "", false,
		/*add list*/			  [] (int)			{ return ServiceScheduler::Data::serviceActionNames();	},
		/*skip list*/			  [] (int)			{ return QStringList(); },
		/*allow change*/		  [] (const QModelIndex &,const QString &)	{ return true; } ) );
}

DlgPPPUser::~DlgPPPUser()
{
	delete ui;
}

bool DlgPPPUser::currentEditing(const ROSPPPSecret &pppSecret)
{
	/*
	 * Intenta descubrir si estamos editando este usuario.
	 * Miramos si en el router del que proviene este dato está la misma ID.
	 * Si no hay información del router, puede que sea un dato nuevo de un router nuevo...
	 * ... en este caso, debe coincidir el userName.
	 * El único caso extremo que se me ocurre es que haya un cambio del nombre de usuario
	 * en uno de los routers y no hayamos recibido la información del usuario anteriormente.
	 */
	if( m_pppSecretMap.isEmpty() )
	{
		if( m_pppSecret.userName() == pppSecret.userName() )
			return true;
		return false;
	}
	if( m_pppSecretMap.contains(pppSecret.routerName()) )
		return m_pppSecretMap.value(pppSecret.routerName(), ROSPPPSecret("")).rosObjectID() == pppSecret.rosObjectID();

	foreach( const ROSPPPSecret &savedPppSecret, m_pppSecretMap )
		if( pppSecret.userName() == savedPppSecret.userName() )
			return true;

	return false;
}

bool DlgPPPUser::checkIPv4(const QString &fieldName, QString &ipString, bool obligated)
{
	if( obligated && ipString.isEmpty() )
		raiseWarning( tr("La IP del campo %1 es obligada").arg(fieldName) );
	else
	if( !ipString.isEmpty() && !IPv4(ipString).isValid() )
		raiseWarning( tr("La IP del campo %1 no es válida").arg(fieldName) );
	else
		return true;
	return false;
}

bool DlgPPPUser::getStaticIP()
{
	if( ui->staticIPComboBox->currentIndex() == 0 )
	{
		m_pppSecret.setStaticIP( IPv4() );
		return true;
	}
	m_pppSecret.setStaticIP( IPv4(ui->staticIPComboBox->currentText().trimmed()) );
	if( !m_pppSecret.staticIP().isValid() )
		raiseWarning( tr("La IP pública estática seleccionada no es válida.") );
	else
		return true;
	return false;
}

bool DlgPPPUser::checkStringData(const QString &fieldName, const QString &originalText, const QString &text, std::function<bool(ROSPPPSecret&, const QString &)> setFnc)
{
	// With this, accepts texts if it's the same than the secrets'.
	// This makes things easier for automatically generated users without some data.
	// So, it just forces to be all well formed for new users or when modifying field data.
	if( !m_pppSecret.rosObjectID().isEmpty() && (originalText == text) )
		return true;
	if( !setFnc(m_pppSecret, text) )
	{
		raiseWarning( tr("El campo '%1', %2").arg( fieldName, m_pppSecret.lastError()) );
		return false;
	}
	return true;
}

bool DlgPPPUser::checkGroupedData(const QGroupBox *group,
								  QString newText,
								  std::function<const QString &(ROSPPPSecret &)> getFnc,
								  std::function<bool (ROSPPPSecret &, const QString &)> setFnc,
								  const QString &fieldName )
{
	if( group->isChecked() )
	{
		if( newText.isEmpty() )
		{
			raiseWarning( tr("El campo %1 no puede estar vacío si tienes el grupo habilitado").arg(fieldName) );
			return false;
		}
	}
	else
		newText.clear();
	return updateTextMember<ROSPPPSecret>( newText, m_pppSecret, getFnc, setFnc, fieldName );
}

bool DlgPPPUser::getPPPUserName()
{
	return updateTextMember<ROSPPPSecret>( ui->pppUserNameLineEdit->text(), m_pppSecret, &ROSPPPSecret::userName, &ROSPPPSecret::setUserName, tr("Nombre del usuario PPP") );
}

bool DlgPPPUser::getPPPUserPass()
{
	return updateTextMember<ROSPPPSecret>( ui->pppUserPassLineEdit->text(), m_pppSecret, &ROSPPPSecret::userPass, &ROSPPPSecret::setUserPass, tr("Contraseña del usuario PPP") );
}

bool DlgPPPUser::getPPPProfile()
{
	if( !ServiceState::isCanceledState(m_pppSecret.serviceState()) )
		updateTextMember<ROSPPPSecret>( ui->pppProfileComboBox->currentText(), m_pppSecret, &ROSPPPSecret::pppProfileName, &ROSPPPSecret::setPPPProfileName, tr("Perfil del cliente") );
	return updateTextMember<ROSPPPSecret>( ui->pppProfileComboBox->currentText(), m_pppSecret, &ROSPPPSecret::originalProfile, &ROSPPPSecret::setOriginalProfile, tr("Perfil del cliente") );
}

bool DlgPPPUser::getClientName()
{
	return updateTextMember<ROSPPPSecret>( ui->clientNameLineEdit->text(), m_pppSecret, &ROSPPPSecret::clientName, &ROSPPPSecret::setClientName, tr("Nombre del cliente") );
}

bool DlgPPPUser::getClientAddress()
{
	return updateTextMember<ROSPPPSecret>( ui->clientAddressLineEdit->text(), m_pppSecret, &ROSPPPSecret::clientAddress, &ROSPPPSecret::setClientAddress, tr("Dirección del cliente") );
}

bool DlgPPPUser::getClientInstaller()
{
	return updateTextMember<ROSPPPSecret>( ui->installerComboBox->currentText(), m_pppSecret, &ROSPPPSecret::installerName, &ROSPPPSecret::setInstallerName, tr("Nombre del instalador") );
}

bool DlgPPPUser::getClientCity()
{
	return updateTextMember<ROSPPPSecret>( ui->clientCityComboBox->currentText(), m_pppSecret, &ROSPPPSecret::clientCity, &ROSPPPSecret::setClientCity, tr("Población instalación") );
}

bool DlgPPPUser::getClientPhones()
{
	return updateTextMember<ROSPPPSecret>( ui->clientPhonesLineEdit->text(), m_pppSecret, &ROSPPPSecret::clientPhones, &ROSPPPSecret::setClientPhones, tr("Teléfonos de contacto del cliente") );
}

bool DlgPPPUser::getClientEMail()
{
	return updateTextMember<ROSPPPSecret>( ui->clientEmailLineEdit->text(), m_pppSecret, &ROSPPPSecret::clientEmail, &ROSPPPSecret::setClientEmail, tr("Correo electrónico del cliente") );
}

bool DlgPPPUser::getClientNotes()
{
    return updateTextMember<ROSPPPSecret>( ui->clientNotesTextEdit->toPlainText().replace('\n', '\\'), m_pppSecret, &ROSPPPSecret::clientNotes, &ROSPPPSecret::setClientNotes, tr("Anotaciones sobre el cliente") );
}

bool DlgPPPUser::getInstallNotes()
{
    return updateTextMember<ROSPPPSecret>( ui->installNotesTextEdit->toPlainText().replace('\n', '\\'), m_pppSecret, &ROSPPPSecret::installNotes, &ROSPPPSecret::setInstallNotes, tr("Anotaciones sobre la instalación") );
}

bool DlgPPPUser::getServiceInfo()
{
	ServiceInfo::ServiceType newType = ServiceInfo::ServiceType(ui->serviceTypeComboBox->currentIndex());
	switch( newType )
	{
	case ServiceInfo::ServiceType::Unk:
		raiseWarning( tr("Debes escoger el tipo de servicio.") );
		return false;
	case ServiceInfo::ServiceType::WiFi:
		m_pppSecret.setONTSN("");
		m_pppSecret.setHasIoC(false);
		m_pppSecret.setHasToF(false);
		break;
	case ServiceInfo::ServiceType::WTTB:
		m_pppSecret.setONTSN("");
		m_pppSecret.setHasIoC( ui->iocCheckBox->isChecked() );
		m_pppSecret.setHasToF( ui->tofCheckBox->isChecked() );
		break;
	case ServiceInfo::ServiceType::FTTB:
		m_pppSecret.setONTSN("");
		m_pppSecret.setHasIoC( ui->iocCheckBox->isChecked() );
		m_pppSecret.setHasToF( ui->tofCheckBox->isChecked() );
		break;
	case ServiceInfo::ServiceType::FTTH:
		if( ui->ontSNComboBox->currentText().isEmpty() )
		{
			raiseWarning( tr("Debes seleccionar una ONT") );
			return false;
		}
		if( !updateTextMember<ROSPPPSecret>( ui->ontSNComboBox->currentText(), m_pppSecret, &ROSPPPSecret::ontSN, &ROSPPPSecret::setONTSN, tr("Número de serie de la ONT") ) )
			return false;
		m_pppSecret.setHasIoC(false);
		m_pppSecret.setHasToF(false);
		break;
	case ServiceInfo::ServiceType::PtP_WiFi:
		m_pppSecret.setHasIoC(false);
		m_pppSecret.setHasToF(false);
		break;
	case ServiceInfo::ServiceType::PtP_FO:
		m_pppSecret.setHasIoC(false);
		m_pppSecret.setHasToF(false);
		break;
	}
	m_pppSecret.setServiceType(newType);
	return true;
}

bool DlgPPPUser::getVoIPPhone()
{
	return checkGroupedData( ui->voipGroupBox, ui->voipPhoneNumber->text(), &ROSPPPSecret::voipPhoneNumber, &ROSPPPSecret::setVoIPPhoneNumber, tr("Número de teléfono SIP") );
}

bool DlgPPPUser::getVoIPSIPServer()
{
	return checkGroupedData( ui->voipGroupBox, ui->voipServerLineEdit->text(), &ROSPPPSecret::voipSIPServer, &ROSPPPSecret::setVoIPSIPServer, tr("URL del servidor SIP") );
}

bool DlgPPPUser::getVoIPUserName()
{
	return checkGroupedData( ui->voipGroupBox, ui->voipUserName->text(), &ROSPPPSecret::voipSIPUserName, &ROSPPPSecret::setVoIPSIPUserName, tr("Nombre de Usuario SIP") );
}

bool DlgPPPUser::getVoIPUserPass()
{
	return checkGroupedData( ui->voipGroupBox, ui->voipUserPass->text(), &ROSPPPSecret::voipSIPUserPass, &ROSPPPSecret::setVoIPSIPUserPass, tr("Contraseña SIP") );
}

bool DlgPPPUser::getWiFi2SSID()
{
	return checkGroupedData( ui->wifi2GroupBox, ui->wifi2SSIDLineEdit->text(), &ROSPPPSecret::wifi2SSID, &ROSPPPSecret::setWiFi2SSID, tr("SSID para el Wifi local a 2,4Ghz") );
}

bool DlgPPPUser::getWiFi2WPA()
{
	return checkGroupedData( ui->wifi2GroupBox, ui->wifi2WPALineEdit->text(), &ROSPPPSecret::wifi2WPA, &ROSPPPSecret::setWiFi2WPA, tr("Contraseña WPA/WPA2 para el Wifi local a 2,4Ghz") );
}

bool DlgPPPUser::getWiFi5SSID()
{
	return checkGroupedData( ui->wifi5GroupBox, ui->wifi5SSIDLineEdit->text(), &ROSPPPSecret::wifi5SSID, &ROSPPPSecret::setWiFi5SSID, tr("SSID para el Wifi local a 5Ghz") );
}

bool DlgPPPUser::getWiFi5WPA()
{
	return checkGroupedData( ui->wifi5GroupBox, ui->wifi5WPALineEdit->text(), &ROSPPPSecret::wifi5WPA, &ROSPPPSecret::setWiFi5WPA, tr("Contraseña WPA/WPA2 para el Wifi local a 5Ghz") );
}

bool DlgPPPUser::getLocalIP()
{
	QString s;
	if( ui->lanGroupBox->isChecked() )
	{
		if( !checkIPv4( tr("IP de la red local"), s = ui->lanIPLineEdit->text()) )
			return false;
	}
	m_pppSecret.setInstallLANIP( IPv4(s) );
	return true;
}

bool DlgPPPUser::getLocalDMZ()
{
	QString s;
	if( ui->lanGroupBox->isChecked() )
	{
		if( !checkIPv4( tr("DMZ de la red local"), s = ui->lanDMZLineEdit->text()) )
			return false;
	}
	m_pppSecret.setInstallLANDMZ( IPv4(s) );
	return true;
}

bool DlgPPPUser::getLocalPorts()
{
	if( !ui->lanGroupBox->isChecked() )
	{
		m_pppSecret.setPortForwardList(QPortForwardList());
		return true;
	}
	m_pppSecret.setPortForwardList( ui->lanPortsTableWidget->portForwardList() );
	if( !ui->lanPortsTableWidget->lastError().isEmpty() )
	{
		raiseWarning( ui->lanPortsTableWidget->lastError() );
		return false;
	}
	return true;
}

bool DlgPPPUser::getSchedulerData()
{
	ServiceScheduler::DataList dataList;
	for( int row = 0; row < ui->schedulerTable->rowCount(); row++ )
	{
		ServiceScheduler::Data data;
		data.setYear( quint16(ui->schedulerTable->item(row, SchedulerTableColums::STC_Year)->text().toUInt()) );
		if( !data.isYearValid() )
		{
			raiseWarning( tr("El año '%1' programado en la fila %2 no es válido").arg(data.year()).arg(row) );
			return false;
		}
		data.setMonth( ui->schedulerTable->item(row, SchedulerTableColums::STC_Month)->text() );
		if( !data.isMonthValid() )
		{
			raiseWarning( tr("El mes '%1' programado en la fila %2 no es válido").arg(data.monthName()).arg(row) );
			return false;
		}
		data.setProfileName( ui->schedulerTable->item(row, SchedulerTableColums::STC_Profile)->text() );
		data.setServiceAction( ui->schedulerTable->item(row, SchedulerTableColums::STC_Service)->text() );
		dataList.append(data);
	}
	gSchedulerData.setDataList(m_pppSecret.userName(), dataList);
	return true;
}

void DlgPPPUser::addServiceSchedulerRow(const ServiceScheduler::Data &schedulerData)
{
	int row = ui->schedulerTable->rowCount();
	ui->schedulerTable->insertRow(row);
	ui->schedulerTable->setItem( row, SchedulerTableColums::STC_Year, new QTableWidgetItem(QString::number(schedulerData.year())) );
	ui->schedulerTable->setItem( row, SchedulerTableColums::STC_Month, new QTableWidgetItem(schedulerData.monthName()) );
	ui->schedulerTable->setItem( row, SchedulerTableColums::STC_Profile, new QTableWidgetItem(schedulerData.profileName()) );
	ui->schedulerTable->setItem( row, SchedulerTableColums::STC_Service, new QTableWidgetItem(schedulerData.serviceActionName()) );
}

void DlgPPPUser::updateGUI()
{
	switch( configData().userLevel() )
	{
	case ROSAPIUser::NoRights:
		reject();
		break;
	case ROSAPIUser::Comercial:
		setReadOnly(true);
		ui->applyDataButton->setVisible(false);
		ui->clientLogsButton->setVisible(false);
		break;
	case ROSAPIUser::Instalator:
		setReadOnly(false);
		ui->applyDataButton->setVisible(true);
		ui->clientLogsButton->setVisible(false);
		ui->pppUserPassCreateButton->setEnabled(true);
		break;
	case ROSAPIUser::Administrator:
		setReadOnly(false);
		ui->pppUserNameLineEdit->setReadOnly(true);
		ui->pppUserPassLineEdit->setReadOnly(true);
		ui->pppUserPassCreateButton->setEnabled(false);
		ui->applyDataButton->setVisible(true);
		ui->clientLogsButton->setVisible(true);
		break;
	case ROSAPIUser::Supervisor:
		setReadOnly(false);
		ui->applyDataButton->setVisible(true);
		ui->clientLogsButton->setVisible(true);
		break;
	}
}

void DlgPPPUser::onConfigDataChanged()
{
	updateInstallersComboBox();
	updateCitiesComboBox();
	updatePPPProfilesComboBox();
	updateStaticIPComboBox();
}

void DlgPPPUser::updatePPPProfilesComboBox()
{
	QString currentProfile = ui->pppProfileComboBox->currentText();

	ui->pppProfileComboBox->blockSignals(true);
	ui->pppProfileComboBox->clear();
	ui->pppProfileComboBox->addItems( configData().clientProfileMap().regularProfileNames() );

	if( !currentProfile.isEmpty() )
		ui->pppProfileComboBox->setCurrentIndex( ui->pppProfileComboBox->findData(currentProfile, Qt::EditRole) );

	ui->pppProfileComboBox->blockSignals(false);
}

void DlgPPPUser::updateInstallersComboBox()
{
	ui->installerComboBox->updateList( configData().instaladores(), true );
}

void DlgPPPUser::updateCitiesComboBox()
{
	ui->clientCityComboBox->updateList( multiConnectionManager.clientCities() );
}

void DlgPPPUser::updateStaticIPComboBox()
{
	ui->staticIPComboBox->blockSignals(true);
	QString profileName = ui->pppProfileComboBox->currentText();
	QString profileGroup;

	if( profileName.isEmpty() )
		raiseWarning( tr("No hay ningún perfil seleccionado y no se puede saber las IPs públicas disponibles sin uno válido.") );
	else
	if( (profileGroup = configData().clientProfileMap().groupName(profileName)).isEmpty() )
		raiseWarning( tr("El perfil perfil $1 no está asociado a ningún grupo y no se puede saber las IPs públicas disponibles sin un grupo válido.") );

	ui->staticIPComboBox->setup( tr("No (IP dinámica)"), "",
								 configData().staticIPv4RangeListMap().staticIPv4StringList(profileGroup),
								 rosMultiConnectManager().staticIPv4List(), m_pppSecret.staticIP().isValid() ? m_pppSecret.staticIP().toString() : QString() );

	if( m_pppSecret.staticIP().isValid() && (ui->staticIPComboBox->currentIndex() <= 0) )
		raiseWarning( tr("La IP estática seleccionada no es válida para el perfil actual.") );

	ui->staticIPComboBox->blockSignals(false);
}

void DlgPPPUser::updateDialog()
{
	updateInstallersComboBox();
	updateCitiesComboBox();
	updateUserData();
	updateDialogInfo();
}

void DlgPPPUser::updateUserData()
{
	ui->pppUserNameLineEdit->setText( m_pppSecret.userName() );
	ui->pppUserPassLineEdit->setText( m_pppSecret.userPass() );
	ui->pppProfileComboBox->blockSignals(true);
	if( m_pppSecret.originalProfile().isEmpty() )
		ui->pppProfileComboBox->setCurrentIndex(-1);
	else
	{
		ui->pppProfileComboBox->setCurrentIndex( ui->pppProfileComboBox->findData(m_pppSecret.originalProfile(), Qt::EditRole) );
		updateStaticIPComboBox();
	}
	ui->pppProfileComboBox->blockSignals(false);
	ui->serviceTypeComboBox->setCurrentIndex(m_pppSecret.serviceInfo().serviceType);
	ui->tofCheckBox->setChecked(m_pppSecret.serviceInfo().hasToF);
	ui->iocCheckBox->setChecked(m_pppSecret.serviceInfo().hasIoC);
	ui->serviceTypeComboBox->blockSignals(true);
	ui->ontSNComboBox->setCurrentText(m_pppSecret.ontSN());

	ui->serviceTypeComboBox->blockSignals(false);
	ui->installerComboBox->setCurrentText( m_pppSecret.installerName() );
	ui->clientNameLineEdit->setText( m_pppSecret.clientName() );
	ui->clientAddressLineEdit->setText( m_pppSecret.clientAddress() );
	ui->clientCityComboBox->setCurrentText( m_pppSecret.clientCity() );
	ui->clientPhonesLineEdit->setText( m_pppSecret.clientPhones() );
	ui->clientEmailLineEdit->setText( m_pppSecret.clientEmail() );
    ui->clientNotesTextEdit->setPlainText( QString("%1").arg(m_pppSecret.clientNotes()).replace('\\', '\n') );
    ui->installNotesTextEdit->setPlainText( QString("%1").arg(m_pppSecret.installNotes()).replace('\\', '\n') );

	ui->wifi2GroupBox->setChecked( !m_pppSecret.wifi2SSID().isEmpty() );
	ui->wifi2SSIDLineEdit->setText( m_pppSecret.wifi2SSID() );
	ui->wifi2WPALineEdit->setText( m_pppSecret.wifi2WPA() );
	ui->wifi5GroupBox->setChecked( !m_pppSecret.wifi5SSID().isEmpty() );
	ui->wifi5SSIDLineEdit->setText( m_pppSecret.wifi5SSID() );
	ui->wifi5WPALineEdit->setText( m_pppSecret.wifi5WPA() );

	ui->voipGroupBox->setChecked( !m_pppSecret.voipSIPUserName().isEmpty() );
	ui->voipServerLineEdit->setText( m_pppSecret.voipSIPServer() );
	ui->voipPhoneNumber->setText( m_pppSecret.voipPhoneNumber() );
	ui->voipUserName->setText( m_pppSecret.voipSIPUserName() );
	ui->voipUserPass->setText( m_pppSecret.voipSIPUserPass() );

	ui->lanGroupBox->setChecked( m_pppSecret.installLANIP().isValid() || m_pppSecret.installLANDMZ().isValid() || !m_pppSecret.portForwardList().isEmpty() );
	ui->lanIPLineEdit->setText( m_pppSecret.installLANIP().isValid() ? m_pppSecret.installLANIP().toString() : QString() );
	ui->lanDMZLineEdit->setText( m_pppSecret.installLANDMZ().isValid() ? m_pppSecret.installLANDMZ().toString() : QString() );
	ui->lanPortsTableWidget->setup( m_pppSecret.portForwardList() );

	ui->schedulerTable->clear();
	ui->schedulerTable->setRowCount(0);

	for( const ServiceScheduler::Data &schedulerData : gSchedulerData.dataList(m_pppSecret.userName()) )
		addServiceSchedulerRow(schedulerData);
}

void DlgPPPUser::updateDialogInfo()
{
	if( m_pppSecret.rosObjectID().isEmpty() )
	{
		setWindowTitle( tr("Creación nuevo cliente") );
		ui->applyDataButton->setText( tr("Crear nuevo") );
	}
	else
	{
		setWindowTitle( tr("Modificando cliente '%1'").arg(m_pppSecret.userName()) );
		ui->applyDataButton->setText( tr("Modificar") );
		if( m_pppActive.rosObjectID().isEmpty() )
			ui->infoLabel->clear();
		else
			ui->infoLabel->setText( tr("Usuario activo con IP %1 en el router %2").arg(m_pppActive.currentIPv4().toString(), m_pppActive.routerName()) );
	}
}

void DlgPPPUser::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::PPPSecret )
	{
		if( currentEditing(static_cast<const ROSPPPSecret &>(rosData)) )
		{
			m_pppSecret = static_cast<const ROSPPPSecret &>(rosData);
			m_pppSecretMap.insert( m_pppSecret );
			updateDialog();
		}
	}
	else
	if( rosData.dataTypeID() == DataTypeID::PPPActive )
	{
		if( m_pppActive.rosObjectID() == rosData.rosObjectID() )
		{
			m_pppActive = static_cast<const ROSPPPActive &>(rosData);
			updateDialogInfo();
		}
		else
		if( m_pppSecret.userName() == static_cast<const ROSPPPActive &>(rosData).userName() )
		{
			m_pppActive = static_cast<const ROSPPPActive &>(rosData);
			updateDialogInfo();
		}
	}
}

void DlgPPPUser::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	if( dataTypeID == DataTypeID::PPPActive )
	{
		if( !m_pppActive.routerName().isEmpty() )
		{
			if( m_pppActive.rosObjectID() == rosObjectID )
			{
				m_pppActive = ROSPPPActive("");
				updateDialogInfo();
			}
		}
	}
	else
	if( dataTypeID == DataTypeID::PPPSecret )
	{
		if( m_pppSecretMap.contains(routerName) )
		{
			m_pppSecretMap.remove(routerName);
			if( m_pppSecret.rosObjectID() == rosObjectID )
			{
				if( m_pppSecretMap.count() )
					m_pppSecret.setROSObjectID( m_pppSecretMap.first().rosObjectID() );
				else
					m_pppSecret = ROSPPPSecret("");
				updateDialogInfo();
			}
		}
	}
}

void DlgPPPUser::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	Q_UNUSED(routerName);
	Q_UNUSED(dataTypeID);
}

void DlgPPPUser::clear()
{
	m_pppSecret = ROSPPPSecret("");
	m_pppActive = ROSPPPActive("");
	m_pppSecretMap.clear();
}

void DlgPPPUser::onLogued(const QString &routerName)
{
	m_pppSecretMap.remove(routerName);
	clear();
}

void DlgPPPUser::onDisconnected(const QString &routerName)
{
	m_pppSecretMap.remove(routerName);
	clear();
}

void DlgPPPUser::on_pppProfileComboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index);
	updateStaticIPComboBox();
}

void DlgPPPUser::onEditUserRequest(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive)
{
	clear();
	if( pppSecretMap.count() )
	{
		m_pppSecretMap = pppSecretMap;
		m_pppSecret = m_pppSecretMap.pppSecret();
		m_pppActive = pppActive;
		updateDialog();
	}
	else
	{
		updateDialog();
		on_pppUserPassCreateButton_clicked();
	}
	show();
}

void DlgPPPUser::hideEvent(QHideEvent *event)
{
	clear();
	return QDlgMultiDataBase::hideEvent(event);
}

void DlgPPPUser::on_applyDataButton_clicked()
{
	if( getPPPUserName() && getPPPUserPass() && getPPPProfile() && getStaticIP() &&
		getClientName() && getClientAddress() && getClientInstaller() &&
		getClientCity() && getClientPhones() && getClientEMail() &&
		getClientNotes() && getInstallNotes() &&
		getServiceInfo() &&
		getVoIPPhone() && getVoIPSIPServer() && getVoIPUserName() && getVoIPUserPass() &&
		getWiFi2SSID() && getWiFi2WPA() &&
		getWiFi5SSID() && getWiFi5WPA() &&
		getLocalIP() && getLocalDMZ() && getLocalPorts() && getSchedulerData() )

	{
		multiConnectionManager.updateRemoteData( m_pppSecret, m_pppSecretMap.toRouterIDMap() );
		gSchedulerData.save();
	}
}

void DlgPPPUser::on_addPortButton_clicked()
{
	ui->lanPortsTableWidget->addPortForwardRow( PortForward() );
}

void DlgPPPUser::on_delPortButton_clicked()
{
	ui->lanPortsTableWidget->removeRow( ui->lanPortsTableWidget->currentRow() );
}

void DlgPPPUser::on_clientLogsButton_clicked()
{
	DlgPPPLogViewer dlgPPPLogViewer( m_pppSecret.userName(), this );
	dlgPPPLogViewer.exec();
}

#include <QGuiApplication>
#include <QClipboard>
void DlgPPPUser::on_pppUserNameCopyButton_clicked()
{
	QClipboard *cb = QGuiApplication::clipboard();
	cb->setText(ui->pppUserNameLineEdit->text());
	ui->pppUserNameLineEdit->setFocus();
	ui->pppUserNameLineEdit->selectAll();
}

void DlgPPPUser::on_pppUserPassCopyButton_clicked()
{
	QClipboard *cb = QGuiApplication::clipboard();
	cb->setText(ui->pppUserPassLineEdit->text());
	ui->pppUserPassLineEdit->setFocus();
	ui->pppUserPassLineEdit->selectAll();
}

void DlgPPPUser::on_pppUserPassCreateButton_clicked()
{
	QDateTime d = QDateTime::currentDateTime();

	QString str = d.toString("ddMMyyyyhhmm");
	ui->pppUserPassLineEdit->setText(str);
}

void DlgPPPUser::on_delChedulerButton_clicked()
{
	QList<QTableWidgetItem*> items = ui->schedulerTable->selectedItems();
	if( items.count() > 0 )
	{
		int row = ui->schedulerTable->selectedItems().first()->row();
		ui->schedulerTable->removeRow(row);
	}
}

void DlgPPPUser::on_addSchedulerButton_clicked()
{
	addServiceSchedulerRow();
}

void DlgPPPUser::on_copyInfoButton_clicked()
{
	/* Formato creado:
	 * <nombre> <User>/<Pass>
	 * <dirección> <Pueblo>
	 * <teléfonos>
	 * Contrato [alta/baja] de <perfil>. Estado actual [activo <fecha> /inactivo <fecha>]
     * Instalado por: <nombre_instalador>
	 * (Tiene VozIP, DVR, etc)
	 * (Notas)
	 * */
	QString txt = tr("%1 (%2/%3)").arg(ui->clientNameLineEdit->text(), ui->pppUserNameLineEdit->text(), ui->pppUserPassLineEdit->text());
	txt.append( tr("\n%1. %2." ).arg(ui->clientAddressLineEdit->text(), ui->clientCityComboBox->currentText()));
	txt.append( tr("\n%1").arg( ui->clientPhonesLineEdit->text().isEmpty()? tr("Sin teléfonos conocidos.") : tr("Teléfono: %1").arg(ui->clientPhonesLineEdit->text()) ) );
	txt.append( tr("\nServicio: %1%2").arg( ServiceState::readableString(m_pppSecret.serviceState()),
										   !ServiceState::isCanceledState(m_pppSecret.serviceState())
										 ? tr(". Perfil: %1").arg(m_pppSecret.originalProfile())
										 : "") );
	txt.append( tr("\nEstado: %1").arg(m_pppActive.rosObjectID().isEmpty()
									   ? tr("Desconectado desde %1").arg(m_pppSecret.lastLogOff().toString("dd/MM/yyyy hh:mm:ss"))
									   : tr("Conectado desde %1 con IP %2").arg(m_pppActive.uptime().toString("dd/MM/yyyy hh:mm:ss"))).arg(m_pppActive.currentIPv4().toString()) );

    txt.append( tr("\nInstalado por: %1").arg(ui->installerComboBox->currentText()) );
	if( !m_pppSecret.voipSIPServer().isEmpty() )
	{
		txt.append( tr("\nVoIP: %1 ").arg(m_pppSecret.voipPhoneNumber()) );
		if( m_pppSecret.voipPhoneNumber() != m_pppSecret.voipSIPUserName() )
			txt.append( QString("(%1/%2)").arg(m_pppSecret.voipSIPUserName(),m_pppSecret.voipSIPUserPass()) );
		else
			txt.append( QString("(%1)").arg(m_pppSecret.voipSIPUserPass()) );
	}
	if( !m_pppSecret.wifi2SSID().isEmpty() )
		txt.append( tr("\nWiFi2: SSID=%1 PASS=%2").arg(m_pppSecret.wifi2SSID(),m_pppSecret.wifi2WPA()) );

	if( !m_pppSecret.wifi5SSID().isEmpty() )
		txt.append( tr("\nWiFi5: SSID=%1 PASS=%2").arg(m_pppSecret.wifi5SSID(),m_pppSecret.wifi5WPA()) );

	if( m_pppSecret.installLANIP().isValid() )
		txt.append( tr("\nLAN IP: %1 ").arg(m_pppSecret.installLANIP().toString()) );
	if( m_pppSecret.installLANDMZ().isValid() )
		txt.append( tr("\nDMZ: %1 ").arg(m_pppSecret.installLANDMZ().toString()) );
	foreach( auto port, m_pppSecret.portForwardList() )
		txt.append( tr("\nPuerto %1").arg(port.toSaveString()) );

    foreach( QString note, ui->installNotesTextEdit->toPlainText().split('\n') )
    {
		if( !note.isEmpty() )
			txt.append( tr("\nNota: %1").arg(note) );
    }

	QGuiApplication::clipboard()->setText(txt);
}


void DlgPPPUser::onConfigChanged()
{
	updateGUI();
}
