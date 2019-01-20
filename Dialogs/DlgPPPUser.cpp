#include <QMessageBox>

#include "DlgPPPUser.h"
#include "ui_DlgPPPUser.h"

#include <QSpinBox>

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

bool DlgPPPUser::getPPPUserName()
{
	QString s = ui->pppUserNameLineEdit->text().trimmed();
	if( s.isEmpty() )
		raiseWarning( tr("El nombre de usuario está vacío o solo contiene caracteres en blanco." ));
	else
	if( s.contains( QRegExp("[^a-zA-Z0-9\\/\\-_]")) )
		raiseWarning( tr("El nombre de usuario contiene caracteres no válidos" ));
	else
	{
		m_pppSecret.setUserName(s);
		return true;
	}
	return false;
}

bool DlgPPPUser::getPPPUserPass()
{
	QString s = ui->pppUserPassLineEdit->text().trimmed();
	if( s.count() < 8 )
		raiseWarning( tr("La contraseña de usuario tiene demasiados pocos caracteres; debe tener más de 7." ));
	else
	if( s.contains( QRegExp("[^a-zA-Z0-9\\/\\-_]")) )
		raiseWarning( tr("La contraseña de usuario contiene caracteres no válidos" ));
	else
	{
		m_pppSecret.setUserPass(s);
		return true;
	}
	return false;
}

bool DlgPPPUser::getPPPProfile()
{
	QString s = ui->pppProfileComboBox->currentText().trimmed();
	if( s.isEmpty() )
		raiseWarning( tr("Ningún perfil seleccionado") );
	else
	{
		m_pppSecret.setOriginalProfile( s );
		return true;
	}
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

bool DlgPPPUser::checkClientData(const QString &fieldName, const QString &originalText, QString &text, int minLenght, QRegExp invalidChars)
{
	// With this, accepts already texts if it's the same.
	// This makes things easier for automatically generated users without some data.
	// So, it just forces to be all well formed for new users or when modifying field data.
	if( !m_pppSecret.rosObjectID().isEmpty() && (originalText == text) )
		return true;
	text = text.trimmed();
	if( text.count() < minLenght )
	{
		if( minLenght == 0 )
			raiseWarning( tr("El campo '%1' no puede estar vacío.").arg(fieldName) );
		else
			raiseWarning( tr("El campo '%1' debe tener al menos %2 caracteres.").arg(fieldName).arg(minLenght) );
	}
	else
	if( text.contains(invalidChars) )
		raiseWarning( tr("El texto del campo '%1' contiene caracteres no válidos").arg(fieldName) );
	else
		return true;
	return false;
}

bool DlgPPPUser::getClientName()
{
	QString s = ui->clientNameLineEdit->text();
	if( !checkClientData( tr("Nombre del cliente"), m_pppSecret.clientName(), s, 1 ) )
		return false;
	m_pppSecret.setClientName( s );
	return true;
}

bool DlgPPPUser::getClientAddress()
{
	QString s = ui->clientAddressLineEdit->text();
	if( !checkClientData( tr("Dirección de la instalación"), m_pppSecret.clientAddress(), s, 1 ) )
		return false;
	m_pppSecret.setClientAddress( s );
	return true;
}

bool DlgPPPUser::getClientInstaller()
{
	QString s = ui->installerComboBox->currentText();
	if( !checkClientData( tr("Nombre del instalador"), m_pppSecret.installerName(), s, 1 ) )
		return false;
	m_pppSecret.setInstallerName( s );
	return true;
}

bool DlgPPPUser::getClientCity()
{
	QString s = ui->clientCityComboBox->currentText();
	if( !checkClientData( tr("Población de la instalación"), m_pppSecret.clientCity(), s, 1 ) )
		return false;
	m_pppSecret.setClientCity( s );
	return true;
}

bool DlgPPPUser::getClientPhones()
{
	QString s = ui->clientPhonesLineEdit->text();
	if( !checkClientData( tr("Teléfonos de contacto"), m_pppSecret.clientPhones(), s, 1 ) )
		return false;
	m_pppSecret.setClientPhones( s );
	return true;
}

bool DlgPPPUser::getClientEMail()
{
	QString s = ui->clientEmailLineEdit->text();
	if( !checkClientData( tr("Correo electrónico"), m_pppSecret.clientEmail(), s, 1 ) )
		return false;
	m_pppSecret.setClientEmail( s );
	return true;
}

bool DlgPPPUser::getClientNotes()
{
	QString s = ui->clientNotesLineEdit->text();
	if( !checkClientData( tr("Anotaciones sobre el cliente"), m_pppSecret.clientNotes(), s, 0 ) )
		return false;
	m_pppSecret.setClientNotes( s );
	return true;
}

bool DlgPPPUser::getInstallNotes()
{
	QString s = ui->installNotesLineEdit->text();
	if( !checkClientData( tr("Anotaciones sobre la instalación"), m_pppSecret.installNotes(), s, 0 ) )
		return false;
	m_pppSecret.setInstallNotes( s );
	return true;
}

bool DlgPPPUser::getONTSN()
{
	if( ui->ftthCheckBox->isChecked() )
	{
		QString s = ui->ontSNComboBox->currentText();
		if( s.isEmpty() )
			raiseWarning( tr("Debes seleccionar una ONT") );
		m_pppSecret.setONTSN( s );
	}
	else
		m_pppSecret.setONTSN( QString() );
	return true;
}

bool DlgPPPUser::getVoIPPhone()
{
	if( ui->voipGroupBox->isChecked() )
	{
		QString s = ui->voipPhoneNumber->text();
		if( !checkClientData( tr("Número del teléfono IP"), m_pppSecret.voipPhoneNumber(), s, 9, QRegExp("[^0-9]") ) )
			return false;
		m_pppSecret.setVoIPPhoneNumber( s );
	}
	else
		m_pppSecret.setVoIPPhoneNumber( QString() );
	return true;
}

bool DlgPPPUser::getVoIPUserName()
{
	if( ui->voipGroupBox->isChecked() )
	{
		QString s = ui->voipUserName->text();
		if( !checkClientData( tr("Usuario SIP"), m_pppSecret.voipSIPUserName(), s, 8, QRegExp("[^a-zA-Z0-9\\/\\-_]") ) )
			return false;
		m_pppSecret.setVoIPSIPUserName( s );
	}
	else
		m_pppSecret.setVoIPSIPUserName( QString() );
	return true;
}

bool DlgPPPUser::getVoIPUserPass()
{
	if( ui->voipGroupBox->isChecked() )
	{
		QString s = ui->voipUserPass->text();
		if( !checkClientData( tr("Contraseña SIP"), m_pppSecret.voipSIPUserPass(), s, 8, QRegExp("[^a-zA-Z0-9\\/\\-_]") ) )
			return false;
		m_pppSecret.setVoIPSIPUserPass( s );
	}
	else
		m_pppSecret.setVoIPSIPUserPass( QString() );
	return true;
}

bool DlgPPPUser::checkWiFiSSID(const QString &fieldName, const QString &originalText, QString &ssid)
{
	return checkClientData( fieldName, originalText, ssid, 4 );
}

bool DlgPPPUser::checkWiFiWPA(const QString &fieldName, const QString &originalText, QString &wpa)
{
	return checkClientData( fieldName, originalText, wpa, 8 );
}

bool DlgPPPUser::getWiFi2SSID()
{
	if( ui->wifiGroupBox->isChecked() )
	{
		QString s = ui->wifi2SSIDLineEdit->text();
		if( !checkWiFiSSID( tr("SSID para el Wifi local a 2,4Ghz"), m_pppSecret.wifi2SSID(), s) )
			return false;
		m_pppSecret.setWiFi2SSID( s );
	}
	else
		m_pppSecret.setWiFi2SSID( QString() );
	return true;
}

bool DlgPPPUser::getWiFi2WPA()
{
	if( ui->wifiGroupBox->isChecked() )
	{
		QString s = ui->wifi2WPALineEdit->text();
		if( !checkWiFiWPA( tr("Contraseña WPA/WPA2 para el Wifi local a 2,4Ghz"), m_pppSecret.wifi2WPA(), s) )
			return false;
		m_pppSecret.setWiFi2WPA( s );
	}
	else
		m_pppSecret.setWiFi2WPA( QString() );
	return true;
}

bool DlgPPPUser::getWiFi5SSID()
{
	if( ui->wifiGroupBox->isChecked() )
	{
		QString s = ui->wifi5SSIDLineEdit->text();
		if( !checkWiFiSSID( tr("SSID para el Wifi local a 5Ghz"), m_pppSecret.wifi5SSID(), s) )
			return false;
		m_pppSecret.setWiFi5SSID(s);
	}
	else
		m_pppSecret.setWiFi5SSID( QString() );
	return true;
}

bool DlgPPPUser::getWiFi5WPA()
{
	if( ui->wifiGroupBox->isChecked() )
	{
		QString s = ui->wifi5WPALineEdit->text();
		if( !checkWiFiWPA( tr("Contraseña WPA/WPA2 para el Wifi local a 5Ghz"), m_pppSecret.wifi5WPA(), s) )
			return false;
		m_pppSecret.setWiFi5WPA( s );
	}
	else
		m_pppSecret.setWiFi5WPA( QString() );
	return true;
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
		m_pppSecret.portForwardList().clear();
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
	ui->pppProfileComboBox->setCurrentIndex( ui->pppProfileComboBox->findData(m_pppSecret.originalProfile(), Qt::EditRole) );
	updateStaticIPComboBox();

	ui->installerComboBox->setCurrentText( m_pppSecret.installerName() );
	ui->clientNameLineEdit->setText( m_pppSecret.clientName() );
	ui->clientAddressLineEdit->setText( m_pppSecret.clientAddress() );
	ui->clientCityComboBox->setCurrentText( m_pppSecret.clientCity() );
	ui->clientPhonesLineEdit->setText( m_pppSecret.clientPhones() );
	ui->clientEmailLineEdit->setText( m_pppSecret.clientEmail() );
	ui->clientNotesLineEdit->setText( m_pppSecret.clientNotes() );
	ui->installNotesLineEdit->setText( m_pppSecret.installNotes() );

	ui->wifiGroupBox->setChecked( !m_pppSecret.wifi2SSID().isEmpty() );
	ui->wifi2SSIDLineEdit->setText( m_pppSecret.wifi2SSID() );
	ui->wifi2WPALineEdit->setText( m_pppSecret.wifi2WPA() );
	ui->wifi5SSIDLineEdit->setText( m_pppSecret.wifi5SSID() );
	ui->wifi5WPALineEdit->setText( m_pppSecret.wifi5WPA() );

	ui->voipGroupBox->setChecked( !m_pppSecret.voipSIPUserName().isEmpty() );
	ui->voipPhoneNumber->setText( m_pppSecret.voipPhoneNumber() );
	ui->voipUserName->setText( m_pppSecret.voipSIPUserName() );
	ui->voipUserPass->setText( m_pppSecret.voipSIPUserPass() );

	ui->lanGroupBox->setChecked( m_pppSecret.installLANIP().isValid() || m_pppSecret.installLANDMZ().isValid() || !m_pppSecretMap.isEmpty() );
	ui->lanIPLineEdit->setText( m_pppSecret.installLANIP().toString() );
	ui->lanDMZLineEdit->setText( m_pppSecret.installLANDMZ().toString() );
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
			m_pppSecretMap.insert( rosData.routerName(), m_pppSecret );
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
					m_pppSecret.setROSObjectID( QString() );
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

void DlgPPPUser::onEditUserRequest(const QMap<QString, ROSPPPSecret> &pppSecretMap, const ROSPPPActive &pppActive)
{
	clear();
	if( pppSecretMap.count() )
	{
		m_pppSecretMap = pppSecretMap;
		m_pppSecret = m_pppSecretMap.first();
		m_pppActive = pppActive;
		updateDialog();
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
		getVoIPPhone() && getVoIPUserName() && 		getVoIPUserPass() &&
		getWiFi2SSID() && getWiFi2WPA() &&
		getWiFi5SSID() && getWiFi5WPA() &&
		getLocalIP() && getLocalDMZ() && getLocalDMZ() )

	{
		QRouterIDMap routerMapIP;
		foreach( const ROSDataBase &rosData, m_pppSecretMap )
		{
			routerMapIP[rosData.routerName()] = rosData.rosObjectID();
		}
		multiConnectionManager.updateRemoteData(m_pppSecret, routerMapIP);
	}
}

void DlgPPPUser::on_addPortButton_clicked()
{
	ui->lanPortsTableWidget->addPortForwardRow( PortForward() );
}

void DlgPPPUser::on_delPortButton_clicked()
{
	ui->lanPortsTableWidget->removeRow(ui->lanPortsTableWidget->currentRow());
}
