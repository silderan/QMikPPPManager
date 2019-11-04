#include "QUserVoIPDataTableWidget.h"

#include "../ConfigData/VoIPData.h"

#include "../Widgets/QComboBoxItemDelegate.h"


#include <QHeaderView>

enum Columns
{
	ColPhone,
	ColSipUser,
	ColSipPass,
	ColSipServer,
	ColCount
};

const QStringList gColNames = { QObject::tr("Teléfono"),
								QObject::tr("Usuario SIP"),
								QObject::tr("Contraseña SIP"),
								QObject::tr("Servidor SIP") };

QUserVoIPDataTableWidget::QUserVoIPDataTableWidget(QWidget *parent) : QTableWidget(parent)
{
	connect( this, &QUserVoIPDataTableWidget::itemChanged, this, &QUserVoIPDataTableWidget::onItemChanged );

	setItemDelegateForColumn( Columns::ColPhone,
							  new QComboBoxItemDelegated( this, "", "", false,
		/*add list*/			  [this] (int row)	{ return QStringList() << item(row, Columns::ColPhone)->text() << gVoipData.unusedPhones();	},
		/*skip list*/			  [] (int)			{ return QStringList(); },
		/*allow change*/		  [] (const QModelIndex &,const QString &)	{ return true; } ) );
}

void QUserVoIPDataTableWidget::onItemChanged(QTableWidgetItem *itemChanged)
{
	if( itemChanged->column() == Columns::ColPhone )
	{
		VoIPData voipData = gVoipData.voipData(itemChanged->text());
		item( itemChanged->row(), Columns::ColSipUser )->setText(voipData.mSipUsername);
		item( itemChanged->row(), Columns::ColSipPass )->setText(voipData.mSipPassword);
		item( itemChanged->row(), Columns::ColSipServer )->setText(voipData.mSipServer);
	}
}

void QUserVoIPDataTableWidget::addVoIPData(const VoIPData &voip)
{
	blockSignals(true);
	int row = rowCount();
	insertRow(row);

	setItem( row, ColPhone,		new QTableWidgetItem(voip.mSipPhone) );
	setItem( row, ColSipUser,	new QTableWidgetItem(voip.mSipUsername) );
	setItem( row, ColSipPass,	new QTableWidgetItem(voip.mSipPassword) );
	setItem( row, ColSipServer,	new QTableWidgetItem(voip.mSipServer) );

	blockSignals(false);
}

void QUserVoIPDataTableWidget::delVoIPData(int row)
{
	if( row == -1 )
		row = currentRow();
	removeRow(row);
}

void QUserVoIPDataTableWidget::setupUser(const QString &userName)
{
	setRowCount(0);

	if( !userName.isEmpty() )
		for( const VoIPData &sip : gVoipData.userVoIPData(userName) )
			addVoIPData(sip);
}

void QUserVoIPDataTableWidget::setup()
{
	Q_ASSERT(Columns::ColCount == gColNames.count());
	setColumnCount(Columns::ColCount);
	setHorizontalHeaderLabels(gColNames);
	resizeColumnsToContents();
	verticalHeader()->setDefaultSectionSize(17);
}

QStringList QUserVoIPDataTableWidget::sipPhones(const QString &userName, QString &err) const
{
	QStringList rtn;
	err.clear();

	QString thisPhone;
	VoIPData voipData;
	for( int row = 0; row < rowCount(); row++ )
	{
		thisPhone = item(row, ColPhone)->text();
		if( thisPhone.isEmpty() )
			err += QString("En la linea %1 el teléfono está vacío.").arg(row);
		else
		if( (voipData = gVoipData.voipData(thisPhone)).mSipUsername.isEmpty() )
			err += QString("En la linea %1 el teléfono no existe en la tabla global de teléfonos.").arg(row);
		else
			rtn.append(thisPhone);
	}
	return rtn;
}
