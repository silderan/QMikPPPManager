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
#ifndef DLGUSERTHROUGHPUT_H
#define DLGUSERTHROUGHPUT_H

#include <QDialog>

#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgUserThroughput;
}

class DlgUserThroughput : public QDialog
{
	Q_OBJECT
	Ui::DlgUserThroughput *ui;

	ROSMultiConnectManager &m_rosMultiConnectManager;
	ROSPPPoEManager *mRosPppoeManager;
	QString mTag;
	QString mInterfaceName;
	QString mSection;

	void onDataReceived(ROS::QSentence &sentence);
public:
	explicit DlgUserThroughput(ROSMultiConnectManager &rosMultiConnectManager, const ROSPPPActive &pppActive, QWidget *parent = nullptr);
	~DlgUserThroughput();
};

#endif // DLGUSERTHROUGHPUT_H
