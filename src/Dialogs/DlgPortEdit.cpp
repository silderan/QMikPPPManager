#include "DlgPortEdit.h"
#include "ui_DlgPortEdit.h"

#include <QIntValidator>
#include <QMessageBox>

DlgPortEdit::DlgPortEdit(const PortForward &port, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgPortEdit)
{
	ui->setupUi(this);
	ui->fromPublicPortLineEdit->setValidator( new QIntValidator(1, 0xFFFF) );
	ui->toPublicPortLineEdit->setValidator( new QIntValidator(1, 0xFFFF) );
	ui->fromPrivatePortLineEdit->setValidator( new QIntValidator(1, 0xFFFF) );
	ui->toPrivatePortLineEdit->setValidator( new QIntValidator(1, 0xFFFF) );
	ui->ipLineEdit->setInputMask("000.000.000.000;_");
	ui->nameLineEdit->setInputMask("Nnnnnnnnnnnnnnn;_");

	ui->fromPublicPortLineEdit->setText( QString::number(port.publicPortIni()) );
	ui->toPublicPortLineEdit->setText( QString::number(port.publicPortEnd()) );
	ui->fromPrivatePortLineEdit->setText( QString::number(port.privatePortIni()) );
	ui->toPrivatePortLineEdit->setText( QString::number(port.privatePortEnd()) );

	ui->protocolComboBox->setProtocol(port.protocol());
	ui->nameLineEdit->setText(port.name());
	ui->ipLineEdit->setText(port.destIP().toString());

	connect(ui->acceptButton, &QAbstractButton::clicked, this, &DlgPortEdit::onAcceptButtonClicked );
}

DlgPortEdit::~DlgPortEdit()
{
	delete ui;
}

void DlgPortEdit::onAcceptButtonClicked()
{
	mValidPort.setName( ui->nameLineEdit->text() );
	mValidPort.setProtocol( ui->protocolComboBox->protocol() );
	mValidPort.setPublicPortIni( ui->fromPublicPortLineEdit->text().toUShort() );
	mValidPort.setPublicPortEnd( ui->toPublicPortLineEdit->text().toUShort() );
	mValidPort.setPrivatePortIni( ui->fromPrivatePortLineEdit->text().toUShort() );
	mValidPort.setPrivatePortEnd( ui->toPrivatePortLineEdit->text().toUShort() );
	mValidPort.setDestIP( IPv4(ui->ipLineEdit->text()) );

	if( mValidPort.publicPortEnd() == 0 )
		mValidPort.setPublicPortEnd(mValidPort.publicPortIni());
	if( mValidPort.publicPortIni() == 0 )
		mValidPort.setPublicPortIni(mValidPort.publicPortEnd());

	if( mValidPort.privatePortEnd() == 0 )
		mValidPort.setPrivatePortEnd(mValidPort.privatePortIni());
	if( mValidPort.privatePortIni() == 0 )
		mValidPort.setPrivatePortIni(mValidPort.privatePortEnd());

	if( mValidPort.privatePortEnd() == 0 )
	{
		mValidPort.setPrivatePortIni(mValidPort.publicPortIni());
		mValidPort.setPrivatePortEnd(mValidPort.publicPortEnd());
	}

	if( mValidPort.protocol() == IPProtocol::Unkown )
		QMessageBox::warning( this, tr("Protocolo redirección puertos"), tr("Escoge un protocolo válido.") );
	else
	if( mValidPort.publicPortIni() > mValidPort.publicPortEnd() )
		QMessageBox::warning( this, tr("Puertos público"), tr("El valor del puerto público inicial no puede ser mayor al puerto final.") );
	else
	if( mValidPort.privatePortIni() > mValidPort.privatePortEnd() )
		QMessageBox::warning( this, tr("Puertos privados"), tr("El valor del puerto privado inicial no puede ser mayor al puerto final.") );
	else
	if( (mValidPort.publicPortEnd() - mValidPort.publicPortIni()) != (mValidPort.privatePortEnd() - mValidPort.privatePortIni()) )
		QMessageBox::warning( this, tr("Rango puertos"), tr("La cantidad de puertos públicos y privados no coinciden") );
	else
	if( !mValidPort.destIP().isValid() )
		QMessageBox::warning(this, tr("IP destino"), tr("La IP destino no es válida") );
	else
	if( !ui->nameLineEdit->hasAcceptableInput() )
		QMessageBox::warning(this, tr("Nombre"), tr("El nombre para la redirección del puerto no es válido.")) ;
	else
	{
		accept();
	}
}
