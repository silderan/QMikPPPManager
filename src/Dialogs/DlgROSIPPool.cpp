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

#include "DlgROSIPPool.h"
#include "ui_DlgROSIPPool.h"

/*
 * Pool IP dialog behaves diferent from APIUsers, PPPProfiles and others like that.
 * Usually all data is identical on all routers.
 * In this case, Name is idéntical, but data is'nt.
 * That's because IP pools cannot be the same on all routers.
 * But, the name must be identical so the ppp-profiles can have configured the same pool name for
 * their local-address and remote-address parameters.
 * So, for a better aproach, I'll chosse a tree widget instead a table widget looking like that:
 *
 * <pool-name> - first-pool-ip, last-pool-ip, router-name+rosObjectID
 *             \ first-pool-ip, last-pool-ip, router-name+rosObjectID
 */


DlgROSIPPool::DlgROSIPPool(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DlgROSIPPool)
{
	ui->setupUi(this);
	ui->poolTree->setColumnCount(4);
	ui->poolTree->setHeaderLabels(QStringList() << tr("Nombre") << tr("Primera IP") << tr("Última IP") << tr("Router") );
}

DlgROSIPPool::~DlgROSIPPool()
{
	delete ui;
}

void DlgROSIPPool::on_closeButton_clicked()
{

}
