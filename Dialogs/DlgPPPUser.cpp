#include <QMessageBox>
#include <QSpinBox>

#include "DlgPPPUser.h"
#include "ui_DlgPPPUser.h"
#include "DlgPPPLogViewer.h"

DlgPPPUser::DlgPPPUser(QWidget *papi, ROSMultiConnectManager &rosMultiConnectManager, QConfigData &configData) :
	DlgDataBase(papi, rosMultiConnectManager), ui(new Ui::DlgPPPUser)
  , m_pppSecret("")
  , m_pppActive("")
{
	ui->setupUi(this);
	setConfigData(configData);
}

DlgPPPUser::~DlgPPPUser()
{
	delete ui;
}

void DlgPPPUser::raiseWarning(const QString &info)
{
	QMessageBox::warning(this, this->windowTitle(), info);
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

bool DlgPPPUser::checkGroupedData(const QGroupBox *group, const QString &fieldName, const QString &originalText, QString text, std::function<bool (ROSPPPSecret &, const QString &)> setFnc)
{
	if( group->isChecked() )
	{
		if( text.isEmpty() )
		{
			raiseWarning( tr("El campo %1 no puede estar vacío si tienes el grupo habilitado").arg(fieldName) );
			return false;
		}
	}
	else
		text.clear();
	return checkStringData( fieldName, originalText, text, setFnc );
}

bool DlgPPPUser::getPPPUserName()
{
	return checkStringData( tr("Nombre del usuario PPP"), m_pppSecret.userName(), ui->pppUserNameLineEdit->text(), &ROSPPPSecret::setUserName );
}

bool DlgPPPUser::getPPPUserPass()
{
	return checkStringData( tr("Contraseña del usuario PPP"), m_pppSecret.userPass(), ui->pppUserPassLineEdit->text(), &ROSPPPSecret::setUserPass );
}

bool DlgPPPUser::getPPPProfile()
{
	return checkStringData( tr("Perfil del cliente"), m_pppSecret.originalProfile(), ui->pppProfileComboBox->currentText(), &ROSPPPSecret::setOriginalProfile );
}

bool DlgPPPUser::getClientName()
{
	return checkStringData( tr("Nombre del cliente"), m_pppSecret.clientName(), ui->clientNameLineEdit->text(), &ROSPPPSecret::setClientName );
}

bool DlgPPPUser::getClientAddress()
{
	return checkStringData( tr("Dirección del cliente"), m_pppSecret.clientAddress(), ui->clientAddressLineEdit->text(), &ROSPPPSecret::setClientAddress );
}

bool DlgPPPUser::getClientInstaller()
{
	return checkStringData( tr("Nombre del instalador"), m_pppSecret.installerName(), ui->installerComboBox->currentText(), &ROSPPPSecret::setInstallerName );
}

bool DlgPPPUser::getClientCity()
{
	return checkStringData( tr("Población de la instalación"), m_pppSecret.clientCity(), ui->clientCityComboBox->currentText(), &ROSPPPSecret::setClientCity );
}

bool DlgPPPUser::getClientPhones()
{
	return checkStringData( tr("Teléfonos de contacto"), m_pppSecret.clientPhones(), ui->clientPhonesLineEdit->text(), &ROSPPPSecret::setClientPhones );
}

bool DlgPPPUser::getClientEMail()
{
	return checkStringData( tr("Correo electrónico"), m_pppSecret.clientEmail(), ui->clientEmailLineEdit->text(), &ROSPPPSecret::setClientEmail );
}

bool DlgPPPUser::getClientNotes()
{
	return checkStringData( tr("Anotaciones sobre el cliente"), m_pppSecret.clientNotes(), ui->clientNotesLineEdit->text(), &ROSPPPSecret::setClientNotes );
}

bool DlgPPPUser::getInstallNotes()
{
	return checkStringData( tr("Anotaciones sobre la instalación"), m_pppSecret.installNotes(), ui->installNotesLineEdit->text(), &ROSPPPSecret::setInstallNotes );
}

bool DlgPPPUser::getONTSN()
{
	QString s = ui->ontSNComboBox->currentText();
	if( ui->ftthCheckBox->isChecked() && s.isEmpty() )
	{
		raiseWarning( tr("Debes seleccionar una ONT") );
		return false;
	}
	return checkStringData( tr("Número de serie de la ONT"), m_pppSecret.ontSN(), s, &ROSPPPSecret::setONTSN );
}

bool DlgPPPUser::getVoIPPhone()
{
	return checkGroupedData( ui->voipGroupBox, tr("Número de teléfono SIP"), m_pppSecret.voipPhoneNumber(), ui->voipPhoneNumber->text(), &ROSPPPSecret::setVoIPPhoneNumber );
}

bool DlgPPPUser::getVoIPSIPServer()
{
	return checkGroupedData( ui->voipGroupBox, tr("URL del servidor SIP"), m_pppSecret.voipSIPServer(), ui->voipServerLineEdit->text(), &ROSPPPSecret::setVoIPSIPServer );
}

bool DlgPPPUser::getVoIPUserName()
{
	return checkGroupedData( ui->voipGroupBox, tr("Nombre de Usuario SIP"), m_pppSecret.voipSIPUserName(), ui->voipUserName->text(), &ROSPPPSecret::setVoIPSIPUserName );
}

bool DlgPPPUser::getVoIPUserPass()
{
	return checkGroupedData( ui->voipGroupBox, tr("Contraseña SIP"), m_pppSecret.voipSIPUserPass(), ui->voipUserPass->text(), &ROSPPPSecret::setVoIPSIPUserPass );
}

bool DlgPPPUser::getWiFi2SSID()
{
	return checkGroupedData( ui->wifi2GroupBox, tr("SSID para el Wifi local a 2,4Ghz"), m_pppSecret.wifi2SSID(), ui->wifi2SSIDLineEdit->text(), &ROSPPPSecret::setWiFi2SSID );
}

bool DlgPPPUser::getWiFi2WPA()
{
	return checkGroupedData( ui->wifi2GroupBox, tr("Contraseña WPA/WPA2 para el Wifi local a 2,4Ghz"), m_pppSecret.wifi2WPA(), ui->wifi2WPALineEdit->text(), &ROSPPPSecret::setWiFi2WPA );
}

bool DlgPPPUser::getWiFi5SSID()
{
	return checkGroupedData( ui->wifi5GroupBox, tr("SSID para el Wifi local a 5Ghz"), m_pppSecret.wifi5SSID(), ui->wifi5SSIDLineEdit->text(), &ROSPPPSecret::setWiFi5SSID );
}

bool DlgPPPUser::getWiFi5WPA()
{
	return checkGroupedData( ui->wifi5GroupBox, tr("Contraseña WPA/WPA2 para el Wifi local a 5Ghz"), m_pppSecret.wifi5WPA(), ui->wifi5WPALineEdit->text(), &ROSPPPSecret::setWiFi5WPA );
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

void DlgPPPUser::updatePPPProfilesComboBox()
{
	QString currentProfile = ui->pppProfileComboBox->currentText();

	ui->pppProfileComboBox->blockSignals(true);
	ui->pppProfileComboBox->clear();
	ui->pppProfileComboBox->addItems( configData().clientProfileMap().regularProfileNames() );
	ui->pppProfileComboBox->blockSignals(false);

	if( !currentProfile.isEmpty() )
		ui->pppProfileComboBox->setCurrentIndex(ui->pppProfileComboBox->findData(currentProfile, Qt::EditRole));
}

void DlgPPPUser::updateInstallersComboBox()
{
	ui->installerComboBox->updateList(configData().instaladores(), true);
}

void DlgPPPUser::updateCitiesComboBox()
{
	ui->clientCityComboBox->updateList( multiConnectionManager.clientCities() );
}

void DlgPPPUser::updateStaticIPComboBox()
{
	ui->staticIPComboBox->blockSignals(true);
	ui->staticIPComboBox->clear();
	ui->staticIPComboBox->addItem( tr("No (Dinámica)") );
	QString profileName = ui->pppProfileComboBox->currentText();
	QString profileGroup;
	if( profileName.isEmpty() )
		raiseWarning( tr("No hay ningún perfil seleccionado y no se puede saber las IPs públicas disponibles sin uno válido.") );
	else
	if( (profileGroup = configData().clientProfileMap().groupName(profileName)).isEmpty() )
		raiseWarning( tr("El perfil perfil $1 no está asociado a ningún grupo y no se puede saber las IPs públicas disponibles sin un grupo válido.") );
	else
		ui->staticIPComboBox->setup( tr("No (IP dinámica)"),
									 configData().staticIPv4RangeListMap().staticIPv4StringList(profileGroup),
									 rosMultiConnectManager().staticIPv4List(), m_pppSecret.staticIP().isValid() ? m_pppSecret.staticIP().toString() : QString() );
	ui->staticIPComboBox->blockSignals(false);
	if( m_pppSecret.staticIP().isValid() && (ui->staticIPComboBox->currentIndex() <= 0) )
		raiseWarning( tr("La IP estática seleccionada no es válida para el perfil actual.") );
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

	ui->installerComboBox->setCurrentText( m_pppSecret.installerName() );
	ui->clientNameLineEdit->setText( m_pppSecret.clientName() );
	ui->clientAddressLineEdit->setText( m_pppSecret.clientAddress() );
	ui->clientCityComboBox->setCurrentText( m_pppSecret.clientCity() );
	ui->clientPhonesLineEdit->setText( m_pppSecret.clientPhones() );
	ui->clientEmailLineEdit->setText( m_pppSecret.clientEmail() );
	ui->clientNotesLineEdit->setText( m_pppSecret.clientNotes() );
	ui->installNotesLineEdit->setText( m_pppSecret.installNotes() );

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
		m_pppSecret = m_pppSecretMap.first();
		m_pppActive = pppActive;
		updateDialog();
	}
	else
	{
		updateDialog();

#ifndef QT_NO_DEBUG
		ui->pppUserNameLineEdit->setText( QString("RandomUserName%1").arg(qrand(), 4, 16, QChar('0')) );
		ui->pppUserPassLineEdit->setText( QString("%1%2").arg(qrand(), 4, 16, QChar('0')).arg(qrand(), 4, 16, QChar('0')) );
#endif
		ui->pppProfileComboBox->setCurrentText( tr("Escoge perfil") );
		ui->installerComboBox->setCurrentText( "a" );
		ui->clientNameLineEdit->setText( "b" );
		ui->clientAddressLineEdit->setText( "c" );
		ui->clientCityComboBox->setCurrentText( "d" );
		ui->clientPhonesLineEdit->setText( "e" );
		ui->clientEmailLineEdit->setText( "f" );
		ui->clientNotesLineEdit->setText( "g" );
		ui->installNotesLineEdit->setText( "h" );

//		ui->wifi2GroupBox->setChecked( false );
//		ui->wifi5GroupBox->setChecked( false );
//		ui->voipGroupBox->setChecked( false );
//		ui->lanGroupBox->setChecked( false );
	}
	show();
}

void DlgPPPUser::onConfigDataChanged()
{
	updatePPPProfilesComboBox();
}


void DlgPPPUser::hideEvent(QHideEvent *event)
{
	clear();
	return DlgDataBase::hideEvent(event);
}

void DlgPPPUser::on_applyDataButton_clicked()
{
	if( getPPPUserName() && getPPPUserPass() && getPPPProfile() && getStaticIP() &&
		getClientName() && getClientAddress() && getClientInstaller() &&
		getClientCity() && getClientPhones() && getClientEMail() &&
		getClientNotes() && getInstallNotes() &&
		getONTSN() &&
		getVoIPPhone() && getVoIPSIPServer() && getVoIPUserName() && getVoIPUserPass() &&
		getWiFi2SSID() && getWiFi2WPA() &&
		getWiFi5SSID() && getWiFi5WPA() &&
		getLocalIP() && getLocalDMZ() && getLocalPorts() )

	{
		multiConnectionManager.updateRemoteData( m_pppSecret, m_pppSecretMap.toRouterIDMap() );
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
