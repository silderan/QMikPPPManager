/**************************************************************************

  Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

  This file is part of BasicSNMP

  BasicSNMP is free software: you can redistribute it and/or modify
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

**************************************************************************/
#include "DlgUserThroughput.h"
#include "ui_DlgUserThroughput.h"

#include <QMessageBox>

DlgUserThroughput::DlgUserThroughput(ROSMultiConnectManager &rosMultiConnectManager, const ROSPPPActive &pppActive, QWidget *parent)
	: QDialog(parent) , ui(new Ui::DlgUserThroughput)
	, m_rosMultiConnectManager(rosMultiConnectManager)
{
	ui->setupUi(this);
	setWindowTitle(tr("Tráfico de %1").arg(pppActive.userName()));
	show();
	connect( this, &QDialog::rejected, [this] {deleteLater();}	);

	mRosPppoeManager = rosMultiConnectManager.rosPppoeManager(pppActive.routerName());
	if( !mRosPppoeManager )
	{
		QMessageBox::warning(this, windowTitle(), tr("No se ha encontrado el router que tiene la conexión activa del usuario") );
		reject();
		return;
	}
	mInterfaceName = pppActive.userName();
	mTag = QString("Monitoring_%1").arg(pppActive.userName());
	mRosPppoeManager->sendSentence( "/tool/torch", mTag, QStringList() << QString("interface=<pppoe-%1>").arg(pppActive.userName()) );
	connect( mRosPppoeManager, &ROS::Comm::comReceive, this, &DlgUserThroughput::onDataReceived );
}

DlgUserThroughput::~DlgUserThroughput()
{
	if( mRosPppoeManager )
		mRosPppoeManager->sendSentence("/cancel", QString("Canceling_Monitoring_%1").arg(mInterfaceName), QStringList() << QString("tag=%1").arg(mTag) );

	delete ui;
}

void DlgUserThroughput::onDataReceived(ROS::QSentence &sentence)
{
	switch( sentence.getResultType() )
	{
	case ROS::QSentence::None:
	case ROS::QSentence::Done:
	case ROS::QSentence::Trap:
	case ROS::QSentence::Fatal:
		break;
	case ROS::QSentence::Reply:
		if( (sentence.tag() == mTag) && (sentence.attribute(".section") != mSection) )
		{
			mSection = sentence.attribute(".section");
			qreal rx = sentence.attribute("rx").toULongLong() / (1024.0 * 1024.0);
			qreal tx = sentence.attribute("tx").toULongLong() / (1024.0 * 1024.0);
//			qDebug() << mInterfaceName << ": Rx=" << rx << ", Tx=" << tx;
			ui->graphicsView->addSpeeds(tx, rx);
		}
		break;
	}
}
