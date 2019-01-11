#include "QROSSecretTableWidget.h"

QROSSecretDataModel::QROSSecretDataModel() : QStandardItemModel()
{

}

QROSSecretTableWidget::QROSSecretTableWidget(QWidget *papi) : QTableView(papi)
{

}

void QROSSecretTableWidget::setupRow(int row, const ROSSecretData &rosSecretData)
{
}

int QROSSecretTableWidget::rowOf(const ROSSecretData &rosSecretData)
{
}

ROSSecretData *QROSSecretTableWidget::getRosData(int row)
{
}

void QROSSecretTableWidget::onROSModReply(const ROSDataBase &rosData)
{
}

void QROSSecretTableWidget::onROSDelReply(const QString &routerName, const QString &rosObjectID)
{
}

