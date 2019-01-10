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
