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

#ifndef DLGNEWROSAPIUSER_H
#define DLGNEWROSAPIUSER_H

#include "DlgDataBase.h"

namespace Ui
{
	class DlgNewROSAPIUser;
}

class DlgNewROSAPIUser : public QNewROSDataDialogBase
{
	Q_OBJECT
	Ui::DlgNewROSAPIUser *ui;
	void updateGUI();

public:
	explicit DlgNewROSAPIUser(QWidget *parent = Q_NULLPTR);
	~DlgNewROSAPIUser() Q_DECL_OVERRIDE;

	virtual void setROSData(ROSDataBase &) Q_DECL_OVERRIDE;
	virtual bool getROSData(ROSDataBase &)const Q_DECL_OVERRIDE;

	void onConfigChanged() Q_DECL_OVERRIDE;
};

#endif // DLGNEWROSAPIUSER_H
